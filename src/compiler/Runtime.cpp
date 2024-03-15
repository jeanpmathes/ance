#include "Runtime.h"

#include <stdexcept>

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Value.h"
#include "lang/type/BooleanType.h"
#include "lang/type/FixedWidthIntegerType.h"
#include "lang/type/OpaquePointerType.h"
#include "lang/type/Type.h"
#include "lang/type/VectorType.h"

void Runtime::init(CompileContext& context)
{
    auto create_function = [&](char const*                                    name,
                               lang::ResolvingHandle<lang::Type>              return_type,
                               std::vector<lang::ResolvingHandle<lang::Type>>& parameter_types) -> lang::Function* {
        std::vector<Shared<lang::Parameter>> parameters;
        parameters.reserve(parameter_types.size());
        for (lang::ResolvingHandle<lang::Type> parameter_type : parameter_types)
        {
            parameters.emplace_back(makeShared<lang::Parameter>(parameter_type));
        }

        lang::ResolvingHandle<lang::Function> function =
            lang::makeHandled<lang::Function>(lang::Identifier::like(name));
        function->defineAsRuntime(return_type, parameters, context);

        context.unit().globalScope().addEntity(lang::OwningHandle<lang::Function>::takeOwnership(function));

        lang::Function* function_ptr = &*function;
        functions_.emplace_back(function_ptr);

        return function_ptr;
    };

    {
        std::vector<lang::ResolvingHandle<lang::Type>> parameters;
        parameters.emplace_back(context.ctx().getSizeType());
        allocate_dynamic_ = create_function(ALLOCATE_DYNAMIC_NAME, context.ctx().getOpaquePointerType(), parameters);
    }

    {
        std::vector<lang::ResolvingHandle<lang::Type>> parameters;
        parameters.emplace_back(context.ctx().getOpaquePointerType());
        delete_dynamic_ = create_function(DELETE_DYNAMIC_NAME, context.ctx().getUnitType(), parameters);
    }

    {
        std::vector<lang::ResolvingHandle<lang::Type>> parameters;
        parameters.emplace_back(context.ctx().getBooleanType());
        parameters.emplace_back(context.ctx().getPointerType(context.ctx().getFixedWidthIntegerType(8, false)));
        assertion_ = create_function(ASSERTION_NAME, context.ctx().getUnitType(), parameters);
    }

    {
        std::vector<lang::ResolvingHandle<lang::Type>> parameters;
        parameters.emplace_back(context.ctx().getPointerType(context.ctx().getFixedWidthIntegerType(8, false)));
        abort_ = create_function(ABORT_NAME, context.ctx().getUnitType(), parameters);
    }

    for (lang::Function* function : functions_) { function->buildDeclaration(context); }

    is_initialized_ = true;
}

bool Runtime::isNameReserved(lang::Identifier const& name)
{
    return std::find(reserved_names_.begin(), reserved_names_.end(), name.text()) != reserved_names_.end();
}

Shared<lang::Value> Runtime::allocate(Allocator                         allocation,
                                      lang::Type const&             type,
                                      Optional<Shared<lang::Value>>     count,
                                      CompileContext&                   context)
{
    assert(is_initialized_);

    lang::Type const& return_type =
        count.hasValue() ? context.ctx().getBufferType(type) : context.ctx().getPointerType(type);

    if (type.getStateCount().isUnit()) return context.exec().getDefault(return_type);

    Optional<Shared<lang::Value>> ptr_to_allocated;

    Shared<lang::Value> count_value = count.valueOr(context.exec().getSizeN(1));

    switch (allocation)
    {
        case AUTOMATIC:
            ptr_to_allocated = allocateAutomatic(type, count_value, context);
            break;

        case DYNAMIC:
            ptr_to_allocated = allocateDynamic(type, count_value, count.hasValue(), context);
            break;
    }

    if (count.hasValue()) { type.performDefaultInitializer(ptr_to_allocated.value(), count_value, context); }
    else { type.performDefaultInitializer(ptr_to_allocated.value(), context); }

    return context.exec().computeCastedAddress(ptr_to_allocated.value(), return_type);
}

void Runtime::deleteDynamic(Shared<lang::Value> address, bool delete_buffer, CompileContext& context)
{
    assert(is_initialized_);

    assert(delete_buffer || address->type().isPointerType());// Not deleting a buffer implies a pointer type.
    assert(!delete_buffer || address->type().isBufferType());// Deleting a buffer implies a buffer type.

    if (address->type().getElementType().getStateCount().isUnit()) return;

    if (delete_buffer)
    {
        Shared<lang::Value> memory_as_size_ptr =
            context.exec().computeCastedAddress(address, context.ctx().getPointerType(context.ctx().getSizeType()));
        Shared<lang::Value> count_value_ptr = context.exec().computeElementPointer(memory_as_size_ptr,
                                                                                   context.exec().getDiffN(-1),
                                                                                   Execution::IndexingMode::POINTER,
                                                                                   std::nullopt);
        Shared<lang::Value> count_value     = context.exec().performLoadFromAddress(count_value_ptr);

        Shared<lang::Value> address_as_ptr =
            context.exec().computeCastedAddress(address,
                                                context.ctx().getPointerType(address->type().getElementType()));

        address->type().getElementType().performFinalizer(address_as_ptr, count_value, context);

        address = count_value_ptr;
    }
    else { address->type().getElementType().performFinalizer(address, context); }

    Shared<lang::Value> opaque_ptr = context.exec().computeCastedAddress(address, context.ctx().getOpaquePointerType());

    std::vector<Shared<lang::Value>> parameters;
    parameters.emplace_back(opaque_ptr);
    delete_dynamic_->buildCall(parameters, context);
}

void Runtime::buildAssert(Shared<lang::Value> value, std::string const& description, CompileContext& context)
{
    assert(is_initialized_);

    if (!context.unit().isAssertionsEnabled()) return;

    Shared<lang::Value> truth_value     = context.exec().performBooleanCollapse(value);
    Shared<lang::Value> description_ptr = context.exec().getCString(description);

    std::vector<Shared<lang::Value>> parameters;
    parameters.emplace_back(truth_value);
    parameters.emplace_back(description_ptr);
    assertion_->buildCall(parameters, context);
}

void Runtime::buildAbort(std::string const& reason, CompileContext& context)
{
    assert(is_initialized_);

    Shared<lang::Value> reason_ptr = context.exec().getCString(reason);

    std::vector<Shared<lang::Value>> parameters;
    parameters.emplace_back(reason_ptr);
    abort_->buildCall(parameters, context);
}

Shared<lang::Value> Runtime::allocateAutomatic(lang::Type const&   type,
                                               Shared<lang::Value>               count,
                                               CompileContext&                   context)
{
    return context.exec().performStackAllocation(type, count);
}

Shared<lang::Value> Runtime::allocateDynamic(lang::Type const&   type,
                                             Shared<lang::Value>               count,
                                             bool                              is_buffer,
                                             CompileContext&                   context)
{
    Shared<lang::Value> size_to_allocate = context.exec().computeAllocatedSize(type, count);

    if (is_buffer)// Prepend a header to store the count.
    {
        Shared<lang::Value> header_size =
            context.exec().computeAllocatedSize(context.ctx().getSizeType(), std::nullopt);
        size_to_allocate =
            context.exec().performOperator(lang::BinaryOperator::ADDITION, size_to_allocate, header_size);
    }

    std::vector<Shared<lang::Value>> parameters;
    parameters.emplace_back(size_to_allocate);
    Shared<lang::Value> opaque_memory_ptr = allocate_dynamic_->buildCall(parameters, context);

    if (is_buffer)
    {
        Shared<lang::Value> header_ptr =
            context.exec().computeCastedAddress(opaque_memory_ptr,
                                                context.ctx().getPointerType(context.ctx().getSizeType()));

        context.exec().performStoreToAddress(header_ptr, count);

        Shared<lang::Value> memory_ptr = context.exec().computeElementPointer(header_ptr,
                                                                              context.exec().getDiffN(1),
                                                                              Execution::IndexingMode::POINTER,
                                                                              std::nullopt);
        opaque_memory_ptr = context.exec().computeCastedAddress(memory_ptr, context.ctx().getOpaquePointerType());
    }

    Shared<lang::Value> result_ptr =
        context.exec().computeCastedAddress(opaque_memory_ptr, context.ctx().getPointerType(type));

    return result_ptr;
}
