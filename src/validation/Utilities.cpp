#include "Utilities.h"

#include "lang/ApplicationVisitor.h"

bool lang::validation::isTypeUndefined(lang::Type const& type,
                                       lang::Location    location,
                                       ValidationLogger& validation_logger)
{
    if (type.isDefined()) return false;

    validation_logger.logError("Type " + type.getAnnotatedName() + " is undefined in current context", location);

    return true;
}

bool lang::validation::isFunctionUndefined(lang::Function const& function,
                                           lang::Location        location,
                                           ValidationLogger&     validation_logger)
{
    if (function.isDefined()) return false;

    validation_logger.logError("Function '" + function.name() + "' is undefined in current context", location);

    return true;
}

bool lang::validation::isNameUndefined(lang::Variable const& variable,
                                       lang::Location        location,
                                       ValidationLogger&     validation_logger)
{
    if (variable.isDefined()) return false;

    validation_logger.logError("Name '" + variable.name() + "' is undefined in current context", location);

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
