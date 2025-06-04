#include "Printer.h"

#include "ance/core/Printer.h"
#include "ance/ret/Node.h"

struct ance::ret::Printer::Implementation
{
    class RET final
        : public Visitor
        , core::Printer
    {
      public:
        using Visitor::visit;

        explicit RET(std::ostream& out) : Printer(out) {}
        ~RET() override = default;

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
            print(let.variable.identifier());
            print(": ");
            print(let.variable.type());

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

        void visit(If const& if_statement) override
        {
            print("if ");
            visit(*if_statement.condition);
            print(" then");
            line();
            visit(*if_statement.true_block);
            line();
            print("else ");
            line();
            visit(*if_statement.false_block);
        }

        void visit(Loop const& loop) override
        {
            print("loop");
            line();
            visit(*loop.body);
        }

        void visit(Break const& ) override { print("break;"); }

        void visit(Continue const& ) override { print("continue;"); }

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

        void visit(ErrorExpression const&) override { print("/* error */"); }

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
            print(constant.value);
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
        utility::Owned<RET> ret = utility::makeOwned<RET>(out_);
        ret->visit(statement);
    }

  private:
    std::ostream& out_;
};

ance::ret::Printer::Printer(std::ostream& out) : implementation_(utility::makeOwned<Implementation>(out)) {}
ance::ret::Printer::~Printer() = default;

void ance::ret::Printer::print(Statement const& statement) const
{
    implementation_->print(statement);
}
