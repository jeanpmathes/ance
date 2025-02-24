#include "Compiler.h"

#include <array>

#include "ance/cet/Node.h"

struct ance::build::Compiler::Implementation
{
    class CET final : public cet::Visitor
    {
    public:
        using Visitor::visit;

        explicit CET(core::Reporter& reporter) : reporter_(reporter) {}
        ~CET() override = default;

        void visit(cet::Unit const& unit) override
        {
            (void) unit;// todo: implement
        }

        void visit(cet::BasicBlock const& basic_block) override
        {
            (void) basic_block;// todo: implement
        }

        void visit(cet::Independent const& independent) override
        {
            (void) independent;// todo: implement
        }

        void visit(cet::Intrinsic const& intrinsic) override
        {
            (void) intrinsic;// todo: implement

            (void)reporter_;//todo: use reporter or remove from compiler at some point
        }

    private:
        core::Reporter& reporter_;
    };

    explicit Implementation(core::Reporter& reporter) : reporter_(reporter) {}

    void compile(cet::Unit const& unit)
    {
        utility::Owned<CET> cet = utility::makeOwned<CET>(reporter_);

        cet->visit(unit);
    }

private:
    core::Reporter& reporter_;
};

ance::build::Compiler::Compiler(core::Reporter& reporter) : implementation_(utility::makeOwned<Implementation>(reporter)) {}

ance::build::Compiler::~Compiler() = default;

void ance::build::Compiler::compile(cet::Unit const& unit)
{
    implementation_->compile(unit);
}
