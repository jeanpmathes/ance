#include "Utilities.h"

#include "lang/ApplicationVisitor.h"

bool lang::validation::isTypeUndefined(lang::ResolvingHandle<lang::Type> type,
                                       lang::Location                    location,
                                       ValidationLogger&                 validation_logger)
{
    if (type->isDefined()) return false;

    validation_logger.logError("Type " + type->getAnnotatedName() + " is undefined in current context", location);

    return true;
}

bool lang::validation::isFunctionUndefined(lang::ResolvingHandle<lang::Function> function,
                                           lang::Location                        location,
                                           ValidationLogger&                     validation_logger)
{
    if (function->isDefined()) return false;

    validation_logger.logError("Function '" + function->name() + "' is undefined in current context", location);

    return true;
}

bool lang::validation::isNameUndefined(lang::ResolvingHandle<lang::Variable> variable,
                                       lang::Location                        location,
                                       ValidationLogger&                     validation_logger)
{
    if (variable->isDefined()) return false;

    validation_logger.logError("Name '" + variable->name() + "' is undefined in current context", location);

    return true;
}
