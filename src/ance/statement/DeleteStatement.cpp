#include "DeleteStatement.h"

#include "ance/construct/DefinedFunction.h"
#include "ance/scope/LocalScope.h"
#include "ance/type/PointerType.h"

DeleteStatement::DeleteStatement(Expression* to_delete, bool delete_buffer, ance::Location location)
    : Statement(location)
    , to_delete_(to_delete)
    , delete_buffer_(delete_buffer)
{
    addChild(*to_delete);
}

void DeleteStatement::setFunction(ance::DefinedFunction* function)
{
    to_delete_->setContainingScope(function);
}

void DeleteStatement::validate(ValidationLogger& validation_logger)
{
    if (to_delete_->validate(validation_logger))
    {
        if (!ance::PointerType::isPointerType(to_delete_->type()))
        {
            validation_logger.logError("Value of type '" + to_delete_->type()->getName()
                                           + "' given to 'delete' cannot be used as pointer type",
                                       to_delete_->location());
        }
    }
}

void DeleteStatement::doBuild(CompileContext* context)
{
    context->runtime()->deleteDynamic(to_delete_->getValue(), delete_buffer_, context);
}

bool DeleteStatement::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitDeleteStatement(*this);
}
