#include "LocalVariable.h"

#include <utility>

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Parameter.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/scope/LocalScope.h"
#include "validation/ValidationLogger.h"

lang::LocalVariable::LocalVariable(lang::ResolvingHandle<lang::Variable> self,
                                   lang::ResolvingHandle<lang::Type>     type,
                                   lang::Location                        type_location,
                                   Scope&                                containing_scope,
                                   bool                                  is_final,
                                   Optional<Shared<lang::Value>>         value,
                                   unsigned                              parameter_no,
                                   lang::Location                        location)
    : VariableDefinition(self, type, type_location, containing_scope, is_final, location)
    , initial_value_(value)
    , parameter_no_(parameter_no)
{
    // Type is already added in declaring statement.
}

void lang::LocalVariable::validate(ValidationLogger&) const
{
    // Validation of variable declaring statement.
}

void lang::LocalVariable::buildDeclaration(CompileContext& context)
{
    native_value_ = context.ir().CreateAlloca(type()->getContentType(context.llvmContext()), nullptr, name().text());
}

void lang::LocalVariable::buildDefinition(CompileContext& context)
{
    assert(native_value_);

    if (parameter_no_ == 0)
    {
        local_debug_variable_ = context.di().createAutoVariable(scope()->getDebugScope(context),
                                                                name().text(),
                                                                context.getSourceFile(location()),
                                                                static_cast<unsigned>(location().line()),
                                                                type()->getDebugType(context),
                                                                true);
    }
    else
    {
        local_debug_variable_ = context.di().createParameterVariable(scope()->getDebugScope(context),
                                                                     name().text(),
                                                                     parameter_no_,
                                                                     context.getSourceFile(location()),
                                                                     static_cast<unsigned>(location().line()),
                                                                     type()->getDebugType(context),
                                                                     true);
    }

    context.di().insertDeclare(native_value_,
                               local_debug_variable_,
                               context.di().createExpression(),
                               location().getDebugLoc(context.llvmContext(), scope()->getDebugScope(context)),
                               context.ir().GetInsertBlock());

    if (initial_value_.hasValue())
    {
        Shared<lang::Value> value = lang::Type::makeMatching(type(), initial_value_.value(), context);

        if (type()->isReferenceType() || parameter_no_ != 0)
        {
            value->buildContentValue(context);
            llvm::Value* stored = value->getContentValue();

            context.ir().CreateStore(stored, native_value_);
        }
        else
        {
            value->buildNativeValue(context);
            llvm::Value* value_ptr = value->getNativeValue();

            type()->buildCopyInitializer(native_value_, value_ptr, context);
        }
    }
    else { type()->buildDefaultInitializer(native_value_, context); }
}

void lang::LocalVariable::buildFinalization(CompileContext& context)
{
    if (!type()->isReferenceType()) { type()->buildFinalizer(native_value_, context); }
}

Shared<lang::Value> lang::LocalVariable::getValue(CompileContext&)
{
    return makeShared<lang::WrappedNativeValue>(type(), native_value_);
}

void lang::LocalVariable::storeValue(Shared<lang::Value> value, CompileContext& context)
{
    value = lang::Type::makeMatching(type(), value, context);

    value->buildNativeValue(context);
    llvm::Value* value_ptr = value->getNativeValue();

    type()->buildCopyInitializer(native_value_, value_ptr, context);
}
