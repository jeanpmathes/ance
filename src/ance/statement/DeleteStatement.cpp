#include "DeleteStatement.h"

#include "ance/construct/DefinedFunction.h"
#include "ance/scope/LocalScope.h"

DeleteStatement::DeleteStatement(Expression* to_delete, bool delete_buffer, ance::Location location)
    : Statement(location)
    , to_delete_(to_delete)
    , delete_buffer_(delete_buffer)
{}

void DeleteStatement::setFunction(ance::DefinedFunction* function)
{
    to_delete_->setContainingScope(function);
}

void DeleteStatement::build(CompileContext* context)
{
    context->runtime()->deleteDynamic(to_delete_->getValue(), delete_buffer_, context);
}
