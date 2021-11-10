#include "DefaultValue.h"

#include "ance/type/Type.h"

DefaultValue::DefaultValue(ance::ResolvingHandle<ance::Type> type, ance::Location location)
    : Expression(location)
    , type_(type)
{}

ance::ResolvingHandle<ance::Type> DefaultValue::type()
{
    return type_;
}

bool DefaultValue::validate(ValidationLogger&)
{
    return true;
}

std::shared_ptr<ance::Value> DefaultValue::getValue() const
{
    return constant_;
}

std::shared_ptr<ance::Constant> DefaultValue::getConstantValue() const
{
    return constant_;
}

llvm::Constant* DefaultValue::buildContentConstant(llvm::LLVMContext& c)
{
    return type_->getDefaultContent(c);
}

DefaultValue::~DefaultValue() = default;