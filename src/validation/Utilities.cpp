#include "Utilities.h"

#include "lang/ApplicationVisitor.h"

bool lang::validation::isUndefined(lang::Entity const& entity,
                                   lang::Scope const*  scope,
                                   lang::Location      location,
                                   ValidationLogger&   validation_logger)
{
    if (entity.isDefined()) return false;
    if (scope != nullptr && scope->isNameConflicted(entity.name()))
        return true;// Conflict is already logged, no need to log again.

    validation_logger.logError("Name " + entity.getAnnotatedName() + " is undefined in current context", location);

    return true;
}

bool lang::validation::isTypeExportable(lang::Type const& type,
                                        lang::Location    location,
                                        ValidationLogger& validation_logger)
{
    if (type.getAccessibility().isExposable()) return true;

    if (type.getAccessibility().isImported())
    {
        validation_logger.logError("Public definitions cannot expose types from private dependencies", location);
    }
    else { validation_logger.logError("Public definitions cannot expose non-public types", location); }

    return false;
}
