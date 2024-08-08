#include "TypeAlias.h"

#include "lang/ApplicationVisitor.h"
#include "lang/scope/Scope.h"
#include "lang/type/Type.h"
#include "lang/utility/Identifier.h"
#include "validation/ValidationLogger.h"

lang::TypeAlias::TypeAlias(lang::Accessibility               accessibility,
                           lang::Identifier                  name,
                           lang::ResolvingHandle<lang::Type> actual,
                           lang::Location                    definition_location)
    : lang::TypeDefinition(name, definition_location)
    , lang::CustomType(accessibility)
    , actual_(actual)
{}

StateCount lang::TypeAlias::getStateCount() const
{
    return actual_->getStateCount();
}

lang::FixedWidthIntegerType const* lang::TypeAlias::isFixedWidthIntegerType() const
{
    return actual_->isFixedWidthIntegerType();
}

bool lang::TypeAlias::isSigned() const
{
    return actual_->isSigned();
}

bool lang::TypeAlias::isFixedWidthIntegerType(uint64_t bit_size, bool is_signed) const
{
    return actual_->isFixedWidthIntegerType(bit_size, is_signed);
}

bool lang::TypeAlias::isBooleanType() const
{
    return actual_->isBooleanType();
}

bool lang::TypeAlias::isCharType() const
{
    return actual_->isCharType();
}

lang::IntegerType const* lang::TypeAlias::isIntegerType() const
{
    return actual_->isIntegerType();
}

lang::FloatingPointType const* lang::TypeAlias::isFloatingPointType() const
{
    return actual_->isFloatingPointType();
}

bool lang::TypeAlias::isFloatingPointType(size_t precision) const
{
    return actual_->isFloatingPointType(precision);
}

bool lang::TypeAlias::isSizeType() const
{
    return actual_->isSizeType();
}

bool lang::TypeAlias::isDiffType() const
{
    return actual_->isDiffType();
}

bool lang::TypeAlias::isUnitType() const
{
    return actual_->isUnitType();
}

bool lang::TypeAlias::isPointerType() const
{
    return actual_->isPointerType();
}

bool lang::TypeAlias::isReferenceType() const
{
    return actual_->isReferenceType();
}

lang::ResolvingHandle<lang::Type> lang::TypeAlias::getElementType()
{
    return actual_->getElementType();
}

lang::Type const& lang::TypeAlias::getElementType() const
{
    return actual_->getElementType();
}

bool lang::TypeAlias::isUnsignedIntegerPointerType() const
{
    return actual_->isUnsignedIntegerPointerType();
}

bool lang::TypeAlias::isNullValueType() const
{
    return actual_->isNullValueType();
}

lang::AddressType const* lang::TypeAlias::isAddressType() const
{
    return actual_->isAddressType();
}

bool lang::TypeAlias::isBufferType() const
{
    return actual_->isBufferType();
}

bool lang::TypeAlias::isOpaquePointerType() const
{
    return actual_->isOpaquePointerType();
}

lang::StructType* lang::TypeAlias::isStructType()
{
    return actual_->isStructType();
}

lang::StructType const* lang::TypeAlias::isStructType() const
{
    return actual_->isStructType();
}

lang::VectorizableType const* lang::TypeAlias::isVectorizable() const
{
    return actual_->isVectorizable();
}

lang::VectorizableType* lang::TypeAlias::isVectorizable()
{
    return actual_->isVectorizable();
}

lang::VectorType const* lang::TypeAlias::isVectorType() const
{
    return actual_->isVectorType();
}

lang::VectorType* lang::TypeAlias::isVectorType()
{
    return actual_->isVectorType();
}

lang::ArrayType const* lang::TypeAlias::isArrayType() const
{
    return actual_->isArrayType();
}

lang::ArrayType* lang::TypeAlias::isArrayType()
{
    return actual_->isArrayType();
}

lang::ResolvingHandle<lang::Type> lang::TypeAlias::getActualType()
{
    if (!actually_actual_.hasValue())
    {
        lang::ResolvingHandle<lang::Type> current = actual_;

        while (current != current->getActualType()) { current = current->getActualType(); }

        actually_actual_ = current;
    }

    return actually_actual_.value();
}

lang::Type const& lang::TypeAlias::getActualType() const
{
    const_cast<TypeAlias*>(this)->getActualType();
    return actually_actual_.value();
}

bool lang::TypeAlias::validate(ValidationLogger&, lang::Location) const
{
    return true;
}

bool lang::TypeAlias::isSubscriptDefined() const
{
    return actual_->isSubscriptDefined();
}

lang::Type const& lang::TypeAlias::getSubscriptReturnType() const
{
    return actual_->getSubscriptReturnType();
}

bool lang::TypeAlias::validateSubscript(lang::Location    indexed_location,
                                        lang::Type const& index_type,
                                        lang::Location    index_location,
                                        ValidationLogger& validation_logger) const
{
    return actual_->validateSubscript(indexed_location, index_type, index_location, validation_logger);
}

Shared<lang::Value> lang::TypeAlias::execSubscript(Shared<lang::Value> indexed,
                                                   Shared<lang::Value> index,
                                                    Execution&          exec) const
{
    return actual_->execSubscript(indexed, index, exec);
}

bool lang::TypeAlias::isImplicitlyConvertibleTo(lang::Type const& other) const
{
    return actual_->isImplicitlyConvertibleTo(other);
}

bool lang::TypeAlias::validateImplicitConversion(lang::Type const& other,
                                                 lang::Location    location,
                                                 ValidationLogger& validation_logger) const
{
    return actual_->validateImplicitConversion(other, location, validation_logger);
}

Shared<lang::Value> lang::TypeAlias::execImplicitConversion(lang::Type const&   other,
                                                            Shared<lang::Value> value,
                                                             Execution&          exec) const
{
    return actual_->execImplicitConversion(other, value, exec);
}

bool lang::TypeAlias::isCastingPossibleTo(lang::Type const& other) const
{
    return actual_->isCastingPossibleTo(other);
}

bool lang::TypeAlias::validateCast(lang::Type const& other,
                                   lang::Location    location,
                                   ValidationLogger& validation_logger) const
{
    return actual_->validateCast(other, location, validation_logger);
}

Shared<lang::Value> lang::TypeAlias::execCast(lang::Type const& other, Shared<lang::Value> value,
                                               Execution&          exec) const
{
    return actual_->execCast(other, value, exec);
}

bool lang::TypeAlias::isOperatorDefined(lang::UnaryOperator op) const
{
    return actual_->isOperatorDefined(op);
}

lang::Type const& lang::TypeAlias::getOperatorResultType(lang::UnaryOperator op) const
{
    return actual_->getOperatorResultType(op);
}

bool lang::TypeAlias::validateOperator(lang::UnaryOperator op,
                                       lang::Location      location,
                                       ValidationLogger&   validation_logger) const
{
    return actual_->validateOperator(op, location, validation_logger);
}

Shared<lang::Value> lang::TypeAlias::execOperator(lang::UnaryOperator op,
                                                  Shared<lang::Value> value,
                                                   Execution&          exec) const
{
    return actual_->execOperator(op, value, exec);
}

bool lang::TypeAlias::isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const
{
    return actual_->isOperatorDefined(op, other);
}

lang::Type const& lang::TypeAlias::getOperatorResultType(lang::BinaryOperator op, lang::Type const& other) const
{
    return actual_->getOperatorResultType(op, other);
}

bool lang::TypeAlias::validateOperator(lang::BinaryOperator op,
                                       lang::Type const&    other,
                                       lang::Location       left_location,
                                       lang::Location       right_location,
                                       ValidationLogger&    validation_logger) const
{
    return actual_->validateOperator(op, other, left_location, right_location, validation_logger);
}

Shared<lang::Value> lang::TypeAlias::execOperator(lang::BinaryOperator op,
                                                  Shared<lang::Value>  left,
                                                   Shared<lang::Value>  right,
                                                   Execution&           exec) const
{
    return actual_->execOperator(op, left, right, exec);
}

bool lang::TypeAlias::hasMember(lang::Identifier const& name) const
{
    return actual_->hasMember(name);
}

lang::Member& lang::TypeAlias::getMember(lang::Identifier const& name)
{
    return actual_->getMember(name);
}

lang::Member const& lang::TypeAlias::getMember(lang::Identifier const& name) const
{
    return actual_->getMember(name);
}

bool lang::TypeAlias::validateMemberAccess(lang::Identifier const& name, ValidationLogger& validation_logger) const
{
    return actual_->validateMemberAccess(name, validation_logger);
}

Shared<lang::Value> lang::TypeAlias::execMemberAccess(Shared<lang::Value>     value,
                                                      lang::Identifier const& name,
                                                       Execution&              exec) const
{
    return actual_->execMemberAccess(value, name, exec);
}

bool lang::TypeAlias::definesIndirection() const
{
    return actual_->definesIndirection();
}

lang::Type const& lang::TypeAlias::getIndirectionType() const
{
    return actual_->getIndirectionType();
}

bool lang::TypeAlias::validateIndirection(lang::Location location, ValidationLogger& validation_logger) const
{
    return actual_->validateIndirection(location, validation_logger);
}

Shared<lang::Value> lang::TypeAlias::execIndirection(Shared<lang::Value> value, Execution& exec) const
{
    return actual_->execIndirection(value, exec);
}

void lang::TypeAlias::performDefaultInitializer(Shared<lang::Value> ptr,
                                                Shared<lang::Value> count,
                                                Execution&          exec) const
{
    actual_->performDefaultInitializer(ptr, count, exec);
}

void lang::TypeAlias::performCopyInitializer(Shared<lang::Value> destination,
                                             Shared<lang::Value> count,
                                             Execution&          exec) const
{
    actual_->performCopyInitializer(destination, count, exec);
}

void lang::TypeAlias::performFinalizer(Shared<lang::Value> ptr,
                                       Shared<lang::Value> count, Execution& exec) const
{
    actual_->performFinalizer(ptr, count, exec);
}

bool lang::TypeAlias::isTriviallyDefaultConstructible() const
{
    return actual_->getDefinition()->isTriviallyDefaultConstructible();
}

bool lang::TypeAlias::isTriviallyCopyConstructible() const
{
    return actual_->getDefinition()->isTriviallyCopyConstructible();
}

bool lang::TypeAlias::isTriviallyDestructible() const
{
    return actual_->getDefinition()->isTriviallyDestructible();
}

void lang::TypeAlias::createConstructors() {}

bool lang::TypeAlias::acceptOverloadRequest(std::vector<ResolvingHandle<lang::Type>>)
{
    return false;// Overloads are rerouted to the actual type by base class.
}

void lang::TypeAlias::execRequestedOverload(std::vector<std::reference_wrapper<lang::Type const>>,
                                            lang::PredefinedFunction&,
                                             Execution&) const
{
    assert(false);// Overloads are rerouted to the actual type by base class.
}

void lang::TypeAlias::registerDeclaration(Execution& exec) const
{
    registerExecutionType(exec);
}

void lang::TypeAlias::registerDefinition(Execution&) const {}

std::string lang::TypeAlias::createMangledName() const
{
    return getActualType().getMangledName();
}

void lang::TypeAlias::registerExecutionType(Execution& exec) const
{
    return exec.registerAlias(self(), getDefinitionLocation());
}

std::vector<lang::ResolvingHandle<lang::Type>> lang::TypeAlias::getDeclarationDependencies()
{
    std::vector<ResolvingHandle<Type>> dependencies;
    dependencies.emplace_back(actual_);
    return dependencies;
}

std::vector<lang::ResolvingHandle<lang::Type>> lang::TypeAlias::getDefinitionDependencies()
{
    return {};
}
