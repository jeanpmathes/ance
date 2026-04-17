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

        void print(Statement const& statement)
        {
            if (statement.isCompound()) line();
            visit(statement);
        }

        using Printer::print;

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
            print(*runnable.body);
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

        void visit(Assignment const& assignment) override
        {
            visit(*assignment.assignee);
            print(" ");
            print(assignment.assigner);
            print(" ");
            visit(*assignment.value);
            print(";");
        }

        void visit(If const& if_statement) override
        {
            print("if ");
            visit(*if_statement.condition);
            print(" then ");
            print(*if_statement.true_block);
            line();
            print("else ");
            print(*if_statement.false_block);
        }

        void visit(Loop const& loop) override
        {
            print("loop ");
            print(*loop.body);
        }

        void visit(Break const&) override
        {
            print("break;");
        }

        void visit(Continue const&) override
        {
            print("continue;");
        }

        void visit(Match const& match_statement) override
        {
            print("match ");
            visit(*match_statement.value);
            print(" with");
            line();
            print("{");
            line();
            enter();

            for (auto& match_case : match_statement.cases)
            {
                visit(*match_case);
                line();
            }

            exit();
            print("}");
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
            print(": ");
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

        void visit(Erase const& erase) override
        {
            print("erase ");
            print(erase.identifier);
            print(";");
        }

        void visit(Assert const& assert) override
        {
            print("assert ");
            visit(*assert.condition);
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

        void visit(BlockExpression const& block_expression) override
        {
            print("({");
            line();
            enter();
            for (auto& statement : block_expression.statements)
            {
                visit(*statement);
                line();
            }
            print("=> ");
            visit(*block_expression.result);
            line();
            exit();
            print("})");
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
            print(", Capture()");// todo: Capture could take a list of entries, each entry is name + type + (either value or reference)
            print(", code ");
            visit(*function_constructor.body);
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

        void visit(FloatingPointLiteral const& floating_point_literal) override
        {
            print(floating_point_literal.value);
            print(floating_point_literal.precision);
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

        void visit(BinaryOperation const& binary_operation) override
        {
            visit(*binary_operation.left);
            print(" ");
            print(binary_operation.op);
            print(" ");
            visit(*binary_operation.right);
        }

        void visit(TypeOf const& type_of) override
        {
            print("typeof(");

            for (size_t index = 0; index < type_of.expressions.size(); index++)
            {
                visit(*type_of.expressions[index]);
                if (index + 1 < type_of.expressions.size()) print(", ");
            }

            print(")");
        }

        void visit(MatchCase const& match_case) override
        {
            if (!match_case.patterns.empty())
            {
                for (size_t index = 0; index < match_case.patterns.size(); index++)
                {
                    visit(*match_case.patterns[index]);
                    if (index + 1 < match_case.patterns.size()) print(" | ");
                }
            }
            else
            {
                print("default");
            }

            print(" => ");
            print(*match_case.body);
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
