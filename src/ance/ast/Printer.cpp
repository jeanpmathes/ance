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

        void visit(File const& file) override
        {
            bool first = true;

            for (auto const& declaration : file.declarations)
            {
                if (!first)
                {
                    line();
                }
                first = false;

                visit(*declaration);
            }
        }

        void visit(ErrorDeclaration const&) override
        {
            print("// error");
        }

        void visit(RunnableDeclaration const& runnable) override
        {
            print("do ");

            if (runnable.body->isCompound()) line();

            visit(*runnable.body);
        }

        void visit(VariableDeclaration const& variable_declaration) override
        {
            print(variable_declaration.access_modifier);
            print(" cmp ");
            print(variable_declaration.identifier);
            print(": ");
            visit(*variable_declaration.type);

            if (variable_declaration.value.hasValue())
            {
                print(" ");
                print(variable_declaration.assigner);
                print(" ");
                visit(**variable_declaration.value);
            }

            print(";");
        }

        void visit(ErrorStatement const&) override
        {
            print("// error");
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

        void visit(Let const& let) override
        {
            print("let ");
            print(let.identifier);
            print(": ");
            visit(*let.type);

            if (let.value.hasValue())
            {
                print(" ");
                print(let.assigner);
                print(" ");
                visit(**let.value);
            }

            print(";");
        }

        void visit(Assignment const& assignment) override
        {
            print(assignment.identifier);
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

        void visit(ErrorExpression const&) override
        {
            print("/* error */");
        }

        void visit(Call const& call) override
        {
            visit(*call.callee);
            print("(");
            for (size_t index = 0; index < call.arguments.size(); ++index)
            {
                visit(*call.arguments[index]);
                if (index + 1 < call.arguments.size()) print(", ");
            }
            print(")");
        }

        void visit(Lambda const& lambda) override
        {
            print("\\[](");
            for (size_t index = 0; index < lambda.parameters.size(); ++index)
            {
                print(lambda.parameters[index].identifier);
                print(": ");
                visit(*lambda.parameters[index].type);
                if (index + 1 < lambda.parameters.size()) print(", ");
            }
            print(") : ");
            visit(*lambda.return_type);
            if (lambda.expression_body.hasValue())
            {
                print(" => ");
                visit(**lambda.expression_body);
            }
            else if (lambda.statement_body.hasValue())
            {
                if ((*lambda.statement_body)->isCompound())
                {
                    line();
                    visit(**lambda.statement_body);
                }
                else
                {
                    visit(**lambda.statement_body);
                }
            }
        }

        void visit(Access const& access) override
        {
            print(access.identifier);
        }

        void visit(Here const&) override
        {
            print("here");
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

        void visit(UnaryOperation const& unary_operation) override
        {
            print(unary_operation.op);
            print(" ");
            visit(*unary_operation.operand);
        }
    };

    explicit Implementation(std::ostream& out) : out_(out) {}

    void print(Node const& node) const
    {
        utility::Owned<AST> ast = utility::makeOwned<AST>(out_);

        ast->visit(node);
    }

  private:
    std::ostream& out_;
};

ance::ast::Printer::Printer(std::ostream& out) : implementation_(utility::makeOwned<Implementation>(out)) {}
ance::ast::Printer::~Printer() = default;

void ance::ast::Printer::print(File const& file) const
{
    implementation_->print(file);
}

void ance::ast::Printer::print(Statement const& statement) const
{
    implementation_->print(statement);
}
