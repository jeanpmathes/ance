#include "Utilities.h"

#include "lang/ApplicationVisitor.h"

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
