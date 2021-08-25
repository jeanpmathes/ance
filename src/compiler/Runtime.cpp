#include "Runtime.h"

#include <stdexcept>

#include "ance/construct/value/Value.h"
#include "ance/construct/value/WrappedNativeValue.h"
#include "ance/type/PointerType.h"
#include "ance/type/SizeType.h"
#include "ance/type/Type.h"
#include "compiler/CompileContext.h"

void Runtime::init(CompileContext* context)
{
    llvm::LLVMContext& llvm_context = *context->llvmContext();
    llvm::Module&      module       = *context->module();

    // Setup dynamic memory allocation call.
    llvm::Type* allocate_dynamic_params[] = {llvm::Type::getInt32Ty(llvm_context),
                                             ance::SizeType::get()->getNativeType(llvm_context)};
    allocate_dynamic_type_ =
        llvm::FunctionType::get(llvm::Type::getInt8PtrTy(llvm_context), allocate_dynamic_params, false);
    allocate_dynamic_ = llvm::Function::Create(allocate_dynamic_type_,
                                               llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                                               "GlobalAlloc",
                                               module);

    // Setup dynamic memory delete call.
    llvm::Type* delete_dynamic_params[] = {llvm::Type::getInt8PtrTy(llvm_context)};
    delete_dynamic_type_ =
        llvm::FunctionType::get(llvm::Type::getInt8PtrTy(llvm_context), delete_dynamic_params, false);
    delete_dynamic_ = llvm::Function::Create(delete_dynamic_type_,
                                             llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                                             "GlobalFree",
                                             module);
}

ance::Value* Runtime::allocate(Allocator allocation, ance::Type* type, ance::Value* count, CompileContext* context)
{
    if (count)
    {
        assert(count->type() == ance::SizeType::get() && "Count parameter of allocation should be of type size.");
    }

    llvm::Value* native_ptr;

    switch (allocation)
    {
        case AUTOMATIC:
            native_ptr = allocateAutomatic(type, count, context);
            break;

        case DYNAMIC:
            native_ptr = allocateDynamic(type, count, context);
            break;

        default:
            throw std::invalid_argument("Unsupported allocation type.");
    }

    return new ance::WrappedNativeValue(ance::PointerType::get(*context->application(), type), native_ptr);
}

void Runtime::deleteDynamic(ance::Value* value, bool delete_buffer, CompileContext* context)
{
    ance::Type* type = value->type();
    assert(ance::PointerType::isPointerType(type) && "Type of value to delete has to be pointer type.");

    value->buildContentValue(context);

    llvm::Value* ptr =
        value->getContentValue();// While native value is a pointer too, it might not be the pointer we need.
    llvm::Value* opaque_ptr = context->ir()->CreateBitCast(ptr, llvm::Type::getInt8PtrTy(*context->llvmContext()));

    llvm::Value* args[] = {opaque_ptr};

    llvm::Value* success = context->ir()->CreateCall(delete_dynamic_type_, delete_dynamic_, args);
    success->setName("..free");
}

llvm::Value* Runtime::allocateAutomatic(ance::Type* type, ance::Value* count, CompileContext* context)
{
    llvm::Value* count_value = nullptr;

    if (count)
    {
        count->buildContentValue(context);
        count_value = count->getContentValue();
    }

    return context->ir()->CreateAlloca(type->getContentType(*context->llvmContext()), count_value);
}

llvm::Value* Runtime::allocateDynamic(ance::Type* type, ance::Value* count, CompileContext* context)
{
    // Set the zero init flag.
    llvm::Value* flags = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context->llvmContext()), 0x0040, false);

    // Calculate the size to allocate.
    llvm::Value* size;

    if (count)
    {
        llvm::Value* element_size =
            llvm::ConstantInt::get(ance::SizeType::get()->getNativeType(*context->llvmContext()),
                                   type->getContentSize(context->module()).getFixedSize(),
                                   false);
        count->buildNativeValue(context);
        llvm::Value* element_count = count->getContentValue();

        size = context->ir()->CreateMul(element_size, element_count);
    }
    else
    {
        size = llvm::ConstantInt::get(ance::SizeType::get()->getNativeType(*context->llvmContext()),
                                      type->getContentSize(context->module()).getFixedSize(),
                                      false);
    }

    llvm::Value* args[] = {flags, size};

    llvm::Value* opaque_ptr = context->ir()->CreateCall(allocate_dynamic_type_, allocate_dynamic_, args);
    return context->ir()->CreateBitCast(
        opaque_ptr,
        ance::PointerType::get(*context->application(), type)->getNativeType(*context->llvmContext()));
}
