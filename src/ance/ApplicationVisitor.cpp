#include "ApplicationVisitor.h"

#include "ance/Element.h"

#include "compiler/Application.h"

#include "ance/assignable/Discard.h"
#include "ance/assignable/IndexerSet.h"
#include "ance/assignable/VariableAssignable.h"

#include "ance/construct/DefinedFunction.h"
#include "ance/construct/ExternFunction.h"

#include "ance/construct/GlobalVariable.h"
#include "ance/construct/LocalVariable.h"

#include "ance/expression/Allocation.h"
#include "ance/expression/ConstantLiteral.h"
#include "ance/expression/DefaultValue.h"
#include "ance/expression/FunctionCall.h"
#include "ance/expression/IndexerGet.h"
#include "ance/expression/RoughCast.h"
#include "ance/expression/SizeofExpression.h"
#include "ance/expression/SizeofType.h"
#include "ance/expression/VariableAccess.h"

#include "ance/scope/GlobalScope.h"
#include "ance/scope/LocalScope.h"

#include "ance/statement/AssignmentStatement.h"
#include "ance/statement/DeleteStatement.h"
#include "ance/statement/ExpressionStatement.h"
#include "ance/statement/LocalVariableDefinition.h"
#include "ance/statement/ReturnStatement.h"

bool ance::ApplicationVisitor::visit(ance::Element& element)
{
    bool result;

    preVisit(element);
    result = element.accept(*this);
    postVisit(element);

    return result;
}

bool ance::ApplicationVisitor::visitChildren(ance::Element& element)
{
    bool ret = true;

    for (size_t i = 0; i < element.childCount(); i++) { ret &= visit(element.getChild(i)); }

    return ret;
}

void ance::ApplicationVisitor::preVisit(ance::Element& element) {}
void ance::ApplicationVisitor::postVisit(ance::Element& element) {}

bool ance::ApplicationVisitor::visitApplication(Application& application)
{
    return visitChildren(application);
}

bool ance::ApplicationVisitor::visitDiscard(Discard& discard)
{
    return visitChildren(discard);
}

bool ance::ApplicationVisitor::visitIndexerSet(IndexerSet& indexer_set)
{
    return visitChildren(indexer_set);
}

bool ance::ApplicationVisitor::visitVariableAssignable(VariableAssignable& variable_assignable)
{
    return visitChildren(variable_assignable);
}

bool ance::ApplicationVisitor::visitDefinedFunction(ance::DefinedFunction& defined_function)
{
    return visitChildren(defined_function);
}

bool ance::ApplicationVisitor::visitExternFunction(ance::ExternFunction& extern_function)
{
    return visitChildren(extern_function);
}

bool ance::ApplicationVisitor::visitGlobalVariable(ance::GlobalVariable& global_variable)
{
    return visitChildren(global_variable);
}

bool ance::ApplicationVisitor::visitLocalVariable(ance::LocalVariable& local_variable)
{
    return visitChildren(local_variable);
}

bool ance::ApplicationVisitor::visitAllocation(Allocation& allocation)
{
    return visitChildren(allocation);
}

bool ance::ApplicationVisitor::visitConstantLiteral(ConstantLiteral& constant_literal)
{
    return visitChildren(constant_literal);
}

bool ance::ApplicationVisitor::visitDefaultValue(DefaultValue& default_value)
{
    return visitChildren(default_value);
}

bool ance::ApplicationVisitor::visitFunctionCall(FunctionCall& function_call)
{
    return visitChildren(function_call);
}

bool ance::ApplicationVisitor::visitIndexerGet(IndexerGet& indexer_get)
{
    return visitChildren(indexer_get);
}

bool ance::ApplicationVisitor::visitRoughCast(RoughCast& rough_cast)
{
    return visitChildren(rough_cast);
}

bool ance::ApplicationVisitor::visitSizeofExpression(SizeofExpression& sizeof_expression)
{
    return visitChildren(sizeof_expression);
}

bool ance::ApplicationVisitor::visitSizeofType(SizeofType& sizeof_type)
{
    return visitChildren(sizeof_type);
}

bool ance::ApplicationVisitor::visitVariableAccess(VariableAccess& variable_access)
{
    return visitChildren(variable_access);
}

bool ance::ApplicationVisitor::visitGlobalScope(ance::GlobalScope& global_scope)
{
    return visitChildren(global_scope);
}

bool ance::ApplicationVisitor::visitLocalScope(ance::LocalScope& local_scope)
{
    return visitChildren(local_scope);
}

bool ance::ApplicationVisitor::visitAssignmentStatement(AssignmentStatement& assignment_statement)
{
    return visitChildren(assignment_statement);
}

bool ance::ApplicationVisitor::visitDeleteStatement(DeleteStatement& delete_statement)
{
    return visitChildren(delete_statement);
}

bool ance::ApplicationVisitor::visitExpressionStatement(ExpressionStatement& expression_statement)
{
    return visitChildren(expression_statement);
}

bool ance::ApplicationVisitor::visitLocalVariableDefinition(LocalVariableDefinition& local_variable_definition)
{
    return visitChildren(local_variable_definition);
}

bool ance::ApplicationVisitor::visitReturnStatement(ReturnStatement& return_statement)
{
    return visitChildren(return_statement);
}
