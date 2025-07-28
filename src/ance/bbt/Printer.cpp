#include "Printer.h"

#include "ance/core/Printer.h"
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

        void visit(Flow const& flow) override
        {
            for (auto& block : flow.blocks)
            {
                visit(*block);
                line();
            }
        }

        void visit(BasicBlock const& block) override
        {
            print("block ");
            print(block.id);
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
            print(branch_link.true_branch.id);
            print(", ");
            print(branch_link.false_branch.id);
            print(") on temporary ");
            print(branch_link.condition.id());
        }

        void visit(Jump const& jump_link) override
        {
            print("jump (");
            print(jump_link.target.id);
            print(")");
        }

        void visit(ErrorStatement const&) override { print("// error"); }

        void visit(Pass const&) override { print("pass;"); }

        void visit(Declare const& declare) override
        {
            print("declare ");
            print(declare.identifier);

            if (declare.value != nullptr)
            {
                print(" <: temporary ");
                print(declare.value->id());
            }

            print(";");
        }

        void visit(Store const& store) override
        {
            print(store.identifier);
            print(" <: temporary ");
            print(store.value.id());
            print(";");
        }

        void visit(Temporary const& temporary) override
        {
            print("let temporary ");
            print(temporary.id());
            print(";");
        }

        void visit(CopyTemporary const& write_temporary) override
        {
            print("temporary ");
            print(write_temporary.destination.id());
            print(" <: temporary ");
            print(write_temporary.source.id());
            print(";");
        }

        void visit(Intrinsic const& intrinsic) override
        {
            print("temporary ");
            print(intrinsic.destination.id());
            print(" <- intrinsic(");
            print(intrinsic.intrinsic);
            for (auto const argument : intrinsic.arguments)
            {
                print(", ");
                print(argument.get().id());
            }
            print(")");
        }

        void visit(Call const& call) override
        {
            print("temporary ");
            print(call.destination.id());
            print(" <- ");
            print(call.called);
            print("(");
            for (size_t i = 0; i < call.arguments.size(); ++i)
            {
                print(call.arguments[i].get().id());
                if (i + 1 < call.arguments.size()) print(", ");
            }
            print(")");
        }

        void visit(Read const& read) override
        {
            print("temporary ");
            print(read.destination.id());
            print(" <: ");
            print(read.identifier);
        }

        void visit(Constant const& constant) override
        {
            print("temporary ");
            print(constant.destination.id());
            print(" <: ");
            print(constant.value);
        }

        void visit(UnaryOperation const& unary_operation) override
        {
            print("temporary ");
            print(unary_operation.destination.id());
            print(" <- ");
            print(unary_operation.op.toString());
            print(" ");
            print(unary_operation.operand.id());
        }

        void visit(ScopeEnter const&) override { print("// enter scope"); }

        void visit(ScopeExit const&) override { print("// exit scope"); }

    };

    explicit Implementation(std::ostream& out) : out_(out) {}

    void print(Flow const& flow) const
    {
        utility::Owned<BBT> bbt = utility::makeOwned<BBT>(out_);
        bbt->visit(flow);
    }

    void print(BasicBlock const& block) const
    {
        utility::Owned<BBT> bbt = utility::makeOwned<BBT>(out_);
        bbt->visit(block);
    }

  private:
    std::ostream& out_;
};

ance::bbt::Printer::Printer(std::ostream& out) : implementation_(utility::makeOwned<Implementation>(out)) {}
ance::bbt::Printer::~Printer() = default;

void ance::bbt::Printer::print(Flow const& flow) const
{
    implementation_->print(flow);
}

void ance::bbt::Printer::print(BasicBlock const& block) const
{
    implementation_->print(block);
}
