#include "DefaultValue.h"

#include "lang/type/Type.h"
#include "lang/statement/Statement.h"

DefaultValue::DefaultValue(lang::ResolvingHandle<lang::Type> type, lang::Location location)
    : Expression(location)
    , type_(type)
{}

lang::ResolvingHandle<lang::Type> DefaultValue::type()
{
    return type_;
}

bool DefaultValue::validate(ValidationLogger&)
{
    return true;
}

Expression::Expansion DefaultValue::expandWith(Expressions) const
{
    return {Statements(), std::make_unique<DefaultValue>(type_, location()), Statements()};
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