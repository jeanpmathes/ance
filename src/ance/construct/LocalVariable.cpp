#include "LocalVariable.h"

#include <utility>

#include "ance/construct/value/WrappedNativeValue.h"
#include "ance/scope/LocalScope.h"
#include "compiler/CompileContext.h"

ance::LocalVariable::LocalVariable(ance::LocalScope* containing_scope,
                                   std::string       identifier,
                                   ance::Type*       type,
                                   ance::Value*      value,
                                   bool              is_final,
                                   unsigned parameter_no,
                                   unsigned          line)
    : Variable(containing_scope, std::move(identifier), type, is_final)
    , initial_value_(value)
    , containing_scope_(containing_scope)
    , parameter_no_(parameter_no)
    , line_(line)
{}

void ance::LocalVariable::build(CompileContext* context)
{
    assert(initial_value_);

    if (parameter_no_ == 0)
    {
        local_debug_variable_ = context->di()->createAutoVariable(containing_scope_->getDebugScope(context),
                                          identifier(),
                                          context->codeFile(),
                                          line_,
                                          type()->getDebugType(context),
                                          true);
    }
    else
    {
        local_debug_variable_ = context->di()->createParameterVariable(containing_scope_->getDebugScope(context),
                                               identifier(),
                                               parameter_no_,
                                               context->codeFile(),
                                               line_,
                                               type()->getDebugType(context),
                                               true);
    }

    if (type()->storage() == InternalStorage::AS_POINTER)
    {
        native_value_ = context->ir()->CreateAlloca(type()->getContentType(*context->llvmContext()), nullptr);
        native_value_->setName(identifier());

        context->di()->insertDeclare(native_value_, local_debug_variable_, context->di()->createExpression(), llvm::DebugLoc::get(line_, 0, containing_scope_->getDebugScope(context)), context->ir()->GetInsertBlock());
    }

    store(initial_value_, context);
}

ance::Value* ance::LocalVariable::getValue(CompileContext*)
{
    return new WrappedNativeValue(type(), native_value_);
}

void ance::LocalVariable::setValue(ance::Value* value, CompileContext* context)
{
    assert(!isFinal() && "Cannot assign to final variable.");
    store(value, context);
}

void ance::LocalVariable::store(ance::Value* value, CompileContext* context)
{
    assert(type() == value->type() && "Assignment types have to match.");

    switch (type()->storage())
    {
        case InternalStorage::AS_TEMPORARY:
        {
            value->buildNativeValue(context);

            native_value_ = value->getNativeValue();
            native_value_->setName(identifier());
            break;
        }

        case InternalStorage::AS_POINTER:
        {
            value->buildContentValue(context);

            llvm::Value* stored = value->getContentValue();
            context->ir()->CreateStore(stored, native_value_);
            break;
        }
    }
}
