#include "DefaultValue.h"

#include "ance/construct/constant/Constant.h"
#include "ance/construct/value/Value.h"
#include "ance/type/Type.h"

DefaultValue::DefaultValue(ance::Type* type, ance::Location location) : Expression(location), type_(type) {}

ance::Type* DefaultValue::type()
{
    return type_;
}

bool DefaultValue::validate(ValidationLogger&)
{
    return true;
}

ance::Value* DefaultValue::getValue() const
{
    return constant_;
}

ance::Constant* DefaultValue::getConstantValue() const
{
    return constant_;
}

llvm::Constant* DefaultValue::buildContentConstant(llvm::LLVMContext& c)
{
    return type_->getDefaultContent(c);
}

bool DefaultValue::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitDefaultValue(*this);
}

DefaultValue::~DefaultValue() = default;