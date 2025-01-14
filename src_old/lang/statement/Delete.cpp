#include "Delete.h"

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

bool Delete::validate(ValidationLogger& validation_logger) const
{
    if (!to_delete_->validate(validation_logger)) return false;

    bool valid = true;

    if (delete_buffer_ && !to_delete_->type().isBufferType())
    {
        validation_logger.logError("Value of type " + to_delete_->type().getAnnotatedName()
                                       + " given to 'delete[]' must be a buffer pointer",
                                   to_delete_->location());

        valid = false;
    }

    if (!delete_buffer_ && !to_delete_->type().isPointerType())
    {
        validation_logger.logError("Value of type " + to_delete_->type().getAnnotatedName()
                                       + " given to 'delete' must be a pointer",
                                   to_delete_->location());

        valid = false;
    }

    valid &= scope().context().validateRuntimeDependency(location(), validation_logger);

    return valid;
}

Statements Delete::expandWith(Expressions subexpressions, Statements, lang::Context&) const
{
    Statements statements;

    statements.emplace_back(makeOwned<Delete>(std::move(subexpressions[0]), delete_buffer_, location()));

    return statements;
}
