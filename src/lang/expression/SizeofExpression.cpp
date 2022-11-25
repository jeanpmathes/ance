#include "SizeofExpression.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/statement/Statement.h"
#include "lang/type/SizeType.h"
#include "lang/type/Type.h"
#include "lang/utility/Values.h"

SizeofExpression::SizeofExpression(std::unique_ptr<Expression> expression, lang::Location location)
    : Expression(location)
    , expression_(std::move(expression))
{
    addSubexpression(*expression_);
}

Expression& SizeofExpression::expression() const
{
    return *expression_;
}

std::optional<lang::ResolvingHandle<lang::Type>> SizeofExpression::tryGetType() const
{
    return lang::SizeType::getSize();
}

bool SizeofExpression::validate(ValidationLogger& validation_logger) const
{
    return expression_->validate(validation_logger);
}

Expression::Expansion SizeofExpression::expandWith(Expressions subexpressions) const
{
    return {Statements(), std::make_unique<SizeofExpression>(std::move(subexpressions[0]), location()), Statements()};
}

void SizeofExpression::doBuild(CompileContext& context)
{
    llvm::Value* content_value =
        lang::SizeType::buildContentValue(expression_->type()->getContentSize(context.module()), context);
    llvm::Value* native_value = lang::values::contentToNative(type(), content_value, context);

    std::shared_ptr<lang::WrappedNativeValue> value = std::make_shared<lang::WrappedNativeValue>(type(), native_value);
    setValue(value);
}
