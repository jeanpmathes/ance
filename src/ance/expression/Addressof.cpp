#include "Addressof.h"

#include "ance/ApplicationVisitor.h"
#include "ance/construct/value/WrappedNativeValue.h"
#include "ance/type/PointerType.h"
#include "ance/type/ReferenceType.h"
#include "ance/utility/Values.h"
#include "validation/ValidationLogger.h"

Addressof::Addressof(Expression* arg, Application& app, ance::Location location)
    : Expression(location)
    , arg_(arg)
    , application_(app)
{
    addChild(*arg);
}

void Addressof::setScope(ance::Scope* scope)
{
    arg_->setContainingScope(scope);
}

ance::Type* Addressof::type()
{
    if (!return_type_)
    {
        ance::Type* value_type = arg_->type();

        if (ance::ReferenceType::isReferenceType(value_type))
        {
            value_type = ance::ReferenceType::getReferencedType(value_type);
        }

        return_type_ = ance::PointerType::get(application_, value_type);
    }

    return return_type_;
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
    ance::Value* value = arg_->getValue();
    value->buildNativeValue(context);

    llvm::Value* address        = value->getNativeValue();
    if (!ance::ReferenceType::isReferenceType(arg_->type()))
        address = ance::Values::contentToNative(type(), address, context);

    setValue(new ance::WrappedNativeValue(type(), address));
}

bool Addressof::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitAddressof(*this);
}

Addressof::~Addressof() = default;
