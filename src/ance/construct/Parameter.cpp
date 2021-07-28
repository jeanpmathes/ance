#include "Parameter.h"

#include <utility>

#include "ance/type/Type.h"
#include "ance/utility/Values.h"

ance::Parameter::Parameter(ance::Type* type, std::string name)
    : type_(type), name_(std::move(name))
{
}

ance::Type* ance::Parameter::type()
{
    return type_;
}

std::string ance::Parameter::name()
{
    return name_;
}

void ance::Parameter::wrap(llvm::Argument* argument)
{
    switch (type_->storage())
    {
        case InternalStorage::AS_TEMPORARY: {
            native_value_ = argument;
            native_value_->setName(name_);
            break;
        }
        case InternalStorage::AS_POINTER: {
            content_value_ = argument;
            content_value_->setName(name_ + ".arg");
            break;
        }
    }
}

void ance::Parameter::buildNativeValue(CompileContext* context)
{
    if (!native_value_)
    {
        native_value_ = ance::Values::contentToNative(type(), content_value_, context);
    }
}

void ance::Parameter::buildContentValue(CompileContext* context)
{
    if (!content_value_)
    {
        content_value_ = ance::Values::nativeToContent(type(), native_value_, context);
    }
}

llvm::Value* ance::Parameter::getNativeValue()
{
    return native_value_;
}

llvm::Value* ance::Parameter::getContentValue()
{
    return content_value_;
}
