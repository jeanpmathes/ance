#include "LocalVariable.h"

#include <utility>

#include "ance/ApplicationVisitor.h"
#include "ance/construct/Parameter.h"
#include "ance/construct/value/WrappedNativeValue.h"
#include "ance/scope/LocalScope.h"
#include "ance/type/Type.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

ance::LocalVariable::LocalVariable(ance::LocalScope*            containing_scope,
                                   std::string                  identifier,
                                   ance::Type*                  type,
                                   std::shared_ptr<ance::Value> value,
                                   bool                         is_final,
                                   unsigned                     parameter_no,
                                   ance::Location               location)
    : Variable(containing_scope, std::move(identifier), type, is_final)
    , initial_value_(std::move(value))
    , containing_scope_(containing_scope)
    , parameter_no_(parameter_no)
    , location_(location)
{}

ance::Location ance::LocalVariable::location() const
{
    return location_;
}

void ance::LocalVariable::validate(ValidationLogger&)
{
    // Validation of initial value in declaring statement.
}

void ance::LocalVariable::buildDeclaration(CompileContext* context)
{
    assert(initial_value_);

    native_value_ = context->ir()->CreateAlloca(type()->getContentType(*context->llvmContext()), nullptr);
    native_value_->setName(identifier());
}

void ance::LocalVariable::buildDefinition(CompileContext* context)
{
    assert(initial_value_);

    if (parameter_no_ == 0)
    {
        local_debug_variable_ = context->di()->createAutoVariable(containing_scope_->getDebugScope(context),
                                                                  identifier(),
                                                                  context->sourceFile(),
                                                                  location_.line(),
                                                                  type()->getDebugType(context),
                                                                  true);
    }
    else
    {
        local_debug_variable_ = context->di()->createParameterVariable(containing_scope_->getDebugScope(context),
                                                                       identifier(),
                                                                       parameter_no_,
                                                                       context->sourceFile(),
                                                                       location_.line(),
                                                                       type()->getDebugType(context),
                                                                       true);
    }

    context->di()->insertDeclare(
        native_value_,
        local_debug_variable_,
        context->di()->createExpression(),
        location_.getDebugLoc(context->llvmContext(), containing_scope_->getDebugScope(context)),
        context->ir()->GetInsertBlock());

    store(initial_value_, context);
}

std::shared_ptr<ance::Value> ance::LocalVariable::getValue(CompileContext*)
{
    return std::make_shared<ance::WrappedNativeValue>(type(), native_value_);
}

void ance::LocalVariable::storeValue(std::shared_ptr<ance::Value> value, CompileContext* context)
{
    store(value, context);
}

void ance::LocalVariable::store(std::shared_ptr<ance::Value> value, CompileContext* context)
{
    value = ance::Type::makeMatching(type(), value, context);

    value->buildContentValue(context);
    llvm::Value* stored = value->getContentValue();

    context->ir()->CreateStore(stored, native_value_);
}

bool ance::LocalVariable::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitLocalVariable(*this);
}
