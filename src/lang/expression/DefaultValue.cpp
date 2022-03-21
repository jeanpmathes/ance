#include "DefaultValue.h"

#include "lang/type/Type.h"

DefaultValue::DefaultValue(lang::ResolvingHandle<lang::Type> type, lang::Location location)
    : Expression(location)
    , type_(type)
{}

lang::ResolvingHandle<lang::Type> DefaultValue::type()
{
    return type_;
}

void DefaultValue::walkDefinitions() {}

bool DefaultValue::validate(ValidationLogger&)
{
    return true;
}

std::shared_ptr<lang::Value> DefaultValue::getValue() const
{
    return constant_;
}

std::shared_ptr<lang::Constant> DefaultValue::getConstantValue() const
{
    return constant_;
}

llvm::Constant* DefaultValue::buildContentConstant(llvm::LLVMContext& c)
{
    return type_->getDefaultContent(c);
}

DefaultValue::~DefaultValue() = default;