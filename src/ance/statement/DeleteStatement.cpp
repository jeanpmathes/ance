#include "DeleteStatement.h"

#include "DefinedFunction.h"
#include "LocalScope.h"

DeleteStatement::DeleteStatement(Expression* to_delete, bool delete_buffer, unsigned int line, unsigned int column)
    : Statement(line, column), to_delete_(to_delete), delete_buffer_(delete_buffer)
{
}

void DeleteStatement::setFunction(ance::DefinedFunction* function)
{
    to_delete_->setScope(function->getScope());
}

void DeleteStatement::build(CompileContext* context)
{
    context->runtime()->deleteDynamic(to_delete_->getValue(), delete_buffer_, context);
}
