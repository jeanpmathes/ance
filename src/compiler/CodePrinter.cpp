#include "CodePrinter.h"

#include "lang/type/VoidType.h"

std::ostream& util::operator<<(std::ostream& os, const std::any&)
{
    return os;
}

using namespace util;

#define END_STATEMENT ";" << std::endl

CodePrinter::CodePrinter(std::ostream& out) : out_(out) {}

std::any CodePrinter::visit(lang::CustomFunction& function)
{
    indent();

    out_ << function.access().toString() << " ";
    out_ << function.name() << " ";
    out_ << function.parameterSource();

    if (function.returnType() != lang::VoidType::get()) { out_ << " : " << function.returnType()->getName(); }

    out_ << std::endl;

    out_ << visitTree(function.code());

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
    out_ << allocation.allocatedType()->getName();

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
    out_ << "ref to " << visitTree(bind_ref.address());

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

std::any CodePrinter::visit(DefaultValue&)
{
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
    out_ << "sizeof " << sizeof_type.targetType()->getName();

    return {};
}

std::any CodePrinter::visit(Subscript& subscript)
{
    out_ << visitTree(subscript.indexed());
    out_ << "[" << visitTree(subscript.index()) << "]";

    return {};
}

std::any CodePrinter::visit(VariableAccess& variable_access)
{
    out_ << variable_access.variable()->identifier();

    return {};
}

std::any CodePrinter::visit(lang::CodeBlock& code_block)
{
    indent();
    out_ << "{" << std::endl;
    indent_++;

    for (auto& statement : code_block.statements()) { visitTree(statement); }

    indent_--;
    indent();
    out_ << "}" << std::endl;

    return {};
}

std::any CodePrinter::visit(Assertion& assertion)
{
    indent();

    out_ << "assert " << visitTree(assertion.condition()) << END_STATEMENT;

    return {};
}

std::any CodePrinter::visit(Assignment& assignment_statement)
{
    indent();

    out_ << visitTree(assignment_statement.assignable()) << " ";
    out_ << assignment_statement.assigner().getSymbol() << " ";
    out_ << visitTree(assignment_statement.assigned()) << END_STATEMENT;

    return {};
}

std::any CodePrinter::visit(Delete& delete_statement)
{
    indent();

    out_ << "delete";
    if (delete_statement.isBufferDelete()) out_ << "[]";

    out_ << " " << visitTree(delete_statement.toDelete()) << END_STATEMENT;

    return {};
}

std::any CodePrinter::visit(ExpressionStatement& expression_statement)
{
    indent();

    out_ << visitTree(expression_statement.expression()) << END_STATEMENT;

    return {};
}

std::any CodePrinter::visit(LocalReferenceVariableDefinition& local_reference_variable_definition)
{
    indent();

    out_ << "let " << local_reference_variable_definition.identifier();
    out_ << ": " << local_reference_variable_definition.type()->getName() << " ";
    out_ << visitTree(local_reference_variable_definition.reference()) << END_STATEMENT;

    return {};
}

std::any CodePrinter::visit(LocalVariableDefinition& local_variable_definition)
{
    indent();

    out_ << "let " << local_variable_definition.identifier();
    out_ << ": " << local_variable_definition.type()->getName();

    if (local_variable_definition.assigned())
    {
        out_ << " " << local_variable_definition.assigner().getSymbol() << " ";
        out_ << visitTree(*local_variable_definition.assigned());
    }

    out_ << END_STATEMENT;

    return {};
}

std::any CodePrinter::visit(Return& return_statement)
{
    indent();

    out_ << "return";

    if (return_statement.expression()) { out_ << " " << visitTree(*return_statement.expression()); }

    out_ << END_STATEMENT;

    return {};
}

void CodePrinter::indent()
{
    out_ << std::string(indent_ * 4, ' ');
}
