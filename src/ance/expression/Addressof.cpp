#include "Addressof.h"

#include "ance/ApplicationVisitor.h"
#include "ance/construct/value/WrappedNativeValue.h"
#include "ance/type/PointerType.h"
#include "ance/utility/Values.h"

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
    if (!return_type_) { return_type_ = ance::PointerType::get(application_, arg_->type()); }

    return return_type_;
}

bool Addressof::validate(ValidationLogger& validation_logger)
{
    return arg_->validate(validation_logger);
}

void Addressof::doBuild(CompileContext* context)
{
    ance::Value* value = arg_->getValue();
    value->buildNativeValue(context);

    llvm::Value* address        = value->getNativeValue();
    llvm::Value* stored_address = ance::Values::contentToNative(type(), address, context);

    setValue(new ance::WrappedNativeValue(type(), stored_address));
}

bool Addressof::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitAddressof(*this);
}

Addressof::~Addressof() = default;
