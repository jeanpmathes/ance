#ifndef ANCE_SRC_VALIDATION_UTILITIES_H_
#define ANCE_SRC_VALIDATION_UTILITIES_H_

#include "lang/construct/Function.h"
#include "lang/construct/Variable.h"
#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"
#include "validation/ValidationLogger.h"

namespace lang::validation
{
    /**
     * Check whether the access level is sufficient to export as part of a public interface.
     */
    bool isTypeExportable(lang::Type const& type, lang::Location location, ValidationLogger& validation_logger);
}

#endif
