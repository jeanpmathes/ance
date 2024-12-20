#include "CodePrinter.h"

#include "lang/construct/Callable.h"

std::ostream& util::operator<<(std::ostream& os, std::any const&)
{
    return os;
}

using namespace util;

CodePrinter::CodePrinter(std::ostream& out) : out_(out) {}

std::any CodePrinter::visit(lang::VariableDescription const& variable_description)
{
    indent();

    assert(variable_description.variable());
    lang::GlobalVariable const& variable = *variable_description.variable();

    out_ << variable.access().toString() << " ";
    if (variable.cmp().isCompileTime()) out_ << variable.cmp().toString() << " ";
    out_ << variable.name() << ": ";
    out_ << variable.type().name();

    if (variable_description.initializer())
    {
        out_ << " " << variable.assigner().getSymbol() << " ";
        visitTree(*variable_description.initializer());
    }

    out_ << ";" << std::endl;

    if (variable_description.initializerFunction())
    {
        indent();
        emitFunction(variable_description.initializerFunction()->function());
    }

    return {};
}

std::any CodePrinter::visit(lang::FunctionDescription const& function_description)
{
    indent();

    assert(function_description.function());
    lang::Function const& function = *function_description.function();

    emitFunction(function);

    return {};
}

std::any CodePrinter::visit(lang::StructDescription const& struct_description)
{
    indent();

    out_ << struct_description.access().modifier().toString() << " ";
    out_ << "struct " << struct_description.name() << std::endl;

    indent();
    indent_++;
    out_ << "{" << std::endl;

    for (auto& member : struct_description.members())
    {
        indent();
        visitTree(member);
        out_ << std::endl;
    }

    indent_--;
    indent();
    out_ << "}" << std::endl;

    return {};
}

std::any CodePrinter::visit(lang::AliasDescription const& alias_description)
{
    indent();

    out_ << alias_description.access().modifier().toString() << " ";
    out_ << "define " << alias_description.name() << " ";
    out_ << "alias " << alias_description.actual().name() << ";" << std::endl;

    return {};
}

std::any CodePrinter::visit(lang::Member const& member)
{
    out_ << member.access().toString() << " ";
    out_ << member.name() << ": ";
    out_ << member.type().name() << ";";

    return {};
}

std::any CodePrinter::visit(Addressof const& addressof)
{
    out_ << "addressof " << visitTree(addressof.argument());

    return {};
}

std::any CodePrinter::visit(Allocation const& allocation)
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
    out_ << allocation.allocatedType().name();

    return {};
}

std::any CodePrinter::visit(And const& an_and)
{
    visitTree(an_and.left());
    if (an_and.negate()) out_ << " not";
    out_ << " and ";
    visitTree(an_and.right());

    return {};
}

std::any CodePrinter::visit(ArrayDefinition const& array_definition)
{
    out_ << "[";

    if (array_definition.elementType().hasValue())
    {
        out_ << array_definition.elementType().value().get().name() << " | ";
    }

    bool is_first = true;
    for (auto& value : array_definition.values())
    {
        if (not is_first) out_ << ", ";
        is_first = false;

        visitTree(value);
    }

    out_ << "]";

    return {};
}

std::any CodePrinter::visit(BinaryOperation const& binary_operation)
{
    out_ << visitTree(binary_operation.left()) << " ";
    out_ << binary_operation.op().toString() << " ";
    out_ << visitTree(binary_operation.right());

    return {};
}

std::any CodePrinter::visit(BindRef const& bind_ref)
{
    out_ << "ref " << visitTree(bind_ref.value());

    return {};
}

std::any CodePrinter::visit(BindRefTo const& bind_ref_to)
{
    out_ << "ref to " << visitTree(bind_ref_to.address());

    return {};
}

std::any CodePrinter::visit(Cast const& visitable)
{
    out_ << visitTree(visitable.value()) << " as " << visitable.target().name();

    return {};
}

std::any CodePrinter::visit(LiteralExpression const& constant_literals)
{
    out_ << constant_literals.constant().toString();

    return {};
}

std::any CodePrinter::visit(FunctionCall const& function_call)
{
    out_ << function_call.callee().name() << "(";

    bool first = true;

    for (Expression const& argument : function_call.arguments())
    {
        if (!first) out_ << ", ";
        first = false;

        out_ << visitTree(argument);
    }

    out_ << ")";

    return {};
}

std::any CodePrinter::visit(IfSelect const& if_select)
{
    out_ << "if " << visitTree(if_select.condition()) << " ";
    out_ << "then " << visitTree(if_select.thenExpression());

    if (if_select.elseExpression() != nullptr)
        out_ << " else " << visitTree(*if_select.elseExpression());

    return {};
}

std::any CodePrinter::visit(MatchSelect const& match_select)
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

std::any CodePrinter::visit(Or const& an_or)
{
    visitTree(an_or.left());
    if (an_or.negate()) out_ << " not";
    out_ << " or ";
    visitTree(an_or.right());

    return {};
}

std::any CodePrinter::visit(Parenthesis const& parenthesis)
{
    out_ << "(" << visitTree(parenthesis.contained()) << ")";

    return {};
}

std::any CodePrinter::visit(SizeofExpression const& sizeof_expression)
{
    out_ << "sizeof(" << visitTree(sizeof_expression.expression()) << ")";

    return {};
}

std::any CodePrinter::visit(SizeofType const& sizeof_type)
{
    out_ << "sizeof " << sizeof_type.target().name();

    return {};
}

std::any CodePrinter::visit(Subscript const& subscript)
{
    out_ << visitTree(subscript.indexed());
    out_ << "[" << visitTree(subscript.index()) << "]";

    return {};
}

std::any CodePrinter::visit(UnaryOperation const& unary_operation)
{
    out_ << unary_operation.op().toString() << " ";
    out_ << visitTree(unary_operation.operand());

    return {};
}

std::any CodePrinter::visit(VariableAccess const& variable_access)
{
    out_ << variable_access.variable().name();

    return {};
}

std::any CodePrinter::visit(VectorDefinition const& vector_definition)
{
    out_ << "<";

    if (vector_definition.elementType().hasValue())
    {
        out_ << vector_definition.elementType().value().get().name() << " | ";
    }

    bool is_first = true;
    for (auto& value : vector_definition.values())
    {
        if (not is_first) out_ << ", ";
        is_first = false;

        visitTree(value);
    }

    out_ << ">";

    return {};
}

std::any CodePrinter::visit(MemberAccess const& member_access)
{
    out_ << visitTree(member_access.value());
    emitWhitespace();
    out_ << member_access.member();

    return {};
}

std::any CodePrinter::visit(Indirection const& indirection)
{
    out_ << visitTree(indirection.value()) << ".";
    consumeWhitespace();

    return {};
}

std::any CodePrinter::visit(lang::CodeBlock const& code_block)
{
    if (code_block.isCompound())
    {
        out_ << "{" << std::endl;
        indent_++;

        for (auto const& statement : code_block.statements())
        {
            indent();
            visitTree(statement);
            out_ << std::endl;
        }

        indent_--;
        indent();
        out_ << "}";
    }
    else
    {
        assert(code_block.statements().size() == 1);
        visitTree(code_block.statements()[0]);
    }

    return {};
}

std::any CodePrinter::visit(Assertion const& assertion)
{
    out_ << "assert " << visitTree(assertion.condition()) << ";";

    return {};
}

std::any CodePrinter::visit(Assignment const& assignment_statement)
{
    out_ << visitTree(assignment_statement.assignable()) << " ";
    out_ << assignment_statement.assigner().getSymbol() << " ";
    out_ << visitTree(assignment_statement.assigned()) << ";";

    return {};
}

std::any CodePrinter::visit(Break const&)
{
    out_ << "break;";

    return {};
}

std::any CodePrinter::visit(Continue const&)
{
    out_ << "continue;";

    return {};
}

std::any CodePrinter::visit(Delete const& delete_statement)
{
    out_ << "delete";
    if (delete_statement.isBufferDelete()) out_ << "[]";

    out_ << " " << visitTree(delete_statement.toDelete()) << ";";

    return {};
}

std::any CodePrinter::visit(Erase const& erase_statement)
{
    out_ << "erase " << erase_statement.variable().name() << ";";

    return {};
}

std::any CodePrinter::visit(ExpressionStatement const& expression_statement)
{
    out_ << visitTree(expression_statement.expression()) << ";";

    return {};
}

std::any CodePrinter::visit(If const& if_statement)
{
    out_ << "if " << visitTree(if_statement.condition()) << " then";

    if (if_statement.ifBlock()->isCompound())
    {
        out_ << std::endl;
        indent();
        visitTree(*if_statement.ifBlock());
    }
    else { out_ << " " << visitTree(*if_statement.ifBlock()); }

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
        else { out_ << " " << visitTree(*if_statement.elseBlock()); }
    }

    return {};
}

std::any CodePrinter::visit(LocalReferenceVariableDefinition const& local_reference_variable_definition)
{
    out_ << "let " << local_reference_variable_definition.name();
    out_ << ": " << local_reference_variable_definition.type().name() << " ";
    out_ << visitTree(local_reference_variable_definition.reference()) << ";";

    return {};
}

std::any CodePrinter::visit(LocalVariableDefinition const& local_variable_definition)
{
    out_ << "let " << local_variable_definition.name();
    if (local_variable_definition.type() != nullptr) out_ << ": " << local_variable_definition.type()->name();

    if (local_variable_definition.assigned())
    {
        out_ << " " << local_variable_definition.assigner().getSymbol() << " ";
        out_ << visitTree(*local_variable_definition.assigned());
    }

    out_ << ";";

    return {};
}

std::any CodePrinter::visit(Match const& match_statement)
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

std::any CodePrinter::visit(Return const& return_statement)
{
    out_ << "return";

    if (return_statement.expression()) { out_ << " " << visitTree(*return_statement.expression()); }

    out_ << ";";

    return {};
}

std::any CodePrinter::visit(While const& while_statement)
{
    out_ << "while " << visitTree(while_statement.condition()) << " do";

    if (while_statement.body().isCompound())
    {
        out_ << std::endl;
        indent();
        visitTree(while_statement.body());
    }
    else { out_ << " " << visitTree(while_statement.body()); }

    return {};
}

std::any CodePrinter::visit(Loop const& loop_statement)
{
    out_ << "loop";

    if (loop_statement.body().isCompound())
    {
        out_ << std::endl;
        indent();
        visitTree(loop_statement.body());
    }
    else { out_ << " " << visitTree(loop_statement.body()); }

    return {};
}

void CodePrinter::postVisit(lang::Visitable<ANCE_CONSTRUCTS> const&)
{
    switch (consume_whitespace_)
    {
        case CONSUME_WS_DISABLED:
        case CONSUME_WS_ACTIVE:
            consume_whitespace_ = CONSUME_WS_DISABLED;
            break;
        case CONSUME_WS_ENABLED:
            consume_whitespace_ = CONSUME_WS_ACTIVE;
            break;
    }
}

void CodePrinter::indent()
{
    out_ << std::string(indent_ * 4, ' ');
}

void CodePrinter::consumeWhitespace()
{
    consume_whitespace_ = CONSUME_WS_ENABLED;
}
void CodePrinter::emitWhitespace()
{
    if (consume_whitespace_ != CONSUME_WS_ACTIVE) { out_ << " "; }
}

void CodePrinter::emitFunction(lang::Function const& function)
{
    out_ << function.access().toString() << " ";
    out_ << function.name() << " ";

    {
        out_ << "(";
        bool is_first = true;

        for (size_t index = 0; index < function.parameterCount(); index++)
        {
            if (!is_first) out_ << ", ";
            out_ << function.parameter(index).name() + ": " + function.parameter(index).type().name();

            is_first = false;
        }

        out_ << ")";
    }

    if (!function.returnType().isUnitType()) { out_ << " : " << function.returnType().name(); }

    if (function.code())
    {
        out_ << std::endl;
        out_ << visitTree(*function.code()) << std::endl;
    }
    else { out_ << ";" << std::endl; }
}
