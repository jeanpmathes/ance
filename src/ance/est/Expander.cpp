#include "Expander.h"

#include "ance/ast/Node.h"
#include "ance/ast/Parser.h"
#include "ance/est/Node.h"

#include "Printer.h"

struct ance::est::Expander::Implementation
{
    explicit Implementation(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context)
        : source_tree_(source_tree), reporter_(reporter), parser_(source_tree, reporter, context), context_(context)
    {}

    using Statements = utility::List<utility::Owned<Statement>>;

    struct Expansion
    {
        Statements                 before;
        utility::Owned<Expression> center;
        Statements                 after;
    };

    class AST final : public ast::Visitor
    {
      public:
        using Visitor::visit;

        explicit AST(core::Reporter& reporter) : reporter_(reporter) {}
        ~AST() override = default;

        void setResult(utility::Owned<File> file)
        {
            assert(!file_expansion_.hasValue() && !statement_expansion_.hasValue() && !expression_expansion_.hasValue());

            file_expansion_ = std::move(file);
            statement_expansion_  = std::nullopt;
            expression_expansion_ = std::nullopt;
        }

        void setResult(utility::Owned<Statement> statement)
        {
            assert(!file_expansion_.hasValue() && !statement_expansion_.hasValue() && !expression_expansion_.hasValue());

            Statements statements;
            statements.emplace_back(std::move(statement));

            file_expansion_ = std::nullopt;
            statement_expansion_  = std::move(statements);
            expression_expansion_ = std::nullopt;
        }

        void setResult(Statements statements)
        {
            assert(!file_expansion_.hasValue() && !statement_expansion_.hasValue() && !expression_expansion_.hasValue());

            file_expansion_ = std::nullopt;
            statement_expansion_  = std::move(statements);
            expression_expansion_ = std::nullopt;
        }

        void setResult(utility::Owned<Expression> expression)
        {
            assert(!file_expansion_.hasValue() && !statement_expansion_.hasValue() && !expression_expansion_.hasValue());

            file_expansion_ = std::nullopt;
            statement_expansion_  = std::nullopt;
            expression_expansion_ = {.before = {}, .center = std::move(expression), .after = {}};
        }

        void setResult(Expansion expansion)
        {
            assert(!file_expansion_.hasValue() && !statement_expansion_.hasValue() && !expression_expansion_.hasValue());

            file_expansion_ = std::nullopt;
            statement_expansion_  = std::nullopt;
            expression_expansion_ = std::move(expansion);
        }

        utility::Owned<File> expand(ast::File const& file)
        {
            visit(file);

            assert(file_expansion_.hasValue());

            utility::Owned<File> result = std::move(*file_expansion_);
            file_expansion_            = std::nullopt;

            return result;
        }

        Statements expand(ast::Statement const& statement)
        {
            visit(statement);

            (void) reporter_;//todo: use reporter or remove from expander at some point

            assert(statement_expansion_.hasValue());

            Statements result    = std::move(*statement_expansion_);
            statement_expansion_ = std::nullopt;

            return result;
        }

        Expansion expand(ast::Expression const& expression)
        {
            visit(expression);

            assert(expression_expansion_.hasValue());

            Expansion result      = std::move(*expression_expansion_);
            expression_expansion_ = std::nullopt;

            return result;
        }

        static void append(Statements& target, Statements&& source)
        {
            target.insert(target.end(), make_move_iterator(source.begin()), make_move_iterator(source.end()));
        }

        static utility::Owned<Statement> wrap(Statements&& statements)
        {
            if (statements.empty()) { return utility::makeOwned<Pass>(core::Location::global()); }

            if (statements.size() == 1 && statements.front()->isCompound())
            {
                return std::move(statements.front());
            }

            core::Location location = statements.front()->location;

            for (auto& statement : statements) { location.extend(statement->location); }

            return utility::makeOwned<Block>(std::move(statements), location);
        }

        void visit(ast::File const& file) override
        {
            setResult(utility::makeOwned<File>(file.location));
        }

        void visit(ast::ErrorStatement const& error_statement) override
        {
            setResult(utility::makeOwned<ErrorStatement>(error_statement.location));
        }

        void visit(ast::Block const& block) override
        {
            Statements statements;

            for (auto& statement : block.statements)
            {
                Statements expanded = expand(*statement);
                append(statements, std::move(expanded));
            }

            setResult(utility::makeOwned<Block>(std::move(statements), block.location));
        }

        void visit(ast::Independent const& independent) override
        {
            Statements statements;

            Expansion expansion = expand(*independent.expression);

            append(statements, std::move(expansion.before));
            statements.emplace_back(utility::makeOwned<Independent>(std::move(expansion.center), independent.location));
            append(statements, std::move(expansion.after));

            setResult(std::move(statements));
        }

        void visit(ast::Let const& let) override
        {
            Statements statements;

            Expansion type_expansion = expand(*let.type);

            append(statements, std::move(type_expansion.before));

            utility::List<utility::Owned<Expression>> declare_arguments;
            declare_arguments.emplace_back(utility::makeOwned<CurrentScope>(let.location));
            declare_arguments.emplace_back(utility::makeOwned<IdentifierCapture>(let.identifier, let.location));
            declare_arguments.emplace_back(std::move(type_expansion.center));
            utility::Owned<Temporary> temporary_entity = utility::makeOwned<Temporary>(utility::makeOwned<Intrinsic>(core::Declare::instance(), std::move(declare_arguments), let.location), let.location); // todo: the core::Declare feels kinda ugly because it does not show it to be an intrinsic
            Temporary const& tmp_entity = *temporary_entity;
            statements.emplace_back(std::move(temporary_entity));

            Statements                                    after;

            if (let.value.hasValue())
            {
                Expansion expansion = expand(**let.value);

                append(statements, std::move(expansion.before));

                statements.emplace_back(utility::makeOwned<Write>(utility::makeOwned<ReadTemporary>(tmp_entity, let.location), std::move(expansion.center), let.location));

                after = std::move(expansion.after);
            }

            append(statements, std::move(after));
            append(statements, std::move(type_expansion.after));

            setResult(std::move(statements));
        }

        void visit(ast::Assignment const& assignment) override
        {
            Statements statements;

            Expansion expansion = expand(*assignment.value);

            append(statements, std::move(expansion.before));

            utility::List<utility::Owned<Expression>> resolve_arguments;
            resolve_arguments.emplace_back(utility::makeOwned<CurrentScope>(assignment.location));
            resolve_arguments.emplace_back(utility::makeOwned<IdentifierCapture>(assignment.identifier, assignment.location));
            utility::Owned<Temporary> temporary_entity = utility::makeOwned<Temporary>(utility::makeOwned<Intrinsic>(core::Resolve::instance(), std::move(resolve_arguments), assignment.location), assignment.location);
            Temporary const& tmp_entity = *temporary_entity;
            statements.emplace_back(std::move(temporary_entity));

            statements.emplace_back(utility::makeOwned<Write>(utility::makeOwned<ReadTemporary>(tmp_entity, assignment.location), std::move(expansion.center), assignment.location));

            append(statements, std::move(expansion.after));

            setResult(std::move(statements));
        }

        void visit(ast::If const& if_statement) override
        {
            Statements statements;

            Expansion condition_expansion = expand(*if_statement.condition);
            append(statements, std::move(condition_expansion.before));

            Statements true_statements  = expand(*if_statement.true_part);
            Statements false_statements = if_statement.false_part.hasValue() ? expand(**if_statement.false_part) : Statements();

            statements.emplace_back(utility::makeOwned<If>(std::move(condition_expansion.center),
                                                           wrap(std::move(true_statements)),
                                                           wrap(std::move(false_statements)),
                                                           if_statement.location));

            append(statements, std::move(condition_expansion.after));

            setResult(std::move(statements));
        }

        void visit(ast::Loop const& loop) override
        {
            Statements statements;

            Statements block = expand(*loop.body);
            statements.emplace_back(utility::makeOwned<Loop>(wrap(std::move(block)), loop.location));

            setResult(std::move(statements));
        }

        void visit(ast::Break const& break_statement) override
        {
            Statements statements;
            statements.emplace_back(utility::makeOwned<Break>(break_statement.location));
            setResult(std::move(statements));
        }

        void visit(ast::Continue const& continue_statement) override
        {
            Statements statements;
            statements.emplace_back(utility::makeOwned<Continue>(continue_statement.location));
            setResult(std::move(statements));
        }

        void visit(ast::While const& while_statement) override
        {
            Statements loop_body;

            Expansion condition = expand(*while_statement.condition);

            Statements exit_body;

            append(exit_body, std::move(condition.before));
            utility::Owned<Temporary> temporary_condition = utility::makeOwned<Temporary>(std::move(condition.center), while_statement.location);
            Temporary const& tmp_condition = *temporary_condition;
            exit_body.emplace_back(std::move(temporary_condition));
            append(exit_body, std::move(condition.after));

            exit_body.emplace_back(utility::makeOwned<If>(utility::makeOwned<UnaryOperation>(core::UnaryOperator::NOT, utility::makeOwned<ReadTemporary>(tmp_condition, while_statement.condition->location), while_statement.location),
                     utility::makeOwned<Break>(while_statement.location),
                     utility::makeOwned<Pass>(while_statement.location),
                     while_statement.location));

            loop_body.emplace_back(utility::makeOwned<Block>(std::move(exit_body), while_statement.location));

            Statements inner_body = expand(*while_statement.body);
            append(loop_body, std::move(inner_body));

            Statements statements;
            statements.emplace_back(utility::makeOwned<Loop>(wrap(std::move(loop_body)), while_statement.location));
            setResult(std::move(statements));
        }

        void visit(ast::ErrorExpression const& error_expression) override
        {
            setResult(utility::makeOwned<ErrorExpression>(error_expression.location));
        }

        void visit(ast::Call const& call) override
        {
            Statements before;
            utility::List<utility::Owned<Expression>> arguments;
            Statements after;

            for (auto& argument : call.arguments)
            {
                Expansion expansion = expand(*argument);

                append(before, std::move(expansion.before));
                arguments.emplace_back(std::move(expansion.center));
                append(after, std::move(expansion.after)); // todo: maybe prepend?
            }

            utility::List<utility::Owned<Expression>> resolve_arguments;
            resolve_arguments.emplace_back(utility::makeOwned<CurrentScope>(call.location));
            resolve_arguments.emplace_back(utility::makeOwned<IdentifierCapture>(call.identifier, call.location));

            setResult({
                .before = std::move(before),
                .center = utility::makeOwned<Call>(utility::makeOwned<Intrinsic>(core::Resolve::instance(), std::move(resolve_arguments), call.location), std::move(arguments), call.location),
                .after  = std::move(after),
            });
        }

        void visit(ast::Access const& access) override
        {
            utility::List<utility::Owned<Expression>> resolve_arguments;
            resolve_arguments.emplace_back(utility::makeOwned<CurrentScope>(access.location));
            resolve_arguments.emplace_back(utility::makeOwned<IdentifierCapture>(access.identifier, access.location));

            setResult({
                .before = {},
                .center = utility::makeOwned<Read>(utility::makeOwned<Intrinsic>(core::Resolve::instance(), std::move(resolve_arguments), access.location), access.location),
                .after  = {}
            });
        }

        void visit(ast::Here const& here) override
        {
            setResult(utility::makeOwned<Here>(here.location));
        }

        void visit(ast::Literal const& literal) override
        {
            setResult(utility::makeOwned<Literal>(literal.value->clone(), literal.location));
        }

        void visit(ast::UnaryOperation const& unary_operation) override
        {
            Expansion operand = expand(*unary_operation.operand);

            setResult({
                .before = std::move(operand.before),
                .center = utility::makeOwned<UnaryOperation>(unary_operation.op, std::move(operand.center), unary_operation.location),
                .after  = std::move(operand.after),
            });
        }

      private:
        utility::Optional<utility::Owned<File>> file_expansion_;
        utility::Optional<Statements> statement_expansion_;
        utility::Optional<Expansion>  expression_expansion_;

        core::Reporter& reporter_;
    };

    utility::Optional<utility::Owned<Statement>> expandOrderedFile(std::filesystem::path const& file) // todo: reduce duplication with below (template)
    {
        (void)source_tree_;//todo: use or remove

        utility::Optional<utility::Owned<ast::Statement>> parsed = parser_.parseOrderedFile(file);
        if (!parsed.hasValue()) return std::nullopt;

        utility::Owned<AST> ast = utility::makeOwned<AST>(reporter_);
        Statements statements = ast->expand(**parsed);

        if (reporter_.isFailed()) return std::nullopt;

        auto block = utility::makeOwned<Block>(std::move(statements), parsed.value()->location);

        context_.print<Printer>(*block, "est");

        return block;
    }

    utility::Optional<utility::Owned<File>> expandUnorderedFile(std::filesystem::path const& file)
    {
        utility::Optional<utility::Owned<ast::File>> parsed = parser_.parseUnorderedFile(file);
        if (!parsed.hasValue()) return std::nullopt;

        utility::Owned<AST> ast = utility::makeOwned<AST>(reporter_);
        utility::Owned<File> est = ast->expand(**parsed);

        if (reporter_.isFailed()) return std::nullopt;

        context_.print<Printer>(*est, "est");

        return est;
    }

  private:
    sources::SourceTree& source_tree_;
    core::Reporter& reporter_;
    ast::Parser     parser_;
    core::Context& context_;
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
