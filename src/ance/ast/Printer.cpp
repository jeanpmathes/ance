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

        void visit(Let const& let) override
        {
            print("let ");
            print(let.identifier);
            print(": ");
            visit(*let.type);

            if (let.value.hasValue())
            {
                print(" <: ");
                visit(**let.value);
            }

            print(";");
        }

        void visit(Assignment const& assignment) override
        {
            print(assignment.identifier);
            print(" <: ");
            visit(*assignment.value);
            print(";");
        }

        void visit(If const& if_statement) override
        {
            print("if ");
            visit(*if_statement.condition);
            print(" then ");

            if (if_statement.true_part->isCompound())
            {
                line();
                visit(*if_statement.true_part);
            }
            else
            {
                visit(*if_statement.true_part);
            }

            if (if_statement.false_part.hasValue())
            {
                line();
                print("else ");

                if (if_statement.false_part.value()->isCompound())
                {
                    line();
                    visit(**if_statement.false_part);
                }
                else
                {
                    visit(**if_statement.false_part);
                }
            }
        }

        void visit(Loop const& loop) override
        {
            print("loop ");
            if (loop.body->isCompound())
            {
                line();
                visit(*loop.body);
            }
            else
            {
                visit(*loop.body);
            }
        }

        void visit(Break const&) override { print("break;"); }

        void visit(Continue const&) override { print("continue;"); }

        void visit(While const& while_statement) override
        {
            print("while ");
            visit(*while_statement.condition);
            print(" do ");

            if (while_statement.body->isCompound())
            {
                line();
                visit(*while_statement.body);
            }
            else
            {
                visit(*while_statement.body);
            }
        }

        void visit(ErrorExpression const&) override { print("/* error */"); }

        void visit(Call const& call) override
        {
            print(call.identifier);
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
            print(access.identifier);
        }

        void visit(Literal const& literal) override
        {
            print(literal.value);
        }

        void visit(UnaryOperation const& unary_operation) override
        {
            print(unary_operation.op.toString());
            print(" ");
            visit(*unary_operation.operand);
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
