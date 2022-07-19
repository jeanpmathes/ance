#include "LocalVariable.h"

#include <utility>

#include "lang/construct/Parameter.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/scope/LocalScope.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

lang::LocalVariable::LocalVariable(Identifier                        name,
                                   lang::ResolvingHandle<lang::Type> type,
                                   lang::Location                    type_location,
                                   Scope&                            containing_scope,
                                   bool                              is_final,
                                   std::shared_ptr<lang::Value>      value,
                                   unsigned                          parameter_no,
                                   lang::Location                    location)
    : VariableDefinition(name, type, type_location, containing_scope, is_final, location)
    , initial_value_(std::move(value))
    , parameter_no_(parameter_no)
{
    // Type is already added in declaring statement.
}

void lang::LocalVariable::validate(ValidationLogger&) const
{
    // Validation of initial value in declaring statement.
}

void lang::LocalVariable::buildDeclaration(CompileContext* context)
{
    native_value_ =
        context->ir()->CreateAlloca(type()->getContentType(*context->llvmContext()), nullptr, name().text());
}

void lang::LocalVariable::buildDefinition(CompileContext* context)
{
    assert(native_value_);

    if (parameter_no_ == 0)
    {
        local_debug_variable_ = context->di()->createAutoVariable(scope()->getDebugScope(context),
                                                                  name().text(),
                                                                  context->sourceFile(),
                                                                  location().line(),
                                                                  type()->getDebugType(context),
                                                                  true);
    }
    else
    {
        local_debug_variable_ = context->di()->createParameterVariable(scope()->getDebugScope(context),
                                                                       name().text(),
                                                                       parameter_no_,
                                                                       context->sourceFile(),
                                                                       location().line(),
                                                                       type()->getDebugType(context),
                                                                       true);
    }

    context->di()->insertDeclare(native_value_,
                                 local_debug_variable_,
                                 context->di()->createExpression(),
                                 location().getDebugLoc(context->llvmContext(), scope()->getDebugScope(context)),
                                 context->ir()->GetInsertBlock());

    if (initial_value_) { store(initial_value_, context); }
    else { type()->buildDefaultInitializer(native_value_, context); }
}

std::shared_ptr<lang::Value> lang::LocalVariable::getValue(CompileContext*)
{
    return std::make_shared<lang::WrappedNativeValue>(type(), native_value_);
}

void lang::LocalVariable::storeValue(std::shared_ptr<lang::Value> value, CompileContext* context)
{
    store(value, context);
}

void lang::LocalVariable::store(std::shared_ptr<lang::Value> value, CompileContext* context)
{
    value = lang::Type::makeMatching(type(), value, context);

    if (type()->isReferenceType())
    {
        value->buildContentValue(context);
        llvm::Value* stored = value->getContentValue();

        context->ir()->CreateStore(stored, native_value_);
    }
    else
    {
        value->buildNativeValue(context);
        llvm::Value* value_ptr = value->getNativeValue();

        type()->buildCopyInitializer(native_value_, value_ptr, context);
    }
}
