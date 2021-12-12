#include "Addressof.h"

#include "ance/construct/value/WrappedNativeValue.h"
#include "ance/type/PointerType.h"
#include "ance/type/ReferenceType.h"
#include "ance/utility/Values.h"
#include "validation/ValidationLogger.h"

Addressof::Addressof(std::unique_ptr<Expression> arg, ance::Location location)
    : Expression(location)
    , arg_(std::move(arg))
{}

void Addressof::setScope(ance::Scope* scope)
{
    arg_->setContainingScope(scope);
}

ance::ResolvingHandle<ance::Type> Addressof::type()
{
    if (!return_type_)
    {
        ance::ResolvingHandle<ance::Type> value_type = arg_->type();

        if (value_type->isReferenceType()) { value_type = ance::ReferenceType::getReferencedType(value_type); }

        return_type_ = ance::PointerType::get(value_type);
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
    std::shared_ptr<ance::Value> value = arg_->getValue();
    value->buildNativeValue(context);

    llvm::Value* address        = value->getNativeValue();
    if (!arg_->type()->isReferenceType()) address = ance::Values::contentToNative(type(), address, context);

    setValue(std::make_shared<ance::WrappedNativeValue>(type(), address));
}

Addressof::~Addressof() = default;
