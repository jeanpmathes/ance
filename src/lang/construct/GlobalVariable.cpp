#include "GlobalVariable.h"

#include "lang/construct/Parameter.h"
#include "lang/construct/constant/Constant.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/expression/ConstantExpression.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/ReferenceType.h"
#include "lang/type/VoidType.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"
#include "lang/AccessModifier.h"

namespace llvm
{
    class Constant;
}

lang::GlobalVariable::GlobalVariable(const std::string&                  name,
                                     lang::ResolvingHandle<lang::Type>   type,
                                     lang::Location                      type_location,
                                     GlobalScope&                        containing_scope,
                                     lang::AccessModifier                access,
                                     std::unique_ptr<ConstantExpression> constant_init,
                                     bool                                is_final,
                                     bool                                is_constant,
                                     lang::Location                      location)
    : VariableDefinition(name, type, type_location, containing_scope, is_final, location)
    , access_(access)
    , is_constant_(is_constant)
    , constant_init_(std::move(constant_init))
{
    containing_scope.addType(type);

    if (constant_init_)
    {
        constant_init_->setContainingScope(containing_scope);
        initial_value_ = constant_init_->getConstantValue();

        addChild(*constant_init_);
    }
}

lang::AccessModifier lang::GlobalVariable::access() const
{
    return access_;
}

bool lang::GlobalVariable::isConstant() const
{
    return is_constant_;
}

lang::Assigner lang::GlobalVariable::assigner() const
{
    if (isFinal()) { return lang::Assigner::FINAL_COPY_ASSIGNMENT; }
    else {
        return lang::Assigner::COPY_ASSIGNMENT;
    }
}

lang::Constant& lang::GlobalVariable::init() const
{
    return *initial_value_;
}

void lang::GlobalVariable::validate(ValidationLogger& validation_logger)
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

    if (!constant_init_)
    {
        if (is_constant_)
        {
            validation_logger.logError("Constants require an explicit initializer", location());
            return;
        }
        else {
            assert(false && "For non-const global vars, an initializer (potentially the default one) must be passed.");
        }
    }

    if (is_constant_ && !isFinal())
    {
        validation_logger.logError("Assignment to constants must be final", location());
        return;
    }

    bool valid = constant_init_->validate(validation_logger);
    if (!valid) return;

    if (!lang::Type::areSame(type(), initial_value_->type()))
    {
        validation_logger.logError("Constant initializer must be of variable type " + type()->getAnnotatedName(),
                                   typeLocation());
        return;
    }
}

void lang::GlobalVariable::buildDeclaration(CompileContext*) {}
void lang::GlobalVariable::buildDefinition(CompileContext* context)
{
    llvm::GlobalValue::LinkageTypes linkage = access_.linkage();

    initial_value_->buildContentConstant(context->module());
    llvm::Constant* native_initializer = initial_value_->getContentConstant();
    native_variable_                   = new llvm::GlobalVariable(*context->module(),
                                                type()->getContentType(context->module()->getContext()),
                                                is_constant_,
                                                linkage,
                                                native_initializer,
                                                name());

    auto* debug_info = context->di()->createGlobalVariableExpression(context->unit(),
                                                                     name(),
                                                                     name(),
                                                                     context->sourceFile(),
                                                                     location().line(),
                                                                     type()->getDebugType(context),
                                                                     true);

    native_variable_->addDebugInfo(debug_info);
}

std::shared_ptr<lang::Value> lang::GlobalVariable::getValue(CompileContext*)
{
    return std::make_shared<lang::WrappedNativeValue>(type(), native_variable_);
}

void lang::GlobalVariable::storeValue(std::shared_ptr<lang::Value> value, CompileContext* context)
{
    value = lang::Type::makeMatching(type(), value, context);

    value->buildContentValue(context);

    llvm::Value* content = value->getContentValue();
    context->ir()->CreateStore(content, native_variable_);
}
