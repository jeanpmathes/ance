#include "Type.h"

#include <utility>

#include "ance/construct/value/Value.h"
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

std::shared_ptr<ance::Value> ance::Type::buildSubscript(std::shared_ptr<Value> indexed,
                                                        std::shared_ptr<Value> index,
                                                        CompileContext*        context)
{
    assert(isDefined());
    return definition_->buildSubscript(std::move(indexed), std::move(index), context);
}

bool ance::Type::isImplicitlyConvertibleTo(ance::ResolvingHandle<ance::Type> target)
{
    assert(isDefined());
    return definition_->isImplicitlyConvertibleTo(target);
}

std::shared_ptr<ance::Value> ance::Type::convertImplicitlyTo(ance::ResolvingHandle<ance::Type> target,
                                                             std::shared_ptr<Value>            value,
                                                             CompileContext*                   context)
{
    assert(isDefined());
    return definition_->convertImplicitlyTo(target, value, context);
}

bool ance::Type::isImplicitlyConvertibleFrom(ance::ResolvingHandle<ance::Type> source)
{
    assert(isDefined());
    return definition_->isImplicitlyConvertibleFrom(source);
}

std::shared_ptr<ance::Value> ance::Type::convertImplicitlyFrom(std::shared_ptr<Value>            value,
                                                               ance::ResolvingHandle<ance::Type> self,
                                                               CompileContext*                   context)
{
    assert(isDefined());
    return definition_->convertImplicitlyFrom(value, self, context);
}

ance::TypeDefinition* ance::Type::getDefinition()
{
    return definition_.get();
}

bool ance::Type::checkMismatch(ance::ResolvingHandle<ance::Type> expected,
                               ance::ResolvingHandle<ance::Type> actual,
                               ance::Location                    location,
                               ValidationLogger&                 validation_logger)
{
    if (expected != actual)
    {
        bool convertible = false;

        if (!actual->isReferenceType())
        {
            convertible |= actual->isImplicitlyConvertibleTo(expected);
            convertible |= expected->isImplicitlyConvertibleFrom(actual);
        }
        else
        {
            ance::ResolvingHandle<ance::Type> referenced_type = actual->getElementType();

            convertible = referenced_type == expected;

            convertible |= referenced_type->isImplicitlyConvertibleTo(expected);
            convertible |= expected->isImplicitlyConvertibleFrom(referenced_type);
        }

        if (convertible) return true;

        std::string actual_name   = actual->getName();
        std::string expected_name = expected->getName();

        validation_logger.logError("Cannot implicitly convert " + getAnnotatedName(actual) + " to "
                                       + getAnnotatedName(expected),
                                   location);

        return false;
    }

    return true;
}

std::shared_ptr<ance::Value> ance::Type::makeMatching(ance::ResolvingHandle<ance::Type> expected,
                                                      std::shared_ptr<ance::Value>      value,
                                                      CompileContext*                   context)
{
    if (value->type() == expected) return value;

    if (!value->type()->isReferenceType())
    {
        if (value->type()->isImplicitlyConvertibleTo(expected))
        {
            return value->type()->convertImplicitlyTo(expected, value, context);
        }

        if (expected->isImplicitlyConvertibleFrom(value->type()))
        {
            return expected->convertImplicitlyFrom(value, expected, context);
        }
    }
    else
    {
        auto reference_type                     = dynamic_cast<ance::ReferenceType*>(value->type()->definition_.get());
        std::shared_ptr<ance::Value> referenced = reference_type->getReferenced(value, context);

        if (referenced->type() == expected) return referenced;

        if (referenced->type()->isImplicitlyConvertibleTo(expected))
        {
            return referenced->type()->convertImplicitlyTo(expected, referenced, context);
        }

        if (expected->isImplicitlyConvertibleFrom(referenced->type()))
        {
            return expected->convertImplicitlyFrom(referenced, expected, context);
        }
    }

    assert(false && "Cannot make the value matching, was mismatch checked before?");
    return nullptr;
}

std::string ance::Type::getAnnotatedName(ance::ResolvingHandle<ance::Type> type)
{
    std::string name = "'" + type->getName() + "'";

    if (type->getActualType() != type) { name += " (aka '" + type->getActualType()->getName() + "')"; }

    return name;
}
