#include "Parser.h"

#include <exception>

#include <boost/locale/encoding_utf.hpp>

#include <ANTLRInputStream.h>

#include "anceBaseVisitor.h"
#include "anceLexer.h"
#include "anceParser.h"

#include "ance/core/Identifier.h"
#include "ance/core/UnaryOperator.h"
#include "ance/core/Type.h"

#include "ance/sources/SourceFile.h"
#include "ance/sources/SourceTree.h"

#include "Node.h"
#include "Printer.h"

namespace ance::ast
{
    static size_t getUtf32Length(std::string const& utf8)
    {
        return boost::locale::conv::utf_to_utf<char32_t>(utf8).size();
    }

    class ErrorHandler
    {
      public:
        explicit ErrorHandler(core::Reporter& reporter, sources::SourceFile const& source_file)
            : reporter_(reporter)
            , source_file_(source_file)
        {}

      private:
        class LexerErrorListener final : public antlr4::BaseErrorListener
        {
          public:
            explicit LexerErrorListener(ErrorHandler& parent) : parent_(parent) {}

            void syntaxError(antlr4::Recognizer*      ,
                             antlr4::Token*           ,
                             size_t const             ,
                             size_t const             ,
                             std::string const&       msg,
                             std::exception_ptr const ) override
            {
                throw std::logic_error("Unhandled lexer error: " + msg);
            }

            ErrorHandler& parent_;
        };

        class ParserErrorListener final : public antlr4::BaseErrorListener
        {
          public:
            explicit ParserErrorListener(ErrorHandler& parent) : parent_(parent) {}

            void syntaxError(antlr4::Recognizer* recognizer,
                             antlr4::Token*      offending_symbol,
                             size_t              line,
                             size_t              char_position,
                             std::string const&  msg,
                             std::exception_ptr const) override
            {
                auto* parser = dynamic_cast<anceParser*>(recognizer);
                if (!parser) return;

                char_position += 1;

                antlr4::Token* previous_symbol = parser->getTokenStream()->LT(-1);

                size_t previous_line          = line;
                size_t previous_char_position = char_position;

                if (previous_symbol)
                {
                    previous_line = previous_symbol->getLine();
                    previous_char_position =
                        previous_symbol->getCharPositionInLine() + getUtf32Length(previous_symbol->getText());

                    if (offending_symbol->getType() == antlr4::Token::EOF)
                    {
                        offending_symbol = previous_symbol;

                        line          = previous_line;
                        char_position = previous_char_position;
                    }
                }

                if (offending_symbol->getType() == anceLexer::ERROR_CHAR)
                {
                    parent_.reporter_.error("Unexpected character",
                                            core::Location::simple(line, char_position, parent_.source_file_.index()));
                    return;
                }

                if (offending_symbol->getType() == anceLexer::EOF)
                {
                    parent_.reporter_.error("Unexpected end of file",
                                            core::Location::simple(line, char_position, parent_.source_file_.index()));
                    return;
                }

                auto const expected_tokens = parser->getExpectedTokens();

                if (static_cast<size_t>(expected_tokens.getSingleElement()) == anceLexer::EOF)
                {
                    parent_.reporter_.error("At most one top-level statement per file allowed",
                                            core::Location::simple(line, char_position, parent_.source_file_.index()));
                    return;
                }

                if (static_cast<size_t>(expected_tokens.getSingleElement()) == anceLexer::SEMICOLON)
                {
                    parent_.reporter_.error("Missing semicolon",
                                            core::Location::simple(previous_line,
                                                                   previous_char_position + 1,
                                                                   parent_.source_file_.index()));
                    return;
                }

                if (expected_tokens.contains(static_cast<size_t>(anceLexer::BRACKET_CLOSE))
                    || expected_tokens.contains(static_cast<size_t>(anceLexer::CURLY_BRACKET_CLOSE))
                    || expected_tokens.contains(static_cast<size_t>(anceLexer::SQUARE_BRACKET_CLOSE))
                    || expected_tokens.contains(static_cast<size_t>(anceLexer::POINTY_BRACKET_CLOSE)))
                {
                    parent_.reporter_.error("Potential missing or mismatched closing bracket",
                                            core::Location::simple(line, char_position, parent_.source_file_.index()));
                    return;
                }

                if (expected_tokens.size() == 1)
                {
                    std::string expected_text(parser->getVocabulary().getLiteralName(static_cast<size_t>(expected_tokens.getSingleElement())));

                    if (expected_text.empty())
                    {
                        expected_text = parser->getVocabulary().getSymbolicName(static_cast<size_t>(expected_tokens.getSingleElement()));
                    }

                    parent_.reporter_.error("Expected " + expected_text + " somewhere around here",
                                            core::Location::simple(line, char_position, parent_.source_file_.index()));
                    return;
                }

                if (!expected_tokens.isEmpty())
                {
                    parent_.reporter_.error("Unexpected token '" + offending_symbol->getText() + "', check it and previous tokens for errors",
                                            core::Location::simple(line, char_position, parent_.source_file_.index()));

                    return;
                }

                throw std::logic_error("Unhandled parser error: " + msg);
            }

            ErrorHandler& parent_;
        };

      public:
        antlr4::BaseErrorListener* lexerErrorListener() { return &lexer_error_listener_; }
        antlr4::BaseErrorListener* parserErrorListener() { return &parser_error_listener_; }

      private:
        LexerErrorListener  lexer_error_listener_ {*this};
        ParserErrorListener parser_error_listener_ {*this};

        core::Reporter&            reporter_;
        sources::SourceFile const& source_file_;
    };

    class SourceVisitor final : public anceBaseVisitor
    {
      public:
        explicit SourceVisitor(size_t const file_index) : file_index_(file_index) {}

        ~SourceVisitor() override = default;

      private:
        core::Location location(antlr4::ParserRuleContext const* ctx) const
        {
            size_t const start_line   = ctx->getStart()->getLine();
            size_t const start_column = ctx->getStart()->getCharPositionInLine() + 1;

            size_t const end_line = ctx->getStop()->getLine();
            size_t const end_column =
                ctx->getStop()->getCharPositionInLine() + getUtf32Length(ctx->getStop()->getText());
            // todo: check if -1 is needed for end_column

            return {start_line, start_column, end_line, end_column, file_index_};
        }

        core::Identifier identifier(antlr4::tree::TerminalNode* i) const
        {
            std::string const text = i->getText();

            auto const token = i->getSymbol();

            size_t const start_line   = token->getLine();
            size_t const start_column = token->getCharPositionInLine() + 1;

            size_t const end_line   = start_line;
            size_t const end_column = start_column + getUtf32Length(text) - 1;

            return core::Identifier::like(text, {start_line, start_column, end_line, end_column, file_index_});
        }

    public:
        utility::Owned<File> expectFile(anceParser::UnorderedScopeFileContext* ctx)
        {
            if (std::any const result = visit(ctx); result.has_value())
                return utility::wrap<File>(result);

            return utility::makeOwned<File>(utility::List<utility::Owned<Statement>> {}, location(ctx));
        }

        template<typename T>
        utility::Owned<Statement> expectStatement(T* ctx)
        {
            if (std::any const result = visit(ctx); result.has_value())
                return utility::wrap<Statement>(result);

            return utility::makeOwned<ErrorStatement>(location(ctx));
        }

        template<typename T>
        utility::Owned<Expression> expectExpression(T* ctx)
        {
            if (std::any const result = visit(ctx); result.has_value())
                return utility::wrap<Expression>(result);

            return utility::makeOwned<ErrorExpression>(location(ctx));
        }

    protected:
        std::any visitUnorderedScopeFile(anceParser::UnorderedScopeFileContext* context) override
        {
            utility::List<utility::Owned<Statement>> statements;

            for (anceParser::StatementContext* statement : context->statement())
            {
                statements.push_back(expectStatement(statement));
            }

            File* file = new File(std::move(statements), location(context));
            return file;
        }

        std::any visitOrderedScopeFile(anceParser::OrderedScopeFileContext* context) override
        {
            return visit(context->statement());
        }

        std::any visitBlockStatement(anceParser::BlockStatementContext* context) override
        {
            utility::List<utility::Owned<Statement>> statements;

            for (anceParser::StatementContext* statement : context->statement())
            {
                statements.push_back(expectStatement(statement));
            }

            Statement* statement = new Block(std::move(statements), location(context));
            return statement;
        }

        std::any visitExpressionStatement(anceParser::ExpressionStatementContext* context) override
        {
            utility::Owned<Expression> expression = expectExpression(context->expression());

            Statement* statement = new Independent(std::move(expression), location(context));
            return statement;
        }

        std::any visitLetStatement(anceParser::LetStatementContext* ctx) override
        {
            core::Identifier const name = identifier(ctx->IDENTIFIER());

            utility::Optional<utility::Owned<Expression>> expression;
            utility::Owned<Expression> type = expectExpression(ctx->varType);

            if (ctx->assigned != nullptr) expression = expectExpression(ctx->assigned);

            Statement* statement = new Let(name, std::move(type), std::move(expression), location(ctx));
            return statement;
        }

        std::any visitAssignmentStatement(anceParser::AssignmentStatementContext* ctx) override
        {
            core::Identifier const     assigned = identifier(ctx->entity()->IDENTIFIER());
            utility::Owned<Expression> value    = expectExpression(ctx->expression());

            Statement* statement = new Assignment(assigned, std::move(value), location(ctx));
            return statement;
        }

        std::any visitIfStatement(anceParser::IfStatementContext* ctx) override
        {
            utility::Owned<Expression> condition = expectExpression(ctx->expression());
            utility::Owned<Statement> true_part = expectStatement(ctx->trueBlock);
            
            utility::Optional<utility::Owned<Statement>> false_part;
            if (ctx->falseBlock != nullptr)
            {
                false_part = expectStatement(ctx->falseBlock);
            }

            Statement* statement = new If(std::move(condition), std::move(true_part), std::move(false_part), location(ctx));
            return statement;
        }

        std::any visitLoopStatement(anceParser::LoopStatementContext* context) override
        {
            utility::Owned<Statement> body = expectStatement(context->statement());

            Statement* statement = new Loop(std::move(body), location(context));
            return statement;
        }

        std::any visitBreakStatement(anceParser::BreakStatementContext* context) override
        {
            Statement* statement = new Break(location(context));
            return statement;
        }

        std::any visitContinueStatement(anceParser::ContinueStatementContext* context) override
        {
            Statement* statement = new Continue(location(context));
            return statement;
        }

        std::any visitWhileStatement(anceParser::WhileStatementContext* context) override
        {
            utility::Owned<Expression> condition = expectExpression(context->expression());
            utility::Owned<Statement> body = expectStatement(context->statement());

            Statement* statement = new While(std::move(condition), std::move(body), location(context));
            return statement;
        }

        std::any visitCallExpression(anceParser::CallExpressionContext* context) override
        {
            core::Identifier const callable = identifier(context->entity()->IDENTIFIER());

            utility::List<utility::Owned<Expression>> arguments;
            for (anceParser::ExpressionContext* expression : context->expression())
            {
                arguments.push_back(expectExpression(expression));
            }

            Expression* expression = new Call(callable, std::move(arguments), location(context));
            return expression;
        }

        std::any visitAccessExpression(anceParser::AccessExpressionContext* ctx) override
        {
            core::Identifier const accessed = identifier(ctx->entity()->IDENTIFIER());

            Expression* expression = new Access(accessed, location(ctx));
            return expression;
        }

        std::any visitHereExpression(anceParser::HereExpressionContext* context) override
        {
            Expression* expression = new Here(location(context));
            return expression;
        }

        std::any visitUnaryOperationExpression(anceParser::UnaryOperationExpressionContext* context) override
        {
            core::UnaryOperator const op = std::any_cast<core::UnaryOperator>(visit(context->unary()));
            utility::Owned<Expression> operand = expectExpression(context->expression());

            Expression* expression = new UnaryOperation(op, std::move(operand), location(context));
            return expression;
        }

        std::any visitUnaryNot(anceParser::UnaryNotContext*) override
        {
            return core::UnaryOperator::NOT;
        }

        std::any visitTrue(anceParser::TrueContext* context) override
        {
            Expression* expression = new Literal(core::Value::makeBool(true), location(context));
            return expression;
        }

        std::any visitFalse(anceParser::FalseContext* context) override
        {
            Expression* expression = new Literal(core::Value::makeBool(false), location(context));
            return expression;
        }

        std::any visitSizeLiteral(anceParser::SizeLiteralContext* context) override
        {
            // todo: use llvm::APInt instead of size_t
            // todo: do all the validation of integer literals and stuff like whether they actually fit into their type

            Expression* expression = new Literal(core::Value::makeSize(std::stoull(context->getText())), location(context));
            return expression;
        }

        std::any visitUnitLiteral(anceParser::UnitLiteralContext* context) override
        {
            Expression* expression = new Literal(core::Value::makeUnit(), location(context));
            return expression;
        }

        std::any visitStringLiteral(anceParser::StringLiteralContext* context) override
        {
            std::string text = context->getText();
            text = text.substr(1, text.size() - 2); // Remove quotes.

            Expression* expression = new Literal(core::Value::makeString(text), location(context));
            return expression;
        }

        std::any visitBoolType(anceParser::BoolTypeContext* context) override
        {
            Expression* expression = new Literal(core::Value::makeType(core::Type::Bool()), location(context));
            return expression;
        }

        std::any visitUnitType(anceParser::UnitTypeContext* context) override
        {
            Expression* expression = new Literal(core::Value::makeType(core::Type::Unit()), location(context));
            return expression;
        }

        std::any visitSizeType(anceParser::SizeTypeContext* context) override
        {
            Expression* expression = new Literal(core::Value::makeType(core::Type::Size()), location(context));
            return expression;
        }

        std::any visitTypeType(anceParser::TypeTypeContext* context) override
        {
            Expression* expression = new Literal(core::Value::makeType(core::Type::Self()), location(context));
            return expression;
        }

        std::any visitStringType(anceParser::StringTypeContext* context) override
        {
            Expression* expression = new Literal(core::Value::makeType(core::Type::String()), location(context));
            return expression;
        }

      protected:
        std::any visitTerminal(antlr4::tree::TerminalNode*) override
        {
            assert(false);// Indicates a missing implementation of a node.

            return {};
        }

      private:
        size_t file_index_;
    };
}

struct ance::ast::Parser::Implementation
{
    explicit Implementation(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context)
        : source_tree_(source_tree), reporter_(reporter), context_(context)
    {}

    utility::Optional<utility::Owned<File>> parseUnorderedFile(std::filesystem::path const& file_path) // todo: reduce duplication with below (templates)
    {
        sources::SourceFile& source_file = source_tree_.addFile(file_path);

        utility::Optional<utility::Owned<File>> file;

        if (source_file.isOk())
        {
            std::fstream code;
            code.open(source_file.getRelativePath());

            utility::Owned<ErrorHandler> syntax_error_listener = utility::makeOwned<ErrorHandler>(reporter_, source_file);

            utility::Owned<antlr4::ANTLRInputStream> input = utility::makeOwned<antlr4::ANTLRInputStream>(code);
            utility::Owned<anceLexer>                lexer = utility::makeOwned<anceLexer>(input.get());
            lexer->removeErrorListeners();
            lexer->addErrorListener(syntax_error_listener->lexerErrorListener());

            utility::Owned<antlr4::CommonTokenStream> tokens = utility::makeOwned<antlr4::CommonTokenStream>(lexer.get());
            utility::Owned<anceParser>                parser = utility::makeOwned<anceParser>(tokens.get());
            parser->removeErrorListeners();
            parser->addErrorListener(syntax_error_listener->parserErrorListener());

            anceParser::UnorderedScopeFileContext* unordered_scope_file_context = parser->unorderedScopeFile();

            SourceVisitor visitor {source_file.index()};

            file = visitor.expectFile(unordered_scope_file_context);
        }
        else
        {
            reporter_.error("Failed to read file", core::Location::file(source_file.index()));
        }

        if (reporter_.isFailed())
            return std::nullopt;

        context_.print<Printer>(**file, "ast", source_file.getRelativePath());

        return file;
    }

    utility::Optional<utility::Owned<Statement>> parseOrderedFile(std::filesystem::path const& file_path)
    {
        sources::SourceFile& source_file = source_tree_.addFile(file_path);

        utility::Optional<utility::Owned<Statement>> statement;

        if (source_file.isOk())
        {
            std::fstream code;
            code.open(source_file.getRelativePath());

            utility::Owned<ErrorHandler> syntax_error_listener = utility::makeOwned<ErrorHandler>(reporter_, source_file);

            utility::Owned<antlr4::ANTLRInputStream> input = utility::makeOwned<antlr4::ANTLRInputStream>(code);
            utility::Owned<anceLexer>                lexer = utility::makeOwned<anceLexer>(input.get());
            lexer->removeErrorListeners();
            lexer->addErrorListener(syntax_error_listener->lexerErrorListener());

            utility::Owned<antlr4::CommonTokenStream> tokens = utility::makeOwned<antlr4::CommonTokenStream>(lexer.get());
            utility::Owned<anceParser>                parser = utility::makeOwned<anceParser>(tokens.get());
            parser->removeErrorListeners();
            parser->addErrorListener(syntax_error_listener->parserErrorListener());

            anceParser::OrderedScopeFileContext* unordered_scope_file_context = parser->orderedScopeFile();

            SourceVisitor visitor {source_file.index()};

            statement = visitor.expectStatement(unordered_scope_file_context);
        }
        else
        {
            reporter_.error("Failed to read file", core::Location::file(source_file.index()));
        }


        if (reporter_.isFailed())
            return std::nullopt;

        context_.print<Printer>(**statement, "ast", source_file.getRelativePath());

        return statement;
    }

  private:
    sources::SourceTree& source_tree_;
    core::Reporter& reporter_;
    core::Context& context_;
};

ance::ast::Parser::Parser(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context)
    : implementation_(utility::makeOwned<Implementation>(source_tree, reporter, context))
{}

ance::ast::Parser::~Parser() = default;

ance::utility::Optional<ance::utility::Owned<ance::ast::File>> ance::ast::Parser::parseUnorderedFile(std::filesystem::path const& file)
{
    return implementation_->parseUnorderedFile(file);
}

ance::utility::Optional<ance::utility::Owned<ance::ast::Statement>> ance::ast::Parser::parseOrderedFile(std::filesystem::path const& file)
{
    return implementation_->parseOrderedFile(file);
}

