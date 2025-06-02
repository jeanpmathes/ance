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

        void visit(Flow const& flow) override
        {
            for (auto& block : flow.blocks)
            {
                visit(*block);
                line();
            }
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

        void visit(ErrorLink const&) override
        {
            print("/* error */");
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

    void print(Flow const& flow) const
    {
        utility::Owned<BBT> bbt = utility::makeOwned<BBT>(out_);
        bbt->visit(flow);
    }

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

void ance::bbt::Printer::print(Flow const& flow) const
{
    implementation_->print(flow);
}

void ance::bbt::Printer::print(BasicBlock const& block) const
{
    implementation_->print(block);
}
