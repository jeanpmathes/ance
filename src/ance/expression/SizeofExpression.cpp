#include "SizeofExpression.h"

#include "ance/ApplicationVisitor.h"
#include "ance/type/SizeType.h"
#include "compiler/CompileContext.h"

SizeofExpression::SizeofExpression(std::unique_ptr<Expression> expression, ance::Location location)
    : Expression(location)
    , expression_(std::move(expression))
{
    addChild(*expression_);
}

void SizeofExpression::setScope(ance::Scope* scope)
{
    expression_->setContainingScope(scope);
}

ance::Type* SizeofExpression::type()
{
    return ance::SizeType::getSize();
}

bool SizeofExpression::validate(ValidationLogger& validation_logger)
{
    return expression_->validate(validation_logger);
}

ance::Value* SizeofExpression::getValue() const
{
    return return_value_;
}

llvm::Value* SizeofExpression::buildNativeValue(CompileContext* context)
{
    return ance::SizeType::buildValue(expression_->type()->getContentSize(context->module()));
}

bool SizeofExpression::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitSizeofExpression(*this);
}
