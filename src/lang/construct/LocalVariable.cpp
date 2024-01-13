#include "LocalVariable.h"

#include <utility>

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Parameter.h"
#include "lang/scope/LocalScope.h"
#include "validation/ValidationLogger.h"

lang::LocalVariable::LocalVariable(lang::ResolvingHandle<lang::Variable> self,
                                   lang::ResolvingHandle<lang::Type>     type,
                                   lang::Location                        type_location,
                                   Scope&                                containing_scope,
                                   bool                                  is_final,
                                   Optional<Shared<lang::Value>>         value,
                                   Optional<unsigned>                    parameter_index,
                                   lang::Location                        location)
    : VariableDefinition(self, type, type_location, containing_scope, is_final, location)
    , initial_value_(std::move(value))
    , parameter_index_(std::move(parameter_index))
{
    // Type is already added in declaring statement.
}

lang::OwningHandle<lang::Variable> lang::LocalVariable::makeLocalVariable(lang::Identifier const&           name,
                                                                          lang::ResolvingHandle<lang::Type> type,
                                                                          lang::Location                type_location,
                                                                          lang::Assigner                assigner,
                                                                          Optional<Shared<lang::Value>> value,
                                                                          lang::Scope&   containing_scope,
                                                                          lang::Location location)
{
    bool const is_final = assigner.isFinal();

    lang::ResolvingHandle<lang::Variable> variable = lang::makeHandled<lang::Variable>(name);
    variable->defineAsLocal(type, type_location, containing_scope, is_final, value, std::nullopt, location);

    return lang::OwningHandle<lang::Variable>::takeOwnership(variable);
}

lang::OwningHandle<lang::Variable> lang::LocalVariable::makeParameterVariable(lang::Identifier const&           name,
                                                                              lang::ResolvingHandle<lang::Type> type,
                                                                              lang::Location      type_location,
                                                                              Shared<lang::Value> value,
                                                                              unsigned int        parameter_index,
                                                                              lang::Scope&        containing_scope,
                                                                              lang::Location      location)
{
    bool const is_final = false;// Assigner has value UNSPECIFIED, so it's not final.

    lang::ResolvingHandle<lang::Variable> variable = lang::makeHandled<lang::Variable>(name);
    variable->defineAsLocal(type, type_location, containing_scope, is_final, value, parameter_index, location);

    return lang::OwningHandle<lang::Variable>::takeOwnership(variable);
}

void lang::LocalVariable::buildDeclaration(CompileContext& context)
{
    local_variable_ = context.exec().declareLocalVariable(name(), type());
}

void lang::LocalVariable::buildInitialization(CompileContext& context)
{
    assert(local_variable_.hasValue());

    context.exec().defineLocalVariable(local_variable_.value(), scope(), parameter_index_, location());

    Shared<lang::Value> pointer = getValuePointer(context);

    if (initial_value_.hasValue())
    {
        Shared<lang::Value> value = lang::Type::makeMatching(type(), initial_value_.value(), context);

        if (type()->isReferenceType() || parameter_index_.hasValue())
        {
            context.exec().performStoreToAddress(pointer, value);
        }
        else
        {
            Shared<lang::Value> value_ptr = context.exec().computeAddressOf(value);
            type()->performCopyInitializer(pointer, value_ptr, context);
        }
    }
    else { type()->performDefaultInitializer(pointer, context); }
}

void lang::LocalVariable::buildFinalization(CompileContext& context)
{
    if (!type()->isReferenceType()) { type()->performFinalizer(getValuePointer(context), context); }
}

Shared<lang::Value> lang::LocalVariable::getValuePointer(CompileContext& context)
{
    return context.exec().computeAddressOfVariable(local_variable_.value());
}

void lang::LocalVariable::storeValue(Shared<lang::Value> value, CompileContext& context)
{
    Shared<lang::Value> variable_ptr = getValuePointer(context);
    Shared<lang::Value> value_ptr    = context.exec().computeAddressOf(value);

    type()->performCopyInitializer(variable_ptr, value_ptr, context);
}
