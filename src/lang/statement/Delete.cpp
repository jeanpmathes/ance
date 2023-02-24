#include "Delete.h"

#include "compiler/CompileContext.h"
#include "compiler/Runtime.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "validation/ValidationLogger.h"

Delete::Delete(Owned<Expression> to_delete, bool delete_buffer, lang::Location location)
    : Statement(location)
    , to_delete_(std::move(to_delete))
    , delete_buffer_(delete_buffer)
{
    addSubexpression(*to_delete_);
}

Expression const& Delete::toDelete() const
{
    return *to_delete_;
}

bool Delete::isBufferDelete() const
{
    return delete_buffer_;
}

void Delete::validate(ValidationLogger& validation_logger) const
{
    if (!to_delete_->validate(validation_logger)) return;

    if (delete_buffer_ && !to_delete_->type().isBufferType())
    {
        validation_logger.logError("Value of type " + to_delete_->type().getAnnotatedName()
                                       + " given to 'delete[]' must be a buffer pointer",
                                   to_delete_->location());
    }

    if (!delete_buffer_ && !to_delete_->type().isPointerType())
    {
        validation_logger.logError("Value of type " + to_delete_->type().getAnnotatedName()
                                       + " given to 'delete' must be a pointer",
                                   to_delete_->location());
    }

    scope()->getGlobalScope()->validateRuntimeDependency(location(), validation_logger);
}

Statements Delete::expandWith(Expressions subexpressions, Statements) const
{
    Statements statements;

    statements.emplace_back(makeOwned<Delete>(std::move(subexpressions[0]), delete_buffer_, location()));

    return statements;
}

void Delete::doBuild(CompileContext& context)
{
    context.runtime().deleteDynamic(to_delete_->getValue(), delete_buffer_, context);
}
