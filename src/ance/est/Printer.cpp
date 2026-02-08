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

        void visit(File const& file) override
        {
            bool first = true;

            for (auto const& declaration_statement : file.declaration_statements)
            {
                if (!first)
                {
                    line();
                }
                first = false;

                print("do /* ");
                print(declaration_statement.name);
                print(" */ ");

                if (declaration_statement.statement->isCompound())
                {
                    line();
                    visit(*declaration_statement.statement);
                }
                else
                {
                    visit(*declaration_statement.statement);
                }
            }
        }

        void visit(ErrorStatement const&) override
        {
            print("// error");
        }

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
            print("write(");
            print(core::Assigner::COPY_ASSIGNMENT);
            print(") ");
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

        void visit(Break const&) override
        {
            print("break;");
        }

        void visit(Continue const&) override
        {
            print("continue;");
        }

        void visit(Return const& return_statement) override
        {
            print("return");
            if (return_statement.value.hasValue())
            {
                print(" ");
                visit(**return_statement.value);
            }
            print(";");
        }

        void visit(Temporary const& temporary) override
        {
            print("let temporary ");
            print(temporary.id());
            if (temporary.definition.hasValue())
            {
                print(" ");
                print(core::Assigner::COPY_ASSIGNMENT);
                print(" ");
                visit(**temporary.definition);
            }
            print(";");
        }

        void visit(WriteTemporary const& write_temporary) override
        {
            print("temporary ");
            print(write_temporary.temporary.id());
            print(" ");
            print(core::Assigner::COPY_ASSIGNMENT);
            print(" temporary ");
            visit(*write_temporary.value);
            print(");");
        }

        void visit(ErrorExpression const&) override
        {
            print("/* error */");
        }

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
            visit(*call.callee);
            print("(");
            for (size_t i = 0; i < call.arguments.size(); ++i)
            {
                if (i > 0) print(", ");
                visit(*call.arguments[i]);
            }
            print(")");
        }

        void visit(AnonymousFunctionConstructor const& ctor) override
        {
            print("Function(Signature(");
            for (size_t i = 0; i < ctor.parameters.size(); ++i)
            {
                if (i > 0) print(", ");
                print("(");
                visit(*ctor.parameters[i].type);
                print(", ");
                print(ctor.parameters[i].identifier);
                print(")");
            }
            print("), ");
            visit(*ctor.return_type);
            print(", Capture()"); // todo: Capture could take a list of entries, each entry is name + type + (either value or reference)
            print(", code ");
            visit(*ctor.body);
            print(")");
        }

        void visit(Read const& access) override
        {
            print("(read ");
            visit(*access.target);
            print(")");
        }

        void visit(UnitLiteral const&) override
        {
            print("()");
        }

        void visit(SizeLiteral const& size_literal) override
        {
            print(size_literal.value);
        }

        void visit(StringLiteral const& string_literal) override
        {
            print("\"" + string_literal.value + "\"");
        }

        void visit(BoolLiteral const& bool_literal) override
        {
            print(bool_literal.value ? "true" : "false");
        }

        void visit(Default const& default_value) override
        {
            print("default (");
            visit(*default_value.type);
            print(")");
        }

        void visit(Here const&) override
        {
            print("here");
        }

        void visit(CurrentScope const&) override
        {
            print("scope");
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

    void print(Node const& node) const
    {
        utility::Owned<EST> est = utility::makeOwned<EST>(out_);
        est->visit(node);
    }

  private:
    std::ostream& out_;
};

ance::est::Printer::Printer(std::ostream& out) : implementation_(utility::makeOwned<Implementation>(out)) {}
ance::est::Printer::~Printer() = default;

void ance::est::Printer::print(File const& file) const
{
    implementation_->print(file);
}

void ance::est::Printer::print(Statement const& statement) const
{
    implementation_->print(statement);
}
