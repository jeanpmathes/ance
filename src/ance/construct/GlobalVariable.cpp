#include "GlobalVariable.h"

#include <utility>

#include "AccessModifier.h"
#include "CompileContext.h"
#include "Constant.h"
#include "Type.h"
#include "VoidType.h"
#include "WrappedNativeValue.h"

namespace llvm
{
    class Constant;
}

ance::GlobalVariable::GlobalVariable(
    ance::Scope*        containing_scope,
    AccessModifier      access,
    std::string         identifier,
    ance::Type*         type,
    ConstantExpression* constant_init,
    bool                is_final,
    bool                is_constant)
    : Variable(containing_scope, std::move(identifier), type, is_final), access_(access), is_constant_(is_constant),
      constant_init_(constant_init)
{
    constant_init_->setScope(containing_scope);
    initial_value_ = constant_init_->getConstantValue();
}

ance::GlobalVariable::GlobalVariable(std::string identifier)
    : Variable(std::move(identifier)), access_(AccessModifier::PRIVATE_ACCESS)
{
}

void ance::GlobalVariable::defineGlobal(
    ance::Scope*        containing_scope,
    AccessModifier      access,
    ance::Type*         type,
    ConstantExpression* constant_init,
    bool                is_final,
    bool                is_constant)
{
    this->define(containing_scope, type, is_final);

    is_constant_   = is_constant;
    access_        = access;
    constant_init_ = constant_init;

    constant_init_->setScope(containing_scope);
    initial_value_ = constant_init_->getConstantValue();
}

void ance::GlobalVariable::buildGlobal(llvm::Module* m)
{
    assert(type() != ance::VoidType::get());
    assert(type() == initial_value_->getType());

    llvm::GlobalValue::LinkageTypes linkage = Convert(access_);

    initial_value_->buildContentConstant(m);
    llvm::Constant* native_initializer = initial_value_->getContentConstant();
    native_variable_                   = new llvm::GlobalVariable(
        *m, type()->getContentType(m->getContext()),
        is_constant_, linkage, native_initializer, identifier());
}

ance::Value* ance::GlobalVariable::getValue(CompileContext* context)
{
    switch (type()->storage())
    {
        case InternalStorage::AS_TEMPORARY: {
            auto* const  value_type = static_cast<llvm::PointerType*>(native_variable_->getType())->getElementType();
            llvm::Value* value      = context->ir()->CreateLoad(value_type, native_variable_);
            value->setName(identifier());
            return new ance::WrappedNativeValue(type(), value);
        }

        case InternalStorage::AS_POINTER: {
            return new ance::WrappedNativeValue(type(), native_variable_);
        }
    }
}

void ance::GlobalVariable::setValue(ance::Value* value, CompileContext* context)
{
    assert(!isFinal() && "Cannot assign to final variable.");
    assert(type() == value->getType() && "Assignment types have to match.");

    value->buildContentValue(context);

    llvm::Value* content = value->getContentValue();
    context->ir()->CreateStore(content, native_variable_);
}