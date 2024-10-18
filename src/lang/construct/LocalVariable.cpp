#include "LocalVariable.h"

#include <utility>

#include "lang/ApplicationVisitor.h"
#include "lang/construct/Parameter.h"
#include "lang/scope/LocalScope.h"
#include "validation/ValidationLogger.h"

lang::LocalVariable::LocalVariable(lang::ResolvingHandle<lang::Variable> self,
                                   lang::ResolvingHandle<lang::Type>     type,
                                   lang::Location                        type_location,
                                   Scope&                                containing_scope,
                                   bool                                  is_final,
                                   lang::LocalInitializer                init,
                                   Optional<size_t>                      parameter_index,
                                   lang::Location                        location)
    : VariableDefinition(self, type, type_location, containing_scope, is_final, location)
    , initializer_(std::move(init))
    , parameter_index_(std::move(parameter_index))
{
    // Type is already added in declaring statement.
}

lang::OwningHandle<lang::Variable> lang::LocalVariable::makeLocalVariable(lang::Identifier const&           name,
                                                                          lang::ResolvingHandle<lang::Type> type,
                                                                          lang::Location type_location,
                                                                          lang::Assigner assigner,
                                                                          Expression*    init,
                                                                          lang::Scope&   containing_scope,
                                                                          lang::Location location)
{
    bool const is_final = assigner.isFinal();

    lang::LocalInitializer local_initializer;
    if (init != nullptr) { local_initializer = makeOptional(std::ref(*init)); }

    lang::ResolvingHandle<lang::Variable> variable = lang::makeHandled<lang::Variable>(name);
    variable->defineAsLocal(type, type_location, containing_scope, is_final, local_initializer, std::nullopt, location);

    return lang::OwningHandle<lang::Variable>::takeOwnership(variable);
}

lang::OwningHandle<lang::Variable> lang::LocalVariable::makeParameterVariable(lang::Parameter& parameter,
                                                                              size_t           parameter_index,
                                                                              lang::Function&  containing_function)
{
    bool const is_final = false;// Assigner has value UNSPECIFIED, so it's not final.

    lang::LocalParameterInitializer initializer = std::make_pair(std::cref(containing_function), parameter_index);

    lang::ResolvingHandle<lang::Variable> variable = lang::makeHandled<lang::Variable>(parameter.name());
    variable->defineAsLocal(parameter.type(),
                            parameter.typeLocation(),
                            containing_function,
                            is_final,
                            makeOptional(initializer),
                            parameter_index,
                            parameter.location());

    return lang::OwningHandle<lang::Variable>::takeOwnership(variable);
}

void lang::LocalVariable::registerDeclaration(Execution& exec) const
{
    exec.declareLocalVariable(*this);
}

void lang::LocalVariable::registerDefinition(Execution&) const
{
    // Nothing to do, variable is defined on initialization.
}

void lang::LocalVariable::performInitialization(Execution& exec) const
{
    exec.defineLocalVariable(*this, scope(), parameter_index_, location());

    Shared<lang::Value> pointer = getValuePointer(exec);

    if (initializer_.hasValue())
    {
        Shared<lang::Value> value = exec.computeInitializerValue(initializer_);

        value = lang::Type::makeMatching(type(), value, exec);

        if (type().isReferenceType() || parameter_index_.hasValue())
        { exec.performStoreToAddress(pointer, value); }
        else
        {
            Shared<lang::Value> value_ptr = exec.computeAddressOf(value);
            type().performCopyInitializer(pointer, value_ptr, exec);
        }
    }
    else { type().performDefaultInitializer(pointer, exec); }
}

void lang::LocalVariable::performFinalization(Execution& exec) const
{
    if (!type().isReferenceType()) { type().performFinalizer(getValuePointer(exec), exec); }
}

Shared<lang::Value> lang::LocalVariable::getValuePointer(Execution& exec) const
{
    return exec.computeAddressOfVariable(self());
}
