#include "Printer.h"

#include "ance/est/Node.h"
#include "ance/core/Printer.h"

struct ance::est::Printer::Implementation
{
    class EST final
        : public Visitor
        , core::Printer
    {
      public:
        using Visitor::visit;

        explicit EST(std::ostream& out) : Printer(out) {}
        ~EST() override = default;

        void visit(ErrorStatement const&) override { print("// error"); }

        void visit(Block const& block) override
        {
            print("{");
            line();
            enter();

            for (auto& statement : block.statements)
            {
                visit(*statement);
                line();
            }

            exit();
            print("}");
        }

        void visit(Independent const& independent) override
        {
            visit(*independent.expression);
            print(";");
        }

        void visit(ErrorExpression const&) override { print("/* error */"); }

        void visit(Call const& call) override
        {
            print(call.identifier);
            print("()");
        }
    };

    explicit Implementation(std::ostream& out) : out_(out) {}

    void print(Statement const& statement) const
    {
        utility::Owned<EST> est = utility::makeOwned<EST>(out_);
        est->visit(statement);
    }

  private:
    std::ostream& out_;
};

ance::est::Printer::Printer(std::ostream& out) : implementation_(utility::makeOwned<Implementation>(out)) {}
ance::est::Printer::~Printer() = default;

void ance::est::Printer::print(Statement const& statement) const
{
    implementation_->print(statement);
}
