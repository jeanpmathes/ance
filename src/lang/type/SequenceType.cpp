#include "SequenceType.h"

#include <utility>

#include "compiler/CompileContext.h"
#include "compiler/Runtime.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/value/Value.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/SizeType.h"

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

Optional<uint64_t> lang::SequenceType::getSize() const
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
    return buildSubscript(indexed, index, true, context);
}

Shared<lang::Value> lang::SequenceType::buildSubscriptInBounds(Shared<lang::Value> indexed,
                                                               Shared<lang::Value> index,
                                                               CompileContext&     context)
{
    return buildSubscript(indexed, index, false, context);
}

Shared<lang::Value> lang::SequenceType::buildSubscript(Shared<lang::Value> indexed,
                                                       Shared<lang::Value> index,
                                                       bool                check_bounds,
                                                       CompileContext&     context)
{
    if (getSubscriptReturnType()->getStateCount().isUnit())
        return context.exec().getDefaultValue(getSubscriptReturnType());

    Optional<uint64_t> bounds = check_bounds ? size_ : std::nullopt;

    index = lang::Type::makeMatching(scope()->context().getSizeType(), index, context);
    Shared<lang::Value> index_as_diff = context.exec().computeConversionOnI(index, context.ctx().getDiffType());

    Shared<lang::Value> sequence_ptr =
        getIndexingMode() == Execution::IndexingMode::POINTER ? indexed : context.exec().computeAddressOf(indexed);
    Shared<lang::Value> element_ptr =
        context.exec().computeElementPointer(sequence_ptr, index_as_diff, getIndexingMode(), bounds);

    return context.exec().computeReferenceFromPointer(element_ptr);
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

void lang::SequenceType::performSingleDefaultInitializerDefinition(Shared<lang::Value> ptr, CompileContext& context)
{
    if (size_.hasValue())
    {
        for (uint64_t index = 0; index < size_.value(); index++)
        {
            Shared<lang::Value> index_value = context.exec().getDiffValue(static_cast<std::ptrdiff_t>(index));
            Shared<lang::Value> element_ptr =
                context.exec().computeElementPointer(ptr, index_value, getIndexingMode(), std::nullopt);

            element_type_->performDefaultInitializer(element_ptr, context);
        }
    }
}

void lang::SequenceType::performSingleCopyInitializerDefinition(Shared<lang::Value> dts_ptr,
                                                                Shared<lang::Value> src_ptr,
                                                                CompileContext& context)
{
    if (size_.hasValue())
    {
        for (uint64_t index = 0; index < size_.value(); index++)
        {
            Shared<lang::Value> index_value = context.exec().getDiffValue(static_cast<std::ptrdiff_t>(index));

            Shared<lang::Value> dst_element_ptr =
                context.exec().computeElementPointer(dts_ptr, index_value, getIndexingMode(), std::nullopt);
            Shared<lang::Value> src_element_ptr =
                context.exec().computeElementPointer(src_ptr, index_value, getIndexingMode(), std::nullopt);

            element_type_->performCopyInitializer(dst_element_ptr, src_element_ptr, context);
        }
    }
}

void lang::SequenceType::buildSingleDefaultFinalizerDefinition(Shared<lang::Value> ptr, CompileContext& context)
{
    if (size_.hasValue())
    {
        for (uint64_t index = 0; index < size_.value(); index++)
        {
            Shared<lang::Value> index_value = context.exec().getDiffValue(static_cast<std::ptrdiff_t>(index));
            Shared<lang::Value> element_ptr =
                context.exec().computeElementPointer(ptr, index_value, getIndexingMode(), std::nullopt);

            element_type_->performFinalizer(element_ptr, context);
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

    Shared<lang::Value> sequence_ptr = context.exec().performStackAllocation(self());

    for (uint64_t index = 0; index < size_.value(); index++)
    {
        Shared<lang::Value> index_value = context.exec().getDiffValue(static_cast<std::ptrdiff_t>(index));
        Shared<lang::Value> element_ptr =
            context.exec().computeElementPointer(sequence_ptr, index_value, getIndexingMode(), std::nullopt);

        context.exec().performStoreToAddress(element_ptr, values[index]);
    }

    return context.exec().performLoadFromAddress(sequence_ptr);
}
