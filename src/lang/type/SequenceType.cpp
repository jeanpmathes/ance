#include "SequenceType.h"

#include <utility>

#include "compiler/CompileContext.h"
#include "compiler/Runtime.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/value/Value.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/ReferenceType.h"
#include "lang/type/SizeType.h"
#include "lang/utility/Values.h"

lang::SequenceType::SequenceType(lang::ResolvingHandle<lang::Type> element_type, Optional<uint64_t> size)
    : element_type_(std::move(element_type))
    , size_(std::move(size))
{}

lang::ResolvingHandle<lang::Type> lang::SequenceType::getElementType()
{
    return element_type_;
}

lang::Type const& lang::SequenceType::getElementType() const
{
    return element_type_;
}

StateCount lang::SequenceType::getStateCount() const
{
    assert(size_.hasValue() && "State count cannot be determined for sequence types without a size.");

    if (size_.value() == 0)// To prevent state count zero.
        return StateCount::unit();

    return element_type_->getStateCount() * size_.value();
}

Optional<uint64_t> lang::SequenceType::getSize()
{
    return size_;
}

bool lang::SequenceType::isSubscriptDefined() const
{
    return true;
}

lang::ResolvingHandle<lang::Type> lang::SequenceType::getSubscriptReturnType()
{
    return scope()->context().getReferenceType(element_type_);
}

bool lang::SequenceType::validateSubscript(lang::Location,
                                           lang::Type const& index_type,
                                           lang::Location    index_location,
                                           ValidationLogger& validation_logger) const
{
    return lang::Type::checkMismatch(scope()->context().getSizeType(), index_type, index_location, validation_logger);
}

Shared<lang::Value> lang::SequenceType::buildSubscript(Shared<Value>   indexed,
                                                       Shared<Value>   index,
                                                       CompileContext& context)
{
    if (getSubscriptReturnType()->getStateCount().isUnit())
        return lang::WrappedNativeValue::makeDefault(getSubscriptReturnType(), context);

    index = lang::Type::makeMatching(scope()->context().getSizeType(), index, context);

    llvm::Value* element_ptr = buildGetElementPointer(indexed, index, context);
    llvm::Value* native_value =
        lang::values::contentToNative(context.types().getReferenceType(element_type_), element_ptr, context);

    return makeShared<lang::WrappedNativeValue>(getSubscriptReturnType(), native_value);
}

llvm::Value* lang::SequenceType::buildGetElementPointer(Shared<Value>   indexed,
                                                        Shared<Value>   index,
                                                        CompileContext& context)
{
    if (getElementType()->getStateCount().isUnit())
        return llvm::Constant::getNullValue(llvm::PointerType::get(getIndexedType(context), 0));

    index->buildContentValue(context);

    llvm::Value* zero         = llvm::ConstantInt::get(llvm::Type::getInt64Ty(context.llvmContext()), 0);
    llvm::Value* native_index = index->getContentValue();

    llvm::Value* sequence_ptr = getIndexingPointer(indexed, context);

    if (size_.hasValue() && scope()->context().isContainingRuntime())// Check if index is in bounds.
    {
        llvm::Value* native_size =
            llvm::ConstantInt::get(context.types().getSizeType()->getContentType(context.llvmContext()), size_.value());
        llvm::Value* in_bounds =
            context.ir().CreateICmpULT(native_index, native_size, native_index->getName() + ".icmp");

        llvm::Value* in_bounds_ptr =
            lang::values::contentToNative(context.types().getBooleanType(), in_bounds, context);
        Shared<lang::Value> truth =
            makeShared<lang::WrappedNativeValue>(context.types().getBooleanType(), in_bounds_ptr);

        context.runtime().buildAssert(truth, "Index out of bounds at " + context.getLocationString(), context);
    }

    llvm::Value* element_ptr = context.ir().CreateGEP(getIndexedType(context),
                                                      sequence_ptr,
                                                      getNativeIndices(zero, native_index),
                                                      sequence_ptr->getName() + ".gep");
    return element_ptr;
}

llvm::Value* lang::SequenceType::buildGetElementPointer(llvm::Value* indexed, uint64_t index, CompileContext& context)
{
    if (getElementType()->getStateCount().isUnit())
        return llvm::Constant::getNullValue(llvm::PointerType::get(getContentType(context.llvmContext()), 0));

    llvm::Value* zero         = llvm::ConstantInt::get(llvm::Type::getInt64Ty(context.llvmContext()), 0);
    llvm::Value* native_index = llvm::ConstantInt::get(llvm::Type::getInt64Ty(context.llvmContext()), index);

    return context.ir().CreateGEP(getContentType(context.llvmContext()),
                                  indexed,
                                  getNativeIndices(zero, native_index),
                                  indexed->getName() + ".gep");
}

llvm::Type* lang::SequenceType::getIndexedType(CompileContext& context) const
{
    return getContentType(context.llvmContext());
}

llvm::Value* lang::SequenceType::getIndexingPointer(Shared<Value> indexed, CompileContext& context)
{
    indexed->buildNativeValue(context);
    return indexed->getNativeValue();
}

llvm::SmallVector<llvm::Value*> lang::SequenceType::getNativeIndices(llvm::Value* zero, llvm::Value* index)
{
    return {zero, index};
}

bool lang::SequenceType::isTriviallyDefaultConstructible() const
{
    return element_type_->getDefinition()->isTriviallyDefaultConstructible();
}

bool lang::SequenceType::isTriviallyCopyConstructible() const
{
    return element_type_->getDefinition()->isTriviallyCopyConstructible();
}

bool lang::SequenceType::isTriviallyDestructible() const
{
    return element_type_->getDefinition()->isTriviallyDestructible();
}

void lang::SequenceType::buildSingleDefaultInitializerDefinition(llvm::Value* ptr, CompileContext& context)
{
    if (size_.hasValue())
    {
        for (uint64_t index = 0; index < size_.value(); index++)
        {
            llvm::Value* element_ptr = buildGetElementPointer(ptr, index, context);
            element_type_->buildDefaultInitializer(element_ptr, context);
        }
    }
}

void lang::SequenceType::buildSingleCopyInitializerDefinition(llvm::Value*    dts_ptr,
                                                              llvm::Value*    src_ptr,
                                                              CompileContext& context)
{
    if (size_.hasValue())
    {
        for (uint64_t index = 0; index < size_.value(); index++)
        {
            llvm::Value* dst_element_ptr = buildGetElementPointer(dts_ptr, index, context);
            llvm::Value* src_element_ptr = buildGetElementPointer(src_ptr, index, context);

            element_type_->buildCopyInitializer(dst_element_ptr, src_element_ptr, context);
        }
    }
}

void lang::SequenceType::buildSingleDefaultFinalizerDefinition(llvm::Value* ptr, CompileContext& context)
{
    if (size_.hasValue())
    {
        for (uint64_t index = 0; index < size_.value(); index++)
        {
            llvm::Value* element_ptr = buildGetElementPointer(ptr, index, context);

            element_type_->buildFinalizer(element_ptr, context);
        }
    }
}

std::vector<lang::ResolvingHandle<lang::Type>> lang::SequenceType::getDeclarationDependencies()
{
    std::vector<ResolvingHandle<Type>> dependencies;
    dependencies.emplace_back(element_type_);
    return dependencies;
}

std::vector<lang::ResolvingHandle<lang::Type>> lang::SequenceType::getDefinitionDependencies()
{
    return {};
}

Shared<lang::Value> lang::SequenceType::createValue(std::vector<Shared<lang::Value>> values, CompileContext& context)
{
    assert(size_.hasValue());
    assert(values.size() == size_.value());

    llvm::Value* sequence_ptr = context.ir().CreateAlloca(getContentType(context.llvmContext()), nullptr, "alloca");

    for (uint64_t index = 0; index < size_.value(); index++)
    {
        values[index]->buildContentValue(context);

        llvm::Value* element_ptr = buildGetElementPointer(sequence_ptr, index, context);

        context.ir().CreateStore(values[index]->getContentValue(), element_ptr);
    }

    return makeShared<lang::WrappedNativeValue>(self(), sequence_ptr);
}
