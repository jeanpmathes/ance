#include "Expander.h"

#include <variant>

#include "ance/core/Constants.h"

#include "ance/ast/Node.h"
#include "ance/ast/Parser.h"

#include "ance/est/Node.h"
#include "ance/est/Printer.h"

#include <llvm/IR/Instruction.h>

namespace
{
    auto prefix = "expander";
}

struct ance::est::Expander::Implementation
{
    explicit Implementation(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context)
        : source_tree_(source_tree)
        , reporter_(reporter)
        , parser_(source_tree, reporter, context)
        , context_(context)
    {}

    using Statements = utility::List<utility::Owned<Statement>>;

    class Result
    {
      public:
        void reset()
        {
            result_ = std::nullopt;
        }

        void setFile(utility::Owned<File> file)
        {
            setResult(std::move(file));
        }

        void setDeclaration(utility::Owned<Declaration> declaration)
        {
            setResult(std::move(declaration));
        }

        void setStatements(Statements statements)
        {
            setResult(std::move(statements));
        }

        void setStatements(utility::Owned<Statement> statement)
        {
            Statements statements;
            statements.emplace_back(std::move(statement));
            setResult(std::move(statements));
        }

        void setStatements(Statements statements, utility::Owned<Statement> final_statement)
        {
            statements.emplace_back(std::move(final_statement));
            setResult(std::move(statements));
        }

        void setExpression(utility::Owned<Expression> expression)
        {
            setResult(std::move(expression));
        }

        void setMatchCase(utility::Owned<MatchCase> match_case)
        {
            setResult(std::move(match_case));
        }

        template<typename T>
        T take()
        {
            assert(result_.has_value());
            assert(std::holds_alternative<T>(*result_));

            T value = std::move(std::get<T>(*result_));
            result_ = std::nullopt;
            return value;
        }

      private:
        using ResultVariant =
            std::variant<utility::Owned<File>, utility::Owned<Declaration>, Statements, utility::Owned<Expression>, utility::Owned<MatchCase>>;

        template<typename T>
        void setResult(T value)
        {
            assert(!result_.has_value());
            result_ = ResultVariant(std::move(value));
        }

        std::optional<ResultVariant> result_;
    };

    class AST final : public ast::Visitor
    {
      public:
        using Visitor::visit;

        explicit AST(core::Reporter& reporter) : reporter_(reporter) {}
        ~AST() override = default;

        class SBuilder final
        {
          public:
            explicit SBuilder(AST& ast) : ast_(ast) {}

            void pushIndependentExpansion(ast::Expression const& expression)
            {
                pushStatement(utility::makeOwned<Independent>(ast_.expand(expression), expression.location));
            }

            void pushExpansion(ast::Statement const& statement)
            {
                Statements expanded = ast_.expand(statement);
                append(statements_, std::move(expanded));
            }

            void pushStatement(utility::Owned<Statement> statement)
            {
                statements_.emplace_back(std::move(statement));
            }

            void pushIndependentExpression(utility::Owned<Expression> expression)
            {
                statements_.emplace_back(utility::makeOwned<Independent>(std::move(expression), expression->location));
            }

            /// Creates an anonymous local name and returns its identifier.
            /// When using this, remember to wrap the expansion in a block so the name is cleaned up after use.
            core::Identifier pushAnonymousBind(utility::Owned<Expression>                    type,
                                               core::VariabilityModifier const               variability,
                                               core::Assigner                                assigner,
                                               utility::Optional<utility::Owned<Expression>> definition,
                                               core::Location const&                         location)
            {
                core::Identifier const identifier = ast_.getAnonymousIdentifier(location);

                statements_.emplace_back(utility::makeOwned<Bind>(identifier, variability, std::move(type), assigner, std::move(definition), location));

                return identifier;
            }

            Statements&& take()
            {
                return std::move(statements_);
            }

            void reset()
            {
                statements_.clear();
            }

          private:
            AST& ast_;

            Statements statements_;
        };

        class EBuilder final
        {
          public:
            explicit EBuilder(AST& ast, core::Location const& location) : ast_(ast), location_(location) {}

            core::Identifier pushAnonymousBind(utility::Owned<Expression>                    type,
                                               core::VariabilityModifier const               variability,
                                               core::Assigner const                          assigner,
                                               utility::Optional<utility::Owned<Expression>> definition)
            {
                core::Identifier const identifier = ast_.getAnonymousIdentifier(location_);

                statements_.emplace_back(utility::makeOwned<Bind>(identifier, variability, std::move(type), assigner, std::move(definition), location_));

                return identifier;
            }

            void pushAnonymousBindAndSetAsResult(utility::Owned<Expression>                    type,
                                                 core::VariabilityModifier const               variability,
                                                 core::Assigner const                          assigner,
                                                 utility::Optional<utility::Owned<Expression>> definition)
            {
                core::Identifier const identifier = pushAnonymousBind(std::move(type), variability, assigner, std::move(definition));

                result_ = identifier;
            }

            [[nodiscard]] utility::Owned<Expression> createAccess(core::Identifier const& identifier)
            {
                return utility::makeOwned<Access>(identifier, location_);
            }

            [[nodiscard]] utility::Owned<Expression> createAccessToResult()
            {
                assert(result_.hasValue());

                return createAccess(result_.value());
            }

            utility::Owned<Statement> createAssignment(core::Identifier const& identifier, core::Assigner const assigner, utility::Owned<Expression> value)
            {
                return utility::makeOwned<Assignment>(createAccess(identifier), assigner, std::move(value), location_);
            }

            utility::Owned<Statement> createExpansionAssignment(core::Identifier const& identifier,
                                                                core::Assigner const    assigner,
                                                                ast::Expression const&  expression)
            {
                return createAssignment(identifier, assigner, ast_.expand(expression));
            }

            utility::Owned<Statement> createAssignmentToResult(core::Assigner const assigner, utility::Owned<Expression> value)
            {
                assert(result_.hasValue());
                return createAssignment(result_.value(), assigner, std::move(value));
            }

            utility::Owned<Statement> createExpansionAssignmentToResult(core::Assigner const assigner, ast::Expression const& expression)
            {
                assert(result_.hasValue());
                return createAssignmentToResult(assigner, ast_.expand(expression));
            }

            void pushAssignment(core::Identifier const& identifier, core::Assigner const assigner, utility::Owned<Expression> value)
            {
                pushStatement(createAssignment(identifier, assigner, std::move(value)));
            }

            void pushExpansionAssignment(core::Identifier const& identifier, core::Assigner const assigner, ast::Expression const& expression)
            {
                pushStatement(createExpansionAssignment(identifier, assigner, expression));
            }

            void pushAssignmentToResult(core::Assigner const assigner, utility::Owned<Expression> value)
            {
                pushStatement(createAssignmentToResult(assigner, std::move(value)));
            }

            void pushExpansionAssignmentToResult(core::Assigner const assigner, ast::Expression const& expression)
            {
                pushStatement(createExpansionAssignmentToResult(assigner, expression));
            }

            void pushStatement(utility::Owned<Statement> statement)
            {
                statements_.emplace_back(std::move(statement));
            }

            utility::Owned<Expression> take()
            {
                return utility::makeOwned<BlockExpression>(std::move(statements_), createAccessToResult(), location_);
            }

          private:
            AST&           ast_;
            core::Location location_;

            Statements                          statements_;
            utility::Optional<core::Identifier> result_;
        };

        utility::Owned<File> expand(ast::File const& file)
        {
            result_.reset();
            visit(file);
            return result_.take<utility::Owned<File>>();
        }

        utility::Owned<Declaration> expand(ast::Declaration const& declaration)
        {
            result_.reset();
            visit(declaration);

            return result_.take<utility::Owned<Declaration>>();
        }

        Statements expand(ast::Statement const& statement)
        {
            result_.reset();
            visit(statement);

            (void) reporter_;//todo: use reporter or remove from expander at some point

            return result_.take<Statements>();
        }

        utility::Owned<Expression> expand(ast::Expression const& expression)
        {
            result_.reset();
            visit(expression);
            return result_.take<utility::Owned<Expression>>();
        }

        utility::Owned<MatchCase> expand(ast::MatchCase const& match_case)
        {
            result_.reset();
            visit(match_case);
            return result_.take<utility::Owned<MatchCase>>();
        }

        [[nodiscard]] Parameter expand(ast::Parameter const& parameter)
        {
            return {parameter.identifier, expand(*parameter.type), parameter.location};
        }

        core::Identifier getAnonymousIdentifier(core::Location const& location)
        {
            std::string const      id         = std::format("anonymous<{}>", anonymous_variable_counter_++);
            core::Identifier const identifier = core::Identifier::make(id, location);

            return identifier;
        }

        static void append(Statements& target, Statements&& source)
        {
            target.insert(target.end(), make_move_iterator(source.begin()), make_move_iterator(source.end()));
        }

        static utility::Owned<Statement> wrap(Statements&& statements)
        {
            if (statements.empty())
            {
                return utility::makeOwned<Pass>(core::Location::project());
            }

            if (statements.size() == 1 && statements.front()->isCompound())
            {
                return std::move(statements.front());
            }

            core::Location location = statements.front()->location;

            for (auto& statement : statements)
            {
                location.extend(statement->location);
            }

            return utility::makeOwned<Block>(std::move(statements), location);
        }

        void visit(ast::File const& file) override
        {
            trace("File", file.location) << ", count(declarations)=" << file.declarations.size();

            utility::List<utility::Owned<Declaration>> declarations;

            for (auto const& declaration : file.declarations)
            {
                declarations.emplace_back(expand(*declaration));
            }

            result_.setFile(utility::makeOwned<File>(std::move(declarations), file.location));
        }

        void visit(ast::ErrorDeclaration const& error) override
        {
            trace("ErrorDeclaration", error.location);

            result_.setDeclaration(utility::makeOwned<RunnableDeclaration>(utility::makeOwned<ErrorStatement>(error.location), error.location));
        }

        void visit(ast::RunnableDeclaration const& runnable) override
        {
            trace("RunnableDeclaration", runnable.location);

            result_.setDeclaration(utility::makeOwned<RunnableDeclaration>(wrap(expand(*runnable.body)), runnable.location));
        }

        void visit(ast::VariableDeclaration const& variable_declaration) override
        {
            trace("VariableDeclaration", variable_declaration.location)
                << ", access=" << variable_declaration.access_modifier << ", execution=" << variable_declaration.execution_modifier
                << ", identifier=" << variable_declaration.identifier << ", assigner=" << variable_declaration.assigner << ", has_value=" << std::boolalpha
                << variable_declaration.value.hasValue();

            utility::Owned<Expression> type = expand(*variable_declaration.type);

            utility::Optional<utility::Owned<Expression>> value = std::nullopt;
            if (variable_declaration.value.hasValue())
            {
                value = expand(**variable_declaration.value);
            }

            result_.setDeclaration(utility::makeOwned<VariableDeclaration>(variable_declaration.access_modifier,
                                                                           variable_declaration.execution_modifier,
                                                                           variable_declaration.identifier,
                                                                           std::move(type),
                                                                           variable_declaration.assigner,
                                                                           std::move(value),
                                                                           variable_declaration.location));
        }

        void visit(ast::FunctionDeclaration const& function_declaration) override
        {
            trace("FunctionDeclaration", function_declaration.location)
                << ", access=" << function_declaration.access_modifier << ", execution=" << function_declaration.execution_modifier
                << ", identifier=" << function_declaration.identifier << ", count(parameters)=" << function_declaration.parameters.size()
                << ", has_return_type=" << std::boolalpha << function_declaration.return_type.hasValue();

            utility::List<Parameter> parameters;
            for (auto const& parameter : function_declaration.parameters)
            {
                utility::Owned<Expression> parameter_type = expand(*parameter.type);
                parameters.emplace_back(parameter.identifier, std::move(parameter_type), parameter.location);
            }

            utility::Owned<Expression> return_type =
                function_declaration.return_type.hasValue()
                    ? expand(**function_declaration.return_type)
                    : utility::makeOwned<Access>(core::Identifier::make(core::UNIT_TYPE_NAME, core::Location::core()), function_declaration.location);

            SBuilder body_builder(*this);
            body_builder.pushExpansion(*function_declaration.body);
            utility::Owned<Statement> body = wrap(body_builder.take());

            // todo: as soon as we have custom types, we would need this access here to be in the global scope, e.g. a global:: prefix
            // todo: or as long as that is not done, just a new type of expression that contains an enum of important types
            // todo: and the same for the Unit type above - remove that constants file to find all places
            utility::Owned<Expression> function_type =
                utility::makeOwned<Access>(core::Identifier::make(core::FUNCTION_TYPE_NAME, core::Location::core()), function_declaration.location);

            utility::Owned<Expression> function_value = utility::makeOwned<FunctionConstructor>(function_declaration.identifier,
                                                                                                std::move(parameters),
                                                                                                std::move(return_type),
                                                                                                std::move(body),
                                                                                                function_declaration.location);

            result_.setDeclaration(utility::makeOwned<VariableDeclaration>(function_declaration.access_modifier,
                                                                           function_declaration.execution_modifier,
                                                                           function_declaration.identifier,
                                                                           std::move(function_type),
                                                                           core::Assigner::COPY_ASSIGNMENT,// todo: should be move
                                                                           std::move(function_value),
                                                                           function_declaration.location));
        }

        void visit(ast::ErrorStatement const& error_statement) override
        {
            trace("ErrorStatement", error_statement.location);

            result_.setStatements(utility::makeOwned<ErrorStatement>(error_statement.location));
        }

        void visit(ast::Block const& block) override
        {
            trace("Block", block.location) << ", count(statements)=" << block.statements.size();

            SBuilder builder(*this);

            for (auto& statement : block.statements)
            {
                builder.pushExpansion(*statement);
            }

            result_.setStatements(utility::makeOwned<Block>(builder.take(), block.location));
        }

        void visit(ast::Independent const& independent) override
        {
            trace("Independent", independent.location);

            SBuilder builder(*this);

            builder.pushIndependentExpansion(*independent.expression);

            result_.setStatements(builder.take());
        }

        void visit(ast::Bind const& bind) override
        {
            trace("Bind", bind.location) << ", identifier=" << bind.identifier << ", variability=" << bind.variability << ", assigner=" << bind.assigner
                                         << ", has_value=" << std::boolalpha << bind.value.hasValue();

            SBuilder builder(*this);

            utility::Owned<Expression> type = expand(*bind.type);

            utility::Optional<utility::Owned<Expression>> value = std::nullopt;
            if (bind.value.hasValue())
            {
                value = expand(**bind.value);
            }

            builder.pushStatement(utility::makeOwned<Bind>(bind.identifier, bind.variability, std::move(type), bind.assigner, std::move(value), bind.location));

            result_.setStatements(builder.take());
        }

        void visit(ast::Assignment const& assignment) override
        {
            trace("Assignment", assignment.location) << ", assigner=" << assignment.assigner;

            SBuilder builder(*this);

            utility::Owned<Expression> assignee = expand(*assignment.assignee);
            utility::Owned<Expression> value    = expand(*assignment.value);

            builder.pushStatement(utility::makeOwned<Assignment>(std::move(assignee), assignment.assigner, std::move(value), assignment.location));

            result_.setStatements(builder.take());
        }

        void visit(ast::If const& if_statement) override
        {
            trace("If", if_statement.location) << ", has_false_part=" << std::boolalpha << if_statement.false_part.hasValue();

            SBuilder builder(*this);

            utility::Owned<Expression> condition = expand(*if_statement.condition);

            Statements true_statements  = expand(*if_statement.true_part);
            Statements false_statements = if_statement.false_part.hasValue() ? expand(**if_statement.false_part) : Statements();

            builder.pushStatement(
                utility::makeOwned<If>(std::move(condition), wrap(std::move(true_statements)), wrap(std::move(false_statements)), if_statement.location));

            result_.setStatements(builder.take());
        }

        void visit(ast::Loop const& loop) override
        {
            trace("Loop", loop.location);

            result_.setStatements(utility::makeOwned<Loop>(wrap(expand(*loop.body)), loop.location));
        }

        void visit(ast::Break const& break_statement) override
        {
            trace("Break", break_statement.location);

            result_.setStatements(utility::makeOwned<Break>(break_statement.location));
        }

        void visit(ast::Continue const& continue_statement) override
        {
            trace("Continue", continue_statement.location);

            result_.setStatements(utility::makeOwned<Continue>(continue_statement.location));
        }

        void visit(ast::Return const& return_statement) override
        {
            trace("Return", return_statement.location) << ", has_value=" << std::boolalpha << return_statement.value.hasValue();

            SBuilder builder(*this);

            utility::Optional<utility::Owned<Expression>> return_value = std::nullopt;

            if (return_statement.value.hasValue())
            {
                return_value = expand(**return_statement.value);
            }

            builder.pushStatement(utility::makeOwned<Return>(std::move(return_value), return_statement.location));

            result_.setStatements(builder.take());
        }

        void visit(ast::While const& while_statement) override
        {
            trace("While", while_statement.location);
            SBuilder builder(*this);

            utility::Owned<Expression> condition = expand(*while_statement.condition);

            builder.pushStatement(
                utility::makeOwned<If>(utility::makeOwned<UnaryOperation>(core::UnaryOperator::NOT, std::move(condition), while_statement.condition->location),
                                       utility::makeOwned<Break>(while_statement.location),
                                       utility::makeOwned<Pass>(while_statement.location),
                                       while_statement.location));

            builder.pushExpansion(*while_statement.body);

            result_.setStatements(utility::makeOwned<Loop>(wrap(builder.take()), while_statement.location));
        }

        void visit(ast::Match const& match_statement) override
        {
            trace("Match", match_statement.location) << ", count(cases)=" << match_statement.cases.size();

            SBuilder builder(*this);

            utility::Owned<Expression> condition = expand(*match_statement.condition);

            utility::List<utility::Owned<MatchCase>> cases;
            for (auto& match_case : match_statement.cases)
            {
                cases.emplace_back(expand(*match_case));
            }

            builder.pushStatement(utility::makeOwned<Match>(std::move(condition), std::move(cases), match_statement.location));

            result_.setStatements(builder.take());
        }

        void visit(ast::Erase const& erase) override
        {
            trace("Erase", erase.location) << ", identifier=" << erase.identifier;

            result_.setStatements(utility::makeOwned<Erase>(erase.identifier, erase.location));
        }

        void visit(ast::Assert const& assert) override
        {
            trace("Assert", assert.location);

            result_.setStatements(utility::makeOwned<Assert>(expand(*assert.condition), assert.location));
        }

        void visit(ast::ErrorExpression const& error_expression) override
        {
            trace("ErrorExpression", error_expression.location);

            result_.setExpression(utility::makeOwned<ErrorExpression>(error_expression.location));
        }

        void visit(ast::And const& and_expression) override
        {
            trace("And", and_expression.location) << ", negated=" << std::boolalpha << and_expression.negated;

            EBuilder builder(*this, and_expression.location);

            // todo: assigners should be move assignments as soon as supported

            builder.pushAnonymousBindAndSetAsResult(
                utility::makeOwned<Access>(core::Identifier::make(core::BOOL_TYPE_NAME, core::Location::core()), and_expression.location),
                core::VariabilityModifier::VARIABLE,
                core::Assigner::COPY_ASSIGNMENT,
                expand(*and_expression.left));

            builder.pushStatement(utility::makeOwned<If>(builder.createAccessToResult(),
                                                         builder.createExpansionAssignmentToResult(core::Assigner::COPY_ASSIGNMENT, *and_expression.right),
                                                         utility::makeOwned<Pass>(and_expression.location),
                                                         and_expression.location));

            utility::Owned<Expression> result = builder.take();

            if (and_expression.negated)
            {
                result = utility::makeOwned<UnaryOperation>(core::UnaryOperator::NOT, std::move(result), and_expression.location);
            }

            result_.setExpression(std::move(result));
        }

        void visit(ast::Or const& or_expression) override
        {
            trace("Or", or_expression.location) << ", negated=" << std::boolalpha << or_expression.negated;

            EBuilder builder(*this, or_expression.location);

            // todo: assigners should be move assignments as soon as supported

            builder.pushAnonymousBindAndSetAsResult(
                utility::makeOwned<Access>(core::Identifier::make(core::BOOL_TYPE_NAME, core::Location::core()), or_expression.location),
                core::VariabilityModifier::VARIABLE,
                core::Assigner::COPY_ASSIGNMENT,
                expand(*or_expression.left));

            builder.pushStatement(utility::makeOwned<If>(builder.createAccessToResult(),
                                                         utility::makeOwned<Pass>(or_expression.location),
                                                         builder.createExpansionAssignmentToResult(core::Assigner::COPY_ASSIGNMENT, *or_expression.right),
                                                         or_expression.location));

            utility::Owned<Expression> result = builder.take();

            if (or_expression.negated)
            {
                result = utility::makeOwned<UnaryOperation>(core::UnaryOperator::NOT, std::move(result), or_expression.location);
            }

            result_.setExpression(std::move(result));
        }

        void visit(ast::Call const& call) override
        {
            trace("Call", call.location) << ", count(arguments)=" << call.arguments.size();

            utility::Owned<Expression> callee = expand(*call.callee);

            utility::List<utility::Owned<Expression>> arguments;
            for (auto& argument : call.arguments)
            {
                arguments.emplace_back(expand(*argument));
            }

            result_.setExpression(utility::makeOwned<Call>(std::move(callee), std::move(arguments), call.location));
        }

        void visit(ast::Subscript const& subscript) override
        {
            trace("Subscript", subscript.location);

            result_.setExpression(utility::makeOwned<Subscript>(expand(*subscript.indexed), expand(*subscript.index), subscript.location));
        }

        void visit(ast::Lambda const& lambda) override
        {
            trace("Lambda", lambda.location) << ", count(parameters)=" << lambda.parameters.size() << ", has_return_type=" << std::boolalpha
                                             << lambda.return_type.hasValue() << ", has_expression_body=" << std::boolalpha << lambda.expression_body.hasValue()
                                             << ", has_statement_body=" << std::boolalpha << lambda.statement_body.hasValue();

            utility::List<Parameter> parameters;
            for (auto& parameter : lambda.parameters)
            {
                parameters.emplace_back(expand(parameter));
            }

            utility::Optional<utility::Owned<Expression>> return_type;
            if (lambda.return_type.hasValue())
            {
                return_type = expand(**lambda.return_type);
            }
            else
            {
                // todo: as soon as we have custom types, we would need this access here to be in the global scope, e.g. a global:: prefix
                // todo: or as long as that is not done, just a new type of expression that contains an enum of important types
                // todo: and the same for the Function type above in function declaration - remove that constants file to find all places
                return_type = utility::makeOwned<Access>(core::Identifier::make(core::UNIT_TYPE_NAME, core::Location::core()), lambda.location);
            }

            SBuilder body_builder(*this);

            if (lambda.expression_body.hasValue())
            {
                utility::Owned<Expression> expression = expand(**lambda.expression_body);
                body_builder.pushStatement(utility::makeOwned<Return>(std::move(expression), lambda.location));
            }
            else
            {
                body_builder.pushExpansion(**lambda.statement_body);
            }

            utility::Owned<Statement> body = wrap(body_builder.take());

            std::string const name = std::format("Lambda'{}", anonymous_function_counter_++);

            result_.setExpression(utility::makeOwned<FunctionConstructor>(core::Identifier::make(name, lambda.location),
                                                                          std::move(parameters),
                                                                          std::move(return_type.value()),
                                                                          std::move(body),
                                                                          lambda.location));
        }

        void visit(ast::Intrinsic const& intrinsic_expression) override
        {
            trace("Intrinsic", intrinsic_expression.location) << ", count(arguments)=" << intrinsic_expression.arguments.size();

            utility::Owned<Expression> name = expand(*intrinsic_expression.name);

            utility::List<utility::Owned<Expression>> arguments;
            for (auto& argument : intrinsic_expression.arguments)
            {
                arguments.emplace_back(expand(*argument));
            }

            result_.setExpression(utility::makeOwned<Intrinsic>(std::move(name), std::move(arguments), intrinsic_expression.location));
        }

        void visit(ast::BlockExpression const& block_expression) override
        {
            trace("BlockExpression", block_expression.location)
                << ", count(statements)=" << block_expression.statements.size() << ", has_result" << std::boolalpha << block_expression.result.hasValue();

            SBuilder builder(*this);

            for (auto& statement : block_expression.statements)
            {
                builder.pushExpansion(*statement);
            }

            utility::Optional<utility::Owned<Expression>> result;
            if (block_expression.result.hasValue())
            {
                result = expand(**block_expression.result);
            }
            else
            {
                result = utility::makeOwned<UnitLiteral>(block_expression.location);
            }

            result_.setExpression(utility::makeOwned<BlockExpression>(builder.take(), std::move(result.value()), block_expression.location));
        }

        void visit(ast::Parenthesis const& parenthesis) override
        {
            trace("Parenthesis", parenthesis.location);

            result_.setExpression(utility::makeOwned<Parenthesis>(expand(*parenthesis.contained), parenthesis.location));
        }

        void visit(ast::Access const& access) override
        {
            trace("Access", access.location) << ", identifier=" << access.identifier;

            result_.setExpression(utility::makeOwned<Access>(access.identifier, access.location));
        }

        void visit(ast::Here const& here) override
        {
            trace("Here", here.location);

            result_.setExpression(utility::makeOwned<Here>(here.location));
        }

        void visit(ast::UnitLiteral const& unit_literal) override
        {
            trace("UnitLiteral", unit_literal.location);

            result_.setExpression(utility::makeOwned<UnitLiteral>(unit_literal.location));
        }

        void visit(ast::SizeLiteral const& size_literal) override
        {
            trace("SizeLiteral", size_literal.location) << ", value=" << size_literal.value;

            result_.setExpression(utility::makeOwned<SizeLiteral>(size_literal.value, size_literal.location));
        }

        void visit(ast::FloatingPointLiteral const& floating_point_literal) override
        {
            trace("FloatingPointLiteral", floating_point_literal.location)
                << ", precision=" << floating_point_literal.precision << ", value=" << floating_point_literal.value;

            result_.setExpression(
                utility::makeOwned<FloatingPointLiteral>(floating_point_literal.precision, floating_point_literal.value, floating_point_literal.location));
        }

        void visit(ast::StringLiteral const& string_literal) override
        {
            trace("StringLiteral", string_literal.location) << ", value=" << string_literal.value;

            result_.setExpression(utility::makeOwned<StringLiteral>(string_literal.value, string_literal.location));
        }

        void visit(ast::BoolLiteral const& bool_literal) override
        {
            trace("BoolLiteral", bool_literal.location) << ", value=" << bool_literal.value;

            result_.setExpression(utility::makeOwned<BoolLiteral>(bool_literal.value, bool_literal.location));
        }

        void visit(ast::IfExpression const& if_expression) override
        {
            trace("IfExpression", if_expression.location) << ", has_else=" << std::boolalpha << if_expression.else_expression.hasValue();

            EBuilder builder(*this, if_expression.location);

            utility::List<utility::Owned<Expression>> typeof_parameters;
            typeof_parameters.push_back(expand(*if_expression.then_expression));
            if (if_expression.else_expression.hasValue())
            {
                typeof_parameters.push_back(expand(**if_expression.else_expression));
            }
            else
            {
                typeof_parameters.emplace_back(utility::makeOwned<BoolLiteral>(true, if_expression.location));
            }
            utility::Owned<Expression> common_type = utility::makeOwned<TypeOf>(std::move(typeof_parameters), if_expression.location);

            // todo: semantics are actually not correctly implemented because typeof currently evaluates the expressions
            builder.pushAnonymousBindAndSetAsResult(std::move(common_type), core::VariabilityModifier::VARIABLE, core::Assigner::COPY_ASSIGNMENT, std::nullopt);

            utility::Owned<Statement> then_part = builder.createExpansionAssignmentToResult(core::Assigner::COPY_ASSIGNMENT, *if_expression.then_expression);
            utility::Optional<utility::Owned<Statement>> else_part;
            if (if_expression.else_expression.hasValue())
            {
                else_part = builder.createExpansionAssignmentToResult(core::Assigner::COPY_ASSIGNMENT, **if_expression.else_expression);
            }
            else
            {
                // todo: the usage of bool literal is not quite uniform and should be replaced with the unit literal but only if unit has an implcit conversion to bool true
                else_part = builder.createAssignmentToResult(core::Assigner::COPY_ASSIGNMENT, utility::makeOwned<BoolLiteral>(true, if_expression.location));
            }

            builder.pushStatement(
                utility::makeOwned<If>(expand(*if_expression.condition), std::move(then_part), std::move(else_part.value()), if_expression.location));

            result_.setExpression(builder.take());
        }

        void visit(ast::MatchExpression const& match_expression) override
        {
            trace("MatchExpression", match_expression.location) << ", count(cases)=" << match_expression.cases.size();

            EBuilder builder(*this, match_expression.location);

            utility::List<utility::Owned<Expression>> typeof_parameters;
            for (auto const& match_case : match_expression.cases)
            {
                typeof_parameters.push_back(expand(*match_case->result));
            }
            utility::Owned<Expression> common_type = utility::makeOwned<TypeOf>(std::move(typeof_parameters), match_expression.location);

            // todo: semantics are actually not correctly implemented because typeof currently evaluates the expressions
            builder.pushAnonymousBindAndSetAsResult(std::move(common_type), core::VariabilityModifier::VARIABLE, core::Assigner::MOVE_ASSIGNMENT, std::nullopt);

            utility::List<utility::Owned<MatchCase>> cases;
            for (auto const& match_case : match_expression.cases)
            {
                utility::List<utility::Owned<Expression>> patterns;
                for (auto& pattern : match_case->patterns)
                {
                    patterns.emplace_back(expand(*pattern));
                }

                utility::Owned<Statement> body = builder.createExpansionAssignmentToResult(core::Assigner::MOVE_ASSIGNMENT, *match_case->result);
                cases.emplace_back(
                    utility::makeOwned<MatchCase>(std::move(patterns), match_case->default_pattern_location, std::move(body), match_case->location));
            }

            builder.pushStatement(utility::makeOwned<Match>(expand(*match_expression.condition), std::move(cases), match_expression.location));

            result_.setExpression(builder.take());
        }

        void visit(ast::UnaryOperation const& unary_operation) override
        {
            trace("UnaryOperation", unary_operation.location) << ", op=" << unary_operation.op.toString();

            result_.setExpression(utility::makeOwned<UnaryOperation>(unary_operation.op, expand(*unary_operation.operand), unary_operation.location));
        }

        void visit(ast::BinaryOperation const& binary_operation) override
        {
            trace("BinaryOperation", binary_operation.location) << ", op=" << binary_operation.op.toString();

            result_.setExpression(utility::makeOwned<BinaryOperation>(expand(*binary_operation.left),
                                                                      binary_operation.op,
                                                                      expand(*binary_operation.right),
                                                                      binary_operation.location));
        }

        void visit(ast::TypeOf const& type_of) override
        {
            trace("TypeOf", type_of.location) << ", count(expressions)=" << type_of.expressions.size();

            utility::List<utility::Owned<Expression>> expressions;
            for (auto const& expression : type_of.expressions)
            {
                expressions.emplace_back(expand(*expression));
            }

            result_.setExpression(utility::makeOwned<TypeOf>(std::move(expressions), type_of.location));
        }

        void visit(ast::ArrayType const& array_type) override
        {
            trace("ArrayType", array_type.location);

            result_.setExpression(utility::makeOwned<ArrayType>(expand(*array_type.element_type), expand(*array_type.length), array_type.location));
        }

        void visit(ast::ArrayConstructor const& array_constructor) override
        {
            trace("ArrayConstructor", array_constructor.location)
                << ", has_type=" << std::boolalpha << array_constructor.element_type.hasValue() << ", count(elements)=" << array_constructor.elements.size();

            utility::Optional<utility::Owned<Expression>> element_type;
            if (array_constructor.element_type.hasValue())
            {
                element_type = expand(**array_constructor.element_type);
            }

            utility::List<utility::Owned<Expression>> elements;
            for (auto const& element : array_constructor.elements)
            {
                elements.emplace_back(expand(*element));
            }

            result_.setExpression(utility::makeOwned<ArrayConstructor>(std::move(element_type), std::move(elements), array_constructor.location));
        }

        void visit(ast::MatchCase const& match_case) override
        {
            trace("MatchCase", match_case.location) << ", count(patterns)=" << match_case.patterns.size();

            utility::List<utility::Owned<Expression>> patterns;
            for (auto& pattern : match_case.patterns)
            {
                patterns.emplace_back(expand(*pattern));
            }

            utility::Owned<Statement> body = wrap(expand(*match_case.body));

            result_.setMatchCase(utility::makeOwned<MatchCase>(std::move(patterns), match_case.default_pattern_location, std::move(body), match_case.location));
        }

        void visit(ast::MatchExpressionCase const&) override
        {
            // This is handled inside visit(ast::MatchExpression)

            assert(false);
        }

      private:
        // ReSharper disable once CppMemberFunctionMayBeConst
        core::Reporter::MessageBuilder trace(std::string_view const node_name, core::Location const& location)
        {
            auto msg = reporter_.trace(prefix, core::Location::nowhere());
            msg << "visit " << node_name << " " << location;
            return msg;
        }

        core::Reporter& reporter_;
        Result          result_;

        size_t anonymous_function_counter_ = 0;
        size_t anonymous_variable_counter_ = 0;
    };

    utility::Optional<utility::Owned<Statement>> expandOrderedFile(std::filesystem::path const& file)// todo: reduce duplication with below (template)
    {
        reporter_.trace(prefix, core::Location::nowhere()) << "expand ordered file enter {file='" << file.string() << "'}";

        (void) source_tree_;//todo: use or remove

        utility::Optional<utility::Owned<ast::Statement>> parsed = parser_.parseOrderedFile(file);

        if (!parsed.hasValue())
        {
            reporter_.trace(prefix, core::Location::nowhere()) << "expand ordered file exit {file='" << file.string() << "', status=no-parse}";

            return std::nullopt;
        }

        utility::Owned<AST> ast        = utility::makeOwned<AST>(reporter_);
        Statements          statements = ast->expand(**parsed);

        auto block = utility::makeOwned<Block>(std::move(statements), parsed.value()->location);

        context_.print<Printer>(*block, "est", file);

        if (reporter_.isFailed())
        {
            reporter_.trace(prefix, core::Location::nowhere()) << "expand ordered file exit {file='" << file.string() << "', status=fail}";

            return std::nullopt;
        }

        reporter_.trace(prefix, core::Location::nowhere()) << "expand ordered file exit {file='" << file.string() << "', status=ok}";

        return block;
    }

    utility::Optional<utility::Owned<File>> expandUnorderedFile(std::filesystem::path const& file)
    {
        reporter_.trace(prefix, core::Location::nowhere()) << "expand unordered file enter {file='" << file.string() << "'}";

        utility::Optional<utility::Owned<ast::File>> parsed = parser_.parseUnorderedFile(file);
        if (!parsed.hasValue())
        {
            reporter_.trace(prefix, core::Location::nowhere()) << "expand unordered file exit {file='" << file.string() << "', status=no-parse}";

            return std::nullopt;
        }

        utility::Owned<AST>  ast = utility::makeOwned<AST>(reporter_);
        utility::Owned<File> est = ast->expand(**parsed);

        context_.print<Printer>(*est, "est", file);

        if (reporter_.isFailed())
        {
            reporter_.trace(prefix, core::Location::nowhere()) << "expand unordered file exit {file='" << file.string() << "', status=fail}";

            return std::nullopt;
        }

        reporter_.trace(prefix, core::Location::nowhere()) << "expand unordered file exit {file='" << file.string() << "', status=ok}";

        return est;
    }

    utility::Optional<utility::Owned<Declaration>> expandDeclaration(std::string const& code, std::string const& id)
    {
        reporter_.trace(prefix, core::Location::nowhere()) << "expand declaration enter {id=" << id << ", code_size=" << code.size() << "}";

        utility::Optional<utility::Owned<ast::Declaration>> parsed = parser_.parseDeclaration(code, id);
        if (!parsed.hasValue())
        {
            reporter_.trace(prefix, core::Location::nowhere()) << "expand declaration exit {id=" << id << ", status=no-parse}";

            return std::nullopt;
        }

        utility::Owned<AST>         ast         = utility::makeOwned<AST>(reporter_);
        utility::Owned<Declaration> declaration = ast->expand(**parsed);

        context_.print<Printer>(*declaration, "est", std::filesystem::path("core") / id);

        if (reporter_.isFailed())
        {
            reporter_.trace(prefix, core::Location::nowhere()) << "expand declaration exit {id=" << id << ", status=fail}";

            return std::nullopt;
        }

        reporter_.trace(prefix, core::Location::nowhere()) << "expand declaration exit {id=" << id << ", status=ok}";

        return declaration;
    }

  private:
    sources::SourceTree& source_tree_;
    core::Reporter&      reporter_;
    ast::Parser          parser_;
    core::Context&       context_;
};

ance::est::Expander::Expander(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context)
    : implementation_(utility::makeOwned<Implementation>(source_tree, reporter, context))
{}

ance::est::Expander::~Expander() = default;

ance::utility::Optional<ance::utility::Owned<ance::est::Statement>> ance::est::Expander::expandOrderedFile(std::filesystem::path const& file)
{
    return implementation_->expandOrderedFile(file);
}

ance::utility::Optional<ance::utility::Owned<ance::est::File>> ance::est::Expander::expandUnorderedFile(std::filesystem::path const& file)
{
    return implementation_->expandUnorderedFile(file);
}

ance::utility::Optional<ance::utility::Owned<ance::est::Declaration>> ance::est::Expander::expandDeclaration(std::string const& code, std::string const& id)
{
    return implementation_->expandDeclaration(code, id);
}
