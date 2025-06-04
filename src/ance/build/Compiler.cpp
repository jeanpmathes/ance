#include "Compiler.h"

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

        void visit(cet::Return const& return_link) override
        {
            (void) return_link;// todo: implement
        }

        void visit(cet::Branch const& branch_link) override
        {
            (void) branch_link;// todo: implement
        }

        void visit(cet::Jump const& jump_link) override
        {
            (void) jump_link;// todo: implement
        }

        void visit(cet::Independent const& independent) override
        {
            (void) independent;// todo: implement
        }

        void visit(cet::Let const& let) override
        {
            (void) let;// todo: implement
        }

        void visit(cet::Assignment const& assignment) override
        {
            (void) assignment;// todo: implement
        }

        void visit(cet::Temporary const& temporary) override
        {
            (void) temporary;// todo: implement
        }

        void visit(cet::WriteTemporary const& write_temporary) override
        {
            (void) write_temporary;// todo: implement
        }

        void visit(cet::Intrinsic const& intrinsic) override
        {
            intrinsics_.run(intrinsic.intrinsic, intrinsic.location);
        }

        void visit(cet::Call const& call) override
        {
            (void) call;// todo: implement
        }

        void visit(cet::Access const& access) override
        {
            (void) access;// todo: implement
        }

        void visit(cet::Constant const& constant) override
        {
            (void) constant;// todo: implement
        }

        void visit(cet::UnaryOperation const& unary_operation) override
        {
            (void) unary_operation;// todo: implement
        }

        void visit(cet::ReadTemporary const& read_temporary) override
        {
            (void) read_temporary;// todo: implement
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
