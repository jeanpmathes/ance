#include "Addressof.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/utility/Values.h"
#include "validation/ValidationLogger.h"

Addressof::Addressof(Owned<Expression> arg, lang::Location location) : Expression(location), arg_(std::move(arg))
{
    addSubexpression(*arg_);
}

Expression const& Addressof::argument() const
{
    return *arg_;
}

void Addressof::defineType(lang::ResolvingHandle<lang::Type>& type)
{
    if (scope() == nullptr) return;

    auto value_type = arg_->type();

    if (value_type->isDefined())
    {
        if (value_type->isReferenceType()) { value_type = value_type->getElementType(); }

        type.reroute(scope()->context().getPointerType(value_type));
    }
}

bool Addressof::validate(ValidationLogger& validation_logger) const
{
    bool const is_arg_valid = arg_->validate(validation_logger);
    if (!is_arg_valid) return false;

    if (!arg_->isNamed())
    {
        validation_logger.logError("Cannot get address of unnamed value", arg_->location());
        return false;
    }

    return true;
}

Expression::Expansion Addressof::expandWith(Expressions subexpressions, lang::Context&) const
{
    return {Statements(), makeOwned<Addressof>(std::move(subexpressions[0]), location()), Statements()};
}

void Addressof::doBuild(CompileContext& context)
{
    Shared<lang::Value> value = arg_->getValue();
    value->buildNativeValue(context);

    llvm::Value* address = value->getNativeValue();
    if (!arg_->type()->isReferenceType()) address = lang::values::contentToNative(type(), address, context);

    setValue(makeShared<lang::WrappedNativeValue>(type(), address));
}

Addressof::~Addressof() = default;
