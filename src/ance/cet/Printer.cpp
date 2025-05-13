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
            print(") on ");
            visit(*branch_link.condition);
        }

        void visit(Jump const& jump_link) override
        {
            print("jump (");
            print(jump_link.target.id);
            print(")");
        }

        void visit(Independent const& independent) override
        {
            visit(*independent.expression);
            print(";");
        }

        void visit(Let const& let) override
        {
            print("let ");
            print(let.variable.identifier());

            if (let.value.hasValue())
            {
                print(" <: ");
                visit(**let.value);
            }

            print(";");
        }

        void visit(Assignment const& assignment) override
        {
            print(assignment.variable.identifier());
            print(" <: ");
            visit(*assignment.value);
            print(";");
        }

        void visit(Intrinsic const& intrinsic) override
        {
            print("intrinsic(");
            print(intrinsic.intrinsic);
            for (const auto& argument : intrinsic.arguments)
            {
                print(", ");
                visit(*argument);
            }
            print(")");
        }

        void visit(Call const& call) override
        {
            print(call.called);
            print("(");
            for (size_t i = 0; i < call.arguments.size(); ++i)
            {
                visit(*call.arguments[i]);
                if (i + 1 < call.arguments.size()) print(", ");
            }
            print(")");
        }

        void visit(Access const& access) override
        {
            print(access.variable.identifier());
        }

        void visit(Constant const& constant) override
        {
            print(constant.value ? "true" : "false");
        }

        void visit(UnaryOperation const& unary_operation) override
        {
            print(unary_operation.op.toString());
            print(" ");
            visit(*unary_operation.operand);
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
