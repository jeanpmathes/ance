#include "SizeofExpression.h"

#include "lang/type/SizeType.h"
#include "lang/type/Type.h"
#include "compiler/CompileContext.h"
#include "lang/statement/Statement.h"
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

lang::ResolvingHandle<lang::Type> SizeofExpression::type()
{
    return lang::SizeType::getSize();
}

bool SizeofExpression::validate(ValidationLogger& validation_logger)
{
    return expression_->validate(validation_logger);
}

Expression::Expansion SizeofExpression::expandWith(Expressions subexpressions) const
{
    return {Statements(), std::make_unique<SizeofExpression>(std::move(subexpressions[0]), location()), Statements()};
}

std::shared_ptr<lang::Value> SizeofExpression::getValue() const
{
    return return_value_;
}

llvm::Value* SizeofExpression::buildNativeValue(CompileContext* context)
{
    llvm::Value* content_value =
        lang::SizeType::buildContentValue(expression_->type()->getContentSize(context->module()));
    return lang::Values::contentToNative(type(), content_value, context);
}