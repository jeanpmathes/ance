#include "Analyzer.h"

#include "ance/core/Intrinsic.h"
#include "ance/core/Function.h"
#include "ance/core/Type.h"

#include "ance/ret/Node.h"

struct ance::analyze::Analyzer::Implementation
{
    class RET final : public ret::Visitor
    {
    public:
        using Visitor::visit;

        explicit RET(core::Reporter& reporter) : reporter_(reporter) {}
        ~RET() override = default;

        void requireType(core::Type const& expected, core::Type const& actual, core::Location const& location) const
        {
            if (expected != actual)
            {
                reporter_.error("Expected type '" + expected.name() + "' but got '" + actual.name() + "'", location);
            }
        }

        void requireSignature(core::Signature const& signature, utility::List<utility::Owned<ret::Expression>> const& arguments, core::Location const& location) const
        {
            size_t const arity = signature.types().size();
            size_t const argument_count = arguments.size();

            if (arity != argument_count)
            {
                reporter_.error("Call to '" + signature.name() + "' with wrong number of arguments: " +
                                " expected " + std::to_string(arity) +
                                " but got " + std::to_string(argument_count),
                                location);
            }

            for (size_t i = 0; i < argument_count; ++i)
            {
                auto const& argument = arguments[i];
                auto const& type = signature.types()[i].get();

                requireType(type, argument->type(), argument->location);
            }
        }

        void visit(ret::ErrorStatement const&) override
        {
        }

        void visit(ret::Block const& block) override
        {
            for (auto& statement : block.statements) { visit(*statement); }
        }

        void visit(ret::Independent const& independent) override
        {
            visit(*independent.expression);
        }

        void visit(ret::Let const& let) override
        {
            if (let.value.hasValue())
            {
                visit(**let.value);
            }

            if (let.value.hasValue())
            {
                requireType(let.variable.type(), (*let.value)->type(), (*let.value)->location);
            }
        }

        void visit(ret::Assignment const& assignment) override
        {
            visit(*assignment.value);

            requireType(assignment.variable.type(), assignment.value->type(), assignment.value->location);
        }

        void visit(ret::If const& if_statement) override
        {
            visit(*if_statement.condition);
            visit(*if_statement.true_block);
            visit(*if_statement.false_block);

            requireType(core::Type::Bool(), if_statement.condition->type(), if_statement.condition->location);
        }

        void visit(ret::Loop const& loop) override
        {
            visit(*loop.body);
        }

        void visit(ret::Break const&) override
        {

        }

        void visit(ret::Continue const&) override {}

        void visit(ret::Temporary const&) override
        {

        }

        void visit(ret::WriteTemporary const& ) override
        {

        }


        void visit(ret::ErrorExpression const&) override
        {

        }

        void visit(ret::Intrinsic const& intrinsic) override
        {
            for (auto& argument : intrinsic.arguments)
            {
                visit(*argument);
            }

            requireSignature(intrinsic.intrinsic.signature(), intrinsic.arguments, intrinsic.location);
        }

        void visit(ret::Call const& call) override
        {
            for (auto& argument : call.arguments)
            {
                visit(*argument);
            }

            requireSignature(call.called.signature(), call.arguments, call.location);
        }

        void visit(ret::Access const&) override
        {

        }

        void visit(ret::Constant const&) override
        {

        }

        void visit(ret::UnaryOperation const& unary_operation) override
        {
            visit(*unary_operation.operand);

            if (unary_operation.op == core::UnaryOperator::NOT)
            {
                requireType(core::Type::Bool(), unary_operation.operand->type(), unary_operation.operand->location);
            }
        }

        void visit(ret::ReadTemporary const&) override {}

      private:
        core::Reporter& reporter_;
    };

    explicit Implementation(core::Reporter& reporter) : reporter_(reporter) {}

    void analyze(ret::Statement const& statement)
    {
        utility::Owned<RET> ret = utility::makeOwned<RET>(reporter_);

        ret->visit(statement);
    }

private:
    core::Reporter& reporter_;
};

ance::analyze::Analyzer::Analyzer(core::Reporter& reporter) : implementation_(utility::makeOwned<Implementation>(reporter)) {}

ance::analyze::Analyzer::~Analyzer() = default;

void ance::analyze::Analyzer::analyze(ret::Statement const& statement)
{
    implementation_->analyze(statement);
}
