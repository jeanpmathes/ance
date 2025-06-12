#include "Printer.h"

#include "ance/core/Printer.h"
#include "ance/cet/Node.h"

struct ance::cet::Printer::Implementation
{
    class CET final
        : public Visitor
        , core::Printer
    {
      public:
        using Visitor::visit;

        explicit CET(std::ostream& out) : Printer(out) {}
        ~CET() override = default;

        void visit(Unit const& unit) override
        {
            print("unit:");
            line();
            enter();

            for (auto& child : unit.children)
            {
                visit(*child);
                line();
            }

            exit();
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

        void visit(Declare const& declare) override
        {
            print("declare ");
            print(declare.variable.identifier());

            if (declare.value != nullptr)
            {
                print(" <: temporary ");
                print(declare.value->id());
            }

            print(";");
        }

        void visit(Store const& store) override
        {
            print(store.variable.identifier());
            print(" <: temporary ");
            print(store.value.id());
            print(";");
        }

        void visit(Temporary const& temporary) override
        {
            print("let temporary ");
            print(temporary.id());
            print(": ");
            print(temporary.type);
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
            for (auto const* argument : intrinsic.arguments)
            {
                print(", ");
                print(argument->id());
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
                print(call.arguments[i]->id());
                if (i + 1 < call.arguments.size()) print(", ");
            }
            print(")");
        }

        void visit(Read const& read) override
        {
            print("temporary ");
            print(read.destination.id());
            print(" <: ");
            print(read.variable.identifier());
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

    };

    explicit Implementation(std::ostream& out) : out_(out) {}

    void print(Unit const& unit) const
    {
        utility::Owned<CET> cet = utility::makeOwned<CET>(out_);
        cet->visit(unit);
    }

    void print(BasicBlock const& block) const
    {
        utility::Owned<CET> cet = utility::makeOwned<CET>(out_);
        cet->visit(block);
    }

  private:
    std::ostream& out_;
};

ance::cet::Printer::Printer(std::ostream& out) : implementation_(utility::makeOwned<Implementation>(out)) {}
ance::cet::Printer::~Printer() = default;

void ance::cet::Printer::print(Unit const& unit) const
{
    implementation_->print(unit);
}

void ance::cet::Printer::print(BasicBlock const& block) const
{
    implementation_->print(block);
}
