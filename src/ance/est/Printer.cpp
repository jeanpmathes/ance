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

        void visit(Pass const&) override
        {
            print("pass;");
        }

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

        void visit(Write const& assignment) override
        {
            print("write(<:) ");
            visit(*assignment.value);
            print(" to ");
            visit(*assignment.target);
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
            print(" <: temporary ");
            visit(*write_temporary.value);
            print(");");
        }

        void visit(ErrorExpression const&) override { print("/* error */"); }

        void visit(Intrinsic const& intrinsic) override
        {
            print("intrinsic(");
            print(intrinsic.intrinsic);
            for (size_t i = 0; i < intrinsic.arguments.size(); ++i)
            {
                print(", ");
                visit(*intrinsic.arguments[i]);
            }
            print(")");
        }

        void visit(Call const& call) override
        {
            print(call.identifier);
            print("(");
            for (size_t i = 0; i < call.arguments.size(); ++i)
            {
                if (i > 0) print(", ");
                visit(*call.arguments[i]);
            }
            print(")");
        }

        void visit(Read const& access) override
        {
            print("read ");
            visit(*access.target);
        }

        void visit(Literal const& literal) override
        {
            print(literal.value);
        }

        void visit(Here const&) override
        {
            print("here");
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

        void visit(TypeOf const& type_of) override
        {
            print("typeof (");
            visit(*type_of.expression);
            print(")");
        }

        void visit(IdentifierCapture const& identifier_capture) override
        {
            print("#");
            print(identifier_capture.identifier);
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
