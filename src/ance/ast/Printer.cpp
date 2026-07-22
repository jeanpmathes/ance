#include "Printer.h"

#include <ranges>

#include "ance/ast/Node.h"

#include "ance/core/Printer.h"

struct ance::ast::Printer::Implementation
{
    class AST
        : public Visitor
        , core::Printer
    {
      public:
        using Visitor::visit;

        explicit AST(std::ostream& out) : Printer(out) {}
        ~AST() override = default;

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

        void visit(ErrorDeclaration const&) override
        {
            print("// error");
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
            if (variable_declaration.value.hasValue())
            {
                print(" ");
                print(variable_declaration.assigner);
                print(" ");
                visit(**variable_declaration.value);
            }
            print(";");
        }

        void visit(FunctionDeclaration const& function_declaration) override
        {
            print(function_declaration.access_modifier);
            print(" ");

            if (function_declaration.execution_modifier != core::ExecutionModifier::ANY_EXECUTION)
            {
                print(function_declaration.execution_modifier);
                print(" ");
            }

            print(function_declaration.identifier);
            print(" (");

            for (size_t const index : std::views::iota(size_t {0}, function_declaration.parameters.size()))
            {
                print(function_declaration.parameters[index].identifier);
                print(": ");
                visit(*function_declaration.parameters[index].type);
                if (index + 1 < function_declaration.parameters.size()) print(", ");
            }

            print(")");

            if (function_declaration.return_type.hasValue())
            {
                print(" : ");
                visit(**function_declaration.return_type);
            }

            line();
            visit(*function_declaration.body);
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

        void visit(Bind const& bind) override
        {
            print(bind.variability.toBindingKeyword());
            print(" ");
            print(bind.identifier);
            print(": ");
            visit(*bind.type);

            if (bind.value.hasValue())
            {
                print(" ");
                print(bind.assigner);
                print(" ");
                visit(**bind.value);
            }

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

            print(*if_statement.true_part);

            if (if_statement.false_part.hasValue())
            {
                line();
                print("else ");
                print(**if_statement.false_part);
            }
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
            print(*while_statement.body);
        }

        void visit(Match const& match_statement) override
        {
            print("match ");
            visit(*match_statement.condition);
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

        void visit(And const& and_expression) override
        {
            visit(*and_expression.left);
            if (and_expression.negated) print(" not");
            print(" and ");
            visit(*and_expression.right);
        }

        void visit(Or const& or_expression) override
        {
            visit(*or_expression.left);
            if (or_expression.negated) print(" not");
            print(" or ");
            visit(*or_expression.right);
        }

        void visit(Call const& call) override
        {
            visit(*call.callee);
            print("(");

            for (size_t const index : std::views::iota(size_t {0}, call.arguments.size()))
            {
                visit(*call.arguments[index]);
                if (index + 1 < call.arguments.size()) print(", ");
            }

            print(")");
        }

        void visit(Subscript const& subscript) override
        {
            visit(*subscript.indexed);
            print("[");
            visit(*subscript.index);
            print("]");
        }

        void visit(Lambda const& lambda) override
        {
            print("\\[](");

            for (size_t const index : std::views::iota(size_t {0}, lambda.parameters.size()))
            {
                print(lambda.parameters[index].identifier);
                print(": ");
                visit(*lambda.parameters[index].type);
                if (index + 1 < lambda.parameters.size()) print(", ");
            }

            print(")");

            if (lambda.return_type.hasValue())
            {
                print(" : ");
                visit(**lambda.return_type);
            }

            if (lambda.expression_body.hasValue())
            {
                print(" => ");
                visit(**lambda.expression_body);
            }
            else if (lambda.statement_body.hasValue())
            {
                print(**lambda.statement_body);
            }
        }

        void visit(Intrinsic const& intrinsic_expression) override
        {
            print("intrinsic ");
            visit(*intrinsic_expression.name);
            print(" args (");

            for (size_t const index : std::views::iota(size_t {0}, intrinsic_expression.arguments.size()))
            {
                visit(*intrinsic_expression.arguments[index]);
                if (index + 1 < intrinsic_expression.arguments.size()) print(", ");
            }

            print(")");
        }

        void visit(TypeOf const& type_of) override
        {
            print("typeof(");

            for (size_t const index : std::views::iota(size_t {0}, type_of.expressions.size()))
            {
                visit(*type_of.expressions[index]);
                if (index + 1 < type_of.expressions.size()) print(", ");
            }

            print(")");
        }

        void visit(ArrayTypeConstructor const& array_type) override
        {
            print("[");
            visit(*array_type.element_type);
            print("; ");
            visit(*array_type.length);
            print("]");
        }

        void visit(ArrayConstructor const& array_constructor) override
        {
            print("[");

            if (array_constructor.element_type.hasValue())
            {
                visit(**array_constructor.element_type);
                print(" | ");
            }

            for (size_t const index : std::views::iota(size_t {0}, array_constructor.elements.size()))
            {
                visit(*array_constructor.elements[index]);
                if (index + 1 < array_constructor.elements.size()) print(", ");
            }

            print("]");
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

            if (block_expression.result.hasValue())
            {
                print("=> ");
                visit(**block_expression.result);
                line();
            }

            exit();
            print("})");
        }

        void visit(Parenthesis const& parenthesis) override
        {
            print("(");
            visit(*parenthesis.contained);
            print(")");
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

        void visit(FloatingPointLiteral const& literal) override
        {
            print(literal.value);
            print(literal.precision);
        }

        void visit(StringLiteral const& string_literal) override
        {
            print("\"" + string_literal.value + "\"");
        }

        void visit(BoolLiteral const& bool_literal) override
        {
            print(bool_literal.value ? "true" : "false");
        }

        void visit(IfExpression const& if_expression) override
        {
            print("if ");
            visit(*if_expression.condition);
            print(" then ");
            visit(*if_expression.then_expression);
            print(" else ");
            visit(*if_expression.else_expression);
        }

        void visit(MatchExpression const& match_expression) override
        {
            print("match ");
            visit(*match_expression.condition);
            print(" with");
            line();
            print("{");
            line();
            enter();

            for (size_t const index : std::views::iota(size_t {0}, match_expression.cases.size()))
            {
                visit(*match_expression.cases[index]);
                if (index + 1 < match_expression.cases.size())
                {
                    print(",");
                    line();
                }
            }

            exit();
            line();
            print("}");
        }

        void visit(UnaryOperation const& unary_operation) override
        {
            print(unary_operation.op);
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

        void visit(MatchCase const& match_case) override
        {
            if (!match_case.patterns.empty())
            {
                for (size_t const index : std::views::iota(size_t {0}, match_case.patterns.size()))
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

        void visit(MatchExpressionCase const& match_case) override
        {
            if (!match_case.patterns.empty())
            {
                for (size_t const index : std::views::iota(size_t {0}, match_case.patterns.size()))
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
            visit(*match_case.result);
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

void ance::ast::Printer::print(Declaration const& declaration) const
{
    implementation_->print(declaration);
}

void ance::ast::Printer::print(Statement const& statement) const
{
    implementation_->print(statement);
}
