#include "Parser.h"

#include <exception>
#include <memory>

#include <boost/locale/encoding_utf.hpp>

#include <ANTLRInputStream.h>
#include <DefaultErrorStrategy.h>

#include "anceBaseVisitor.h"
#include "anceLexer.h"
#include "anceParser.h"

#include "ance/core/Context.h"
#include "ance/core/ExecutionModifier.h"
#include "ance/core/Identifier.h"
#include "ance/core/UnaryOperator.h"

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
        explicit ErrorHandler(core::Reporter& reporter, sources::SourceFile const* source_file) : reporter_(reporter), source_file_(source_file) {}

      private:
        class LexerErrorListener final : public antlr4::BaseErrorListener
        {
          public:
            explicit LexerErrorListener(ErrorHandler& parent) : parent_(parent) {}

            void syntaxError(antlr4::Recognizer*, antlr4::Token*, size_t const, size_t const, std::string const& msg, std::exception_ptr const) override
            {
                throw std::logic_error("Unhandled lexer error: " + msg);
            }

            ErrorHandler& parent_;
        };

        class ParserErrorListener final : public antlr4::BaseErrorListener
        {
          public:
            explicit ParserErrorListener(ErrorHandler& parent) : parent_(parent) {}

            core::Location location(size_t const line, size_t const char_position) const
            {
                if (parent_.source_file_ == nullptr) return core::Location::core();

                return core::Location::simple(line, char_position, parent_.source_file_->index());
            }

            void syntaxError(antlr4::Recognizer* recognizer,
                             antlr4::Token*      offending_symbol,
                             size_t              line,
                             size_t              char_position,
                             std::string const&  msg,
                             std::exception_ptr const) override
            {
                auto* parser = dynamic_cast<grammar::anceParser*>(recognizer);
                if (!parser) return;

                char_position += 1;

                antlr4::Token* previous_symbol = parser->getTokenStream()->LT(-1);

                size_t previous_line          = line;
                size_t previous_char_position = char_position;

                if (previous_symbol)
                {
                    previous_line          = previous_symbol->getLine();
                    previous_char_position = previous_symbol->getCharPositionInLine() + getUtf32Length(previous_symbol->getText());

                    if (offending_symbol->getType() == antlr4::Token::EOF)
                    {
                        offending_symbol = previous_symbol;

                        line          = previous_line;
                        char_position = previous_char_position;
                    }
                }

                if (offending_symbol->getType() == grammar::anceLexer::ERROR_CHAR)
                {
                    parent_.reporter_.error(location(line, char_position)) << "Unexpected character";
                    return;
                }

                if (offending_symbol->getType() == grammar::anceLexer::EOF)
                {
                    parent_.reporter_.error(location(line, char_position)) << "Unexpected end of file";
                    return;
                }

                auto const expected_tokens = parser->getExpectedTokens();

                if (static_cast<size_t>(expected_tokens.getSingleElement()) == grammar::anceLexer::EOF)
                {
                    parent_.reporter_.error(location(line, char_position)) << "At most one top-level statement per file allowed";
                    return;
                }

                if (static_cast<size_t>(expected_tokens.getSingleElement()) == grammar::anceLexer::SEMICOLON)
                {
                    parent_.reporter_.error(location(previous_line, previous_char_position + 1)) << "Missing semicolon";
                    return;
                }

                if (expected_tokens.contains(static_cast<size_t>(grammar::anceLexer::BRACKET_CLOSE))
                    || expected_tokens.contains(static_cast<size_t>(grammar::anceLexer::CURLY_BRACKET_CLOSE))
                    || expected_tokens.contains(static_cast<size_t>(grammar::anceLexer::SQUARE_BRACKET_CLOSE))
                    || expected_tokens.contains(static_cast<size_t>(grammar::anceLexer::POINTY_BRACKET_CLOSE)))
                {
                    parent_.reporter_.error(location(line, char_position)) << "Potential missing or mismatched closing bracket";
                    return;
                }

                if (expected_tokens.size() == 1)
                {
                    std::string expected_text(parser->getVocabulary().getLiteralName(static_cast<size_t>(expected_tokens.getSingleElement())));

                    if (expected_text.empty())
                    {
                        expected_text = parser->getVocabulary().getSymbolicName(static_cast<size_t>(expected_tokens.getSingleElement()));
                    }

                    parent_.reporter_.error(location(line, char_position)) << "Expected " << expected_text << " somewhere around here";
                    return;
                }

                if (!expected_tokens.isEmpty())
                {
                    parent_.reporter_.error(location(line, char_position))
                        << "Unexpected token '" << offending_symbol->getText() << "', check it and previous tokens for errors";

                    return;
                }

                throw std::logic_error("Unhandled parser error: " + msg);
            }

            ErrorHandler& parent_;
        };

        class ParserErrorStrategy final : public antlr4::DefaultErrorStrategy
        {
          public:
            void recover(antlr4::Parser* recognizer, std::exception_ptr const) override
            {
                beginErrorCondition(recognizer);

                auto* token_stream = recognizer->getTokenStream();
                int   depth        = 0;

                while (true)
                {
                    size_t const type = token_stream->LA(1);

                    if (type == antlr4::Token::EOF) break;

                    if (depth == 0 && type == grammar::anceLexer::SEMICOLON) break;
                    if (depth == 0 && type == grammar::anceLexer::CURLY_BRACKET_CLOSE) break;

                    if (isOpen(type)) depth += 1;
                    else if (isClose(type) && depth > 0) depth -= 1;

                    recognizer->consume();
                }
            }

            antlr4::Token* recoverInline(antlr4::Parser* recognizer) override
            {
                antlr4::InputMismatchException const mismatch = {recognizer};

                reportInputMismatch(recognizer, mismatch);
                recover(recognizer, std::make_exception_ptr(mismatch));

                return recognizer->getTokenStream()->LT(1);
            }

          private:
            static bool isOpen(size_t const type)
            {
                return type == grammar::anceLexer::BRACKET_OPEN || type == grammar::anceLexer::SQUARE_BRACKET_OPEN
                    || type == grammar::anceLexer::CURLY_BRACKET_OPEN || type == grammar::anceLexer::POINTY_BRACKET_OPEN;
            }

            static bool isClose(size_t const type)
            {
                return type == grammar::anceLexer::BRACKET_CLOSE || type == grammar::anceLexer::SQUARE_BRACKET_CLOSE
                    || type == grammar::anceLexer::CURLY_BRACKET_CLOSE || type == grammar::anceLexer::POINTY_BRACKET_CLOSE;
            }
        };

      public:
        antlr4::BaseErrorListener* lexerErrorListener()
        {
            return &lexer_error_listener_;
        }

        antlr4::BaseErrorListener* parserErrorListener()
        {
            return &parser_error_listener_;
        }

        std::shared_ptr<ParserErrorStrategy> parserErrorStrategy()
        {
            return parser_error_strategy_;
        }

      private:
        LexerErrorListener  lexer_error_listener_ {*this};
        ParserErrorListener parser_error_listener_ {*this};

        std::shared_ptr<ParserErrorStrategy> parser_error_strategy_ = std::make_shared<ParserErrorStrategy>();

        core::Reporter&            reporter_;
        sources::SourceFile const* source_file_;
    };

    class SourceVisitor final : public grammar::anceBaseVisitor
    {
      public:
        SourceVisitor(utility::Optional<size_t> file_index, core::Reporter& reporter) : file_index_(file_index), reporter_(reporter) {}

        ~SourceVisitor() override = default;

      private:
        [[nodiscard]] core::Location location(size_t const start_line, size_t const start_column, size_t const end_line, size_t const end_column) const
        {
            if (!file_index_.hasValue()) return core::Location::core();

            return {start_line, start_column, end_line, end_column, file_index_.value()};
        }

        [[nodiscard]] core::Location location() const
        {
            if (!file_index_.hasValue()) return core::Location::core();

            return core::Location::file(file_index_.value());
        }

        core::Location location(antlr4::ParserRuleContext const* ctx) const
        {
            size_t const start_line   = ctx->getStart()->getLine();
            size_t const start_column = ctx->getStart()->getCharPositionInLine() + 1;

            size_t const end_line   = ctx->getStop()->getLine();
            size_t const end_column = ctx->getStop()->getCharPositionInLine() + getUtf32Length(ctx->getStop()->getText());
            // todo: check if -1 is needed for end_column

            return location(start_line, start_column, end_line, end_column);
        }

        core::Identifier identifier(antlr4::tree::TerminalNode* i) const
        {
            std::string const text = i->getText();

            auto const token = i->getSymbol();

            size_t const start_line   = token->getLine();
            size_t const start_column = token->getCharPositionInLine() + 1;

            size_t const end_line   = start_line;
            size_t const end_column = start_column + getUtf32Length(text) - 1;

            return core::Identifier::make(text, location(start_line, start_column, end_line, end_column));
        }

      public:
        utility::Owned<File> expectFile(grammar::anceParser::UnorderedScopeFileContext* ctx)
        {
            if (ctx == nullptr) return utility::makeOwned<File>(utility::List<utility::Owned<Declaration>> {}, location());

            if (std::any const result = visit(ctx); result.has_value()) return utility::wrap<File>(result);

            return utility::makeOwned<File>(utility::List<utility::Owned<Declaration>> {}, location(ctx));
        }

        template<typename T>
        utility::Owned<Declaration> expectDeclaration(T* ctx)
        {
            if (ctx == nullptr) return utility::makeOwned<ErrorDeclaration>(location());

            if (std::any const result = visit(ctx); result.has_value()) return utility::wrap<Declaration>(result);

            return utility::makeOwned<ErrorDeclaration>(location(ctx));
        }

        template<typename T>
        utility::Owned<Statement> expectStatement(T* ctx)
        {
            if (ctx == nullptr) return utility::makeOwned<ErrorStatement>(location());

            if (std::any const result = visit(ctx); result.has_value()) return utility::wrap<Statement>(result);

            return utility::makeOwned<ErrorStatement>(location(ctx));
        }

        template<typename T>
        utility::Owned<Expression> expectExpression(T* ctx)
        {
            if (ctx == nullptr) return utility::makeOwned<ErrorExpression>(location());

            if (std::any const result = visit(ctx); result.has_value()) return utility::wrap<Expression>(result);

            return utility::makeOwned<ErrorExpression>(location(ctx));
        }

        Parameter expectParameter(grammar::anceParser::ParameterContext* ctx)
        {
            core::Identifier const     name     = identifier(ctx->IDENTIFIER());
            utility::Owned<Expression> type     = expectExpression(ctx->expression());
            core::Location const       location = this->location(ctx);

            return {name, std::move(type), location};
        }

        core::UnaryOperator expectUnaryOperator(grammar::anceParser::UnaryContext* ctx)
        {
            if (ctx == nullptr) return core::UnaryOperator::UNSPECIFIED;

            if (std::any const result = visit(ctx); result.has_value()) return std::any_cast<core::UnaryOperator>(result);

            return core::UnaryOperator::UNSPECIFIED;
        }

        core::Assigner expectAssigner(grammar::anceParser::AssignerContext* ctx)
        {
            if (ctx == nullptr) return core::Assigner::UNSPECIFIED;

            if (std::any const result = visit(ctx); result.has_value()) return std::any_cast<core::Assigner>(result);

            return core::Assigner::UNSPECIFIED;
        }

        core::AccessModifier expectAccessModifier(grammar::anceParser::AccessModifierContext* ctx)
        {
            if (ctx == nullptr) return core::AccessModifier::PRIVATE_ACCESS;

            if (std::any const result = visit(ctx); result.has_value()) return std::any_cast<core::AccessModifier>(result);

            return core::AccessModifier::PRIVATE_ACCESS;
        }

        core::ExecutionModifier expectExecutionModifier(grammar::anceParser::ExecutionModeContext* ctx)
        {
            if (ctx == nullptr) return core::ExecutionModifier::ANY_EXECUTION;

            if (std::any const result = visit(ctx); result.has_value()) return std::any_cast<core::ExecutionModifier>(result);

            return core::ExecutionModifier::ANY_EXECUTION;
        }

      protected:
        std::any visitUnorderedScopeFile(grammar::anceParser::UnorderedScopeFileContext* ctx) override
        {
            utility::List<utility::Owned<Declaration>> declarations;

            for (grammar::anceParser::DeclarationContext* declaration : ctx->declaration())
            {
                declarations.push_back(expectDeclaration(declaration));
            }

            File* file = new File(std::move(declarations), location(ctx));
            return file;
        }

        std::any visitOrderedScopeFile(grammar::anceParser::OrderedScopeFileContext* ctx) override
        {
            return visit(ctx->statement());
        }

        std::any visitRunnableDeclaration(grammar::anceParser::RunnableDeclarationContext* ctx) override
        {
            utility::Owned<Statement> body = expectStatement(ctx->statement());

            Declaration* declaration = new RunnableDeclaration(std::move(body), location(ctx));
            return declaration;
        }

        std::any visitVariableDeclaration(grammar::anceParser::VariableDeclarationContext* ctx) override
        {
            core::AccessModifier const access_modifier    = expectAccessModifier(ctx->accessModifier());
            core::ExecutionModifier    execution_modifier = expectExecutionModifier(ctx->executionMode());
            core::Identifier const     name               = identifier(ctx->IDENTIFIER());
            utility::Owned<Expression> type               = expectExpression(ctx->varType);

            if (execution_modifier != core::ExecutionModifier::ANY_EXECUTION)
            {
                reporter_.error(location(ctx->executionMode())) << "Execution modifiers are not yet supported";
                execution_modifier = core::ExecutionModifier::ANY_EXECUTION;
            }

            core::Assigner                                assigner = core::Assigner::UNSPECIFIED;
            utility::Optional<utility::Owned<Expression>> expression;
            if (ctx->assigned != nullptr)
            {
                assigner   = expectAssigner(ctx->assigner());
                expression = expectExpression(ctx->assigned);

                if (!assigner.isFinal())
                {
                    reporter_.error(location(ctx->assigner())) << "Unordered scope variable declarations must be final";
                }
            }

            Declaration* declaration =
                new VariableDeclaration(access_modifier, execution_modifier, name, std::move(type), assigner, std::move(expression), location(ctx));
            return declaration;
        }

        std::any visitFunctionDeclaration(grammar::anceParser::FunctionDeclarationContext* ctx) override
        {
            core::AccessModifier const access_modifier    = expectAccessModifier(ctx->accessModifier());
            core::ExecutionModifier    execution_modifier = expectExecutionModifier(ctx->executionMode());
            core::Identifier const     name               = identifier(ctx->IDENTIFIER());

            if (execution_modifier != core::ExecutionModifier::ANY_EXECUTION)
            {
                reporter_.error(location(ctx->executionMode())) << "Execution modifiers are not yet supported";
                execution_modifier = core::ExecutionModifier::ANY_EXECUTION;
            }

            utility::List<Parameter> parameters;
            for (grammar::anceParser::ParameterContext* parameter_ctx : ctx->parameter()) parameters.push_back(expectParameter(parameter_ctx));

            utility::Optional<utility::Owned<Expression>> return_type;
            if (ctx->type != nullptr)
            {
                return_type = expectExpression(ctx->type);
            }

            utility::Owned<Statement> body = utility::Owned<Statement>(*createBlockStatement(ctx->statement(), location(ctx)));

            Declaration* declaration = new FunctionDeclaration(access_modifier,
                                                               execution_modifier,
                                                               name,
                                                               std::move(parameters),
                                                               std::move(return_type),
                                                               std::move(body),
                                                               location(ctx));
            return declaration;
        }

        std::any visitBlockStatement(grammar::anceParser::BlockStatementContext* ctx) override
        {
            Statement* statement = createBlockStatement(ctx->statement(), location(ctx));
            return statement;
        }

        std::any visitExpressionStatement(grammar::anceParser::ExpressionStatementContext* ctx) override
        {
            utility::Owned<Expression> expression = expectExpression(ctx->expression());

            Statement* statement = new Independent(std::move(expression), location(ctx));
            return statement;
        }

        std::any visitLetStatement(grammar::anceParser::LetStatementContext* ctx) override
        {
            core::Identifier const     name = identifier(ctx->IDENTIFIER());
            utility::Owned<Expression> type = expectExpression(ctx->varType);

            core::Assigner                                assigner = core::Assigner::UNSPECIFIED;
            utility::Optional<utility::Owned<Expression>> expression;
            if (ctx->assigned != nullptr)
            {
                assigner   = expectAssigner(ctx->assigner());
                expression = expectExpression(ctx->assigned);
            }

            Statement* statement = new Let(name, std::move(type), assigner, std::move(expression), location(ctx));
            return statement;
        }

        std::any visitAssignmentStatement(grammar::anceParser::AssignmentStatementContext* ctx) override
        {
            utility::Owned<Expression> assignee = expectExpression(ctx->assignee);
            core::Assigner const       assigner = expectAssigner(ctx->assigner());
            utility::Owned<Expression> assigned = expectExpression(ctx->assgined);

            if (assigner.isFinal())
            {
                reporter_.error(location(ctx->assigner())) << "Assignment to existing variable cannot be final";
            }

            Statement* statement = new Assignment(std::move(assignee), assigner, std::move(assigned), location(ctx));
            return statement;
        }

        std::any visitIfStatement(grammar::anceParser::IfStatementContext* ctx) override
        {
            utility::Owned<Expression> condition = expectExpression(ctx->expression());
            utility::Owned<Statement>  true_part = expectStatement(ctx->trueBlock);

            utility::Optional<utility::Owned<Statement>> false_part;
            if (ctx->falseBlock != nullptr)
            {
                false_part = expectStatement(ctx->falseBlock);
            }

            Statement* statement = new If(std::move(condition), std::move(true_part), std::move(false_part), location(ctx));
            return statement;
        }

        std::any visitLoopStatement(grammar::anceParser::LoopStatementContext* ctx) override
        {
            utility::Owned<Statement> body = expectStatement(ctx->statement());

            Statement* statement = new Loop(std::move(body), location(ctx));
            return statement;
        }

        std::any visitBreakStatement(grammar::anceParser::BreakStatementContext* ctx) override
        {
            Statement* statement = new Break(location(ctx));
            return statement;
        }

        std::any visitContinueStatement(grammar::anceParser::ContinueStatementContext* ctx) override
        {
            Statement* statement = new Continue(location(ctx));
            return statement;
        }

        std::any visitReturnStatement(grammar::anceParser::ReturnStatementContext* ctx) override
        {
            utility::Optional<utility::Owned<Expression>> value = {};
            if (ctx->expression() != nullptr) value = expectExpression(ctx->expression());

            Statement* statement = new Return(std::move(value), location(ctx));
            return statement;
        }

        std::any visitWhileStatement(grammar::anceParser::WhileStatementContext* ctx) override
        {
            utility::Owned<Expression> condition = expectExpression(ctx->expression());
            utility::Owned<Statement>  body      = expectStatement(ctx->statement());

            Statement* statement = new While(std::move(condition), std::move(body), location(ctx));
            return statement;
        }

        std::any visitEraseStatement(grammar::anceParser::EraseStatementContext* context) override
        {
            core::Identifier const name = identifier(context->IDENTIFIER());

            Statement* statement = new Erase(name, location(context));
            return statement;
        }

        std::any visitUnaryOperationExpression(grammar::anceParser::UnaryOperationExpressionContext* ctx) override
        {
            core::UnaryOperator const  op      = expectUnaryOperator(ctx->unary());
            utility::Owned<Expression> operand = expectExpression(ctx->target);

            Expression* expression = new UnaryOperation(op, std::move(operand), location(ctx));
            return expression;
        }

        std::any visitCallExpression(grammar::anceParser::CallExpressionContext* ctx) override
        {
            utility::Owned<Expression> callee = expectExpression(ctx->callee);

            utility::List<utility::Owned<Expression>> arguments;
            for (grammar::anceParser::ExpressionContext* expression : ctx->expression()) arguments.push_back(expectExpression(expression));

            Expression* expression = new Call(std::move(callee), std::move(arguments), location(ctx));
            return expression;
        }

        std::any visitLambdaExpression(grammar::anceParser::LambdaExpressionContext* ctx) override
        {
            utility::List<Parameter> parameters;
            for (grammar::anceParser::ParameterContext* parameter_ctx : ctx->parameter()) parameters.push_back(expectParameter(parameter_ctx));

            utility::Optional<utility::Owned<Expression>> return_type;
            if (ctx->type != nullptr)
            {
                return_type = expectExpression(ctx->type);
            }

            utility::Optional<utility::Owned<Expression>> expression_body;
            utility::Optional<utility::Owned<Statement>>  statement_body;
            if (ctx->body != nullptr)
            {
                expression_body = expectExpression(ctx->body);
            }
            else if (!ctx->statement().empty())
            {
                statement_body = utility::wrap<Statement>(createBlockStatement(ctx->statement(), location(ctx)));
            }

            Expression* expression =
                new Lambda(std::move(parameters), std::move(return_type), std::move(expression_body), std::move(statement_body), location(ctx));
            return expression;
        }

        std::any visitIntrinsicExpression(grammar::anceParser::IntrinsicExpressionContext* ctx) override
        {
            utility::Owned<Expression> name = expectExpression(ctx->name);

            utility::List<utility::Owned<Expression>> arguments;
            for (grammar::anceParser::ExpressionContext* expression : ctx->expression())
            {
                if (expression == ctx->name) continue;

                arguments.push_back(expectExpression(expression));
            }

            Expression* expression = new Intrinsic(std::move(name), std::move(arguments), location(ctx));
            return expression;
        }

        std::any visitBlockExpression(grammar::anceParser::BlockExpressionContext* context) override
        {
            utility::List<utility::Owned<Statement>> statements;
            for (grammar::anceParser::StatementContext* statement : context->statement())
            {
                statements.push_back(expectStatement(statement));
            }

            utility::Optional<utility::Owned<Expression>> expression;
            if (context->expression() != nullptr)
            {
                expression = expectExpression(context->expression());
            }

            Expression* block_expression = new BlockExpression(std::move(statements), std::move(expression), location(context));
            return block_expression;
        }

        std::any visitAccessExpression(grammar::anceParser::AccessExpressionContext* ctx) override
        {
            core::Identifier const accessed = identifier(ctx->IDENTIFIER());

            Expression* expression = new Access(accessed, location(ctx));
            return expression;
        }

        std::any visitHereExpression(grammar::anceParser::HereExpressionContext* ctx) override
        {
            Expression* expression = new Here(location(ctx));
            return expression;
        }

        std::any visitUnaryNot(grammar::anceParser::UnaryNotContext*) override
        {
            core::UnaryOperator op = core::UnaryOperator::NOT;
            return op;
        }

        std::any visitTrue(grammar::anceParser::TrueContext* ctx) override
        {
            Expression* expression = new BoolLiteral(true, location(ctx));
            return expression;
        }

        std::any visitFalse(grammar::anceParser::FalseContext* ctx) override
        {
            Expression* expression = new BoolLiteral(false, location(ctx));
            return expression;
        }

        std::any visitSizeLiteral(grammar::anceParser::SizeLiteralContext* ctx) override
        {
            // todo: use llvm::APInt instead of size_t
            // todo: do all the validation of integer literals and stuff like whether they actually fit into their type

            Expression* expression = new SizeLiteral(ctx->getText(), location(ctx));
            return expression;
        }

        std::any visitUnitLiteral(grammar::anceParser::UnitLiteralContext* ctx) override
        {
            Expression* expression = new UnitLiteral(location(ctx));
            return expression;
        }

        std::any visitStringLiteral(grammar::anceParser::StringLiteralContext* ctx) override
        {
            std::string text = ctx->getText();
            text             = text.substr(1, text.size() - 2);// Remove quotes.

            Expression* expression = new StringLiteral(text, location(ctx));
            return expression;
        }

        std::any visitCopyAssigner(grammar::anceParser::CopyAssignerContext*) override
        {
            core::Assigner assigner = core::Assigner::COPY_ASSIGNMENT;
            return assigner;
        }

        std::any visitFinalCopyAssigner(grammar::anceParser::FinalCopyAssignerContext*) override
        {
            core::Assigner assigner = core::Assigner::FINAL_COPY_ASSIGNMENT;
            return assigner;
        }

        std::any visitPublic(grammar::anceParser::PublicContext*) override
        {
            core::AccessModifier access_modifier = core::AccessModifier::PUBLIC_ACCESS;
            return access_modifier;
        }

        std::any visitPrivate(grammar::anceParser::PrivateContext*) override
        {
            core::AccessModifier access_modifier = core::AccessModifier::PRIVATE_ACCESS;
            return access_modifier;
        }

        std::any visitExtern(grammar::anceParser::ExternContext*) override
        {
            core::AccessModifier access_modifier = core::AccessModifier::EXTERN_ACCESS;
            return access_modifier;
        }

        std::any visitCompileTime(grammar::anceParser::CompileTimeContext*) override
        {
            core::ExecutionModifier execution_modifier = core::ExecutionModifier::COMPILETIME_EXECUTION;
            return execution_modifier;
        }

        std::any visitRuntime(grammar::anceParser::RuntimeContext*) override
        {
            core::ExecutionModifier execution_modifier = core::ExecutionModifier::RUNTIME_EXECUTION;
            return execution_modifier;
        }

        std::any visitTerminal(antlr4::tree::TerminalNode*) override
        {
            assert(false);// Indicates a missing implementation of a node.

            return {};
        }

        Block* createBlockStatement(std::vector<grammar::anceParser::StatementContext*> const& statement_contexts, core::Location const& source_location)
        {
            utility::List<utility::Owned<Statement>> statements;

            for (grammar::anceParser::StatementContext* statement : statement_contexts)
            {
                statements.push_back(expectStatement(statement));
            }

            return new Block(std::move(statements), source_location);
        }

      private:
        utility::Optional<size_t> file_index_;
        core::Reporter&           reporter_;
    };
}

struct ance::ast::Parser::Implementation
{
    explicit Implementation(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& ctx)
        : source_tree_(source_tree)
        , reporter_(reporter)
        , ctx_(ctx)
    {}

    template<typename Target, typename Code, typename Reader>
    utility::Optional<utility::Owned<Target>> parse(sources::SourceFile* source_file, std::string const& id, Code&& code, Reader&& reader)
    {
        utility::Optional<utility::Owned<Target>> result;

        if (source_file == nullptr || source_file->isOk())
        {
            utility::Owned<ErrorHandler> error_handler = utility::makeOwned<ErrorHandler>(reporter_, source_file);

            auto i_stream = code();

            utility::Owned<antlr4::ANTLRInputStream> input = utility::makeOwned<antlr4::ANTLRInputStream>(i_stream);
            utility::Owned<grammar::anceLexer>       lexer = utility::makeOwned<grammar::anceLexer>(input.get());
            lexer->removeErrorListeners();
            lexer->addErrorListener(error_handler->lexerErrorListener());

            utility::Owned<antlr4::CommonTokenStream> tokens = utility::makeOwned<antlr4::CommonTokenStream>(lexer.get());
            utility::Owned<grammar::anceParser>       parser = utility::makeOwned<grammar::anceParser>(tokens.get());
            parser->removeErrorListeners();
            parser->addErrorListener(error_handler->parserErrorListener());
            parser->setErrorHandler(error_handler->parserErrorStrategy());

            utility::Optional<size_t> file_index;
            if (source_file != nullptr) file_index = source_file->index();

            SourceVisitor visitor {file_index, reporter_};

            result = reader(parser.get(), visitor);
        }
        else
        {
            reporter_.error(core::Location::file(source_file->index())) << "Failed to read file";
        }

        std::filesystem::path file_path;

        if (source_file != nullptr) file_path = source_file->getRelativePath();
        else file_path = std::filesystem::path("core") / id;

        ctx_.print<Printer>(**result, "ast", file_path);

        if (reporter_.isFailed()) return std::nullopt;

        return result;
    }

    utility::Optional<utility::Owned<File>> parseUnorderedFile(std::filesystem::path const& file_path)// todo: reduce duplication with below (templates)
    {
        sources::SourceFile& source_file = source_tree_.addFile(file_path);

        return parse<File>(
            &source_file,
            "",
            [&source_file] {
                std::fstream code;// todo: this appears to be a double read as addFile also reads the file
                code.open(source_file.getRelativePath());

                return code;
            },
            [](grammar::anceParser* parser, SourceVisitor& visitor) { return visitor.expectFile(parser->unorderedScopeFile()); });
    }

    utility::Optional<utility::Owned<Statement>> parseOrderedFile(std::filesystem::path const& file_path)
    {
        sources::SourceFile& source_file = source_tree_.addFile(file_path);

        return parse<Statement>(
            &source_file,
            "",
            [&source_file] {
                std::fstream code;// todo: this appears to be a double read as addFile also reads the file
                code.open(source_file.getRelativePath());

                return code;
            },
            [](grammar::anceParser* parser, SourceVisitor& visitor) { return visitor.expectStatement(parser->orderedScopeFile()); });
    }

    utility::Optional<utility::Owned<Declaration>> parseDeclaration(std::string const& code, std::string const& id)
    {
        return parse<Declaration>(
            nullptr,
            id,
            [&code] { return std::istringstream(code); },
            [](grammar::anceParser* parser, SourceVisitor& visitor) { return visitor.expectDeclaration(parser->declaration()); });
    }

  private:
    sources::SourceTree& source_tree_;
    core::Reporter&      reporter_;
    core::Context&       ctx_;
};

ance::ast::Parser::Parser(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& ctx)
    : implementation_(utility::makeOwned<Implementation>(source_tree, reporter, ctx))
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

ance::utility::Optional<ance::utility::Owned<ance::ast::Declaration>> ance::ast::Parser::parseDeclaration(std::string const& code, std::string const& id)
{
    return implementation_->parseDeclaration(code, id);
}
