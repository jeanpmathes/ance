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
     * Check whether a type is undefined. If so, a message is logged.
     */
    bool isTypeUndefined(lang::Type const& type, lang::Location location, ValidationLogger& validation_logger);

    /**
     * Check whether a function is undefined. If so, a message is logged.
     */
    bool isFunctionUndefined(lang::Function const& function,
                             lang::Location        location,
                             ValidationLogger&     validation_logger);

    /**
     * Check whether a (variable) name is undefined. If so, a message is logged.
     */
    bool isNameUndefined(lang::Variable const& variable, lang::Location location, ValidationLogger& validation_logger);
}

#endif
