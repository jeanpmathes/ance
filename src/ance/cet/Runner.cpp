#include "Runner.h"

#include <iostream>
#include <map>

#include "ance/core/Intrinsic.h"
#include "ance/core/Function.h"

#include "ance/bbt/Node.h"
#include "ance/cet/Node.h"
#include "ance/core/Value.h"

struct ance::cet::Runner::Implementation
{
    class Intrinsics final : core::IntrinsicVisitor
    {
    public:
        using IntrinsicVisitor::visit;

        explicit Intrinsics(core::Reporter& reporter) : reporter_(reporter) {}

        void run(core::Intrinsic const& intrinsic, utility::List<utility::Shared<core::Value>> const& arguments, core::Location const& location)
        {
            location_ = location;
            arguments_ = &arguments;

            this->visit(intrinsic);

            location_ = core::Location::global();
            arguments_ = nullptr;
        }

        void visit(core::Dynamic const& dynamic) override
        {
            reporter_.error("Unsupported intrinsic '" + dynamic.identifier() + "'", location_);
        }

        void visit(core::NoOp const&) override
        {
            // Do nothing.
        }

    private:
        core::Reporter& reporter_;

        core::Location location_ = core::Location::global();
        utility::List<utility::Shared<core::Value>> const* arguments_ = nullptr;
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

            // todo: when creating new basic blocks here, also implement simplification / already output simplified blocks for compilation
            // todo: maybe simplification code should be shared in some way?
        }

        void run(bbt::Statement const& statement)
        {
            visit(statement);
        }

        utility::Shared<core::Value> run(bbt::Expression const& expression)
        {
            assert(!result_.hasValue());

            visit(expression);

            if (!result_.hasValue())
                return core::Value::makeUnit();

            utility::Shared<core::Value> result = result_.value();
            result_ = std::nullopt;

            return result;
        }

        void setResult(utility::Shared<core::Value> value)
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
            if (run(*branch_link.condition)->getBool())
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
            utility::Shared<core::Value> value = core::Value::makeDefault(let.variable.type());

            if (let.value.hasValue())
            {
                value = run(**let.value);
            }

            state_.insert_or_assign(&let.variable, value);
        }

        void visit(bbt::Assignment const& assignment) override
        {
            state_.insert_or_assign(&assignment.variable, run(*assignment.value));
        }

        void visit(bbt::ErrorExpression const& error_expression) override
        {
            reporter_.error("Cannot execute this expression", error_expression.location);
        }

        void visit(bbt::Intrinsic const& intrinsic) override
        {
            utility::List<utility::Shared<core::Value>> arguments = {};
            for (auto& argument : intrinsic.arguments)
            {
                arguments.push_back(run(*argument));
            }

            intrinsics_.run(intrinsic.intrinsic, arguments, intrinsic.location);
        }

        void visit(bbt::Call const& call) override
        {
            utility::List<utility::Shared<core::Value>> arguments = {};
            for (auto& argument : call.arguments)
            {
                arguments.push_back(run(*argument));
            }

            call.called.run(arguments);
        }

        void visit(bbt::Access const& access) override
        {
            utility::Shared<core::Value> value = state_.at(&access.variable);

            setResult(value);
        }

        void visit(bbt::Constant const& constant) override
        {
            setResult(constant.value->clone());
        }

        void visit(bbt::UnaryOperation const& unary_operation) override
        {
            utility::Shared<core::Value> value = run(*unary_operation.operand);

            switch (unary_operation.op)
            {
                case core::UnaryOperator::NOT:
                    setResult(core::Value::makeBool(!value->getBool()));
                    break;
            }
        }

      private:
        core::Reporter& reporter_;

        Intrinsics intrinsics_ {reporter_};

        std::map<core::Variable const*, utility::Shared<core::Value>> state_ = {};
        utility::Optional<utility::Shared<core::Value>> result_ = std::nullopt;

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
