#include "Expander.h"

#include <variant>

#include "ance/core/Constants.h"

#include "ance/ast/Node.h"
#include "ance/ast/Parser.h"

#include "ance/est/Node.h"
#include "ance/est/Printer.h"

struct ance::est::Expander::Implementation
{
    explicit Implementation(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context)
        : source_tree_(source_tree)
        , reporter_(reporter)
        , parser_(source_tree, reporter, context)
        , context_(context)
    {}

    using Statements = utility::List<utility::Owned<Statement>>;

    struct Expansion
    {
        Statements                 before;
        utility::Owned<Expression> center;
        Statements                 after;
    };

    struct ParameterExpansion
    {
        Expansion        expansion;
        core::Identifier identifier;
    };

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

        void setExpression(Expansion expansion)
        {
            setResult(std::move(expansion));
        }

        void setExpression(utility::Owned<Expression> expression)
        {
            Expansion expansion = {.before = {}, .center = std::move(expression), .after = {}};
            setResult(std::move(expansion));
        }

        void setParameter(ParameterExpansion parameter_expansion)
        {
            setResult(std::move(parameter_expansion));
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
        using ResultVariant = std::variant<utility::Owned<File>, utility::Owned<Declaration>, Statements, Expansion, ParameterExpansion>;

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

            [[nodiscard]] utility::Owned<Expression> pushExpansion(ast::Expression const& expression)
            {
                Expansion expansion = ast_.expand(expression);

                append(statements_, std::move(expansion.before));
                cleanup_statements_.emplace_back(std::move(expansion.after));

                return std::move(expansion.center);
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

            /// Creates an anonymous local variable and returns its identifier.
            /// When using this, do not forget to wrap the expansion in a block so the variable is cleaned up after use.
            core::Identifier pushAnonymousLet(utility::Owned<Expression>                    type,
                                              core::Assigner                                assigner,
                                              utility::Optional<utility::Owned<Expression>> definition,
                                              core::Location const&                         location)
            {
                std::string const id         = std::format("_anonymous'{}", ast_.anonymous_variable_counter_++);
                core::Identifier  identifier = core::Identifier::make(id, location);

                statements_.emplace_back(utility::makeOwned<Let>(identifier, std::move(type), assigner, std::move(definition), location));

                return identifier;
            }

            Statements&& take()
            {
                for (size_t index = cleanup_statements_.size(); index > 0; index--)
                {
                    append(statements_, std::move(cleanup_statements_[index - 1]));
                }

                cleanup_statements_.clear();

                return std::move(statements_);
            }

            void reset()
            {
                statements_.clear();
                cleanup_statements_.clear();
            }

          private:
            AST& ast_;

            Statements                statements_;
            utility::List<Statements> cleanup_statements_;
        };

        class EBuilder final
        {
          public:
            explicit EBuilder(AST& ast) : ast_(ast) {}

            [[nodiscard]] utility::Owned<Expression> pushExpansion(ast::Expression const& expression)
            {
                Expansion expansion = ast_.expand(expression);

                append(before_, std::move(expansion.before));
                after_.emplace_back(std::move(expansion.after));

                return std::move(expansion.center);
            }

            [[nodiscard]] Parameter pushParameterExpansion(ast::Parameter const& parameter)
            {
                Expansion expansion = ast_.expand(*parameter.type);

                append(before_, std::move(expansion.before));
                after_.emplace_back(std::move(expansion.after));

                return {parameter.identifier, std::move(expansion.center), parameter.location};
            }

            Expansion take(utility::Owned<Expression> expression)
            {
                Statements after;
                for (size_t index = after_.size(); index > 0; index--)
                {
                    append(after, std::move(after_[index - 1]));
                }

                Expansion expansion = {
                    .before = std::move(before_),
                    .center = std::move(expression),
                    .after  = std::move(after),
                };

                before_.clear();
                after_.clear();

                return expansion;
            }

          private:
            AST& ast_;

            Statements                before_;
            utility::List<Statements> after_;
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

        Expansion expand(ast::Expression const& expression)
        {
            result_.reset();
            visit(expression);
            return result_.take<Expansion>();
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
            utility::List<utility::Owned<Declaration>> declarations;

            for (auto const& declaration : file.declarations)
            {
                declarations.emplace_back(expand(*declaration));
            }

            result_.setFile(utility::makeOwned<File>(std::move(declarations), file.location));
        }

        void visit(ast::ErrorDeclaration const& error) override
        {
            result_.setDeclaration(utility::makeOwned<RunnableDeclaration>(utility::makeOwned<ErrorStatement>(error.location), error.location));
        }

        void visit(ast::RunnableDeclaration const& runnable) override
        {
            result_.setDeclaration(utility::makeOwned<RunnableDeclaration>(wrap(expand(*runnable.body)), runnable.location));
        }

        void visit(ast::VariableDeclaration const& variable_declaration) override
        {
            utility::Owned<Expression> type = expand(*variable_declaration.type).center;

            utility::Optional<utility::Owned<Expression>> value = std::nullopt;
            if (variable_declaration.value.hasValue())
            {
                value = expand(**variable_declaration.value).center;
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
            utility::List<Parameter> parameters;
            for (auto const& parameter : function_declaration.parameters)
            {
                utility::Owned<Expression> param_type = expand(*parameter.type).center;
                parameters.emplace_back(parameter.identifier, std::move(param_type), parameter.location);
            }

            utility::Owned<Expression> return_type =
                function_declaration.return_type.hasValue()
                    ? expand(**function_declaration.return_type).center
                    : expand(ast::Access(core::Identifier::make(core::UNIT_TYPE_NAME, core::Location::core()), function_declaration.location)).center;

            SBuilder body_builder(*this);
            body_builder.pushExpansion(*function_declaration.body);
            utility::Owned<Statement> body = wrap(body_builder.take());

            // todo: as soon as we have custom types, we would need this access here to be in the global scope, e.g. a global:: prefix
            // todo: or as long as that is not done, just a new type of expression that contains an enum of important types
            // todo: and the same for the Unit type above - remove that constants file to find all places
            utility::Owned<Expression> function_type =
                expand(ast::Access(core::Identifier::make(core::FUNCTION_TYPE_NAME, core::Location::core()), function_declaration.location)).center;

            utility::Owned<Expression> function_value = utility::makeOwned<FunctionConstructor>(function_declaration.identifier,
                                                                                                std::move(parameters),
                                                                                                std::move(return_type),
                                                                                                std::move(body),
                                                                                                function_declaration.location);

            result_.setDeclaration(utility::makeOwned<VariableDeclaration>(function_declaration.access_modifier,
                                                                           function_declaration.execution_modifier,
                                                                           function_declaration.identifier,
                                                                           std::move(function_type),
                                                                           core::Assigner::FINAL_COPY_ASSIGNMENT,// todo: should be final move
                                                                           std::move(function_value),
                                                                           function_declaration.location));
        }

        void visit(ast::ErrorStatement const& error_statement) override
        {
            result_.setStatements(utility::makeOwned<ErrorStatement>(error_statement.location));
        }

        void visit(ast::Block const& block) override
        {
            SBuilder builder(*this);

            for (auto& statement : block.statements)
            {
                builder.pushExpansion(*statement);
            }

            result_.setStatements(utility::makeOwned<Block>(builder.take(), block.location));
        }

        void visit(ast::Independent const& independent) override
        {
            SBuilder builder(*this);

            utility::Owned<Expression> expression = builder.pushExpansion(*independent.expression);
            builder.pushStatement(utility::makeOwned<Independent>(std::move(expression), independent.location));

            result_.setStatements(builder.take());
        }

        void visit(ast::Let const& let) override
        {
            SBuilder builder(*this);

            utility::Owned<Expression> type = builder.pushExpansion(*let.type);

            utility::Optional<utility::Owned<Expression>> value = std::nullopt;
            if (let.value.hasValue())
            {
                value = builder.pushExpansion(**let.value);
            }

            builder.pushStatement(utility::makeOwned<Let>(let.identifier, std::move(type), let.assigner, std::move(value), let.location));

            result_.setStatements(builder.take());
        }

        void visit(ast::Assignment const& assignment) override
        {
            SBuilder builder(*this);

            utility::Owned<Expression> assignee = builder.pushExpansion(*assignment.assignee);
            utility::Owned<Expression> value    = builder.pushExpansion(*assignment.value);

            builder.pushStatement(utility::makeOwned<Write>(std::move(assignee), std::move(value), assignment.location));

            result_.setStatements(builder.take());
        }

        void visit(ast::If const& if_statement) override
        {
            SBuilder builder(*this);

            utility::Owned<Expression> condition = builder.pushExpansion(*if_statement.condition);

            Statements true_statements  = expand(*if_statement.true_part);
            Statements false_statements = if_statement.false_part.hasValue() ? expand(**if_statement.false_part) : Statements();

            builder.pushStatement(
                utility::makeOwned<If>(std::move(condition), wrap(std::move(true_statements)), wrap(std::move(false_statements)), if_statement.location));

            result_.setStatements(builder.take());
        }

        void visit(ast::Loop const& loop) override
        {
            result_.setStatements(utility::makeOwned<Loop>(wrap(expand(*loop.body)), loop.location));
        }

        void visit(ast::Break const& break_statement) override
        {
            result_.setStatements(utility::makeOwned<Break>(break_statement.location));
        }

        void visit(ast::Continue const& continue_statement) override
        {
            result_.setStatements(utility::makeOwned<Continue>(continue_statement.location));
        }

        void visit(ast::Return const& return_statement) override
        {
            SBuilder builder(*this);

            utility::Optional<utility::Owned<Expression>> return_value = std::nullopt;

            if (return_statement.value.hasValue())
            {
                return_value = builder.pushExpansion(**return_statement.value);
            }

            builder.pushStatement(utility::makeOwned<Return>(std::move(return_value), return_statement.location));

            result_.setStatements(builder.take());
        }

        void visit(ast::While const& while_statement) override
        {
            SBuilder builder(*this);

            utility::Owned<Expression> condition = builder.pushExpansion(*while_statement.condition);

            builder.pushStatement(
                utility::makeOwned<If>(utility::makeOwned<UnaryOperation>(core::UnaryOperator::NOT, std::move(condition), while_statement.condition->location),
                                       utility::makeOwned<Break>(while_statement.location),
                                       utility::makeOwned<Pass>(while_statement.location),
                                       while_statement.location));

            builder.pushExpansion(*while_statement.body);

            result_.setStatements(utility::makeOwned<Loop>(wrap(builder.take()), while_statement.location));
        }

        void visit(ast::Erase const& erase) override
        {
            result_.setStatements(utility::makeOwned<Erase>(erase.identifier, erase.location));
        }

        void visit(ast::ErrorExpression const& error_expression) override
        {
            result_.setExpression(utility::makeOwned<ErrorExpression>(error_expression.location));
        }

        void visit(ast::Call const& call) override
        {
            EBuilder builder(*this);

            utility::Owned<Expression> callee = builder.pushExpansion(*call.callee);

            utility::List<utility::Owned<Expression>> arguments;
            for (auto& argument : call.arguments)
            {
                arguments.emplace_back(builder.pushExpansion(*argument));
            }

            result_.setExpression(builder.take(utility::makeOwned<Call>(std::move(callee), std::move(arguments), call.location)));
        }

        void visit(ast::Lambda const& lambda) override
        {
            EBuilder builder(*this);

            utility::List<Parameter> parameters;
            for (auto& parameter : lambda.parameters)
            {
                parameters.emplace_back(builder.pushParameterExpansion(parameter));
            }

            utility::Optional<utility::Owned<Expression>> return_type;
            if (lambda.return_type.hasValue())
            {
                return_type = builder.pushExpansion(**lambda.return_type);
            }
            else
            {
                // todo: as soon as we have custom types, we would need this access here to be in the global scope, e.g. a global:: prefix
                // todo: or as long as that is not done, just a new type of expression that contains an enum of important types
                // todo: and the same for the Function type above in function declaration - remove that constants file to find all places
                return_type = builder.pushExpansion(ast::Access(core::Identifier::make(core::UNIT_TYPE_NAME, core::Location::core()), lambda.location));
            }

            SBuilder body_builder(*this);

            if (lambda.expression_body.hasValue())
            {
                utility::Owned<Expression> expression = builder.pushExpansion(**lambda.expression_body);
                body_builder.pushStatement(utility::makeOwned<Return>(std::move(expression), lambda.location));
            }
            else
            {
                body_builder.pushExpansion(**lambda.statement_body);
            }

            utility::Owned<Statement> body = wrap(body_builder.take());

            std::string const name = std::format("Lambda'{}", anonymous_function_counter_++);

            result_.setExpression(builder.take(utility::makeOwned<FunctionConstructor>(core::Identifier::make(name, lambda.location),
                                                                                       std::move(parameters),
                                                                                       std::move(return_type.value()),
                                                                                       std::move(body),
                                                                                       lambda.location)));
        }

        void visit(ast::Intrinsic const& intrinsic_expression) override
        {
            EBuilder builder(*this);

            utility::Owned<Expression> name = builder.pushExpansion(*intrinsic_expression.name);

            utility::List<utility::Owned<Expression>> arguments;
            for (auto& argument : intrinsic_expression.arguments)
            {
                arguments.emplace_back(builder.pushExpansion(*argument));
            }

            result_.setExpression(builder.take(utility::makeOwned<Intrinsic>(std::move(name), std::move(arguments), intrinsic_expression.location)));
        }

        void visit(ast::BlockExpression const& block_expression) override
        {
            SBuilder builder(*this);

            for (auto& statement : block_expression.statements)
            {
                builder.pushExpansion(*statement);
            }

            utility::Optional<utility::Owned<Expression>> result;
            if (block_expression.result.hasValue())
            {
                // todo: SBuilder stores expression cleanup in take(); for block expressions this can run cleanup before the result is evaluated in Segmenter.
                // todo: when expansion is reworked, ensure the result expression's cleanup executes after the result expression, not before.
                result = builder.pushExpansion(**block_expression.result);
            }
            else
            {
                result = utility::makeOwned<UnitLiteral>(block_expression.location);
            }

            result_.setExpression(utility::makeOwned<BlockExpression>(builder.take(), std::move(result.value()), block_expression.location));
        }

        void visit(ast::Access const& access) override
        {
            result_.setExpression(utility::makeOwned<Access>(access.identifier, access.location));
        }

        void visit(ast::Here const& here) override
        {
            result_.setExpression(utility::makeOwned<Here>(here.location));
        }

        void visit(ast::UnitLiteral const& unit_literal) override
        {
            result_.setExpression(utility::makeOwned<UnitLiteral>(unit_literal.location));
        }

        void visit(ast::SizeLiteral const& size_literal) override
        {
            result_.setExpression(utility::makeOwned<SizeLiteral>(size_literal.value, size_literal.location));
        }

        void visit(ast::StringLiteral const& string_literal) override
        {
            result_.setExpression(utility::makeOwned<StringLiteral>(string_literal.value, string_literal.location));
        }

        void visit(ast::BoolLiteral const& bool_literal) override
        {
            result_.setExpression(utility::makeOwned<BoolLiteral>(bool_literal.value, bool_literal.location));
        }

        void visit(ast::UnaryOperation const& unary_operation) override
        {
            EBuilder builder(*this);

            utility::Owned<Expression> operand = builder.pushExpansion(*unary_operation.operand);

            result_.setExpression(builder.take(utility::makeOwned<UnaryOperation>(unary_operation.op, std::move(operand), unary_operation.location)));
        }

      private:
        core::Reporter& reporter_;
        Result          result_;

        size_t anonymous_function_counter_ = 0;
        size_t anonymous_variable_counter_ = 0;
    };

    utility::Optional<utility::Owned<Statement>> expandOrderedFile(std::filesystem::path const& file)// todo: reduce duplication with below (template)
    {
        (void) source_tree_;//todo: use or remove

        utility::Optional<utility::Owned<ast::Statement>> parsed = parser_.parseOrderedFile(file);
        if (!parsed.hasValue()) return std::nullopt;

        utility::Owned<AST> ast        = utility::makeOwned<AST>(reporter_);
        Statements          statements = ast->expand(**parsed);

        auto block = utility::makeOwned<Block>(std::move(statements), parsed.value()->location);

        context_.print<Printer>(*block, "est", file);

        if (reporter_.isFailed()) return std::nullopt;

        return block;
    }

    utility::Optional<utility::Owned<File>> expandUnorderedFile(std::filesystem::path const& file)
    {
        utility::Optional<utility::Owned<ast::File>> parsed = parser_.parseUnorderedFile(file);
        if (!parsed.hasValue()) return std::nullopt;

        utility::Owned<AST>  ast = utility::makeOwned<AST>(reporter_);
        utility::Owned<File> est = ast->expand(**parsed);

        context_.print<Printer>(*est, "est", file);

        if (reporter_.isFailed()) return std::nullopt;

        return est;
    }

    utility::Optional<utility::Owned<Declaration>> expandDeclaration(std::string const& code, std::string const& id)
    {
        utility::Optional<utility::Owned<ast::Declaration>> parsed = parser_.parseDeclaration(code, id);
        if (!parsed.hasValue()) return std::nullopt;

        utility::Owned<AST>         ast         = utility::makeOwned<AST>(reporter_);
        utility::Owned<Declaration> declaration = ast->expand(**parsed);

        context_.print<Printer>(*declaration, "est", std::filesystem::path("core") / id);

        if (reporter_.isFailed()) return std::nullopt;

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
