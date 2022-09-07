#include "IndirectType.h"

#include "lang/construct/value/Value.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/type/ReferenceType.h"
#include "lang/utility/Values.h"

lang::IndirectType::IndirectType(lang::ResolvingHandle<lang::Type> element_type)
    : value_type_(element_type)
    , value_reference_(lang::ReferenceType::get(element_type))
{}

llvm::Constant* lang::IndirectType::getDefaultContent(llvm::Module& m)
{
    return llvm::ConstantPointerNull::get(getContentType(m.getContext()));
}

llvm::PointerType* lang::IndirectType::getContentType(llvm::LLVMContext& c) const
{
    llvm::Type* native_type;

    if (value_type_->isVoidType()) { native_type = llvm::Type::getInt8PtrTy(c); }
    else { native_type = value_type_->getContentType(c); }

    return llvm::PointerType::get(native_type, 0);
}

bool lang::IndirectType::definesIndirection()
{
    return true;
}

lang::ResolvingHandle<lang::Type> lang::IndirectType::getIndirectionType()
{
    return value_type_;
}

bool lang::IndirectType::validateIndirection(lang::Location, ValidationLogger&) const
{
    return true;
}

std::shared_ptr<lang::Value> lang::IndirectType::buildIndirection(std::shared_ptr<Value> value, CompileContext& context)
{
    value->buildContentValue(context);
    llvm::Value* ptr = value->getContentValue();

    llvm::Value* native_value = lang::Values::contentToNative(value_reference_, ptr, context);
    return std::make_shared<lang::WrappedNativeValue>(value_reference_, native_value);
}
