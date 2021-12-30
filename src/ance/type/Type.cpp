#include "Type.h"

#include <utility>

#include "ance/construct/value/RoughlyCastedValue.h"
#include "ance/type/ReferenceType.h"
#include "validation/ValidationLogger.h"

ance::Type::Type(std::string name) : name_(std::move(name)) {}

ance::Type::Type(std::unique_ptr<ance::TypeDefinition> definition)
    : name_(definition->getName())
    , definition_(std::move(definition))
{
    definition_->setType(this);
}

const std::string& ance::Type::getName() const
{
    if (isDefined()) { return definition_->getName(); }
    else
    {
        return name_;
    }
}

std::string ance::Type::getAnnotatedName()
{
    std::string name = "'" + getName() + "'";

    if (getActualType() != self()) { name += " (aka '" + getActualType()->getName() + "')"; }

    return name;
}

const std::string& ance::Type::getMangledName()
{
    assert(isDefined());
    return definition_->getMangledName();
}

bool ance::Type::isDefined() const
{
    return (definition_ != nullptr);
}

void ance::Type::define(std::unique_ptr<ance::TypeDefinition> definition)
{
    assert(!isDefined());
    definition_ = std::move(definition);
    definition_->setType(this);
}

bool ance::Type::isCustom() const
{
    assert(isDefined());
    return definition_->isCustom();
}

bool ance::Type::isIntegerType() const
{
    assert(isDefined());
    return definition_->isIntegerType();
}

bool ance::Type::isIntegerType(uint64_t bit_size, bool is_signed) const
{
    assert(isDefined());
    return definition_->isIntegerType(bit_size, is_signed);
}

bool ance::Type::isBooleanType() const
{
    assert(isDefined());
    return definition_->isBooleanType();
}

bool ance::Type::isFloatingPointType() const
{
    assert(isDefined());
    return definition_->isFloatingPointType();
}

bool ance::Type::isFloatingPointType(size_t precision) const
{
    assert(isDefined());
    return definition_->isFloatingPointType(precision);
}

bool ance::Type::isSizeType() const
{
    assert(isDefined());
    return definition_->isSizeType();
}

bool ance::Type::isDiffType() const
{
    assert(isDefined());
    return definition_->isDiffType();
}

bool ance::Type::isVoidType() const
{
    assert(isDefined());
    return definition_->isVoidType();
}

bool ance::Type::isPointerType() const
{
    assert(isDefined());
    return definition_->isPointerType();
}

bool ance::Type::isReferenceType() const
{
    assert(isDefined());
    return definition_->isReferenceType();
}

ance::ResolvingHandle<ance::Type> ance::Type::getElementType() const
{
    assert(isDefined());
    return definition_->getElementType();
}

ance::ResolvingHandle<ance::Type> ance::Type::getActualType()
{
    assert(isDefined());
    return definition_->getActualType();
}
ance::ResolvingHandle<ance::Type> ance::Type::getOriginalType()
{
    assert(isDefined());
    return definition_->getOriginalType();
}

void ance::Type::setContainingScope(ance::Scope* scope)
{
    assert(isDefined());
    definition_->setContainingScope(scope);
}

ance::Scope* ance::Type::getContainingScope() const
{
    assert(isDefined());
    return definition_->scope();
}

llvm::Constant* ance::Type::getDefaultContent(llvm::LLVMContext& c)
{
    assert(isDefined());
    return definition_->getDefaultContent(c);
}

llvm::Type* ance::Type::getNativeType(llvm::LLVMContext& c)
{
    assert(isDefined());
    return definition_->getNativeType(c);
}

llvm::Type* ance::Type::getContentType(llvm::LLVMContext& c)
{
    assert(isDefined());
    return definition_->getContentType(c);
}

llvm::DIType* ance::Type::getDebugType(CompileContext* context)
{
    assert(isDefined());
    return definition_->getDebugType(context);
}

llvm::TypeSize ance::Type::getNativeSize(llvm::Module* m)
{
    assert(isDefined());
    return definition_->getNativeSize(m);
}

llvm::TypeSize ance::Type::getContentSize(llvm::Module* m)
{
    assert(isDefined());
    return definition_->getContentSize(m);
}

bool ance::Type::isSubscriptDefined()
{
    assert(isDefined());
    return definition_->isSubscriptDefined();
}

ance::ResolvingHandle<ance::Type> ance::Type::getSubscriptReturnType()
{
    assert(isDefined());
    return definition_->getSubscriptReturnType();
}

bool ance::Type::isOperatorDefined(BinaryOperator op, ance::ResolvingHandle<ance::Type> other)
{
    assert(isDefined());
    return definition_->isOperatorDefined(op, other);
}
ance::ResolvingHandle<ance::Type> ance::Type::getOperatorResultType(BinaryOperator                    op,
                                                                    ance::ResolvingHandle<ance::Type> other)
{
    assert(isDefined());
    return definition_->getOperatorResultType(op, other);
}

bool ance::Type::validateDefinition(ValidationLogger& validation_logger)
{
    assert(isDefined());
    if (definition_->isCustom())
        return definition_->validateDefinition(validation_logger);
    else
        return true;
}

bool ance::Type::validate(ValidationLogger& validation_logger, ance::Location location)
{
    assert(isDefined());
    return definition_->validate(validation_logger, location);
}

bool ance::Type::validateSubscript(ance::Location                    indexed_location,
                                   ance::ResolvingHandle<ance::Type> index_type,
                                   ance::Location                    index_location,
                                   ValidationLogger&                 validation_logger)
{
    assert(isDefined());
    return definition_->validateSubscript(indexed_location, std::move(index_type), index_location, validation_logger);
}

bool ance::Type::validateOperator(BinaryOperator                    op,
                                  ance::ResolvingHandle<ance::Type> other,
                                  ance::Location                    left_location,
                                  ance::Location                    right_location,
                                  ValidationLogger&                 validation_logger)
{
    assert(isDefined());
    return definition_->validateOperator(op, std::move(other), left_location, right_location, validation_logger);
}

std::shared_ptr<ance::Value> ance::Type::buildSubscript(std::shared_ptr<Value> indexed,
                                                        std::shared_ptr<Value> index,
                                                        CompileContext*        context)
{
    assert(isDefined());
    return definition_->buildSubscript(std::move(indexed), std::move(index), context);
}

std::shared_ptr<ance::Value> ance::Type::buildOperator(BinaryOperator         op,
                                                       std::shared_ptr<Value> left,
                                                       std::shared_ptr<Value> right,
                                                       CompileContext*        context)
{
    assert(isDefined());
    return definition_->buildOperator(op, std::move(left), std::move(right), context);
}

ance::TypeDefinition* ance::Type::getDefinition()
{
    return definition_.get();
}

bool ance::Type::isMatching(ance::ResolvingHandle<ance::Type> expected, ance::ResolvingHandle<ance::Type> actual)
{
    if (areSame(expected, actual)) return true;

    if (actual->isReferenceType())
    {
        ance::ResolvingHandle<ance::Type> referenced_type = actual->getElementType();
        if (areSame(referenced_type, expected)) return true;
    }

    return false;
}

bool ance::Type::checkMismatch(ance::ResolvingHandle<ance::Type> expected,
                               ance::ResolvingHandle<ance::Type> actual,
                               ance::Location                    location,
                               ValidationLogger&                 validation_logger)
{
    bool matching = isMatching(expected, actual);

    if (!matching)
    {
        validation_logger.logError("Cannot implicitly convert " + actual->getAnnotatedName() + " to "
                                       + expected->getAnnotatedName(),
                                   location);
    }

    return matching;
}

std::shared_ptr<ance::Value> ance::Type::makeMatching(ance::ResolvingHandle<ance::Type> expected,
                                                      std::shared_ptr<ance::Value>      value,
                                                      CompileContext*                   context)
{
    if (areSame(expected, value->type())) return makeActual(value);

    if (value->type()->isReferenceType())
    {
        auto reference_type                     = dynamic_cast<ance::ReferenceType*>(value->type()->definition_.get());
        std::shared_ptr<ance::Value> referenced = reference_type->getReferenced(value, context);

        return makeActual(referenced);
    }

    assert(false && "Cannot make the value matching, was mismatch checked before?");
    return nullptr;
}

bool ance::Type::areSame(ance::ResolvingHandle<ance::Type> lhs, ance::ResolvingHandle<ance::Type> rhs)
{
    return lhs->getActualType() == rhs->getActualType();
}

std::shared_ptr<ance::Value> ance::Type::makeActual(std::shared_ptr<ance::Value> value)
{
    ance::ResolvingHandle<ance::Type> actual_type = value->type()->getActualType();
    if (actual_type == value->type()) return value;

    return std::make_shared<ance::RoughlyCastedValue>(actual_type, value);
}
