#include "SequenceType.h"

#include "compiler/CompileContext.h"
#include "lang/construct/value/Value.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/type/ReferenceType.h"
#include "lang/type/SizeType.h"
#include "lang/utility/Values.h"

lang::SequenceType::SequenceType(lang::Identifier                  name,
                                 lang::ResolvingHandle<lang::Type> element_type,
                                 std::optional<size_t>             size)
    : TypeDefinition(name)
    , element_type_(std::move(element_type))
    , element_reference_(lang::ReferenceType::get(element_type_))
    , size_(size)
{}

lang::ResolvingHandle<lang::Type> lang::SequenceType::getElementType() const
{
    return element_type_;
}

StateCount lang::SequenceType::getStateCount() const
{
    assert(size_.has_value() && "State count cannot be determined for sequence types without a size.");

    StateCount state_count = element_type_->getStateCount();

    if (auto* size = std::get_if<size_t>(&state_count)) { *size *= size_.value(); }

    return state_count;
}

bool lang::SequenceType::isSubscriptDefined()
{
    return true;
}

lang::ResolvingHandle<lang::Type> lang::SequenceType::getSubscriptReturnType()
{
    return element_reference_;
}

bool lang::SequenceType::validateSubscript(lang::Location,
                                           lang::ResolvingHandle<lang::Type> index_type,
                                           lang::Location                    index_location,
                                           ValidationLogger&                 validation_logger) const
{
    return lang::Type::checkMismatch(lang::SizeType::getSize(), index_type, index_location, validation_logger);
}

std::shared_ptr<lang::Value> lang::SequenceType::buildSubscript(std::shared_ptr<Value> indexed,
                                                                std::shared_ptr<Value> index,
                                                                CompileContext&        context)
{
    index = lang::Type::makeMatching(lang::SizeType::getSize(), index, context);

    llvm::Value* element_ptr  = buildGetElementPointer(indexed, index, context);
    llvm::Value* native_value = lang::Values::contentToNative(element_reference_, element_ptr, context);

    return std::make_shared<lang::WrappedNativeValue>(getSubscriptReturnType(), native_value);
}

llvm::Value* lang::SequenceType::buildGetElementPointer(const std::shared_ptr<lang::Value>& indexed,
                                                        const std::shared_ptr<lang::Value>& index,
                                                        CompileContext&                     context)
{
    index->buildContentValue(context);

    llvm::Value* zero         = llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context.llvmContext()), 0);
    llvm::Value* native_index = index->getContentValue();

    llvm::Value* sequence_ptr = getIndexingPointer(indexed, context);

    if (size_.has_value())// Check if index is in bounds.
    {
        llvm::Value* native_size =
            llvm::ConstantInt::get(lang::SizeType::getSize()->getContentType(*context.llvmContext()), size_.value());
        llvm::Value* in_bounds =
            context.ir()->CreateICmpULT(native_index, native_size, native_index->getName() + ".icmp");

        in_bounds->setName("..inbounds");

        // todo: use in_bounds bool to throw exception
    }

    llvm::Value* element_ptr = context.ir()->CreateGEP(getIndexedType(context),
                                                       sequence_ptr,
                                                       getNativeIndices(zero, native_index),
                                                       sequence_ptr->getName() + ".gep");
    return element_ptr;
}

llvm::Value* lang::SequenceType::buildGetElementPointer(llvm::Value* indexed, uint64_t index, CompileContext& context)
{
    llvm::Value* zero         = llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context.llvmContext()), 0);
    llvm::Value* native_index = llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context.llvmContext()), index);

    return context.ir()->CreateGEP(getContentType(*context.llvmContext()),
                                   indexed,
                                   getNativeIndices(zero, native_index),
                                   indexed->getName() + ".gep");
}

llvm::Type* lang::SequenceType::getIndexedType(CompileContext& context) const
{
    return getContentType(*context.llvmContext());
}

llvm::Value* lang::SequenceType::getIndexingPointer(std::shared_ptr<Value> indexed, CompileContext& context)
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
    if (size_.has_value())
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
    if (size_.has_value())
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
    if (size_.has_value())
    {
        for (uint64_t index = 0; index < size_.value(); index++)
        {
            llvm::Value* element_ptr = buildGetElementPointer(ptr, index, context);
            element_type_->buildFinalizer(element_ptr, context);
        }
    }
}

std::vector<lang::TypeDefinition*> lang::SequenceType::getDependencies() const
{
    std::vector<lang::TypeDefinition*> dependencies;

    if (element_type_->getDefinition()) dependencies.push_back(element_type_->getDefinition());

    return dependencies;
}
