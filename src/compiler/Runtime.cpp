#include "Runtime.h"

#include <stdexcept>

#include "ance/construct/value/Value.h"
#include "ance/construct/value/WrappedNativeValue.h"
#include "ance/type/PointerType.h"
#include "ance/type/SizeType.h"
#include "ance/type/IntegerType.h"
#include "ance/type/Type.h"
#include "ance/utility/Values.h"
#include "compiler/CompileContext.h"

void Runtime::init(CompileContext* context)
{
    context_ = context;

    llvm::LLVMContext& llvm_context = *context->llvmContext();
    llvm::Module&      module       = *context->module();

    // Setup dynamic memory allocation call.
    llvm::Type* allocate_dynamic_params[] = {llvm::Type::getInt32Ty(llvm_context),
                                             ance::SizeType::getSize()->getContentType(llvm_context)};
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

void Runtime::setExit(ance::ResolvingHandle<ance::Function> exit)
{
    llvm::LLVMContext& llvm_context = *context_->llvmContext();
    llvm::Module&      module       = *context_->module();

    llvm::Type* assertion_params[] = {llvm::Type::getInt1Ty(llvm_context)};

    assertion_type_ = llvm::FunctionType::get(llvm::Type::getVoidTy(llvm_context), assertion_params, false);
    assertion_ =
        llvm::Function::Create(assertion_type_, llvm::GlobalValue::LinkageTypes::PrivateLinkage, "rt$assert", module);

    llvm::BasicBlock* entry_block = llvm::BasicBlock::Create(llvm_context, "entry", assertion_);
    llvm::BasicBlock* abort_block = llvm::BasicBlock::Create(llvm_context, "abort", assertion_);
    llvm::BasicBlock* exit_block  = llvm::BasicBlock::Create(llvm_context, "exit", assertion_);

    context_->ir()->SetInsertPoint(entry_block);
    {
        llvm::Value* truth_value = assertion_->getArg(0);
        context_->ir()->CreateCondBr(truth_value, exit_block, abort_block);
    }

    context_->ir()->SetInsertPoint(abort_block);
    {
        ance::ResolvingHandle<ance::Type> exit_value_type = ance::IntegerType::get(32, false);
        llvm::Value* exit_value_content = llvm::ConstantInt::get(exit_value_type->getContentType(llvm_context), 3);
        llvm::Value* exit_value_native  = ance::Values::contentToNative(exit_value_type, exit_value_content, context_);
        std::shared_ptr<ance::Value> exit_value =
            std::make_shared<ance::WrappedNativeValue>(exit_value_type, exit_value_native);

        std::vector<std::shared_ptr<ance::Value>> args;
        args.push_back(exit_value);
        exit->buildCall(args, context_);
        context_->ir()->CreateBr(exit_block);
    }

    context_->ir()->SetInsertPoint(exit_block);
    {
        context_->ir()->CreateRetVoid();
    }
}

std::shared_ptr<ance::Value> Runtime::allocate(Allocator                           allocation,
                                               ance::ResolvingHandle<ance::Type>   type,
                                               const std::shared_ptr<ance::Value>& count,
                                               CompileContext*                     context)
{
    if (count) { assert(count->type() == ance::SizeType::getSize()); }

    llvm::Value* ptr_to_allocated;

    switch (allocation)
    {
        case AUTOMATIC:
            ptr_to_allocated = allocateAutomatic(type, count, context);
            break;

        case DYNAMIC:
            ptr_to_allocated = allocateDynamic(type, count, context);
            break;

        default:
            throw std::invalid_argument("Unsupported allocation type.");
    }

    ance::ResolvingHandle<ance::Type> ptr_type   = ance::PointerType::get(type);
    llvm::Value*                      native_ptr = ance::Values::contentToNative(ptr_type, ptr_to_allocated, context);

    return std::make_shared<ance::WrappedNativeValue>(ptr_type, native_ptr);
}

void Runtime::deleteDynamic(const std::shared_ptr<ance::Value>& value, bool, CompileContext* context)
{
    assert(value->type()->isPointerType());

    value->buildContentValue(context);

    llvm::Value* ptr =
        value->getContentValue();// While native value is a pointer too, it might not be the pointer we need.
    llvm::Value* opaque_ptr = context->ir()->CreateBitCast(ptr, llvm::Type::getInt8PtrTy(*context->llvmContext()));

    llvm::Value* args[] = {opaque_ptr};

    llvm::Value* success = context->ir()->CreateCall(delete_dynamic_type_, delete_dynamic_, args);
    success->setName("..free");
}

void Runtime::buildAssert(const std::shared_ptr<ance::Value>& value, CompileContext* context)
{
    assert(value->type()->isBooleanType());

    value->buildContentValue(context);
    llvm::Value* truth_value = value->getContentValue();

    context_->ir()->CreateCall(assertion_, truth_value);
}

llvm::Value* Runtime::allocateAutomatic(ance::ResolvingHandle<ance::Type>   type,
                                        const std::shared_ptr<ance::Value>& count,
                                        CompileContext*                     context)
{
    llvm::Value* count_value = nullptr;

    if (count)
    {
        count->buildContentValue(context);
        count_value = count->getContentValue();
    }

    return context->ir()->CreateAlloca(type->getContentType(*context->llvmContext()), count_value);
}

llvm::Value* Runtime::allocateDynamic(ance::ResolvingHandle<ance::Type>   type,
                                      const std::shared_ptr<ance::Value>& count,
                                      CompileContext*                     context)
{
    // Set the zero init flag.
    llvm::Value* flags = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context->llvmContext()), 0x0040, false);

    // Calculate the size to allocate.
    llvm::Value* size;

    if (count)
    {
        llvm::Value* element_size =
            llvm::ConstantInt::get(ance::SizeType::getSize()->getContentType(*context->llvmContext()),
                                   type->getContentSize(context->module()).getFixedSize(),
                                   false);

        count->buildContentValue(context);
        llvm::Value* element_count = count->getContentValue();

        size = context->ir()->CreateMul(element_size, element_count);
    }
    else
    {
        size = llvm::ConstantInt::get(ance::SizeType::getSize()->getContentType(*context->llvmContext()),
                                      type->getContentSize(context->module()).getFixedSize(),
                                      false);
    }

    llvm::Value* args[] = {flags, size};

    llvm::Value* opaque_ptr = context->ir()->CreateCall(allocate_dynamic_type_, allocate_dynamic_, args);
    return context->ir()->CreateBitCast(opaque_ptr,
                                        ance::PointerType::get(type)->getContentType(*context->llvmContext()));
}
