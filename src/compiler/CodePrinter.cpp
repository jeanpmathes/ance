#include "CodePrinter.h"

std::ostream& util::operator<<(std::ostream&, const std::any&)
{
    return os;
}

using namespace util;

#define END_STATEMENT ";" << std::endl

CodePrinter::CodePrinter(std::ostream& out) : out_(out) {}

std::any CodePrinter::visit(Addressof& addressof)
{
    out_ << "addressof " << visitChildren(addressof.argument());

    return {};
}

std::any CodePrinter::visit(Allocation& allocation)
{
    out_ << "new";
    if (allocation.count()) out_ << "[" << visitChildren(*allocation.count()) << "]";

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
    out_ << allocation.allocatedType()->getName();

    return {};
}

std::any CodePrinter::visit(BinaryOperation& binary_operation)
{
    out_ << visitChildren(binary_operation.left()) << " ";
    out_ << binary_operation.op().toString() << " ";
    out_ << visitChildren(binary_operation.right());

    return {};
}

std::any CodePrinter::visit(BindRef& bind_ref)
{
    out_ << "ref to " << visitChildren(bind_ref.address());

    return {};
}

std::any CodePrinter::visit(ConstantLiteral& constant_literals)
{
    if (constant_literals.constant().getBackingExpression())
    {
        out_ << visitChildren(*constant_literals.constant().getBackingExpression());
    }
    else {
        out_ << constant_literals.constant().toString();
    }

    return {};
}

std::any CodePrinter::visit(DefaultValue& default_value)
{
    return {};
}

std::any CodePrinter::visit(FunctionCall& function_call)
{
    out_ << function_call.group()->name() << "(";

    bool first = true;

    for (Expression& argument : function_call.arguments())
    {
        out_ << visitChildren(argument);
        if (!first) out_ << ", ";
        first = false;
    }

    out_ << ")";

    return {};
}

std::any CodePrinter::visit(SizeofExpression& sizeof_expression)
{
    out_ << "sizeof(" << visitChildren(sizeof_expression.expression()) << ")";

    return {};
}

std::any CodePrinter::visit(SizeofType& sizeof_type)
{
    out_ << "sizeof " << sizeof_type.type()->getName();

    return {};
}

std::any CodePrinter::visit(Subscript& subscript)
{
    out_ << visitChildren(subscript.indexed());
    out_ << "[" << visitChildren(subscript.index()) << "]";

    return {};
}

std::any CodePrinter::visit(VariableAccess& variable_access)
{
    out_ << variable_access.variable()->identifier();

    return {};
}

std::any CodePrinter::visit(Assertion& assertion)
{
    out_ << "assert " << visitChildren(assertion.condition()) << END_STATEMENT;

    return {};
}

std::any CodePrinter::visit(AssignmentStatement& assignment_statement)
{
    out_ << visitChildren(assignment_statement.assignable()) << " ";
    out_ << assignment_statement.assigner().getSymbol() << " ";
    out_ << visitChildren(assignment_statement.assigned()) << END_STATEMENT;

    return {};
}

std::any CodePrinter::visit(DeleteStatement& delete_statement)
{
    out_ << "delete";
    if (delete_statement.isBufferDelete()) out_ << "[]";

    out_ << " " << visitChildren(delete_statement.toDelete()) << END_STATEMENT;

    return {};
}

std::any CodePrinter::visit(ExpressionStatement& expression_statement)
{
    out_ << visitChildren(expression_statement.expression()) << END_STATEMENT;

    return {};
}

std::any CodePrinter::visit(LocalReferenceVariableDefinition& local_reference_variable_definition)
{
    out_ << "let " << local_reference_variable_definition.identifier();
    out_ << " : " << local_reference_variable_definition.type()->getName() << " ";
    out_ << visitChildren(local_reference_variable_definition.reference()) << END_STATEMENT;

    return {};
}

std::any CodePrinter::visit(LocalVariableDefinition& local_variable_definition)
{
    out_ << "let " << local_variable_definition.identifier();
    out_ << " : " << local_variable_definition.type()->getName();

    if (local_variable_definition.assigned())
    {
        out_ << " " << local_variable_definition.assigner().getSymbol() << " ";
        out_ << visitChildren(*local_variable_definition.assigned());
    }

    out_ << END_STATEMENT;

    return {};
}

std::any CodePrinter::visit(ReturnStatement& return_statement)
{
    out_ << "return";

    if (return_statement.expression()) { out_ << " " << visitChildren(*return_statement.expression()); }

    out_ << END_STATEMENT;

    return {};
}
