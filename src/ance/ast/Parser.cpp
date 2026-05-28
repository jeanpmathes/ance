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
#include "ance/core/BinaryOperator.h"
#include "ance/core/UnaryOperator.h"

#include "ance/sources/SourceFile.h"
#include "ance/sources/SourceTree.h"

#include "Node.h"
#include "Printer.h"

namespace
{
    auto prefix = "parser";
}

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

        core::Location location(antlr4::ParserRuleContext const* context) const
        {
            size_t const start_line   = context->getStart()->getLine();
            size_t const start_column = context->getStart()->getCharPositionInLine() + 1;

            size_t const end_line   = context->getStop()->getLine();
            size_t const end_column = context->getStop()->getCharPositionInLine() + getUtf32Length(context->getStop()->getText());
            // todo: check if -1 is needed for end_column

            return location(start_line, start_column, end_line, end_column);
        }

        core::Location location(antlr4::tree::TerminalNode* terminal_node) const
        {
            std::string const text = terminal_node->getText();

            auto const token = terminal_node->getSymbol();

            size_t const start_line   = token->getLine();
            size_t const start_column = token->getCharPositionInLine() + 1;

            size_t const end_line   = start_line;
            size_t const end_column = start_column + getUtf32Length(text) - 1;

            return location(start_line, start_column, end_line, end_column);
        }

        core::Identifier identifier(antlr4::tree::TerminalNode* terminal_node) const
        {
            return core::Identifier::make(terminal_node->getText(), location(terminal_node));
        }

        // ReSharper disable once CppMemberFunctionMayBeConst
        core::Reporter::MessageBuilder trace(std::string_view const node_name, antlr4::ParserRuleContext const* context)
        {
            auto msg = reporter_.trace(prefix, core::Location::nowhere());
            msg << "visit node " << node_name << " " << location(context);
            return msg;
        }

      public:
        utility::Owned<File> expectFile(grammar::anceParser::UnorderedScopeFileContext* context)
        {
            if (context == nullptr) return utility::makeOwned<File>(utility::List<utility::Owned<Declaration>> {}, location());

            if (std::any const result = visit(context); result.has_value()) return utility::wrap<File>(result);

            return utility::makeOwned<File>(utility::List<utility::Owned<Declaration>> {}, location(context));
        }

        template<typename T>
        utility::Owned<Declaration> expectDeclaration(T* context)
        {
            if (context == nullptr) return utility::makeOwned<ErrorDeclaration>(location());

            if (std::any const result = visit(context); result.has_value()) return utility::wrap<Declaration>(result);

            return utility::makeOwned<ErrorDeclaration>(location(context));
        }

        template<typename T>
        utility::Owned<Statement> expectStatement(T* context)
        {
            if (context == nullptr) return utility::makeOwned<ErrorStatement>(location());

            if (std::any const result = visit(context); result.has_value()) return utility::wrap<Statement>(result);

            return utility::makeOwned<ErrorStatement>(location(context));
        }

        template<typename T>
        utility::Owned<Expression> expectExpression(T* context)
        {
            if (context == nullptr) return utility::makeOwned<ErrorExpression>(location());

            if (std::any const result = visit(context); result.has_value()) return utility::wrap<Expression>(result);

            return utility::makeOwned<ErrorExpression>(location(context));
        }

        template<typename T, typename Context>
        utility::Optional<utility::Owned<T>> expect(Context* context)
        {
            if (context == nullptr) return std::nullopt;

            if (std::any const result = visit(context); result.has_value()) return std::move(utility::wrap<T>(result));

            return std::nullopt;
        }

        Parameter expectParameter(grammar::anceParser::ParameterContext* context)
        {
            // todo: when Parameter becomes auxiliary as well, this would be replaced with the method above

            core::Identifier const     name     = identifier(context->IDENTIFIER());
            utility::Owned<Expression> type     = expectExpression(context->expression());
            core::Location const       location = this->location(context);

            return {name, std::move(type), location};
        }

        core::UnaryOperator expectUnaryOperator(grammar::anceParser::UnaryOperatorContext* context)
        {
            if (context == nullptr) return core::UnaryOperator::UNSPECIFIED;

            if (std::any const result = visit(context); result.has_value()) return std::any_cast<core::UnaryOperator>(result);

            return core::UnaryOperator::UNSPECIFIED;
        }

        core::BinaryOperator expectBinaryOperator(grammar::anceParser::BinaryOperatorMultiplicativeContext* context)
        {
            if (context == nullptr) return core::BinaryOperator::UNSPECIFIED;

            if (std::any const result = visit(context); result.has_value()) return std::any_cast<core::BinaryOperator>(result);

            return core::BinaryOperator::UNSPECIFIED;
        }

        core::BinaryOperator expectBinaryOperator(grammar::anceParser::BinaryOperatorAdditiveContext* context)
        {
            if (context == nullptr) return core::BinaryOperator::UNSPECIFIED;

            if (std::any const result = visit(context); result.has_value()) return std::any_cast<core::BinaryOperator>(result);

            return core::BinaryOperator::UNSPECIFIED;
        }

        core::BinaryOperator expectBinaryOperator(grammar::anceParser::BinaryOperatorRelationalContext* context)
        {
            if (context == nullptr) return core::BinaryOperator::UNSPECIFIED;

            if (std::any const result = visit(context); result.has_value()) return std::any_cast<core::BinaryOperator>(result);

            return core::BinaryOperator::UNSPECIFIED;
        }

        core::BinaryOperator expectBinaryOperator(grammar::anceParser::BinaryOperatorEqualityContext* context)
        {
            if (context == nullptr) return core::BinaryOperator::UNSPECIFIED;

            if (std::any const result = visit(context); result.has_value()) return std::any_cast<core::BinaryOperator>(result);

            return core::BinaryOperator::UNSPECIFIED;
        }

        core::Assigner expectAssigner(grammar::anceParser::AssignerContext* context)
        {
            if (context == nullptr) return core::Assigner::UNSPECIFIED;

            if (std::any const result = visit(context); result.has_value()) return std::any_cast<core::Assigner>(result);

            return core::Assigner::UNSPECIFIED;
        }

        core::AccessModifier expectAccessModifier(grammar::anceParser::AccessModifierContext* context)
        {
            if (context == nullptr) return core::AccessModifier::PRIVATE_ACCESS;

            if (std::any const result = visit(context); result.has_value()) return std::any_cast<core::AccessModifier>(result);

            return core::AccessModifier::PRIVATE_ACCESS;
        }

        core::ExecutionModifier expectExecutionModifier(grammar::anceParser::ExecutionModeContext* context)
        {
            if (context == nullptr) return core::ExecutionModifier::ANY_EXECUTION;

            if (std::any const result = visit(context); result.has_value()) return std::any_cast<core::ExecutionModifier>(result);

            return core::ExecutionModifier::ANY_EXECUTION;
        }

        std::any visitUnorderedScopeFile(grammar::anceParser::UnorderedScopeFileContext* context) override
        {
            trace("UnorderedScopeFile", context);

            utility::List<utility::Owned<Declaration>> declarations;

            for (grammar::anceParser::DeclarationContext* declaration : context->declaration())
            {
                declarations.push_back(expectDeclaration(declaration));
            }

            File* file = new File(std::move(declarations), location(context));
            return file;
        }

        std::any visitOrderedScopeFile(grammar::anceParser::OrderedScopeFileContext* context) override
        {
            trace("OrderedScopeFile", context);

            return visit(context->statement());
        }

        std::any visitRunnableDeclaration(grammar::anceParser::RunnableDeclarationContext* context) override
        {
            trace("RunnableDeclaration", context);

            utility::Owned<Statement> body = expectStatement(context->statement());

            Declaration* declaration = new RunnableDeclaration(std::move(body), location(context));
            return declaration;
        }

        std::any visitVariableDeclaration(grammar::anceParser::VariableDeclarationContext* context) override
        {
            trace("VariableDeclaration", context);

            core::AccessModifier const access_modifier    = expectAccessModifier(context->accessModifier());
            core::ExecutionModifier    execution_modifier = expectExecutionModifier(context->executionMode());
            core::Identifier const     name               = identifier(context->IDENTIFIER());
            utility::Owned<Expression> type               = expectExpression(context->varType);

            if (execution_modifier != core::ExecutionModifier::ANY_EXECUTION)
            {
                reporter_.error(location(context->executionMode())) << "Execution modifiers are not yet supported";
                execution_modifier = core::ExecutionModifier::ANY_EXECUTION;
            }

            core::Assigner                                assigner = core::Assigner::UNSPECIFIED;
            utility::Optional<utility::Owned<Expression>> expression;
            if (context->assigned != nullptr)
            {
                assigner   = expectAssigner(context->assigner());
                expression = expectExpression(context->assigned);

                if (!assigner.isFinal())
                {
                    reporter_.error(location(context->assigner())) << "Unordered scope variable declarations must be final";
                }
            }

            Declaration* declaration =
                new VariableDeclaration(access_modifier, execution_modifier, name, std::move(type), assigner, std::move(expression), location(context));
            return declaration;
        }

        std::any visitFunctionDeclaration(grammar::anceParser::FunctionDeclarationContext* context) override
        {
            trace("FunctionDeclaration", context);

            core::AccessModifier const access_modifier    = expectAccessModifier(context->accessModifier());
            core::ExecutionModifier    execution_modifier = expectExecutionModifier(context->executionMode());
            core::Identifier const     name               = identifier(context->IDENTIFIER());

            if (execution_modifier != core::ExecutionModifier::ANY_EXECUTION)
            {
                reporter_.error(location(context->executionMode())) << "Execution modifiers are not yet supported";
                execution_modifier = core::ExecutionModifier::ANY_EXECUTION;
            }

            utility::List<Parameter> parameters;
            for (grammar::anceParser::ParameterContext* parameter_context : context->parameter()) parameters.push_back(expectParameter(parameter_context));

            utility::Optional<utility::Owned<Expression>> return_type;
            if (context->type != nullptr)
            {
                return_type = expectExpression(context->type);
            }

            utility::Owned<Statement> body = utility::Owned<Statement>(*createBlockStatement(context->statement(), location(context)));

            Declaration* declaration = new FunctionDeclaration(access_modifier,
                                                               execution_modifier,
                                                               name,
                                                               std::move(parameters),
                                                               std::move(return_type),
                                                               std::move(body),
                                                               location(context));
            return declaration;
        }

        std::any visitBlockStatement(grammar::anceParser::BlockStatementContext* context) override
        {
            trace("BlockStatement", context);

            Statement* statement = createBlockStatement(context->statement(), location(context));
            return statement;
        }

        std::any visitExpressionStatement(grammar::anceParser::ExpressionStatementContext* context) override
        {
            trace("ExpressionStatement", context);

            utility::Owned<Expression> expression = expectExpression(context->expression());

            Statement* statement = new Independent(std::move(expression), location(context));
            return statement;
        }

        std::any visitLetStatement(grammar::anceParser::LetStatementContext* context) override
        {
            trace("LetStatement", context);

            core::Identifier const     name = identifier(context->IDENTIFIER());
            utility::Owned<Expression> type = expectExpression(context->varType);

            core::Assigner                                assigner = core::Assigner::UNSPECIFIED;
            utility::Optional<utility::Owned<Expression>> expression;
            if (context->assigned != nullptr)
            {
                assigner   = expectAssigner(context->assigner());
                expression = expectExpression(context->assigned);
            }

            Statement* statement = new Let(name, std::move(type), assigner, std::move(expression), location(context));
            return statement;
        }

        std::any visitAssignmentStatement(grammar::anceParser::AssignmentStatementContext* context) override
        {
            trace("AssignmentStatement", context);

            utility::Owned<Expression> assignee = expectExpression(context->assignee);
            core::Assigner const       assigner = expectAssigner(context->assigner());
            utility::Owned<Expression> assigned = expectExpression(context->assgined);

            if (assigner.isFinal())
            {
                reporter_.error(location(context->assigner())) << "Assignment to existing variable cannot be final";
            }

            Statement* statement = new Assignment(std::move(assignee), assigner, std::move(assigned), location(context));
            return statement;
        }

        std::any visitIfStatement(grammar::anceParser::IfStatementContext* context) override
        {
            trace("IfStatement", context);

            utility::Owned<Expression> condition = expectExpression(context->expression());
            utility::Owned<Statement>  true_part = expectStatement(context->trueBlock);

            utility::Optional<utility::Owned<Statement>> false_part;
            if (context->falseBlock != nullptr)
            {
                false_part = expectStatement(context->falseBlock);
            }

            Statement* statement = new If(std::move(condition), std::move(true_part), std::move(false_part), location(context));
            return statement;
        }

        std::any visitLoopStatement(grammar::anceParser::LoopStatementContext* context) override
        {
            trace("LoopStatement", context);

            utility::Owned<Statement> body = expectStatement(context->statement());

            Statement* statement = new Loop(std::move(body), location(context));
            return statement;
        }

        std::any visitBreakStatement(grammar::anceParser::BreakStatementContext* context) override
        {
            trace("BreakStatement", context);

            Statement* statement = new Break(location(context));
            return statement;
        }

        std::any visitContinueStatement(grammar::anceParser::ContinueStatementContext* context) override
        {
            trace("ContinueStatement", context);

            Statement* statement = new Continue(location(context));
            return statement;
        }

        std::any visitReturnStatement(grammar::anceParser::ReturnStatementContext* context) override
        {
            trace("ReturnStatement", context);

            utility::Optional<utility::Owned<Expression>> value = {};
            if (context->expression() != nullptr) value = expectExpression(context->expression());

            Statement* statement = new Return(std::move(value), location(context));
            return statement;
        }

        std::any visitWhileStatement(grammar::anceParser::WhileStatementContext* context) override
        {
            trace("WhileStatement", context);

            utility::Owned<Expression> condition = expectExpression(context->expression());
            utility::Owned<Statement>  body      = expectStatement(context->statement());

            Statement* statement = new While(std::move(condition), std::move(body), location(context));
            return statement;
        }

        std::any visitMatchStatement(grammar::anceParser::MatchStatementContext* context) override
        {
            trace("MatchStatement", context);

            utility::Owned<Expression> value = expectExpression(context->expression());

            utility::List<utility::Owned<MatchCase>> cases;
            for (grammar::anceParser::MatchCaseContext* case_context : context->matchCase())
            {
                utility::Optional<utility::Owned<MatchCase>> match_case = expect<MatchCase>(case_context);
                if (match_case.hasValue())
                {
                    cases.push_back(std::move(match_case.value()));
                }
            }

            Statement* statement = new Match(std::move(value), std::move(cases), location(context));
            return statement;
        }

        std::any visitExpressionMatchCase(grammar::anceParser::ExpressionMatchCaseContext* context) override
        {
            trace("ExpressionMatchCase", context);

            utility::List<utility::Owned<Expression>> patterns;
            for (grammar::anceParser::ExpressionContext* pattern_context : context->expression())
            {
                patterns.push_back(expectExpression(pattern_context));
            }

            utility::Owned<Statement> code = expectStatement(context->statement());

            return new MatchCase(std::move(patterns), core::Location::nowhere(), std::move(code), location(context));
        }

        std::any visitDefaultMatchCase(grammar::anceParser::DefaultMatchCaseContext* context) override
        {
            trace("DefaultMatchCase", context);

            return new MatchCase({}, location(context->DEFAULT()), expectStatement(context->statement()), location(context));
        }

        std::any visitEraseStatement(grammar::anceParser::EraseStatementContext* context) override
        {
            trace("EraseStatement", context);

            core::Identifier const name = identifier(context->IDENTIFIER());

            Statement* statement = new Erase(name, location(context));
            return statement;
        }

        std::any visitAssertStatement(grammar::anceParser::AssertStatementContext* context) override
        {
            trace("AssertStatement", context);

            utility::Owned<Expression> expression = expectExpression(context->expression());

            Statement* statement = new Assert(std::move(expression), location(context));
            return statement;
        }

        std::any visitOrExpression(grammar::anceParser::OrExpressionContext* context) override
        {
            trace("OrExpression", context) << ", count(expression)=" << context->andExpression().size();

            utility::Owned<Expression> left = expectExpression(context->andExpression(0));

            core::Location location = left->location;
            for (size_t index = 1; index < context->andExpression().size(); index++)
            {
                bool const                 negated = context->orOperator(index - 1)->NOT() != nullptr;
                utility::Owned<Expression> right   = expectExpression(context->andExpression(index));

                location.extend(right->location);
                left = utility::makeOwned<Or>(std::move(left), negated, std::move(right), location);
            }

            Expression* expression = utility::unwrap(std::move(left));
            return expression;
        }

        std::any visitAndExpression(grammar::anceParser::AndExpressionContext* context) override
        {
            trace("AndExpression", context) << ", count(expression)=" << context->equalityExpression().size();

            utility::Owned<Expression> left = expectExpression(context->equalityExpression(0));

            core::Location location = left->location;
            for (size_t index = 1; index < context->equalityExpression().size(); index++)
            {
                bool const                 negated = context->andOperator(index - 1)->NOT() != nullptr;
                utility::Owned<Expression> right   = expectExpression(context->equalityExpression(index));

                location.extend(right->location);
                left = utility::makeOwned<And>(std::move(left), negated, std::move(right), location);
            }

            Expression* expression = utility::unwrap(std::move(left));
            return expression;
        }

        std::any visitEqualityExpression(grammar::anceParser::EqualityExpressionContext* context) override
        {
            trace("EqualityExpression", context) << ", count(expression)=" << context->relationalExpression().size();

            utility::Owned<Expression> left = expectExpression(context->relationalExpression(0));

            core::Location location = left->location;
            for (size_t index = 1; index < context->relationalExpression().size(); index++)
            {
                core::BinaryOperator const op    = expectBinaryOperator(context->binaryOperatorEquality(index - 1));
                utility::Owned<Expression> right = expectExpression(context->relationalExpression(index));

                location.extend(right->location);
                left = utility::makeOwned<BinaryOperation>(std::move(left), op, std::move(right), location);
            }

            Expression* expression = utility::unwrap(std::move(left));
            return expression;
        }

        std::any visitRelationalExpression(grammar::anceParser::RelationalExpressionContext* context) override
        {
            trace("RelationalExpression", context) << ", count(expression)=" << context->additiveExpression().size();

            utility::Owned<Expression> left = expectExpression(context->additiveExpression(0));

            core::Location location = left->location;
            for (size_t index = 1; index < context->additiveExpression().size(); index++)
            {
                core::BinaryOperator const op    = expectBinaryOperator(context->binaryOperatorRelational(index - 1));
                utility::Owned<Expression> right = expectExpression(context->additiveExpression(index));

                location.extend(right->location);
                left = utility::makeOwned<BinaryOperation>(std::move(left), op, std::move(right), location);
            }

            Expression* expression = utility::unwrap(std::move(left));
            return expression;
        }

        std::any visitAdditiveExpression(grammar::anceParser::AdditiveExpressionContext* context) override
        {
            trace("AdditiveExpression", context) << ", count(expression)=" << context->multiplicativeExpression().size();

            utility::Owned<Expression> left = expectExpression(context->multiplicativeExpression(0));

            core::Location location = left->location;
            for (size_t index = 1; index < context->multiplicativeExpression().size(); index++)
            {
                core::BinaryOperator const op    = expectBinaryOperator(context->binaryOperatorAdditive(index - 1));
                utility::Owned<Expression> right = expectExpression(context->multiplicativeExpression(index));

                location.extend(right->location);
                left = utility::makeOwned<BinaryOperation>(std::move(left), op, std::move(right), location);
            }

            Expression* expression = utility::unwrap(std::move(left));
            return expression;
        }

        std::any visitMultiplicativeExpression(grammar::anceParser::MultiplicativeExpressionContext* context) override
        {
            trace("MultiplicativeExpression", context) << ", count(expression)=" << context->unaryExpression().size();

            utility::Owned<Expression> left = expectExpression(context->unaryExpression(0));

            core::Location location = left->location;
            for (size_t index = 1; index < context->unaryExpression().size(); index++)
            {
                core::BinaryOperator const op    = expectBinaryOperator(context->binaryOperatorMultiplicative(index - 1));
                utility::Owned<Expression> right = expectExpression(context->unaryExpression(index));

                location.extend(right->location);
                left = utility::makeOwned<BinaryOperation>(std::move(left), op, std::move(right), location);
            }

            Expression* expression = utility::unwrap(std::move(left));
            return expression;
        }

        std::any visitUnaryOperationExpression(grammar::anceParser::UnaryOperationExpressionContext* context) override
        {
            trace("UnaryOperationExpression", context);

            core::UnaryOperator const  op      = expectUnaryOperator(context->unaryOperator());
            utility::Owned<Expression> operand = expectExpression(context->target);

            Expression* expression = new UnaryOperation(op, std::move(operand), location(context));
            return expression;
        }

        std::any visitCallExpression(grammar::anceParser::CallExpressionContext* context) override
        {
            trace("CallExpression", context);

            utility::Owned<Expression> callee = expectExpression(context->callee);

            utility::List<utility::Owned<Expression>> arguments;
            for (grammar::anceParser::ExpressionContext* expression : context->expression()) arguments.push_back(expectExpression(expression));

            Expression* expression = new Call(std::move(callee), std::move(arguments), location(context));
            return expression;
        }

        std::any visitSubscriptExpression(grammar::anceParser::SubscriptExpressionContext* context) override
        {
            trace("SubscriptExpression", context);

            utility::Owned<Expression> indexed = expectExpression(context->indexed);
            utility::Owned<Expression> index   = expectExpression(context->index);

            Expression* expression = new Subscript(std::move(indexed), std::move(index), location(context));
            return expression;
        }

        std::any visitLambdaExpression(grammar::anceParser::LambdaExpressionContext* context) override
        {
            trace("LambdaExpression", context);

            utility::List<Parameter> parameters;
            for (grammar::anceParser::ParameterContext* parameter_context : context->parameter()) parameters.push_back(expectParameter(parameter_context));

            utility::Optional<utility::Owned<Expression>> return_type;
            if (context->type != nullptr)
            {
                return_type = expectExpression(context->type);
            }

            utility::Optional<utility::Owned<Expression>> expression_body;
            utility::Optional<utility::Owned<Statement>>  statement_body;
            if (context->body != nullptr)
            {
                expression_body = expectExpression(context->body);
            }
            else if (!context->statement().empty())
            {
                statement_body = utility::wrap<Statement>(createBlockStatement(context->statement(), location(context)));
            }

            Expression* expression =
                new Lambda(std::move(parameters), std::move(return_type), std::move(expression_body), std::move(statement_body), location(context));
            return expression;
        }

        std::any visitIntrinsicExpression(grammar::anceParser::IntrinsicExpressionContext* context) override
        {
            trace("IntrinsicExpression", context);

            utility::Owned<Expression> name = expectExpression(context->name);

            utility::List<utility::Owned<Expression>> arguments;
            for (grammar::anceParser::ExpressionContext* expression : context->expression())
            {
                if (expression == context->name) continue;

                arguments.push_back(expectExpression(expression));
            }

            Expression* expression = new Intrinsic(std::move(name), std::move(arguments), location(context));
            return expression;
        }

        std::any visitTypeOfExpression(grammar::anceParser::TypeOfExpressionContext* context) override
        {
            trace("TypeOfExpression", context);

            utility::List<utility::Owned<Expression>> expressions;
            for (grammar::anceParser::ExpressionContext* expression : context->expression())
            {
                expressions.push_back(expectExpression(expression));
            }

            Expression* expression = new TypeOf(std::move(expressions), location(context));
            return expression;
        }

        std::any visitArrayTypeExpression(grammar::anceParser::ArrayTypeExpressionContext* context) override
        {
            trace("ArrayTypeExpression", context);

            utility::Owned<Expression> element_type = expectExpression(context->type);
            utility::Owned<Expression> length       = expectExpression(context->length);

            Expression* expression = new ArrayType(std::move(element_type), std::move(length), location(context));
            return expression;
        }

        std::any visitArrayConstructorExpression(grammar::anceParser::ArrayConstructorExpressionContext* context) override
        {
            trace("ArrayConstructorExpression", context);

            utility::Optional<utility::Owned<Expression>> element_type;
            if (context->type != nullptr)
            {
                element_type = expectExpression(context->type);
            }

            utility::List<utility::Owned<Expression>> elements;
            for (grammar::anceParser::ExpressionContext* expression_context : context->expression())
            {
                if (expression_context == context->type) continue;

                elements.push_back(expectExpression(expression_context));
            }

            Expression* expression = new ArrayConstructor(std::move(element_type), std::move(elements), location(context));
            return expression;
        }

        std::any visitIfExpression(grammar::anceParser::IfExpressionContext* context) override
        {
            trace("IfExpression", context);

            utility::Owned<Expression> condition  = expectExpression(context->condition);
            utility::Owned<Expression> true_block = expectExpression(context->trueBlock);

            utility::Optional<utility::Owned<Expression>> false_block;
            if (context->falseBlock != nullptr)
            {
                false_block = expectExpression(context->falseBlock);
            }

            Expression* expression = new IfExpression(std::move(condition), std::move(true_block), std::move(false_block), location(context));
            return expression;
        }

        std::any visitMatchExpression(grammar::anceParser::MatchExpressionContext* context) override
        {
            trace("MatchExpression", context);

            utility::Owned<Expression> condition = expectExpression(context->condition);

            utility::List<utility::Owned<MatchExpressionCase>> cases;
            for (grammar::anceParser::MatchExpressionCaseContext* case_context : context->matchExpressionCase())
            {
                utility::Optional<utility::Owned<MatchExpressionCase>> match_case = expect<MatchExpressionCase>(case_context);
                if (match_case.hasValue())
                {
                    cases.push_back(std::move(match_case.value()));
                }
            }

            Expression* expression = new MatchExpression(std::move(condition), std::move(cases), location(context));
            return expression;
        }

        std::any visitExpressionMatchExpressionCase(grammar::anceParser::ExpressionMatchExpressionCaseContext* context) override
        {
            trace("ExpressionMatchExpressionCase", context);

            utility::List<utility::Owned<Expression>> patterns;
            for (grammar::anceParser::ExpressionContext* pattern_context : context->expression())
            {
                patterns.push_back(expectExpression(pattern_context));
            }

            utility::Owned<Expression> expression = std::move(patterns.back());
            patterns.pop_back();

            return new MatchExpressionCase(std::move(patterns), core::Location::nowhere(), std::move(expression), location(context));
        }

        std::any visitDefaultMatchExpressionCase(grammar::anceParser::DefaultMatchExpressionCaseContext* context) override
        {
            trace("DefaultMatchExpressionCase", context);

            return new MatchExpressionCase({}, location(context->DEFAULT()), expectExpression(context->expression()), location(context));
        }

        std::any visitBlockExpression(grammar::anceParser::BlockExpressionContext* context) override
        {
            trace("BlockExpression", context);

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

        std::any visitParenthesisExpression(grammar::anceParser::ParenthesisExpressionContext* context) override
        {
            trace("ParenthesisExpression", context);

            Expression* expression = new Parenthesis(expectExpression(context->expression()), location(context));
            return expression;
        }

        std::any visitAccessExpression(grammar::anceParser::AccessExpressionContext* context) override
        {
            trace("AccessExpression", context);

            core::Identifier const accessed = identifier(context->IDENTIFIER());

            Expression* expression = new Access(accessed, location(context));
            return expression;
        }

        std::any visitHereExpression(grammar::anceParser::HereExpressionContext* context) override
        {
            trace("HereExpression", context);

            Expression* expression = new Here(location(context));
            return expression;
        }

        std::any visitUnaryNot(grammar::anceParser::UnaryNotContext* context) override
        {
            trace("UnaryNot", context);

            core::UnaryOperator op = core::UnaryOperator::NOT;
            return op;
        }

        std::any visitUnaryBitwiseNot(grammar::anceParser::UnaryBitwiseNotContext* context) override
        {
            trace("UnaryBitwiseNot", context);

            core::UnaryOperator op = core::UnaryOperator::BITWISE_NOT;
            return op;
        }

        std::any visitUnaryNegation(grammar::anceParser::UnaryNegationContext* context) override
        {
            trace("UnaryNegation", context);

            core::UnaryOperator op = core::UnaryOperator::NEGATION;
            return op;
        }

        std::any visitMultiplication(grammar::anceParser::MultiplicationContext* context) override
        {
            trace("Multiplication", context);

            core::BinaryOperator op = core::BinaryOperator::MULTIPLICATION;
            return op;
        }

        std::any visitDivision(grammar::anceParser::DivisionContext* context) override
        {
            trace("Division", context);

            core::BinaryOperator op = core::BinaryOperator::DIVISION;
            return op;
        }

        std::any visitRemainder(grammar::anceParser::RemainderContext* context) override
        {
            trace("Remainder", context);

            core::BinaryOperator op = core::BinaryOperator::REMAINDER;
            return op;
        }

        std::any visitAddition(grammar::anceParser::AdditionContext* context) override
        {
            trace("Addition", context);

            core::BinaryOperator op = core::BinaryOperator::ADDITION;
            return op;
        }

        std::any visitSubtraction(grammar::anceParser::SubtractionContext* context) override
        {
            trace("Subtraction", context);

            core::BinaryOperator op = core::BinaryOperator::SUBTRACTION;
            return op;
        }

        std::any visitLessThan(grammar::anceParser::LessThanContext* context) override
        {
            trace("LessThan", context);

            core::BinaryOperator op = core::BinaryOperator::LESS_THAN;
            return op;
        }

        std::any visitLessThanOrEqual(grammar::anceParser::LessThanOrEqualContext* context) override
        {
            trace("LessThanOrEqual", context);

            core::BinaryOperator op = core::BinaryOperator::LESS_THAN_OR_EQUAL;
            return op;
        }

        std::any visitGreaterThan(grammar::anceParser::GreaterThanContext* context) override
        {
            trace("GreaterThan", context);

            core::BinaryOperator op = core::BinaryOperator::GREATER_THAN;
            return op;
        }

        std::any visitGreaterThanOrEqual(grammar::anceParser::GreaterThanOrEqualContext* context) override
        {
            trace("GreaterThanOrEqual", context);

            core::BinaryOperator op = core::BinaryOperator::GREATER_THAN_OR_EQUAL;
            return op;
        }

        std::any visitEqual(grammar::anceParser::EqualContext* context) override
        {
            trace("Equal", context);

            core::BinaryOperator op = core::BinaryOperator::EQUAL;
            return op;
        }

        std::any visitNotEqual(grammar::anceParser::NotEqualContext* context) override
        {
            trace("NotEqual", context);

            core::BinaryOperator op = core::BinaryOperator::NOT_EQUAL;
            return op;
        }

        std::any visitTrue(grammar::anceParser::TrueContext* context) override
        {
            trace("True", context);

            Expression* expression = new BoolLiteral(true, location(context));
            return expression;
        }

        std::any visitFalse(grammar::anceParser::FalseContext* context) override
        {
            trace("False", context);

            Expression* expression = new BoolLiteral(false, location(context));
            return expression;
        }

        std::any visitSizeLiteral(grammar::anceParser::SizeLiteralContext* context) override
        {
            trace("SizeLiteral", context);

            // todo: use llvm::APInt instead of size_t
            // todo: do all the validation of integer literals and stuff like whether they actually fit into their type

            Expression* expression = new SizeLiteral(context->getText(), location(context));
            return expression;
        }

        std::any visitHalfLiteral(grammar::anceParser::HalfLiteralContext* context) override
        {
            trace("HalfLiteral", context);

            std::string text = context->getText();
            text             = text.substr(0, text.size() - 1);// Remove type suffix.

            Expression* expression = new FloatingPointLiteral(core::Precision::HALF, text, location(context));
            return expression;
        }

        std::any visitSingleLiteral(grammar::anceParser::SingleLiteralContext* context) override
        {
            trace("SingleLiteral", context);

            std::string text = context->getText();
            text             = text.substr(0, text.size() - 1);// Remove type suffix.

            Expression* expression = new FloatingPointLiteral(core::Precision::SINGLE, text, location(context));
            return expression;
        }

        std::any visitDoubleLiteral(grammar::anceParser::DoubleLiteralContext* context) override
        {
            trace("DoubleLiteral", context);

            std::string text = context->getText();
            text             = text.substr(0, text.size() - 1);// Remove type suffix.

            Expression* expression = new FloatingPointLiteral(core::Precision::DOUBLE, text, location(context));
            return expression;
        }

        std::any visitQuadLiteral(grammar::anceParser::QuadLiteralContext* context) override
        {
            trace("QuadLiteral", context);

            std::string text = context->getText();
            text             = text.substr(0, text.size() - 1);// Remove type suffix.

            Expression* expression = new FloatingPointLiteral(core::Precision::QUAD, text, location(context));
            return expression;
        }

        std::any visitUnitLiteral(grammar::anceParser::UnitLiteralContext* context) override
        {
            trace("UnitLiteral", context);

            Expression* expression = new UnitLiteral(location(context));
            return expression;
        }

        std::any visitStringLiteral(grammar::anceParser::StringLiteralContext* context) override
        {
            trace("StringLiteral", context);

            std::string text = context->getText();
            text             = text.substr(1, text.size() - 2);// Remove quotes.

            Expression* expression = new StringLiteral(text, location(context));
            return expression;
        }

        std::any visitCopyAssigner(grammar::anceParser::CopyAssignerContext* context) override
        {
            trace("CopyAssigner", context);

            core::Assigner assigner = core::Assigner::COPY_ASSIGNMENT;
            return assigner;
        }

        std::any visitFinalCopyAssigner(grammar::anceParser::FinalCopyAssignerContext* context) override
        {
            trace("FinalCopyAssigner", context);

            core::Assigner assigner = core::Assigner::FINAL_COPY_ASSIGNMENT;
            return assigner;
        }

        std::any visitPublic(grammar::anceParser::PublicContext* context) override
        {
            trace("Public", context);

            core::AccessModifier access_modifier = core::AccessModifier::PUBLIC_ACCESS;
            return access_modifier;
        }

        std::any visitPrivate(grammar::anceParser::PrivateContext* context) override
        {
            trace("Private", context);

            core::AccessModifier access_modifier = core::AccessModifier::PRIVATE_ACCESS;
            return access_modifier;
        }

        std::any visitExtern(grammar::anceParser::ExternContext* context) override
        {
            trace("Extern", context);

            core::AccessModifier access_modifier = core::AccessModifier::EXTERN_ACCESS;
            return access_modifier;
        }

        std::any visitCompileTime(grammar::anceParser::CompileTimeContext* context) override
        {
            trace("CompileTime", context);

            core::ExecutionModifier execution_modifier = core::ExecutionModifier::COMPILETIME_EXECUTION;
            return execution_modifier;
        }

        std::any visitRuntime(grammar::anceParser::RuntimeContext* context) override
        {
            trace("Runtime", context);

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
    explicit Implementation(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context)
        : source_tree_(source_tree)
        , reporter_(reporter)
        , context_(context)
    {}

    template<typename Target, typename Code, typename Reader>
    utility::Optional<utility::Owned<Target>> parse(sources::SourceFile* source_file, std::string const& id, Code&& code, Reader&& reader)
    {
        reporter_.trace(prefix, core::Location::nowhere()) << "parse enter {id=" << id << "}";

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

        context_.print<Printer>(**result, "ast", file_path);

        if (reporter_.isFailed())
        {
            reporter_.trace(prefix, core::Location::nowhere()) << "parse exit {id=" << id << ", status=fail}";

            return std::nullopt;
        }

        reporter_.trace(prefix, core::Location::nowhere()) << "parse exit {id=" << id << ", status=ok}";

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
    core::Context&       context_;
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

ance::utility::Optional<ance::utility::Owned<ance::ast::Declaration>> ance::ast::Parser::parseDeclaration(std::string const& code, std::string const& id)
{
    return implementation_->parseDeclaration(code, id);
}
