#include "Analyzer.h"

#include "ance/ret/Node.h"

namespace ance::analyze
{
    class RET final : public ret::Visitor
    {
      public:
        using Visitor::visit;

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

        }
    };
}

struct ance::analyze::Analyzer::Implementation
{
    void analyze(ret::Statement const& statement)
    {
        utility::Owned<RET> ret = utility::makeOwned<RET>();

        ret->visit(statement);
    }
};

ance::analyze::Analyzer::Analyzer() : implementation_(utility::makeOwned<Implementation>()) {}

ance::analyze::Analyzer::~Analyzer() = default;

void ance::analyze::Analyzer::analyze(ret::Statement const& statement)
{
    implementation_->analyze(statement);
}
