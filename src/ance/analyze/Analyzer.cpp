#include "Analyzer.h"

#include "ance/ret/Node.h"

struct ance::analyze::Analyzer::Implementation
{
    class RET final : public ret::Visitor
    {
    public:
        using Visitor::visit;

        explicit RET(core::Reporter& reporter) : reporter_(reporter) {}
        ~RET() override = default;

        void visit(ret::ErrorStatement const&) override
        {
        }

        void visit(ret::Block const& block) override
        {
            for (auto& statement : block.statements)
            {
                visit(*statement);
            }
        }

        void visit(ret::Independent const& independent) override
        {
            visit(*independent.expression);
        }

        void visit(ret::ErrorExpression const&) override
        {

        }

        void visit(ret::Intrinsic const&) override
        {
            (void)reporter_; //todo: use it here
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
