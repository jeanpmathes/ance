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

            for (auto const& declaration : file.declarations)
            {
                if (!first) line();
                first = false;

                visit(*declaration);
                line();
            }
        }

        void visit(RunnableDeclaration const& runnable) override
        {
            print("do ");
            if (runnable.body->isCompound())
            {
                line();
                visit(*runnable.body);
            }
            else
            {
                visit(*runnable.body);
            }
        }

        void visit(VariableDeclaration const& variable_declaration) override
        {
            print(variable_declaration.access_modifier);
            print(" ");
            if (variable_declaration.execution_modifier != core::ExecutionModifier::ANY_EXECUTION)
            {
                print(variable_declaration.execution_modifier);
                print(" ");
            }
            print(variable_declaration.identifier);
            print(": ");
            visit(*variable_declaration.type);
            print(" ");
            print(variable_declaration.assigner);
            print(" ");
            if (variable_declaration.value.hasValue())
            {
                visit(**variable_declaration.value);
            }
            else
            {
                print("default");
            }
            print(";");
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

        void visit(Let const& let) override
        {
            print("let ");
            print(let.identifier);
            print(" : ");
            visit(*let.type);
            print(" ");
            print(let.assigner);
            print(" ");
            if (let.value.hasValue())
            {
                visit(**let.value);
            }
            else
            {
                print("default");
            }
            print(";");
        }

        void visit(ErrorExpression const&) override
        {
            print("/* error */");
        }

        void visit(Intrinsic const& intrinsic) override
        {
            print("intrinsic ");
            visit(*intrinsic.name);
            print(" (");
            for (size_t index = 0; index < intrinsic.arguments.size(); index++)
            {
                visit(*intrinsic.arguments[index]);
                if (index + 1 < intrinsic.arguments.size()) print(", ");
            }
            print(")");
        }

        void visit(Call const& call) override
        {
            visit(*call.callee);
            print("(");
            for (size_t index = 0; index < call.arguments.size(); index++)
            {
                if (index > 0) print(", ");
                visit(*call.arguments[index]);
            }
            print(")");
        }

        void visit(FunctionConstructor const& function_constructor) override
        {
            print("Function(Signature(#");
            print(function_constructor.name);
            print(", [");
            for (size_t index = 0; index < function_constructor.parameters.size(); index++)
            {
                if (index > 0) print(", ");
                print("(");
                visit(*function_constructor.parameters[index].type);
                print(", ");
                print(function_constructor.parameters[index].identifier);
                print(")");
            }
            print("]), ");
            visit(*function_constructor.return_type);
            print(", Capture()"); // todo: Capture could take a list of entries, each entry is name + type + (either value or reference)
            print(", code ");
            visit(*function_constructor.body);
            print(")");
        }

        void visit(Read const& read) override
        {
            print("(read ");
            visit(*read.target);
            print(")");
        }

        void visit(Access const& access) override
        {
            print(access.identifier);
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

        void visit(UnaryOperation const& unary_operation) override
        {
            print(unary_operation.op.toString());
            print(" ");
            visit(*unary_operation.operand);
        }

        void visit(TypeOf const& type_of) override
        {
            print("typeof (");
            visit(*type_of.expression);
            print(")");
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

void ance::est::Printer::print(Declaration const& declaration) const
{
    implementation_->print(declaration);
}

void ance::est::Printer::print(Statement const& statement) const
{
    implementation_->print(statement);
}
