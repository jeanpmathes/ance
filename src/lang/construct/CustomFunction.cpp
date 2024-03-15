#include "CustomFunction.h"

#include <utility>

#include <llvm/ADT/SmallVector.h>// critical, missing include will cause linking error

#include "compiler/CompileContext.h"
#include "lang/AccessModifier.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/type/Type.h"
#include "validation/ValidationLogger.h"

lang::CustomFunction::CustomFunction(Function&                            function,
                                     lang::AccessModifier                 access,
                                     lang::ResolvingHandle<lang::Type>    return_type,
                                     lang::Location                       return_type_location,
                                     std::vector<Shared<lang::Parameter>> parameters,
                                     Statement&                           code,
                                     Scope&                               containing_scope,
                                     lang::Location                       declaration_location,
                                     lang::Location                       definition_location)
    : lang::StatementFunction(function,
                              access,
                              return_type,
                              return_type_location,
                              std::move(parameters),
                              code,
                              containing_scope,
                              declaration_location)
    , definition_location_(definition_location)
{}

bool lang::CustomFunction::isMangled() const
{
    return access() != lang::AccessModifier::EXTERN_ACCESS;
}

Optional<lang::Location> lang::CustomFunction::getDefinitionLocation() const
{
    return definition_location_;
}

bool lang::CustomFunction::preserveUnitReturn() const
{
    return false;
}

bool lang::CustomFunction::validateFlow(ValidationLogger& validation_logger) const
{
    validateReturn(validation_logger);
    validateUnreachable(validation_logger);

    return true;
}

void lang::CustomFunction::validateReturn(ValidationLogger& validation_logger) const
{
    std::list<lang::BasicBlock const*> const final_blocks = getInitialBlock().getLeaves();

    Optional<lang::Location> missing_return_location;

    for (auto* block : final_blocks)
    {
        Optional<std::pair<std::reference_wrapper<lang::Type const>, lang::Location>> return_value =
            block->getReturnType();

        if (return_value.hasValue())
        {
            auto& [value, location] = *return_value;

            if (value.get().isDefined())
                lang::Type::checkMismatch(returnType(), value.get(), location, validation_logger);
        }
        else
        {
            if (!returnType().isUnitType())// Missing return statement implies a 'return ();' statement.
            {
                lang::Location end = block->getEndLocation();
                if (end.isGlobal()) end = this->location();
                missing_return_location = end;
            }
        }
    }

    if (missing_return_location.hasValue())
    {
        validation_logger.logError("Not all code paths of '" + name() + "' return a value", *missing_return_location);
    }
}

void lang::CustomFunction::validateUnreachable(ValidationLogger& validation_logger) const
{
    Optional<lang::Location> unreachable_code_location = findUnreachableCode();

    if (unreachable_code_location.hasValue())
    {
        validation_logger.logWarning("Unreachable code in function '" + name() + "'", *unreachable_code_location);
    }
}
