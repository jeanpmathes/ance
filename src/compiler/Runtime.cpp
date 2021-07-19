#include "Runtime.h"

#include <stdexcept>

#include "compiler/CompileContext.h"
#include "ance/type/PointerType.h"
#include "ance/type/SizeType.h"
#include "ance/type/Type.h"
#include "ance/construct/value/Value.h"
#include "ance/construct/value/WrappedNativeValue.h"

void Runtime::init(
    llvm::LLVMContext& c,
    llvm::Module*      m,
    CompileContext*,
    llvm::IRBuilder<>&,
    llvm::DIBuilder*)
{
    // Setup dynamic memory allocation call.
    llvm::Type* allocate_dynamic_params[] =
        {llvm::Type::getInt32Ty(c), ance::SizeType::get()->getNativeType(c)};
    allocate_dynamic_type_ = llvm::FunctionType::get(llvm::Type::getInt8PtrTy(c), allocate_dynamic_params, false);
    allocate_dynamic_      = llvm::Function::Create(
        allocate_dynamic_type_,
        llvm::GlobalValue::LinkageTypes::ExternalLinkage,
        "GlobalAlloc",
        m);

    // Setup dynamic memory delete call.
    llvm::Type* delete_dynamic_params[] = {llvm::Type::getInt8PtrTy(c)};
    delete_dynamic_type_                = llvm::FunctionType::get(llvm::Type::getInt8PtrTy(c), delete_dynamic_params, false);
    delete_dynamic_                     = llvm::Function::Create(
        delete_dynamic_type_,
        llvm::GlobalValue::LinkageTypes::ExternalLinkage,
        "GlobalFree",
        m);
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

    value->buildNativeValue(context);

    llvm::Value* ptr        = value->getNativeValue();
    llvm::Value* opaque_ptr = context->ir()->CreateBitCast(ptr, llvm::Type::getInt8PtrTy(*context->llvmContext()));

    llvm::Value* args[] = {opaque_ptr};

    context->ir()->CreateCall(delete_dynamic_type_, delete_dynamic_, args);
}

llvm::Value* Runtime::allocateAutomatic(ance::Type* type, ance::Value* count, CompileContext* context)
{
    llvm::Value* count_value = nullptr;

    if (count)
    {
        count->buildNativeValue(context);
        count_value = count->getNativeValue();
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
            llvm::ConstantInt::get(
                ance::SizeType::get()->getNativeType(*context->llvmContext()),
                type->getContentSize(context->module()).getFixedSize(),
                false);
        count->buildNativeValue(context);
        llvm::Value* element_count = count->getNativeValue();

        size = context->ir()->CreateMul(element_size, element_count);
    }
    else
    {
        size = llvm::ConstantInt::get(
            ance::SizeType::get()->getNativeType(*context->llvmContext()),
            type->getContentSize(context->module()).getFixedSize(), false);
    }

    llvm::Value* args[] = {flags, size};

    llvm::Value* opaque_ptr = context->ir()->CreateCall(allocate_dynamic_type_, allocate_dynamic_, args);
    return context->ir()
        ->CreateBitCast(
            opaque_ptr,
            ance::PointerType::get(*context->application(), type)->getNativeType(*context->llvmContext()));
}
