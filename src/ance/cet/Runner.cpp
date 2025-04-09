#include "Runner.h"

#include <iostream>
#include <map>

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
            std::cout << "DEBUG" << std::endl; // todo: remove
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

        void run(bbt::BasicBlock const& basic_block)
        {
            next_ = &basic_block;

            while (next_ != nullptr)
            {
                visit(*next_);
            }
        }

        void run(bbt::Statement const& statement)
        {
            visit(statement);
        }

        bool run(bbt::Expression const& expression)
        {
            assert(!result_.hasValue());

            visit(expression);

            if (!result_.hasValue())
                return false; // todo: unit type

            bool const result = result_.value();
            result_ = std::nullopt;

            return result;
        }

        void setResult(bool const value)
        {
            assert(!result_.hasValue());
            result_ = value;
        }

        void visit(bbt::Flow const& flow) override
        {
            run(flow.entry);
        }

        void visit(bbt::BasicBlock const& basic_block) override
        {
            for (auto& statement : basic_block.statements)
            {
                run(*statement);
            }

            visit(*basic_block.link);
        }

        void visit(bbt::ErrorLink const& error_link) override
        {
            reporter_.error("Cannot execute this link", error_link.location);

            next_ = nullptr;
        }

        void visit(bbt::Return const&) override
        {
            next_ = nullptr;
        }

        void visit(bbt::Branch const& branch_link) override
        {
            if (run(*branch_link.condition))
            {
                next_ = &branch_link.true_branch;
            }
            else
            {
                next_ = &branch_link.false_branch;
            }
        }

        void visit(bbt::Jump const& jump_link) override
        {
            next_ = &jump_link.target;
        }

        void visit(bbt::ErrorStatement const& error_statement) override
        {
            reporter_.error("Cannot execute this statement", error_statement.location);
        }

        void visit(bbt::Independent const& independent) override
        {
            run(*independent.expression);
        }

        void visit(bbt::Let const& let) override
        {
            bool value = false;

            if (let.value.hasValue())
            {
                value = run(**let.value);
            }

            state_[&let.variable] = value;
        }

        void visit(bbt::Assignment const& assignment) override
        {
            bool const value = run(*assignment.value);

            state_[&assignment.variable] = value;
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
            bool const value = state_.at(&access.variable);

            setResult(value);
        }

        void visit(bbt::Constant const& constant) override
        {
            setResult(constant.value);
        }

      private:
        core::Reporter& reporter_;

        Intrinsics intrinsics_ {reporter_};

        std::map<core::Variable const*, bool> state_ = {};
        utility::Optional<bool> result_ = std::nullopt;

        bbt::BasicBlock const* next_ = nullptr;
    };

    explicit Implementation(core::Reporter& reporter) : reporter_(reporter) {}

    utility::Owned<Unit> run(bbt::Flow const& flow)
    {
        utility::Owned<Unit> unit = utility::makeOwned<Unit>();

        utility::Owned<BBT> bbt = utility::makeOwned<BBT>(reporter_);
        bbt->visit(flow);

        return unit;
    }

private:
    core::Reporter& reporter_;
};

ance::cet::Runner::Runner(core::Reporter& reporter) : implementation_(utility::makeOwned<Implementation>(reporter)) {}

ance::cet::Runner::~Runner() = default;

ance::utility::Owned<ance::cet::Unit> ance::cet::Runner::run(bbt::Flow const& flow)
{
    return implementation_->run(flow);
}
