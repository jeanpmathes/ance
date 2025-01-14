#include "SequenceType.h"

#include <utility>

#include "compiler/Runtime.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Value.h"
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

lang::Type const& lang::SequenceType::getSubscriptReturnType() const
{
    return scope().context().getReferenceType(*element_type_);
}

bool lang::SequenceType::validateSubscript(lang::Location,
                                           lang::Type const& index_type,
                                           lang::Location    index_location,
                                           ValidationLogger& validation_logger) const
{
    return lang::Type::checkMismatch(scope().context().getSizeType(), index_type, index_location, validation_logger);
}

Shared<lang::Value> lang::SequenceType::execSubscript(Shared<lang::Value> indexed,
                                                      Shared<lang::Value> index,
                                                       Execution&          exec) const
{
    return execSubscript(indexed, index, true, exec);
}

Shared<lang::Value> lang::SequenceType::execSubscriptInBounds(Shared<lang::Value> indexed,
                                                              Shared<lang::Value> index,
                                                               Execution&          exec) const
{
    return execSubscript(indexed, index, false, exec);
}

Shared<lang::Value> lang::SequenceType::execSubscript(Shared<lang::Value> indexed,
                                                      Shared<lang::Value> index,
                                                       bool                check_bounds,
                                                       Execution&          exec) const
{
    if (getSubscriptReturnType().getStateCount().isUnit()) return exec.getDefault(getSubscriptReturnType());

    Optional<uint64_t> bounds = check_bounds ? size_ : std::nullopt;

    index                             = lang::Type::makeMatching(exec.ctx().getSizeType(), index, exec);
    Shared<lang::Value> index_as_diff = exec.computeConversionOnI(index, exec.ctx().getDiffType());

    Shared<lang::Value> sequence_ptr =
        getIndexingMode() == Execution::IndexingMode::POINTER ? indexed : exec.computeAddressOf(indexed);
    Shared<lang::Value> element_ptr =
        exec.computeElementPointer(sequence_ptr, index_as_diff, getIndexingMode(), bounds);

    return exec.computeReferenceFromPointer(element_ptr);
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

void lang::SequenceType::performSingleDefaultInitializerDefinition(Shared<lang::Value> ptr, Execution& exec) const
{
    if (size_.hasValue())
    {
        for (uint64_t index = 0; index < size_.value(); index++)
        {
            Shared<lang::Value> index_value = exec.getDiffN(static_cast<std::ptrdiff_t>(index));
            Shared<lang::Value> element_ptr =
                exec.computeElementPointer(ptr, index_value, getIndexingMode(), std::nullopt);

            element_type_->performDefaultInitializer(element_ptr, exec);
        }
    }
}

void lang::SequenceType::performSingleCopyInitializerDefinition(Shared<lang::Value> dts_ptr,
                                                                Shared<lang::Value> src_ptr,
                                                                Execution&          exec) const
{
    if (size_.hasValue())
    {
        for (uint64_t index = 0; index < size_.value(); index++)
        {
            Shared<lang::Value> index_value = exec.getDiffN(static_cast<std::ptrdiff_t>(index));

            Shared<lang::Value> dst_element_ptr =
                exec.computeElementPointer(dts_ptr, index_value, getIndexingMode(), std::nullopt);
            Shared<lang::Value> src_element_ptr =
                exec.computeElementPointer(src_ptr, index_value, getIndexingMode(), std::nullopt);

            element_type_->performCopyInitializer(dst_element_ptr, src_element_ptr, exec);
        }
    }
}

void lang::SequenceType::performSingleDefaultFinalizerDefinition(Shared<lang::Value> ptr, Execution& exec) const
{
    if (size_.hasValue())
    {
        for (uint64_t index = 0; index < size_.value(); index++)
        {
            Shared<lang::Value> index_value = exec.getDiffN(static_cast<std::ptrdiff_t>(index));
            Shared<lang::Value> element_ptr =
                exec.computeElementPointer(ptr, index_value, getIndexingMode(), std::nullopt);

            element_type_->performFinalizer(element_ptr, exec);
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

Shared<lang::Value> lang::SequenceType::createValue(std::vector<Shared<lang::Value>>& values, Execution& exec) const
{
    assert(size_.hasValue());
    assert(values.size() == size_.value());

    Shared<lang::Value> sequence_ptr = exec.performStackAllocation(self());

    for (uint64_t index = 0; index < size_.value(); index++)
    {
        Shared<lang::Value> index_value = exec.getDiffN(static_cast<std::ptrdiff_t>(index));
        Shared<lang::Value> element_ptr =
            exec.computeElementPointer(sequence_ptr, index_value, getIndexingMode(), std::nullopt);

        exec.performStoreToAddress(element_ptr, values[index]);
    }

    return exec.performLoadFromAddress(sequence_ptr);
}
