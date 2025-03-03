#include "Compiler.h"

#include <array>

#include "ance/core/Intrinsic.h"

#include "ance/cet/Node.h"

struct ance::build::Compiler::Implementation
{
    class Intrinsics final : core::IntrinsicVisitor
    {
    public:
        using IntrinsicVisitor::visit;

        explicit Intrinsics(core::Reporter& reporter) : reporter_(reporter) {}

        void run(core::Intrinsic const& intrinsic, core::Location const& location)
        {
            location_ = location;

            this->visit(intrinsic);

            location_ = core::Location::global();
        }

        void unsupported(core::Intrinsic const& intrinsic) const
        {
            reporter_.error("Unsupported intrinsic '" + intrinsic.identifier() + "'", location_);
        }

        void visit(core::Dynamic const& dynamic) override
        {
            unsupported(dynamic);
        }

        void visit(core::Print const& print) override
        {
            unsupported(print);
        }

        void visit(core::NoOp const&) override
        {
            // Do nothing.
        }

    private:
        core::Reporter& reporter_;

        core::Location location_ = core::Location::global();
    };

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
            intrinsics_.run(intrinsic.intrinsic, intrinsic.location);
        }

    private:
        core::Reporter& reporter_;

        Intrinsics intrinsics_ {reporter_};
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
