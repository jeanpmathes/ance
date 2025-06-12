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
            if (temporaries_.at(&branch_link.condition)->getBool()) {
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

        void visit(bbt::Declare const& declare) override
        {
            utility::Shared<core::Value> value = core::Value::makeDefault(declare.variable.type());

            if (declare.value != nullptr) { value = temporaries_.at(declare.value); }

            variables_.insert_or_assign(&declare.variable, value);
        }

        void visit(bbt::Store const& store) override
        {
            variables_.insert_or_assign(&store.variable, temporaries_.at(&store.value));
        }

        void visit(bbt::Temporary const& temporary) override
        {
            utility::Shared<core::Value> value = core::Value::makeDefault(temporary.type);
            temporaries_.insert_or_assign(&temporary, value);
        }

        void visit(bbt::CopyTemporary const& write_temporary) override
        {
            utility::Shared<core::Value> value = temporaries_.at(&write_temporary.source);
            temporaries_.insert_or_assign(&write_temporary.destination, value);
        }

        void visit(bbt::Intrinsic const& intrinsic) override
        {
            utility::List<utility::Shared<core::Value>> arguments = {};
            for (auto argument : intrinsic.arguments) { arguments.emplace_back(temporaries_.at(&argument.get())); }

            intrinsics_.run(intrinsic.intrinsic, arguments, intrinsic.location);
            temporaries_.insert_or_assign(&intrinsic.destination, core::Value::makeUnit());
        }

        void visit(bbt::Call const& call) override
        {
            utility::List<utility::Shared<core::Value>> arguments = {};
            for (auto argument : call.arguments)
            {
                arguments.emplace_back(temporaries_.at(&argument.get())); }

            call.called.run(arguments);
            temporaries_.insert_or_assign(&call.destination, core::Value::makeUnit());
        }

        void visit(bbt::Read const& read) override
        {
            utility::Shared<core::Value> value = variables_.at(&read.variable);

            temporaries_.insert_or_assign(&read.destination, value);
        }

        void visit(bbt::Constant const& constant) override
        {
            temporaries_.insert_or_assign(&constant.destination, constant.value->clone());
        }

        void visit(bbt::UnaryOperation const& unary_operation) override
        {
            utility::Shared<core::Value> value = temporaries_.at(&unary_operation.operand);

            switch (unary_operation.op)
            {
                case core::UnaryOperator::NOT:
                    temporaries_.insert_or_assign(&unary_operation.destination, core::Value::makeBool(!value->getBool()));
                    break;
            }
        }

      private:
        core::Reporter& reporter_;

        Intrinsics intrinsics_ {reporter_};

        std::map<core::Variable const*, utility::Shared<core::Value>> variables_ = {};
        std::map<bbt::Temporary const*, utility::Shared<core::Value>> temporaries_ = {};
        

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
