#include "Runtime.h"

#include <stdexcept>

#include "lang/construct/value/Value.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/type/PointerType.h"
#include "lang/type/SizeType.h"
#include "lang/type/IntegerType.h"
#include "lang/type/Type.h"
#include "lang/utility/Values.h"
#include "compiler/CompileContext.h"

void Runtime::init(CompileContext* context)
{
    context_ = context;

    llvm::LLVMContext& llvm_context = *context->llvmContext();
    llvm::Module&      module       = *context->module();

    // Setup dynamic memory allocation call.
    llvm::Type* allocate_dynamic_params[] = {llvm::Type::getInt32Ty(llvm_context),
                                             lang::SizeType::getSize()->getContentType(llvm_context)};
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

void Runtime::setExit(lang::ResolvingHandle<lang::Function> exit)
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
        lang::ResolvingHandle<lang::Type> exit_value_type = lang::IntegerType::get(32, false);
        llvm::Value* exit_value_content = llvm::ConstantInt::get(exit_value_type->getContentType(llvm_context), 3);
        llvm::Value* exit_value_native  = lang::Values::contentToNative(exit_value_type, exit_value_content, context_);
        std::shared_ptr<lang::Value> exit_value =
            std::make_shared<lang::WrappedNativeValue>(exit_value_type, exit_value_native);

        std::vector<std::shared_ptr<lang::Value>> args;
        args.push_back(exit_value);
        exit->buildCall(args, context_);
        context_->ir()->CreateBr(exit_block);
    }

    context_->ir()->SetInsertPoint(exit_block);
    {
        context_->ir()->CreateRetVoid();
    }
}

std::shared_ptr<lang::Value> Runtime::allocate(Allocator                           allocation,
                                               lang::ResolvingHandle<lang::Type>   type,
                                               const std::shared_ptr<lang::Value>& count,
                                               CompileContext*                     context)
{
    llvm::Value* count_value = nullptr;

    if (count)
    {
        assert(lang::Type::areSame(count->type(), lang::SizeType::getSize()));

        count->buildContentValue(context);
        count_value = count->getContentValue();
    }

    llvm::Value* ptr_to_allocated;

    switch (allocation)
    {
        case AUTOMATIC:
            ptr_to_allocated = allocateAutomatic(type, count_value, context);
            break;

        case DYNAMIC:
            ptr_to_allocated = allocateDynamic(type, count_value, context);
            break;

        default:
            throw std::invalid_argument("Unsupported allocation type.");
    }

    lang::ResolvingHandle<lang::Type> ptr_type   = lang::PointerType::get(type);
    llvm::Value*                      native_ptr = lang::Values::contentToNative(ptr_type, ptr_to_allocated, context);

    if (count_value) { type->buildDefaultInitializer(ptr_to_allocated, count_value, context); }
    else { type->buildDefaultInitializer(ptr_to_allocated, context); }

    return std::make_shared<lang::WrappedNativeValue>(ptr_type, native_ptr);
}

void Runtime::deleteDynamic(const std::shared_ptr<lang::Value>& value, bool, CompileContext* context)
{
    assert(value->type()->isPointerType());

    value->buildContentValue(context);

    llvm::Value* ptr =
        value->getContentValue();// While native value is a pointer too, it might not be the pointer we need.
    llvm::Value* opaque_ptr = context->ir()->CreateBitCast(ptr,
                                                           llvm::Type::getInt8PtrTy(*context->llvmContext()),
                                                           ptr->getName() + ".bitcast");

    llvm::Value* args[] = {opaque_ptr};

    llvm::Value* success = context->ir()->CreateCall(delete_dynamic_type_, delete_dynamic_, args);
    success->setName(delete_dynamic_->getName() + ".call");
}

void Runtime::buildAssert(const std::shared_ptr<lang::Value>& value, CompileContext* context)
{
    assert(value->type()->isBooleanType());

    value->buildContentValue(context);
    llvm::Value* truth_value = value->getContentValue();

    context_->ir()->CreateCall(assertion_, truth_value);
}

llvm::Value* Runtime::allocateAutomatic(lang::ResolvingHandle<lang::Type> type,
                                        llvm::Value*                      count_value,
                                        CompileContext*                   context)
{
    return context->ir()->CreateAlloca(type->getContentType(*context->llvmContext()), count_value, "alloca");
}

llvm::Value* Runtime::allocateDynamic(lang::ResolvingHandle<lang::Type> type,
                                      llvm::Value*                      count_value,
                                      CompileContext*                   context)
{
    // Set the zero init flag.
    llvm::Value* flags = llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context->llvmContext()), 0x0040, false);

    // Calculate the size to allocate.
    llvm::Value* size;

    if (count_value)
    {
        llvm::Value* element_size =
            llvm::ConstantInt::get(lang::SizeType::getSize()->getContentType(*context->llvmContext()),
                                   type->getContentSize(context->module()).getFixedSize(),
                                   false);

        size = context->ir()->CreateMul(count_value, element_size, count_value->getName() + ".mul");
    }
    else
    {
        size = llvm::ConstantInt::get(lang::SizeType::getSize()->getContentType(*context->llvmContext()),
                                      type->getContentSize(context->module()).getFixedSize(),
                                      false);
    }

    llvm::Value* args[] = {flags, size};

    llvm::Value* opaque_ptr = context->ir()->CreateCall(allocate_dynamic_type_,
                                                        allocate_dynamic_,
                                                        args,
                                                        allocate_dynamic_->getName() + ".call");
    return context->ir()->CreateBitCast(opaque_ptr,
                                        lang::PointerType::get(type)->getContentType(*context->llvmContext()),
                                        opaque_ptr->getName() + ".bitcast");
}
