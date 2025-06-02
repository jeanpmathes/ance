#include "Printer.h"

#include "ance/core/Printer.h"
#include "ance/est/Node.h"

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
            if (block.statements.empty())
            {
                print("{}");
                return;
            }

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
            print(let.type);

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
            if (if_statement.true_block->isCompound())
            {
                line();
                visit(*if_statement.true_block);
            }
            else
            {
                visit(*if_statement.true_block);
            }
            line();
            print("else ");
            if (if_statement.false_block->isCompound())
            {
                line();
                visit(*if_statement.false_block);
            }
            else
            {
                visit(*if_statement.false_block);
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

        void visit(Continue const&) override
        {
            print("continue;");
        }

        void visit(Temporary const& temporary) override
        {
            print("let temporary ");
            print(temporary.id());
            print(": ");
            print(temporary.type);
            if (temporary.definition.hasValue())
            {
                print(" <: ");
                visit(**temporary.definition);
            }
            print(";");
        }

        void visit(WriteTemporary const& write_temporary) override
        {
            print("temporary ");
            print(write_temporary.temporary.id());
            print(" <: ");
            visit(*write_temporary.value);
            print(");");
        }

        void visit(EraseTemporary const& erase_temporary) override
        {
            print("erase temporary ");
            print(erase_temporary.temporary.id());
            print(";");
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

        void visit(ReadTemporary const& read_temporary) override
        {
            print("(read temporary ");
            print(read_temporary.temporary.id());
            print(")");
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
