#include "Printer.h"

#include <unordered_set>
#include <queue>

#include "ance/core/Printer.h"

#include "Value.h"
#include "ance/bbt/Node.h"

struct ance::bbt::Printer::Implementation
{
    class BBT final
        : public Visitor
        , core::Printer
    {
      public:
        using Visitor::visit;

        explicit BBT(std::ostream& out) : Printer(out) {}
        ~BBT() override = default;

        void visit(Flows const& flows) override
        {
            for (auto const& flow : flows.flows)
            {
                visit(*flow);
            }
        }

        void visit(UnorderedScope const& scope) override
        {
            for (auto const& flow : scope.flows)
            {
                visit(*flow);
            }
        }

        void visit(Flow const& flow) override
        {
            auto [_, inserted] = printed_flows_.insert(&flow);
            if (!inserted) return;

            bool const is_top_level_flow = flow_depth_ == 0;
            flow_depth_++;

            print("flow ");
            print(flow.id());
            print(":");
            line();
            enter();

            for (auto& block : flow.blocks)
            {
                visit(*block);
                line();
            }

            exit();

            if (is_top_level_flow)
            {
                while (!nested_flows_to_print_.empty())
                {
                    visit(*nested_flows_to_print_.front());
                    nested_flows_to_print_.pop();
                }

                printed_flows_.clear();
            }

            flow_depth_--;
        }

        void visit(BasicBlock const& block) override
        {
            print("block ");
            print(std::to_string(block.id));
            line();
            enter();

            print("begin");
            line();
            enter();

            for (auto& statement : block.statements)
            {
                visit(*statement);
                line();
            }

            exit();

            print("end");
            line();

            visit(*block.link);

            exit();
            line();
        }

        void visit(ErrorLink const&) override
        {
            print("/* error */");
        }

        void visit(Return const&) override
        {
            print("return ()");
        }

        void visit(Branch const& branch_link) override
        {
            print("branch (");
            print(std::to_string(branch_link.true_branch.id));
            print(", ");
            print(std::to_string(branch_link.false_branch.id));
            print(") on temporary ");
            print(branch_link.condition.id());
        }

        void visit(Jump const& jump_link) override
        {
            print("jump (");
            print(std::to_string(jump_link.target.id));
            print(")");
        }

        void visit(ErrorStatement const&) override
        {
            print("// error");
        }

        void visit(Pass const&) override
        {
            print("pass;");
        }

        void visit(Store const& store) override
        {
            print("store ");
            print(store.value.id());
            print(" at ");
            print(store.target.id());
            print(";");
        }

        void visit(Access const& access) override
        {
            print(access.destination.id());
            print(" ");
            print(core::Assigner::COPY_ASSIGNMENT);
            print(" access ");
            print(access.variable.id());
            print(";");
        }

        void visit(Temporary const& temporary) override
        {
            print("temporary ");
            print(temporary.id());
            print(";");
        }

        void visit(CopyTemporary const& write_temporary) override
        {
            print(write_temporary.destination.id());
            print(" ");
            print(core::Assigner::COPY_ASSIGNMENT);
            print(" ");
            print(write_temporary.source.id());
            print(";");
        }

        void visit(Intrinsic const& intrinsic) override
        {
            print(intrinsic.destination.id());
            print(" ");
            print(core::Assigner::MOVE_ASSIGNMENT);
            print(" intrinsic (");
            print(intrinsic.intrinsic);
            for (auto const argument : intrinsic.arguments)
            {
                print(", ");
                print(argument.get().id());
            }
            print(");");
        }

        void visit(Call const& call) override
        {
            print(call.destination.id());
            print(" ");
            print(core::Assigner::MOVE_ASSIGNMENT);
            print(" call ");
            print(call.called.id());
            print(" (");
            for (size_t i = 0; i < call.arguments.size(); ++i)
            {
                print(call.arguments[i].get().id());
                if (i + 1 < call.arguments.size()) print(", ");
            }
            print(");");
        }

        void visit(AnonymousFunctionConstructor const& function_constructor) override
        {
            print(function_constructor.destination.id());
            print(" ");
            print(core::Assigner::MOVE_ASSIGNMENT);
            print(" Function::ctor(Signature::ctor(");
            for (size_t i = 0; i < function_constructor.parameters.size(); ++i)
            {
                print("(");
                print(function_constructor.parameters[i].type.id());
                print(", ");
                print(function_constructor.parameters[i].identifier);
                print(")");
                if (i + 1 < function_constructor.parameters.size()) print(", ");
            }
            print("), ");
            print(function_constructor.return_type.id());
            print("), flow ");
            print(function_constructor.body->id());
            print(";");

            nested_flows_to_print_.push(function_constructor.body.get());
        }

        void visit(Constant const& constant) override
        {
            print(constant.destination.id());
            print(" ");
            print(core::Assigner::COPY_ASSIGNMENT);
            print(" ");
            print(constant.value->toString());
            print(";");
        }

        void visit(Default const& default_value) override
        {
            print(default_value.destination.id());
            print(" ");
            print(core::Assigner::COPY_ASSIGNMENT);
            print(" default ( ");
            print(default_value.type.id());
            print(");");
        }

        void visit(CurrentScope const& current_scope) override
        {
            print(current_scope.destination.id());
            print(" ");
            print(core::Assigner::COPY_ASSIGNMENT);
            print(" scope;");
        }

        void visit(UnaryOperation const& unary_operation) override
        {
            print(unary_operation.destination.id());
            print(" ");
            print(core::Assigner::MOVE_ASSIGNMENT);
            print(" ");
            print(unary_operation.op.toString());
            print(" ");
            print(unary_operation.operand.id());
            print(";");
        }

        void visit(TypeOf const& type_of) override
        {
            print(type_of.destination.id());
            print(" ");
            print(core::Assigner::COPY_ASSIGNMENT);
            print(" typeof ( ");
            print(type_of.expression.id());
            print(");");
        }

        void visit(OrderedScopeEnter const&) override
        {
            print("// enter scope");
        }

        void visit(OrderedScopeExit const&) override
        {
            print("// exit scope");
        }

        void visit(SetReturnValue const& set_return_value) override
        {
            print("return ");
            print(core::Assigner::MOVE_ASSIGNMENT);
            print(" ");
            print(set_return_value.value.id());
            print(";");
        }

      private:
        size_t flow_depth_ = 0;
        std::queue<Flow const*> nested_flows_to_print_;
        std::unordered_set<Flow const*> printed_flows_;
    };

    explicit Implementation(std::ostream& out) : out_(out) {}

    void print(Node const& node) const
    {
        utility::Owned<BBT> bbt = utility::makeOwned<BBT>(out_);
        bbt->visit(node);
    }

  private:
    std::ostream& out_;
};

ance::bbt::Printer::Printer(std::ostream& out) : implementation_(utility::makeOwned<Implementation>(out)) {}
ance::bbt::Printer::~Printer() = default;

void ance::bbt::Printer::print(Flows const& flows) const
{
    implementation_->print(flows);
}

void ance::bbt::Printer::print(Flow const& flow) const
{
    implementation_->print(flow);
}

void ance::bbt::Printer::print(BasicBlock const& block) const
{
    implementation_->print(block);
}
