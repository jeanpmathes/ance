#include "DefaultValueExpression.h"

#include "ance/construct/constant/Constant.h"
#include "ance/construct/value/Value.h"
#include "ance/type/Type.h"

DefaultValueExpression::DefaultValueExpression(ance::Type* type, ance::Location location)
    : BackingConstantExpression(location)
    , type_(type)
{}

ance::Type* DefaultValueExpression::type()
{
    return type_;
}

ance::Value* DefaultValueExpression::getValue()
{
    return constant_;
}

ance::Constant* DefaultValueExpression::getConstantValue()
{
    return constant_;
}

llvm::Constant* DefaultValueExpression::buildContentConstant(llvm::LLVMContext& c)
{
    return type_->getDefaultContent(c);
}

DefaultValueExpression::~DefaultValueExpression() = default;