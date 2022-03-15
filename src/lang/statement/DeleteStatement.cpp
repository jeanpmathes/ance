#include "DeleteStatement.h"

#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "lang/scope/LocalScope.h"
#include "compiler/CompileContext.h"
#include "compiler/Runtime.h"
#include "validation/ValidationLogger.h"

DeleteStatement::DeleteStatement(std::unique_ptr<Expression> to_delete, bool delete_buffer, lang::Location location)
    : Statement(location)
    , to_delete_(std::move(to_delete))
    , delete_buffer_(delete_buffer)
{
    addChild(*to_delete_);
}

Expression& DeleteStatement::toDelete() const
{
    return *to_delete_;
}

bool DeleteStatement::isBufferDelete() const
{
    return delete_buffer_;
}

void DeleteStatement::setScope(lang::Scope* scope)
{
    to_delete_->setContainingScope(scope);
}

void DeleteStatement::validate(ValidationLogger& validation_logger)
{
    if (to_delete_->validate(validation_logger))
    {
        if (!to_delete_->type()->isPointerType())
        {
            validation_logger.logError("Value of type " + to_delete_->type()->getAnnotatedName()
                                           + " given to 'delete' cannot be used as pointer type",
                                       to_delete_->location());
        }
    }
}

void DeleteStatement::doBuild(CompileContext* context)
{
    context->runtime()->deleteDynamic(to_delete_->getValue(), delete_buffer_, context);
}
