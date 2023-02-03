#include "Runtime.h"

#include <stdexcept>

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/value/Value.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/type/BooleanType.h"
#include "lang/type/BufferType.h"
#include "lang/type/FixedWidthIntegerType.h"
#include "lang/type/OpaquePointerType.h"
#include "lang/type/PointerType.h"
#include "lang/type/SizeType.h"
#include "lang/type/Type.h"
#include "lang/type/VoidType.h"
#include "lang/utility/Values.h"

void Runtime::init(CompileContext& context)
{
    context_ = &context;

    llvm::LLVMContext& llvm_context = context.llvmContext();
    llvm::Module&      module       = context.llvmModule();

    auto create_function = [&](char const*                                    name,
                               lang::ResolvingHandle<lang::Type>              return_type,
                               std::vector<lang::ResolvingHandle<lang::Type>> parameters) -> llvm::Function* {
        std::vector<llvm::Type*> llvm_parameters;
        llvm_parameters.reserve(parameters.size());
        for (lang::ResolvingHandle<lang::Type> const& parameter : parameters)
        {
            llvm_parameters.push_back(parameter->getContentType(llvm_context));
        }

        llvm::FunctionType* function_type =
            llvm::FunctionType::get(return_type->getContentType(llvm_context), llvm_parameters, false);
        return llvm::Function::Create(function_type, llvm::Function::ExternalLinkage, name, &module);
    };

    std::vector<lang::ResolvingHandle<lang::Type>> allocate_dynamic_parameters;
    allocate_dynamic_parameters.emplace_back(lang::SizeType::getSize());
    allocate_dynamic_ =
        create_function(ALLOCATE_DYNAMIC_NAME, lang::OpaquePointerType::get(), allocate_dynamic_parameters);

    std::vector<lang::ResolvingHandle<lang::Type>> delete_dynamic_parameters;
    delete_dynamic_parameters.emplace_back(lang::OpaquePointerType::get());
    delete_dynamic_ = create_function(DELETE_DYNAMIC_NAME, lang::VoidType::get(), delete_dynamic_parameters);

    std::vector<lang::ResolvingHandle<lang::Type>> assertion_parameters;
    assertion_parameters.emplace_back(lang::BooleanType::get());
    assertion_ = create_function(ASSERTION_NAME, lang::VoidType::get(), assertion_parameters);

    std::vector<lang::ResolvingHandle<lang::Type>> exit_parameters;
    exit_parameters.emplace_back(lang::FixedWidthIntegerType::get(32, false));
    exit_ = create_function(EXIT_NAME, lang::VoidType::get(), exit_parameters);

    std::vector<lang::ResolvingHandle<lang::Type>> const abort_parameters;
    abort_ = create_function(ABORT_NAME, lang::VoidType::get(), abort_parameters);

    is_initialized_ = true;
}

bool Runtime::isNameReserved(lang::Identifier const& name)
{
    return std::find(reserved_names_.begin(), reserved_names_.end(), name.text()) != reserved_names_.end();
}

Shared<lang::Value> Runtime::allocate(Allocator                         allocation,
                                      lang::ResolvingHandle<lang::Type> type,
                                      Optional<Shared<lang::Value>>     count,
                                      CompileContext&                   context)
{
    assert(is_initialized_);

    llvm::Value* count_value = nullptr;

    if (count.hasValue())
    {
        assert(lang::Type::areSame(count.value()->type(), lang::SizeType::getSize()));

        count.value()->buildContentValue(context);
        count_value = count.value()->getContentValue();
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
    }

    lang::ResolvingHandle<lang::Type> ptr_type =
        count.hasValue() ? lang::BufferType::get(type) : lang::PointerType::get(type);
    llvm::Value* native_ptr = lang::values::contentToNative(ptr_type, ptr_to_allocated, context);

    if (count_value) { type->buildDefaultInitializer(ptr_to_allocated, count_value, context); }
    else { type->buildDefaultInitializer(ptr_to_allocated, context); }

    return makeShared<lang::WrappedNativeValue>(ptr_type, native_ptr);
}

void Runtime::deleteDynamic(Shared<lang::Value> value, bool delete_buffer, CompileContext& context)
{
    assert(is_initialized_);

    assert(delete_buffer || value->type()->isPointerType());// Not deleting a buffer implies a pointer type.
    assert(!delete_buffer || value->type()->isBufferType());// Deleting a buffer implies a buffer type.

    value->buildContentValue(context);

    llvm::Value* ptr =
        value
            ->getContentValue();// While native value is a pointer too, it is not the pointer we need (points to stack).

    llvm::Type* size_content_type = lang::SizeType::getSize()->getContentType(context.llvmContext());
    llvm::Type* size_ptr_content_type =
        lang::PointerType::get(lang::SizeType::getSize())->getContentType(context.llvmContext());

    llvm::Value* memory_ptr = ptr;

    if (delete_buffer)
    {
        llvm::Value* content_ptr = context.ir().CreateBitCast(ptr, size_ptr_content_type, ptr->getName() + ".bitcast");

        memory_ptr = context.ir().CreateGEP(size_content_type,
                                            content_ptr,
                                            llvm::ConstantInt::get(llvm::IntegerType::getInt64Ty(context.llvmContext()),
                                                                   static_cast<uint64_t>(-1),
                                                                   true),
                                            content_ptr->getName() + ".gep");

        llvm::Value* count = context.ir().CreateLoad(size_content_type, memory_ptr, memory_ptr->getName() + ".load");

        value->type()->getElementType()->buildFinalizer(ptr, count, context);
    }
    else { value->type()->getElementType()->buildFinalizer(ptr, context); }

    llvm::Value* opaque_ptr = context.ir().CreateBitCast(memory_ptr,
                                                         llvm::Type::getInt8PtrTy(context.llvmContext()),
                                                         ptr->getName() + ".bitcast");

    std::array<llvm::Value*, 1> const args = {opaque_ptr};
    context.ir().CreateCall(delete_dynamic_, args);
}

void Runtime::buildAssert(Shared<lang::Value> value, CompileContext& context)
{
    assert(is_initialized_);

    assert(value->type()->isBooleanType());

    if (context_->unit().isAssertionsEnabled())
    {
        value->buildContentValue(context);
        llvm::Value* truth_value = value->getContentValue();

        context_->ir().CreateCall(assertion_, truth_value);
    }
}

void Runtime::buildExit(Shared<lang::Value> value, CompileContext& context)
{
    assert(is_initialized_);

    assert(value->type()->isFixedWidthIntegerType(32, false));

    value->buildContentValue(context);
    llvm::Value* exit_code = value->getContentValue();

    context_->ir().CreateCall(exit_, exit_code);
}

llvm::Value* Runtime::allocateAutomatic(lang::ResolvingHandle<lang::Type> type,
                                        llvm::Value*                      count_value,
                                        CompileContext&                   context)
{
    return context.ir().CreateAlloca(type->getContentType(context.llvmContext()), count_value, "alloca");
}

llvm::Value* Runtime::allocateDynamic(lang::ResolvingHandle<lang::Type> type,
                                      llvm::Value*                      count_value,
                                      CompileContext&                   context)
{
    llvm::Type* size_content_type = lang::SizeType::getSize()->getContentType(context.llvmContext());

    // Calculate the size to allocate.
    llvm::Value* size;

    if (count_value)
    {
        llvm::Value* element_size = llvm::ConstantInt::get(
            size_content_type,
            context.llvmModule().getDataLayout().getTypeAllocSize(type->getContentType(context.llvmContext())),
            false);

        size = context.ir().CreateMul(count_value, element_size, count_value->getName() + ".mul");

        llvm::Value* header_size =
            llvm::ConstantInt::get(size_content_type,
                                   context.llvmModule().getDataLayout().getTypeAllocSize(size_content_type),
                                   false);

        size = context.ir().CreateAdd(size, header_size, size->getName() + ".add");
    }
    else
    {
        size = llvm::ConstantInt::get(lang::SizeType::getSize()->getContentType(context.llvmContext()),
                                      type->getContentSize(context.llvmModule()).getFixedSize(),
                                      false);
    }

    llvm::Value* opaque_ptr = context.ir().CreateCall(allocate_dynamic_, size, allocate_dynamic_->getName() + ".call");

    llvm::Value* result_ptr;

    llvm::Type* result_content_type = lang::PointerType::get(type)->getContentType(context.llvmContext());
    llvm::Type* size_ptr_content_type =
        lang::PointerType::get(lang::SizeType::getSize())->getContentType(context.llvmContext());

    if (count_value)
    {
        llvm::Value* header_ptr =
            context.ir().CreateBitCast(opaque_ptr, size_ptr_content_type, opaque_ptr->getName() + ".bitcast");

        context.ir().CreateStore(count_value, header_ptr);

        llvm::Value* content_ptr =
            context.ir().CreateGEP(size_content_type,
                                   header_ptr,
                                   llvm::ConstantInt::get(llvm::IntegerType::getInt64Ty(context.llvmContext()), 1),
                                   header_ptr->getName() + ".gep");

        result_ptr = context.ir().CreateBitCast(content_ptr, result_content_type, content_ptr->getName() + ".bitcast");
    }
    else
    {
        result_ptr = context.ir().CreateBitCast(opaque_ptr, result_content_type, opaque_ptr->getName() + ".bitcast");
    }

    return result_ptr;
}
