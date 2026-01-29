#include "Expander.h"

#include <map>
#include <variant>

#include "ance/core/Intrinsic.h"

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

        void setDeclaration(DeclarationStatement declaration_statement)
        {
            setResult(std::move(declaration_statement));
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

        void setExpression(Expansion expansion)
        {
            setResult(std::move(expansion));
        }

        void setExpression(utility::Owned<Expression> expression)
        {
            Expansion expansion = {.before = {}, .center = std::move(expression), .after = {}};
            setResult(std::move(expansion));
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
        using ResultVariant = std::variant<utility::Owned<File>, DeclarationStatement, Statements, Expansion>;

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

            Temporary const& pushTemporary(utility::Optional<utility::Owned<Expression>> definition, std::string id, core::Location const& location)
            {
                size_t&     counter      = ast_.temporary_name_counters_[id];
                std::string temporary_id = std::format("{}'{}", id, counter++);

                utility::Owned<Temporary> temporary = utility::makeOwned<Temporary>(std::move(definition), std::move(temporary_id), location);
                Temporary const&          tmp       = *temporary;
                statements_.emplace_back(std::move(temporary));
                return tmp;
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

        DeclarationStatement expand(ast::Declaration const& declaration)
        {
            result_.reset();
            temporary_name_counters_.clear();

            visit(declaration);

            return result_.take<DeclarationStatement>();
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

        template<typename... Args>
        static utility::Owned<Expression> intrinsic(core::Intrinsic const& called, core::Location const& source_location, Args&&... args)
        {
            utility::List<utility::Owned<Expression>> arguments;
            (arguments.emplace_back(std::forward<Args>(args)), ...);
            return utility::makeOwned<Intrinsic>(called, std::move(arguments), source_location);
        }

        static utility::Owned<Statement> wrap(Statements&& statements)
        {
            if (statements.empty())
            {
                return utility::makeOwned<Pass>(core::Location::global());
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
            utility::List<DeclarationStatement> declaration_statements;

            for (auto const& declaration : file.declarations)
            {
                DeclarationStatement expanded = expand(*declaration);
                declaration_statements.emplace_back(std::move(expanded));
            }

            result_.setFile(utility::makeOwned<File>(std::move(declaration_statements), file.location));
        }

        void visit(ast::ErrorDeclaration const& error) override
        {
            result_.setDeclaration({
                .statement = utility::makeOwned<ErrorStatement>(error.location),
                .name      = "ErrorDeclaration",
            });
        }

        void visit(ast::RunnableDeclaration const& runnable) override
        {
            result_.setDeclaration({
                .statement = wrap(expand(*runnable.body)),
                .name      = "RunnableDeclaration",
            });
        }

        void visit(ast::VariableDeclaration const& variable_declaration) override
        {
            SBuilder builder(*this);

            utility::Owned<Expression> type = builder.pushExpansion(*variable_declaration.type);

            utility::Owned<Expression> parent_scope =
                intrinsic(core::Intrinsic::GET_PARENT, variable_declaration.location, utility::makeOwned<CurrentScope>(variable_declaration.location));

            Temporary const& tmp_type = builder.pushTemporary(std::move(type), "VariableDeclaration_Type", variable_declaration.location);

            // We need to go through the initializer expression first, otherwise the name would already be declared.
            // If we then yield in the initializer other run points could access the undefined variable.

            Temporary const* initial_value;

            if (variable_declaration.value.hasValue())
            {
                utility::Owned<Expression> value = builder.pushExpansion(**variable_declaration.value);
                initial_value                    = &builder.pushTemporary(std::move(value), "VariableDeclaration_InitialValue", variable_declaration.location);
            }
            else
            {
                initial_value = &builder.pushTemporary(
                    utility::makeOwned<Default>(utility::makeOwned<ReadTemporary>(tmp_type, variable_declaration.location), variable_declaration.location),
                    "VariableDeclaration_DefaultValue",
                    variable_declaration.location);
            }

            utility::Owned<Expression> declared_expression =
                intrinsic(core::Intrinsic::DECLARE,
                          variable_declaration.location,
                          std::move(parent_scope),
                          utility::makeOwned<IdentifierCapture>(variable_declaration.identifier, variable_declaration.location),
                          utility::makeOwned<BoolLiteral>(variable_declaration.assigner.isFinal(), variable_declaration.location),
                          utility::makeOwned<ReadTemporary>(tmp_type, variable_declaration.location));

            Temporary const& declared =
                builder.pushTemporary(std::move(declared_expression), "VariableDeclaration_DefaultValue", variable_declaration.location);

            builder.pushStatement(utility::makeOwned<Write>(utility::makeOwned<ReadTemporary>(declared, variable_declaration.location),
                                                            utility::makeOwned<ReadTemporary>(*initial_value, variable_declaration.location),
                                                            variable_declaration.location));

            result_.setDeclaration({
                .statement = wrap(builder.take()),
                .name      = std::format("VariableDeclaration({})", variable_declaration.identifier.text()),
            });
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

            utility::Owned<Expression> type_expression = builder.pushExpansion(*let.type);
            Temporary const&           type            = builder.pushTemporary(std::move(type_expression), "Let_Type", let.location);

            Temporary const* initial_value;

            if (let.value.hasValue())
            {
                utility::Owned<Expression> value = builder.pushExpansion(**let.value);
                initial_value                    = &builder.pushTemporary(std::move(value), "Let_InitialValue", let.location);
            }
            else
            {
                initial_value = &builder.pushTemporary(utility::makeOwned<Default>(utility::makeOwned<ReadTemporary>(type, let.location), let.location),
                                                       "Let_DefaultValue",
                                                       let.location);
            }

            utility::Owned<Expression> declared_expression = intrinsic(core::Intrinsic::DECLARE,
                                                                       let.location,
                                                                       utility::makeOwned<CurrentScope>(let.location),
                                                                       utility::makeOwned<IdentifierCapture>(let.identifier, let.location),
                                                                       utility::makeOwned<BoolLiteral>(let.assigner.isFinal(), let.location),
                                                                       utility::makeOwned<ReadTemporary>(type, let.location));

            Temporary const& declared = builder.pushTemporary(std::move(declared_expression), "Let_Declared", let.location);

            builder.pushStatement(utility::makeOwned<Write>(utility::makeOwned<ReadTemporary>(declared, let.location),
                                                            utility::makeOwned<ReadTemporary>(*initial_value, let.location),
                                                            let.location));

            result_.setStatements(builder.take());
        }

        void visit(ast::Assignment const& assignment) override
        {
            SBuilder builder(*this);

            utility::Owned<Expression> value = builder.pushExpansion(*assignment.value);

            utility::Owned<Expression> resolved_expression = intrinsic(core::Intrinsic::RESOLVE,
                                                                       assignment.location,
                                                                       utility::makeOwned<CurrentScope>(assignment.location),
                                                                       utility::makeOwned<IdentifierCapture>(assignment.identifier, assignment.location));

            Temporary const& resolved = builder.pushTemporary(std::move(resolved_expression), "Assignment_Resolved", assignment.location);

            builder.pushStatement(
                utility::makeOwned<Write>(utility::makeOwned<ReadTemporary>(resolved, assignment.location), std::move(value), assignment.location));

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

            if (return_statement.value.hasValue())
            {
                utility::Owned<Expression> value = builder.pushExpansion(**return_statement.value);
                builder.pushStatement(utility::makeOwned<Return>(std::move(value), return_statement.location));
            }
            else
            {
                builder.pushStatement(utility::makeOwned<Return>(std::nullopt, return_statement.location));
            }

            result_.setStatements(builder.take());
        }

        void visit(ast::While const& while_statement) override
        {
            SBuilder builder(*this);

            {
                SBuilder exit_builder(*this);

                utility::Owned<Expression> condition_expression = exit_builder.pushExpansion(*while_statement.condition);
                Temporary const&           condition = exit_builder.pushTemporary(std::move(condition_expression), "While_Condition", while_statement.location);

                exit_builder.pushStatement(
                    utility::makeOwned<If>(utility::makeOwned<UnaryOperation>(core::UnaryOperator::NOT,
                                                                              utility::makeOwned<ReadTemporary>(condition, while_statement.condition->location),
                                                                              while_statement.location),
                                           utility::makeOwned<Break>(while_statement.location),
                                           utility::makeOwned<Pass>(while_statement.location),
                                           while_statement.location));

                builder.pushStatement(utility::makeOwned<Block>(exit_builder.take(), while_statement.location));
            }

            builder.pushExpansion(*while_statement.body);

            result_.setStatements(utility::makeOwned<Loop>(wrap(builder.take()), while_statement.location));
        }

        void visit(ast::ErrorExpression const& error_expression) override
        {
            result_.setExpression(utility::makeOwned<ErrorExpression>(error_expression.location));
        }

        void visit(ast::Call const& call) override
        {
            EBuilder builder(*this);

            utility::List<utility::Owned<Expression>> arguments;
            for (auto& argument : call.arguments)
            {
                arguments.emplace_back(builder.pushExpansion(*argument));
            }

            utility::Owned<Expression> resolved = intrinsic(core::Intrinsic::RESOLVE,
                                                            call.location,
                                                            utility::makeOwned<CurrentScope>(call.location),
                                                            utility::makeOwned<IdentifierCapture>(call.identifier, call.location));

            result_.setExpression(builder.take(
                utility::makeOwned<Call>(utility::makeOwned<Read>(std::move(resolved), call.identifier.location()), std::move(arguments), call.location)));
        }

        void visit(ast::Access const& access) override
        {
            utility::Owned<Expression> resolved = intrinsic(core::Intrinsic::RESOLVE,
                                                            access.location,
                                                            utility::makeOwned<CurrentScope>(access.location),
                                                            utility::makeOwned<IdentifierCapture>(access.identifier, access.location));

            result_.setExpression(utility::makeOwned<Read>(std::move(resolved), access.location));
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

        std::map<std::string, size_t> temporary_name_counters_;
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
