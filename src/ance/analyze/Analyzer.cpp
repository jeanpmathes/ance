#include "Analyzer.h"

#include "ance/core/Intrinsic.h"
#include "ance/core/Function.h"

#include "ance/ret/Node.h"

struct ance::analyze::Analyzer::Implementation
{
    class RET final : public ret::Visitor
    {
    public:
        using Visitor::visit;

        explicit RET(core::Reporter& reporter) : reporter_(reporter) {}
        ~RET() override = default;

        void analyzeCall(core::Signature const& signature, utility::List<utility::Owned<ret::Expression>> const& arguments, core::Location const& location) const
        {
            size_t const arity = signature.arity();
            size_t const argument_count = arguments.size();

            if (arity != argument_count)
            {
                reporter_.error("Call to '" + signature.name() + "' with wrong number of arguments: " +
                                " expected " + std::to_string(arity) +
                                " but got " + std::to_string(argument_count),
                                location);
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
        }

        void visit(ret::Assignment const& assignment) override
        {
            visit(*assignment.value);
        }

        void visit(ret::If const& if_statement) override
        {
            visit(*if_statement.condition);
            visit(*if_statement.true_block);
            visit(*if_statement.false_block);
        }

        void visit(ret::Loop const& loop) override
        {
            visit(*loop.body);
        }

        void visit(ret::Break const&) override
        {

        }

        void visit(ret::Continue const&) override
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

            analyzeCall(intrinsic.intrinsic.signature(), intrinsic.arguments, intrinsic.location);
        }

        void visit(ret::Call const& call) override
        {
            for (auto& argument : call.arguments)
            {
                visit(*argument);
            }

            analyzeCall(call.called.signature(), call.arguments, call.location);
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
        }

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
