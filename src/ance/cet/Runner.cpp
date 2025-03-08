#include "Runner.h"

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

        void visit(bbt::ErrorStatement const& error_statement) override
        {
            reporter_.error("Cannot execute this statement", error_statement.location);
        }

        void visit(bbt::Independent const& independent) override
        {
            visit(*independent.expression);
        }

        void visit(bbt::Let const& let) override
        {
            std::cout << "declare " << let.variable.identifier() << std::endl; // todo: remove
        }

        void visit(bbt::ErrorExpression const& error_expression) override
        {
            reporter_.error("Cannot execute this expression", error_expression.location);
        }

        void visit(bbt::Intrinsic const& intrinsic) override
        {
            intrinsics_.run(intrinsic.intrinsic, intrinsic.location);
        }

        void visit(bbt::Access const& access) override
        {
            std::cout << "read " << access.variable.identifier() << std::endl; // todo: remove
        }

    private:
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
