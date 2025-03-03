#include "Runner.h"

#include <array>
#include <iostream>

#include "ance/core/Intrinsic.h"

#include "ance/bbt/Node.h"
#include "ance/cet/Node.h"

struct ance::cet::Runner::Implementation
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

        void visit(core::Dynamic const& dynamic) override
        {
            reporter_.error("Unsupported intrinsic '" + dynamic.identifier() + "'", location_);
        }

        void visit(core::Print const&) override
        {
            std::cout << "DEBUG: " << "foo" << std::endl; // todo: remove
        }

        void visit(core::NoOp const&) override
        {
            // Do nothing.
        }

    private:
        core::Reporter& reporter_;

        core::Location location_ = core::Location::global();
    };

    class BBT final : public bbt::Visitor
    {
    public:
        using Visitor::visit;

        explicit BBT(core::Reporter& reporter) : reporter_(reporter) {}
        ~BBT() override = default;

        void visit(bbt::BasicBlock const& basic_block) override
        {
            for (auto& statement : basic_block.statements)
            {
                visit(*statement);
            }
        }

        void visit(bbt::ErrorStatement const&) override
        {
            is_invalid_ = true;
        }

        void visit(bbt::Independent const& independent) override
        {
            visit(*independent.expression);
        }

        void visit(bbt::ErrorExpression const&) override
        {
            is_invalid_ = true;
        }

        void visit(bbt::Intrinsic const& intrinsic) override
        {
            intrinsics_.run(intrinsic.intrinsic, intrinsic.location);
        }

    private:
        bool is_invalid_ = false;

        core::Reporter& reporter_;

        Intrinsics intrinsics_ {reporter_};
    };

    explicit Implementation(core::Reporter& reporter) : reporter_(reporter) {}

    utility::Owned<Unit> run(bbt::BasicBlock const& block)
    {
        utility::Owned<Unit> unit = utility::makeOwned<Unit>();

        utility::Owned<BBT> bbt = utility::makeOwned<BBT>(reporter_);
        bbt->visit(block);

        return unit;
    }

private:
    core::Reporter& reporter_;
};

ance::cet::Runner::Runner(core::Reporter& reporter) : implementation_(utility::makeOwned<Implementation>(reporter)) {}

ance::cet::Runner::~Runner() = default;

ance::utility::Owned<ance::cet::Unit> ance::cet::Runner::run(bbt::BasicBlock const& block)
{
    return implementation_->run(block);
}
