#include "Addressof.h"

#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/type/PointerType.h"
#include "lang/utility/Values.h"
#include "validation/ValidationLogger.h"

Addressof::Addressof(std::unique_ptr<Expression> arg, lang::Location location)
    : Expression(location)
    , arg_(std::move(arg))
{
    addSubexpression(*arg_);
}

Expression& Addressof::argument() const
{
    return *arg_;
}

lang::ResolvingHandle<lang::Type> Addressof::type()
{
    if (!return_type_)
    {
        lang::ResolvingHandle<lang::Type> value_type = arg_->type();

        if (value_type->isReferenceType()) { value_type = value_type->getElementType(); }

        return_type_ = lang::PointerType::get(value_type);
    }

    return *return_type_;
}

bool Addressof::validate(ValidationLogger& validation_logger)
{
    bool is_arg_valid = arg_->validate(validation_logger);
    if (!is_arg_valid) return false;

    if (!arg_->isNamed())
    {
        validation_logger.logError("Cannot get address of unnamed value", arg_->location());
        return false;
    }

    return true;
}

void Addressof::doBuild(CompileContext* context)
{
    std::shared_ptr<lang::Value> value = arg_->getValue();
    value->buildNativeValue(context);

    llvm::Value* address        = value->getNativeValue();
    if (!arg_->type()->isReferenceType()) address = lang::Values::contentToNative(type(), address, context);

    setValue(std::make_shared<lang::WrappedNativeValue>(type(), address));
}

Addressof::~Addressof() = default;
