#include "CodePrinter.h"

#include "lang/type/VoidType.h"

std::ostream& util::operator<<(std::ostream& os, const std::any&)
{
    return os;
}

using namespace util;

CodePrinter::CodePrinter(std::ostream& out) : out_(out) {}

std::any CodePrinter::visit(lang::GlobalVariable& variable)
{
    indent();

    out_ << variable.access().toString() << " ";
    if (variable.isConstant())
        out_ << "const"
             << " ";
    out_ << variable.name() << ": ";
    out_ << variable.type()->name();

    if (variable.init())
    {
        out_ << " " << variable.assigner().getSymbol() << " ";
        out_ << variable.init()->toString();
    }

    out_ << ";" << std::endl;

    return {};
}

std::any CodePrinter::visit(lang::CustomFunction& function)
{
    indent();

    out_ << function.access().toString() << " ";
    out_ << function.name() << " ";
    out_ << function.parameterSource();

    if (function.returnType() != lang::VoidType::get()) { out_ << " : " << function.returnType()->name(); }

    out_ << std::endl;

    out_ << visitTree(function.code()) << std::endl;

    return {};
}

std::any CodePrinter::visit(lang::ExternFunction& function)
{
    indent();

    out_ << "extern " << function.name() << " ";
    out_ << function.parameterSource() << ";" << std::endl;

    return {};
}

std::any CodePrinter::visit(Addressof& addressof)
{
    out_ << "addressof " << visitTree(addressof.argument());

    return {};
}

std::any CodePrinter::visit(Allocation& allocation)
{
    out_ << "new";
    if (allocation.count()) out_ << "[" << visitTree(*allocation.count()) << "]";

    std::string allocator;
    switch (allocation.allocator())
    {
        case Runtime::AUTOMATIC:
            allocator = "automatic";
            break;
        case Runtime::DYNAMIC:
            allocator = "dynamic";
            break;
    }

    out_ << " " << allocator << " ";
    out_ << allocation.allocatedType()->name();

    return {};
}

std::any CodePrinter::visit(And& an_and)
{
    visitTree(an_and.left());
    out_ << " and ";
    visitTree(an_and.right());

    return {};
}

std::any CodePrinter::visit(BinaryOperation& binary_operation)
{
    out_ << visitTree(binary_operation.left()) << " ";
    out_ << binary_operation.op().toString() << " ";
    out_ << visitTree(binary_operation.right());

    return {};
}

std::any CodePrinter::visit(BindRef& bind_ref)
{
    out_ << "ref " << visitTree(bind_ref.value());

    return {};
}

std::any CodePrinter::visit(BindRefTo& bind_ref_to)
{
    out_ << "ref to " << visitTree(bind_ref_to.address());

    return {};
}

std::any CodePrinter::visit(ConstantLiteral& constant_literals)
{
    if (constant_literals.constant().getBackingExpression())
    {
        out_ << visitTree(*constant_literals.constant().getBackingExpression());
    }
    else {
        out_ << constant_literals.constant().toString();
    }

    return {};
}

std::any CodePrinter::visit(FunctionCall& function_call)
{
    out_ << function_call.group()->name() << "(";

    bool first = true;

    for (Expression& argument : function_call.arguments())
    {
        if (!first) out_ << ", ";
        first = false;

        out_ << visitTree(argument);
    }

    out_ << ")";

    return {};
}

std::any CodePrinter::visit(IfSelect& if_select)
{
    out_ << "if " << visitTree(if_select.condition()) << " ";
    out_ << "then " << visitTree(if_select.thenExpression()) << " ";
    out_ << "else " << visitTree(if_select.elseExpression()) << " ";

    return {};
}

std::any CodePrinter::visit(MatchSelect& match_select)
{
    out_ << "match " << visitTree(match_select.condition()) << " with ";
    out_ << "{ ";

    bool first_case = true;
    for (auto& case_ref : match_select.cases())
    {
        if (!first_case) out_ << ", ";
        first_case = false;

        bool first_condition = true;
        for (auto& condition : case_ref.get().conditions())
        {
            if (!first_condition) out_ << " | ";
            first_condition = false;

            out_ << visitTree(condition);
        }

        out_ << " => " << visitTree(case_ref.get().code());
    }

    out_ << " }";

    return {};
}

std::any CodePrinter::visit(Or& an_or)
{
    visitTree(an_or.left());
    out_ << " or ";
    visitTree(an_or.right());

    return {};
}

std::any CodePrinter::visit(Parenthesis& parenthesis)
{
    out_ << "(" << visitTree(parenthesis.contained()) << ")";

    return {};
}

std::any CodePrinter::visit(SizeofExpression& sizeof_expression)
{
    out_ << "sizeof(" << visitTree(sizeof_expression.expression()) << ")";

    return {};
}

std::any CodePrinter::visit(SizeofType& sizeof_type)
{
    out_ << "sizeof " << sizeof_type.targetType()->name();

    return {};
}

std::any CodePrinter::visit(Subscript& subscript)
{
    out_ << visitTree(subscript.indexed());
    out_ << "[" << visitTree(subscript.index()) << "]";

    return {};
}

std::any CodePrinter::visit(UnaryOperation& unary_operation)
{
    out_ << unary_operation.op().toString() << " ";
    out_ << visitTree(unary_operation.operand());

    return {};
}

std::any CodePrinter::visit(VariableAccess& variable_access)
{
    out_ << variable_access.variable()->name();

    return {};
}

std::any CodePrinter::visit(lang::CodeBlock& code_block)
{
    if (code_block.isCompound())
    {
        out_ << "{" << std::endl;
        indent_++;

        for (auto& statement : code_block.statements())
        {
            indent();
            visitTree(statement);
            out_ << std::endl;
        }

        indent_--;
        indent();
        out_ << "}";
    }
    else {
        assert(code_block.statements().size() == 1);
        visitTree(code_block.statements()[0]);
    }

    return {};
}

std::any CodePrinter::visit(Assertion& assertion)
{
    out_ << "assert " << visitTree(assertion.condition()) << ";";

    return {};
}

std::any CodePrinter::visit(Assignment& assignment_statement)
{
    out_ << visitTree(assignment_statement.assignable()) << " ";
    out_ << assignment_statement.assigner().getSymbol() << " ";
    out_ << visitTree(assignment_statement.assigned()) << ";";

    return {};
}

std::any CodePrinter::visit(Delete& delete_statement)
{
    out_ << "delete";
    if (delete_statement.isBufferDelete()) out_ << "[]";

    out_ << " " << visitTree(delete_statement.toDelete()) << ";";

    return {};
}

std::any CodePrinter::visit(Drop& drop_statement)
{
    out_ << "drop " << drop_statement.variable()->name() << ";";

    return {};
}

std::any CodePrinter::visit(ExpressionStatement& expression_statement)
{
    out_ << visitTree(expression_statement.expression()) << ";";

    return {};
}

std::any CodePrinter::visit(If& if_statement)
{
    out_ << "if " << visitTree(if_statement.condition()) << " then";

    if (if_statement.ifBlock()->isCompound())
    {
        out_ << std::endl;
        indent();
        visitTree(*if_statement.ifBlock());
    }
    else {
        out_ << " " << visitTree(*if_statement.ifBlock());
    }

    if (if_statement.elseBlock())
    {
        out_ << std::endl;
        indent();
        out_ << "else";

        if (if_statement.elseBlock()->isCompound())
        {
            out_ << std::endl;
            indent();
            visitTree(*if_statement.elseBlock());
        }
        else {
            out_ << " " << visitTree(*if_statement.elseBlock());
        }
    }

    return {};
}

std::any CodePrinter::visit(LocalReferenceVariableDefinition& local_reference_variable_definition)
{
    out_ << "let " << local_reference_variable_definition.name();
    out_ << ": " << local_reference_variable_definition.type()->name() << " ";
    out_ << visitTree(local_reference_variable_definition.reference()) << ";";

    return {};
}

std::any CodePrinter::visit(LocalVariableDefinition& local_variable_definition)
{
    out_ << "let " << local_variable_definition.name();
    out_ << ": " << local_variable_definition.type()->name();

    if (local_variable_definition.assigned())
    {
        out_ << " " << local_variable_definition.assigner().getSymbol() << " ";
        out_ << visitTree(*local_variable_definition.assigned());
    }

    out_ << ";";

    return {};
}

std::any CodePrinter::visit(Match& match_statement)
{
    out_ << "match " << visitTree(match_statement.expression()) << " with" << std::endl;
    indent();
    out_ << "{ " << std::endl;
    indent_++;

    for (auto& case_ref : match_statement.cases())
    {
        indent();

        size_t condition_number = 0;
        for (auto& condition : case_ref.get().conditions())
        {
            if (condition_number > 0) out_ << " | ";
            condition_number++;

            out_ << visitTree(condition);
        }

        if (condition_number == 0) { out_ << "default"; }

        out_ << " => " << visitTree(case_ref.get().code()) << std::endl;
    }

    indent_--;
    indent();
    out_ << "}";

    return {};
}

std::any CodePrinter::visit(Return& return_statement)
{
    out_ << "return";

    if (return_statement.expression()) { out_ << " " << visitTree(*return_statement.expression()); }

    out_ << ";";

    return {};
}

std::any CodePrinter::visit(While& while_statement)
{
    out_ << "while " << visitTree(while_statement.condition()) << " do";

    if (while_statement.body().isCompound())
    {
        out_ << std::endl;
        indent();
        visitTree(while_statement.body());
    }
    else {
        out_ << " " << visitTree(while_statement.body());
    }

    return {};
}

void CodePrinter::indent()
{
    out_ << std::string(indent_ * 4, ' ');
}

