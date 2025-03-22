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

        void visit(BasicBlock const& block) override
        {
            print("block:");
            line();
            enter();

            for (auto& statement : block.statements)
            {
                visit(*statement);
                line();
            }

            exit();
        }

        void visit(ErrorStatement const&) override { print("// error"); }

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

        void visit(ErrorExpression const&) override { print("/* error */"); }

        void visit(Intrinsic const& intrinsic) override
        {
            print("(");
            print("call ");
            print(intrinsic.intrinsic);
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
    };

    explicit Implementation(std::ostream& out) : out_(out) {}

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

void ance::bbt::Printer::print(BasicBlock const& block) const
{
    implementation_->print(block);
}
