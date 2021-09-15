#include "GlobalVariable.h"

#include <utility>

#include "ance/AccessModifier.h"
#include "ance/construct/constant/Constant.h"
#include "ance/construct/value/WrappedNativeValue.h"
#include "ance/expression/ConstantExpression.h"
#include "ance/type/Type.h"
#include "ance/type/VoidType.h"
#include "compiler/CompileContext.h"

namespace llvm
{
    class Constant;
}

ance::GlobalVariable::GlobalVariable(ance::Scope*        containing_scope,
                                     AccessModifier      access,
                                     std::string         identifier,
                                     ance::Type*         type,
                                     ConstantExpression* constant_init,
                                     bool                is_final,
                                     bool                is_constant,
                                     ance::Location      location)
    : Variable(containing_scope, std::move(identifier), type, is_final)
    , access_(access)
    , location_(location)
    , is_constant_(is_constant)
    , constant_init_(constant_init)
{
    constant_init_->setContainingScope(containing_scope);
    initial_value_ = constant_init_->getConstantValue();
}

ance::GlobalVariable::GlobalVariable(std::string identifier)
    : Variable(std::move(identifier))
    , access_(AccessModifier::PRIVATE_ACCESS)
    , location_(0, 0, 0, 0)
{}

void ance::GlobalVariable::defineGlobal(ance::Scope*        containing_scope,
                                        AccessModifier      access,
                                        ance::Type*         type,
                                        ConstantExpression* constant_init,
                                        bool                is_final,
                                        bool                is_constant,
                                        ance::Location      location)
{
    this->define(containing_scope, type, is_final);

    is_constant_   = is_constant;
    access_        = access;
    constant_init_ = constant_init;
    location_      = location;

    constant_init_->setContainingScope(containing_scope);
    initial_value_ = constant_init_->getConstantValue();
}

void ance::GlobalVariable::validate(ValidationLogger& validation_logger)
{
    if (type() == ance::VoidType::get())
    {
        validation_logger.logError("Global variable cannot have 'void' type", location_);
        return;
    }

    ance::Type::checkMismatch(type(), initial_value_->type(), constant_init_->location(), validation_logger);
}

void ance::GlobalVariable::createNativeBacking(CompileContext* context)
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
                                                                     location_.line(),
                                                                     type()->getDebugType(context),
                                                                     true);

    native_variable_->addDebugInfo(debug_info);
}

ance::Value* ance::GlobalVariable::getValue(CompileContext* context)
{
    switch (type()->storage())
    {
        case InternalStorage::AS_TEMPORARY:
        {
            auto* const  value_type = static_cast<llvm::PointerType*>(native_variable_->getType())->getElementType();
            llvm::Value* value      = context->ir()->CreateLoad(value_type, native_variable_);
            value->setName(identifier());
            return new ance::WrappedNativeValue(type(), value);
        }

        case InternalStorage::AS_POINTER:
        {
            return new ance::WrappedNativeValue(type(), native_variable_);
        }
    }
}

void ance::GlobalVariable::setValue(ance::Value* value, CompileContext* context)
{
    value->buildContentValue(context);

    llvm::Value* content = value->getContentValue();
    context->ir()->CreateStore(content, native_variable_);
}

bool ance::GlobalVariable::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitGlobalVariable(*this);
}
