#include "SizeofExpression.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/statement/Statement.h"
#include "lang/type/SizeType.h"
#include "lang/type/Type.h"
#include "lang/utility/Values.h"

SizeofExpression::SizeofExpression(Owned<Expression> expression, lang::Location location)
    : Expression(location)
    , expression_(std::move(expression))
{
    addSubexpression(*expression_);
}

Expression const& SizeofExpression::expression() const
{
    return *expression_;
}

void SizeofExpression::defineType(lang::ResolvingHandle<lang::Type>& type)
{
    if (scope() == nullptr) return;

    type.reroute(scope()->context().getSizeType());
}

bool SizeofExpression::validate(ValidationLogger& validation_logger) const
{
    return expression_->validate(validation_logger);
}

Expression::Expansion SizeofExpression::expandWith(Expressions subexpressions, lang::Context&) const
{
    return {Statements(), makeOwned<SizeofExpression>(std::move(subexpressions[0]), location()), Statements()};
}

void SizeofExpression::doBuild(CompileContext& context)
{
    llvm::Value* content_value =
        lang::SizeType::buildContentValue(expression_->type()->getContentSize(context.llvmModule()), context);
    llvm::Value* native_value = lang::values::contentToNative(type(), content_value, context);

    Shared<lang::WrappedNativeValue> value = makeShared<lang::WrappedNativeValue>(type(), native_value);
    setValue(value);
}
