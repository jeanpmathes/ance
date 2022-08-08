#include "Type.h"

#include <utility>

#include "lang/construct/Function.h"
#include "lang/construct/value/RoughlyCastedValue.h"
#include "lang/type/ReferenceType.h"
#include "lang/utility/Identifier.h"
#include "validation/ValidationLogger.h"

lang::Type::Type(Identifier name) : name_(std::move(name)) {}

lang::Type::Type(std::unique_ptr<lang::TypeDefinition> definition)
    : name_(definition->name())
    , definition_(std::move(definition))
{
    definition_->setType(this);
}

const lang::Identifier& lang::Type::name() const
{
    if (isDefined()) { return definition_->name(); }
    else {
        return name_;
    }
}

std::string lang::Type::getAnnotatedName(bool is_safe) const
{
    std::string name = "'" + this->name() + "'";

    is_safe &= isDefined();

    if (is_safe && getActualType() != self()) { name += " (aka '" + getActualType()->name() + "')"; }

    return name;
}

const std::string& lang::Type::getMangledName() const
{
    assert(isDefined());
    return definition_->getMangledName();
}

bool lang::Type::isDefined() const
{
    return (definition_ != nullptr);
}

void lang::Type::define(std::unique_ptr<lang::TypeDefinition> definition)
{
    assert(!isDefined());
    definition_ = std::move(definition);
    definition_->setType(this);
}

StateCount lang::Type::getStateCount() const
{
    assert(isDefined());
    return definition_->getStateCount();
}

bool lang::Type::isCustom() const
{
    assert(isDefined());
    return definition_->isCustom();
}

bool lang::Type::isIntegerType() const
{
    assert(isDefined());
    return definition_->isIntegerType();
}

bool lang::Type::isIntegerType(uint64_t bit_size, bool is_signed) const
{
    assert(isDefined());
    return definition_->isIntegerType(bit_size, is_signed);
}

bool lang::Type::isSigned() const
{
    assert(isDefined());
    return definition_->isSigned();
}

bool lang::Type::isBooleanType() const
{
    assert(isDefined());
    return definition_->isBooleanType();
}

bool lang::Type::isFloatingPointType() const
{
    assert(isDefined());
    return definition_->isFloatingPointType();
}

bool lang::Type::isFloatingPointType(size_t precision) const
{
    assert(isDefined());
    return definition_->isFloatingPointType(precision);
}

bool lang::Type::isSizeType() const
{
    assert(isDefined());
    return definition_->isSizeType();
}

bool lang::Type::isDiffType() const
{
    assert(isDefined());
    return definition_->isDiffType();
}

bool lang::Type::isVoidType() const
{
    assert(isDefined());
    return definition_->isVoidType();
}

bool lang::Type::isPointerType() const
{
    assert(isDefined());
    return definition_->isPointerType();
}

bool lang::Type::isReferenceType() const
{
    assert(isDefined());
    return definition_->isReferenceType();
}

lang::ResolvingHandle<lang::Type> lang::Type::getElementType() const
{
    assert(isDefined());
    return definition_->getElementType();
}

lang::ResolvingHandle<lang::Type> lang::Type::getActualType() const
{
    assert(isDefined());
    return definition_->getActualType();
}

lang::ResolvingHandle<lang::Type> lang::Type::getOriginalType() const
{
    assert(isDefined());
    return definition_->getOriginalType();
}

lang::AccessModifier lang::Type::getAccessModifier() const
{
    assert(isDefined());
    return definition_->getAccessModifier();
}

void lang::Type::setContainingScope(lang::Scope* scope)
{
    assert(isDefined());
    definition_->setContainingScope(scope);
}

lang::Scope* lang::Type::getContainingScope() const
{
    assert(isDefined());
    return definition_->scope();
}

void lang::Type::postResolve()
{
    assert(isDefined());
    definition_->postResolve();
}

void lang::Type::requestOverload(std::vector<lang::ResolvingHandle<lang::Type>> parameters)
{
    assert(isDefined());
    definition_->requestOverload(std::move(parameters));
}

bool lang::Type::enableImplicitConversionOnCall() const
{
    return false;
}

llvm::Constant* lang::Type::getDefaultContent(llvm::Module& m)
{
    assert(isDefined());
    return definition_->getDefaultContent(m);
}

llvm::Type* lang::Type::getNativeType(llvm::LLVMContext& c) const
{
    assert(isDefined());
    return definition_->getNativeType(c);
}

llvm::Type* lang::Type::getContentType(llvm::LLVMContext& c) const
{
    assert(isDefined());
    return definition_->getContentType(c);
}

llvm::DIType* lang::Type::getDebugType(CompileContext* context)
{
    assert(isDefined());
    return definition_->getDebugType(context);
}

llvm::TypeSize lang::Type::getNativeSize(llvm::Module* m)
{
    assert(isDefined());
    return definition_->getNativeSize(m);
}

llvm::TypeSize lang::Type::getContentSize(llvm::Module* m)
{
    assert(isDefined());
    return definition_->getContentSize(m);
}

bool lang::Type::isSubscriptDefined()
{
    assert(isDefined());
    return definition_->isSubscriptDefined();
}

lang::ResolvingHandle<lang::Type> lang::Type::getSubscriptReturnType()
{
    assert(isDefined());
    return definition_->getSubscriptReturnType();
}

bool lang::Type::isOperatorDefined(lang::BinaryOperator op, lang::ResolvingHandle<lang::Type> other)
{
    assert(isDefined());
    return definition_->isOperatorDefined(op, other);
}

bool lang::Type::isOperatorDefined(lang::UnaryOperator op)
{
    assert(isDefined());
    return definition_->isOperatorDefined(op);
}

lang::ResolvingHandle<lang::Type> lang::Type::getOperatorResultType(lang::BinaryOperator              op,
                                                                    lang::ResolvingHandle<lang::Type> other)
{
    assert(isDefined());
    return definition_->getOperatorResultType(op, other);
}

lang::ResolvingHandle<lang::Type> lang::Type::getOperatorResultType(lang::UnaryOperator op)
{
    assert(isDefined());
    return definition_->getOperatorResultType(op);
}

bool lang::Type::isImplicitlyConvertibleTo(lang::ResolvingHandle<lang::Type> other)
{
    assert(isDefined());
    return definition_->isImplicitlyConvertibleTo(other);
}

bool lang::Type::hasMember(const lang::Identifier& name)
{
    assert(isDefined());
    return definition_->hasMember(name);
}

lang::ResolvingHandle<lang::Type> lang::Type::getMemberType(const lang::Identifier& name)
{
    assert(isDefined());
    return definition_->getMemberType(name);
}

bool lang::Type::definesIndirection()
{
    assert(isDefined());
    return definition_->definesIndirection();
}

lang::ResolvingHandle<lang::Type> lang::Type::getIndirectionType()
{
    assert(isDefined());
    return definition_->getIndirectionType();
}

bool lang::Type::validateDefinition(ValidationLogger& validation_logger) const
{
    assert(isDefined());
    if (definition_->isCustom()) return definition_->validateDefinition(validation_logger);
    else return true;
}

bool lang::Type::validate(ValidationLogger& validation_logger, lang::Location location) const
{
    assert(isDefined());
    return definition_->validate(validation_logger, location);
}

bool lang::Type::validateSubscript(lang::Location                    indexed_location,
                                   lang::ResolvingHandle<lang::Type> index_type,
                                   lang::Location                    index_location,
                                   ValidationLogger&                 validation_logger) const
{
    assert(isDefined());
    return definition_->validateSubscript(indexed_location, std::move(index_type), index_location, validation_logger);
}

bool lang::Type::validateOperator(lang::BinaryOperator              op,
                                  lang::ResolvingHandle<lang::Type> other,
                                  lang::Location                    left_location,
                                  lang::Location                    right_location,
                                  ValidationLogger&                 validation_logger) const
{
    assert(isDefined());
    return definition_->validateOperator(op, std::move(other), left_location, right_location, validation_logger);
}

bool lang::Type::validateOperator(lang::UnaryOperator op,
                                  lang::Location      location,
                                  ValidationLogger&   validation_logger) const
{
    assert(isDefined());
    return definition_->validateOperator(op, location, validation_logger);
}

bool lang::Type::validateImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                            lang::Location                    location,
                                            ValidationLogger&                 validation_logger) const
{
    assert(isDefined());
    return definition_->validateImplicitConversion(std::move(other), location, validation_logger);
}

bool lang::Type::validateMemberAccess(const lang::Identifier& name, ValidationLogger& validation_logger) const
{
    assert(isDefined());
    return definition_->validateMemberAccess(name, validation_logger);
}

bool lang::Type::validateIndirection(lang::Location location, ValidationLogger& validation_logger) const
{
    assert(isDefined());
    return definition_->validateIndirection(location, validation_logger);
}

std::shared_ptr<lang::Value> lang::Type::buildSubscript(std::shared_ptr<Value> indexed,
                                                        std::shared_ptr<Value> index,
                                                        CompileContext*        context)
{
    assert(isDefined());
    return definition_->buildSubscript(std::move(indexed), std::move(index), context);
}

std::shared_ptr<lang::Value> lang::Type::buildOperator(lang::BinaryOperator   op,
                                                       std::shared_ptr<Value> left,
                                                       std::shared_ptr<Value> right,
                                                       CompileContext*        context)
{
    assert(isDefined());
    return definition_->buildOperator(op, std::move(left), std::move(right), context);
}

std::shared_ptr<lang::Value> lang::Type::buildOperator(lang::UnaryOperator    op,
                                                       std::shared_ptr<Value> value,
                                                       CompileContext*        context)
{
    assert(isDefined());
    return definition_->buildOperator(op, std::move(value), context);
}

std::shared_ptr<lang::Value> lang::Type::buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                                 std::shared_ptr<Value>            value,
                                                                 CompileContext*                   context)
{
    assert(isDefined());
    return definition_->buildImplicitConversion(other, std::move(value), context);
}

std::shared_ptr<lang::Value> lang::Type::buildMemberAccess(std::shared_ptr<Value>  value,
                                                           const lang::Identifier& name,
                                                           CompileContext*         context)
{
    assert(isDefined());
    return definition_->buildMemberAccess(std::move(value), name, context);
}

std::shared_ptr<lang::Value> lang::Type::buildIndirection(std::shared_ptr<Value> value, CompileContext* context)
{
    assert(isDefined());
    return definition_->buildIndirection(std::move(value), context);
}

void lang::Type::buildDefaultInitializer(llvm::Value* ptr, CompileContext* context)
{
    assert(isDefined());
    definition_->buildDefaultInitializer(ptr, context);
}

void lang::Type::buildCopyInitializer(llvm::Value* ptr, llvm::Value* original, CompileContext* context)
{
    assert(isDefined());
    definition_->buildCopyInitializer(ptr, original, context);
}

void lang::Type::buildDefaultInitializer(llvm::Value* ptr, llvm::Value* count, CompileContext* context)
{
    assert(isDefined());
    definition_->buildDefaultInitializer(ptr, count, context);
}

void lang::Type::buildFinalizer(llvm::Value* ptr, CompileContext* context)
{
    assert(isDefined());
    definition_->buildFinalizer(ptr, context);
}

void lang::Type::buildFinalizer(llvm::Value* ptr, llvm::Value* count, CompileContext* context)
{
    assert(isDefined());
    definition_->buildFinalizer(ptr, count, context);
}

void lang::Type::buildNativeDeclaration(CompileContext* context)
{
    assert(isDefined());
    definition_->buildNativeDeclaration(context);
}

void lang::Type::buildNativeDefinition(CompileContext* context)
{
    assert(isDefined());
    definition_->buildNativeDefinition(context);
}

lang::TypeDefinition* lang::Type::getDefinition() const
{
    return definition_.get();
}

bool lang::Type::isMatching(lang::ResolvingHandle<lang::Type> expected, lang::ResolvingHandle<lang::Type> actual)
{
    if (areSame(expected, actual)) return true;

    if (actual->isImplicitlyConvertibleTo(expected)) return true;

    if (actual->isReferenceType())
    {
        lang::ResolvingHandle<lang::Type> referenced_type = actual->getElementType();
        if (isMatching(expected, referenced_type)) return true;
    }

    return false;
}

bool lang::Type::checkMismatch(lang::ResolvingHandle<lang::Type> expected,
                               lang::ResolvingHandle<lang::Type> actual,
                               lang::Location                    location,
                               ValidationLogger&                 validation_logger)
{
    bool matching = isMatching(expected, actual);

    if (!matching)
    {
        validation_logger.logError("Cannot implicitly convert " + actual->getAnnotatedName() + " to "
                                       + expected->getAnnotatedName(),
                                   location);
    }

    lang::ResolvingHandle<lang::Type> start_type = actual;
    if (actual->isReferenceType()) start_type = actual->getElementType();

    if (start_type->isImplicitlyConvertibleTo(expected))
    {
        matching &= start_type->validateImplicitConversion(expected, location, validation_logger);
    }

    return matching;
}

std::shared_ptr<lang::Value> lang::Type::makeMatching(lang::ResolvingHandle<lang::Type> expected,
                                                      std::shared_ptr<lang::Value>      value,
                                                      CompileContext*                   context)
{
    if (areSame(expected, value->type())) return makeActual(value);

    if (value->type()->isImplicitlyConvertibleTo(expected))
        return value->type()->buildImplicitConversion(expected, value, context);

    if (value->type()->isReferenceType())
    {
        auto* reference_type                    = dynamic_cast<lang::ReferenceType*>(value->type()->definition_.get());
        std::shared_ptr<lang::Value> referenced = reference_type->getReferenced(value, context);

        return makeMatching(expected, referenced, context);
    }

    assert(false && "Cannot make the value matching, was mismatch checked before?");
    return nullptr;
}

lang::ResolvingHandle<lang::Type> lang::Type::getReferencedType(lang::ResolvingHandle<lang::Type> type)
{
    if (type->isReferenceType()) type = type->getElementType();
    return type;
}

std::shared_ptr<lang::Value> lang::Type::getValueOrReferencedValue(std::shared_ptr<lang::Value> value,
                                                                   CompileContext*              context)
{
    if (value->type()->isReferenceType())
    {
        auto* reference_type = dynamic_cast<lang::ReferenceType*>(value->type()->definition_.get());
        return reference_type->getReferenced(value, context);
    }

    return value;
}

bool lang::Type::areSame(lang::ResolvingHandle<lang::Type> lhs, lang::ResolvingHandle<lang::Type> rhs)
{
    return lhs->getActualType() == rhs->getActualType();
}

std::shared_ptr<lang::Value> lang::Type::makeActual(std::shared_ptr<lang::Value> value)
{
    lang::ResolvingHandle<lang::Type> actual_type = value->type()->getActualType();
    if (actual_type == value->type()) return value;

    return std::make_shared<lang::RoughlyCastedValue>(actual_type, value);
}

lang::ResolvingHandle<lang::Type> lang::Type::toUndefined() const
{
    if (isDefined() && !isCustom()) return self();

    return lang::makeHandled<lang::Type>(name());
}

lang::ResolvingHandle<lang::Type> lang::Type::toSeparateUndefined() const
{
    return isDefined() ? self() : lang::makeHandled<lang::Type>(name());
}
