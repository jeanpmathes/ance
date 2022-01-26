#include "GlobalVariable.h"

#include "ance/construct/Parameter.h"
#include "ance/construct/constant/Constant.h"
#include "ance/construct/value/WrappedNativeValue.h"
#include "ance/expression/ConstantExpression.h"
#include "ance/scope/GlobalScope.h"
#include "ance/scope/LocalScope.h"
#include "ance/type/ReferenceType.h"
#include "ance/type/VoidType.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

namespace llvm
{
    class Constant;
}

ance::GlobalVariable::GlobalVariable(const std::string&                identifier,
                                     ance::ResolvingHandle<ance::Type> type,
                                     ance::Location                    type_location,
                                     ance::GlobalScope*                containing_scope,
                                     AccessModifier                    access,
                                     ConstantExpression*               constant_init,
                                     bool                              is_final,
                                     bool                              is_constant,
                                     ance::Location                    location)
    : VariableDefinition(identifier, type, type_location, containing_scope, is_final, location)
    , access_(access)
    , is_constant_(is_constant)
    , constant_init_(constant_init)
{
    containing_scope->addType(type);

    constant_init_->setContainingScope(containing_scope);
    initial_value_ = constant_init_->getConstantValue();
}

void ance::GlobalVariable::validate(ValidationLogger& validation_logger)
{
    if (!type()->isDefined())
    {
        validation_logger.logError("Variable type " + type()->getAnnotatedName() + " not defined", typeLocation());
        return;
    }

    if (!type()->validate(validation_logger, typeLocation())) return;

    if (type()->isVoidType())
    {
        validation_logger.logError("Global variable cannot have 'void' type", typeLocation());
        return;
    }

    if (type()->isReferenceType())
    {
        validation_logger.logError("Global variable cannot have reference type", typeLocation());
        return;
    }

    bool valid = constant_init_->validate(validation_logger);
    if (!valid) return;

    ance::Type::checkMismatch(type(), initial_value_->type(), constant_init_->location(), validation_logger);
}

void ance::GlobalVariable::buildDeclaration(CompileContext*) {}
void ance::GlobalVariable::buildDefinition(CompileContext* context)
{
    llvm::GlobalValue::LinkageTypes linkage = access_.linkage();

    initial_value_->buildContentConstant(context->module());
    llvm::Constant* native_initializer = initial_value_->getContentConstant();
    native_variable_                   = new llvm::GlobalVariable(*context->module(),
                                                type()->getContentType(context->module()->getContext()),
                                                is_constant_,
                                                linkage,
                                                native_initializer,
                                                identifier());

    auto* debug_info = context->di()->createGlobalVariableExpression(context->unit(),
                                                                     identifier(),
                                                                     identifier(),
                                                                     context->sourceFile(),
                                                                     location().line(),
                                                                     type()->getDebugType(context),
                                                                     true);

    native_variable_->addDebugInfo(debug_info);
}

std::shared_ptr<ance::Value> ance::GlobalVariable::getValue(CompileContext*)
{
    return std::make_shared<ance::WrappedNativeValue>(type(), native_variable_);
}

void ance::GlobalVariable::storeValue(std::shared_ptr<ance::Value> value, CompileContext* context)
{
    value = ance::Type::makeMatching(type(), value, context);

    value->buildContentValue(context);

    llvm::Value* content = value->getContentValue();
    context->ir()->CreateStore(content, native_variable_);
}
