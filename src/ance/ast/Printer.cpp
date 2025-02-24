#include "Printer.h"

#include "ance/ast/Node.h"

#include "ance/core/Printer.h"

struct ance::ast::Printer::Implementation
{
    class AST final
        : public Visitor
        , core::Printer
    {
      public:
        using Visitor::visit;

        explicit AST(std::ostream& out) : Printer(out) {}
        ~AST() override = default;

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
        utility::Owned<AST> ast = utility::makeOwned<AST>(out_);

        ast->visit(statement);
    }

  private:
    std::ostream& out_;
};

ance::ast::Printer::Printer(std::ostream& out) : implementation_(utility::makeOwned<Implementation>(out)) {}
ance::ast::Printer::~Printer() = default;

void ance::ast::Printer::print(Statement const& statement) const
{
    implementation_->print(statement);
}
