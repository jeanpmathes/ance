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
            line();
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

        void visit(Independent const& independent) override
        {
            visit(*independent.expression);
            print(";");
        }

        void visit(Intrinsic const& intrinsic) override
        {
            print(intrinsic.identifier);
            print("()");
        }
    };

    explicit Implementation(std::ostream& out) : out_(out) {}

    void print(Unit const& unit) const
    {
        utility::Owned<CET> cet = utility::makeOwned<CET>(out_);
        cet->visit(unit);
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
