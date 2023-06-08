#include "IndirectType.h"

#include "compiler/CompileContext.h"
#include "compiler/Runtime.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/value/Value.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/BooleanType.h"
#include "lang/type/ReferenceType.h"
#include "lang/utility/Values.h"

lang::IndirectType::IndirectType(lang::ResolvingHandle<lang::Type> element_type) : value_type_(element_type) {}

llvm::Constant* lang::IndirectType::getDefaultContent(llvm::Module& m) const
{
    return llvm::ConstantPointerNull::get(getContentType(m.getContext()));
}

llvm::PointerType* lang::IndirectType::getContentType(llvm::LLVMContext& c) const
{
    llvm::Type* native_type = value_type_->getContentType(c);
    return llvm::PointerType::get(native_type, 0);
}

bool lang::IndirectType::definesIndirection() const
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

Shared<lang::Value> lang::IndirectType::buildIndirection(Shared<Value> value, CompileContext& context)
{
    if (getIndirectionType()->getStateCount().isUnit())
        return lang::WrappedNativeValue::makeDefault(getIndirectionType(), context);

    value->buildContentValue(context);
    llvm::Value* ptr = value->getContentValue();

    if (scope()->context().isContainingRuntime())
    {
        llvm::Value* is_null     = context.ir().CreateIsNull(ptr, ptr->getName() + "is_null");
        llvm::Value* is_not_null = context.ir().CreateNot(is_null, ptr->getName() + "is_not_null");

        llvm::Value* is_not_null_ptr =
            lang::values::contentToNative(context.types().getBooleanType(), is_not_null, context);
        Shared<lang::Value> truth =
            makeShared<lang::WrappedNativeValue>(context.types().getBooleanType(), is_not_null_ptr);

        context.runtime().buildAssert(truth, "Null pointer dereference at " + context.getLocationString(), context);
    }

    auto value_reference = context.types().getReferenceType(value_type_);

    llvm::Value* native_value = lang::values::contentToNative(value_reference, ptr, context);
    return makeShared<lang::WrappedNativeValue>(value_reference, native_value);
}
