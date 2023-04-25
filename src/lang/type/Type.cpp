#include "Type.h"

#include <utility>

#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/construct/value/RoughlyCastedValue.h"
#include "lang/type/ArrayType.h"
#include "lang/type/FixedWidthIntegerType.h"
#include "lang/type/ReferenceType.h"
#include "lang/type/VectorType.h"
#include "lang/utility/Identifier.h"
#include "lang/utility/Storage.h"
#include "validation/ValidationLogger.h"

lang::Type::Type(Identifier name) : name_(name)
{
    assert(not name_.text().empty());
}

lang::Type::Type(Owned<lang::TypeDefinition> definition) : name_(definition->name()), definition_(std::move(definition))
{
    definition_.value()->setType(this);
}

lang::Type::Type() : name_(lang::Identifier::like("")) {}

lang::ResolvingHandle<lang::Type> lang::Type::getUndefined()
{
    return ResolvingHandle<Type>(Owned<Type>(*(new Type())));
}

lang::Identifier const& lang::Type::name() const
{
    static const lang::Identifier undefined = lang::Identifier::like("$undefined");

    if (isDefined()) { return definition_.value()->name(); }
    else { return name_.text().empty() ? undefined : name_; }
}

std::string lang::Type::getAnnotatedName(bool is_safe) const
{
    std::string name = "'" + this->name() + "'";

    is_safe &= isDefined();

    if (is_safe && getActualType() != self()) { name += " (aka '" + getActualType().name() + "')"; }

    return name;
}

std::string const& lang::Type::getMangledName() const
{
    assert(isDefined());
    return definition_.value()->getMangledName();
}

bool lang::Type::isDefined() const
{
    return definition_.hasValue() && definition_.value()->isFullyDefined();
}

void lang::Type::define(Owned<lang::TypeDefinition> definition)
{
    assert(!isDefined());
    assert(!name_.text().empty() && "Cannot define the undefined type.");

    definition_ = std::move(definition);
    definition_.value()->setType(this);
}

StateCount lang::Type::getStateCount() const
{
    assert(isDefined());
    return definition_.value()->getStateCount();
}

bool lang::Type::isCustom() const
{
    assert(definition_.hasValue());
    return definition_.value()->isCustom();
}

lang::FixedWidthIntegerType const* lang::Type::isFixedWidthIntegerType() const
{
    assert(isDefined());
    return definition_.value()->isFixedWidthIntegerType();
}

bool lang::Type::isFixedWidthIntegerType(uint64_t bit_size, bool is_signed) const
{
    assert(isDefined());
    return definition_.value()->isFixedWidthIntegerType(bit_size, is_signed);
}

bool lang::Type::isSigned() const
{
    assert(isDefined());
    return definition_.value()->isSigned();
}

lang::IntegerType const* lang::Type::isIntegerType() const
{
    assert(isDefined());
    return definition_.value()->isIntegerType();
}

bool lang::Type::isBooleanType() const
{
    assert(isDefined());
    return definition_.value()->isBooleanType();
}

bool lang::Type::isCharType() const
{
    assert(isDefined());
    return definition_.value()->isCharType();
}

bool lang::Type::isUnsignedIntegerPointerType() const
{
    assert(isDefined());
    return definition_.value()->isUnsignedIntegerPointerType();
}

lang::FloatingPointType const* lang::Type::isFloatingPointType() const
{
    assert(isDefined());
    return definition_.value()->isFloatingPointType();
}

bool lang::Type::isFloatingPointType(size_t precision) const
{
    assert(isDefined());
    return definition_.value()->isFloatingPointType(precision);
}

bool lang::Type::isSizeType() const
{
    assert(isDefined());
    return definition_.value()->isSizeType();
}

bool lang::Type::isDiffType() const
{
    assert(isDefined());
    return definition_.value()->isDiffType();
}

bool lang::Type::isVoidType() const
{
    assert(isDefined());
    return definition_.value()->isVoidType();
}

bool lang::Type::isNullValueType() const
{
    assert(isDefined());
    return definition_.value()->isNullValueType();
}

bool lang::Type::isPointerType() const
{
    assert(isDefined());
    return definition_.value()->isPointerType();
}

bool lang::Type::isAddressType() const
{
    assert(isDefined());
    return definition_.value()->isAddressType();
}

bool lang::Type::isBufferType() const
{
    assert(isDefined());
    return definition_.value()->isBufferType();
}

bool lang::Type::isOpaquePointerType() const
{
    assert(isDefined());
    return definition_.value()->isOpaquePointerType();
}

bool lang::Type::isReferenceType() const
{
    assert(isDefined());
    return definition_.value()->isReferenceType();
}

bool lang::Type::isStructType() const
{
    assert(isDefined());
    return definition_.value()->isStructType();
}

lang::VectorizableType const* lang::Type::isVectorizable() const
{
    assert(isDefined());
    return definition_.value()->isVectorizable();
}

lang::VectorizableType* lang::Type::isVectorizable()
{
    assert(isDefined());
    return definition_.value()->isVectorizable();
}

lang::VectorType const* lang::Type::isVectorType() const
{
    assert(isDefined());
    return definition_.value()->isVectorType();
}

lang::VectorType* lang::Type::isVectorType()
{
    assert(isDefined());
    return definition_.value()->isVectorType();
}

lang::ArrayType const* lang::Type::isArrayType() const
{
    assert(isDefined());
    return definition_.value()->isArrayType();
}

lang::ArrayType* lang::Type::isArrayType()
{
    assert(isDefined());
    return definition_.value()->isArrayType();
}

lang::ResolvingHandle<lang::Type> lang::Type::getElementType()
{
    assert(isDefined());
    return definition_.value()->getElementType();
}

lang::Type const& lang::Type::getElementType() const
{
    assert(isDefined());
    return definition_.value()->getElementType();
}

lang::ResolvingHandle<lang::Type> lang::Type::getActualType()
{
    assert(definition_.hasValue());
    return definition_.value()->getActualType();
}

lang::Type const& lang::Type::getActualType() const
{
    assert(definition_.hasValue());
    return definition_.value()->getActualType();
}

lang::Accessibility const& lang::Type::getAccessibility() const
{
    assert(isDefined());
    return definition_.value()->getAccessibility();
}

void lang::Type::setContainingScope(lang::Scope* scope)
{
    if (definition_.hasValue()) { definition_.value()->setContainingScope(scope); }
}

lang::Scope* lang::Type::getContainingScope()
{
    assert(definition_.hasValue());
    return definition_.value()->scope();
}

lang::Scope const* lang::Type::getContainingScope() const
{
    assert(isDefined());
    return definition_.value()->scope();
}

void lang::Type::postResolve()
{
    assert(isDefined());
    definition_.value()->postResolve();
}

bool lang::Type::requestOverload(std::vector<lang::ResolvingHandle<lang::Type>> parameters)
{
    assert(isDefined());
    return definition_.value()->requestOverload(std::move(parameters));
}

bool lang::Type::enableImplicitConversionOnCall() const
{
    return false;
}

llvm::Constant* lang::Type::getDefaultContent(llvm::Module& m) const
{
    assert(isDefined());
    return definition_.value()->getDefaultContent(m);
}

llvm::Type* lang::Type::getNativeType(llvm::LLVMContext& c) const
{
    assert(isDefined());
    return definition_.value()->getNativeType(c);
}

llvm::Type* lang::Type::getContentType(llvm::LLVMContext& c) const
{
    assert(isDefined());
    return definition_.value()->getContentType(c);
}

llvm::DIType* lang::Type::getDebugType(CompileContext& context) const
{
    assert(isDefined());
    return definition_.value()->getDebugType(context);
}

llvm::TypeSize lang::Type::getNativeSize(llvm::Module& m)
{
    assert(isDefined());
    return definition_.value()->getNativeSize(m);
}

llvm::TypeSize lang::Type::getContentSize(llvm::Module& m)
{
    assert(isDefined());
    return definition_.value()->getContentSize(m);
}

bool lang::Type::isSubscriptDefined() const
{
    assert(isDefined());
    return definition_.value()->isSubscriptDefined();
}

lang::ResolvingHandle<lang::Type> lang::Type::getSubscriptReturnType()
{
    assert(isDefined());
    return definition_.value()->getSubscriptReturnType();
}

bool lang::Type::isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const
{
    assert(isDefined());
    return definition_.value()->isOperatorDefined(op, other);
}

bool lang::Type::isOperatorDefined(lang::UnaryOperator op) const
{
    assert(isDefined());
    return definition_.value()->isOperatorDefined(op);
}

lang::ResolvingHandle<lang::Type> lang::Type::getOperatorResultType(lang::BinaryOperator              op,
                                                                    lang::ResolvingHandle<lang::Type> other)
{
    assert(isDefined());
    return definition_.value()->getOperatorResultType(op, other);
}

lang::ResolvingHandle<lang::Type> lang::Type::getOperatorResultType(lang::UnaryOperator op)
{
    assert(isDefined());
    return definition_.value()->getOperatorResultType(op);
}

bool lang::Type::isImplicitlyConvertibleTo(lang::Type const& other) const
{
    assert(isDefined());
    return definition_.value()->isImplicitlyConvertibleTo(other);
}

bool lang::Type::hasMember(lang::Identifier const& name) const
{
    assert(isDefined());
    return definition_.value()->hasMember(name);
}

lang::ResolvingHandle<lang::Type> lang::Type::getMemberType(lang::Identifier const& name)
{
    assert(isDefined());
    return definition_.value()->getMemberType(name);
}

bool lang::Type::definesIndirection() const
{
    assert(isDefined());
    return definition_.value()->definesIndirection();
}

lang::ResolvingHandle<lang::Type> lang::Type::getIndirectionType()
{
    assert(isDefined());
    return definition_.value()->getIndirectionType();
}

bool lang::Type::validate(ValidationLogger& validation_logger, lang::Location location) const
{
    assert(definition_.hasValue());
    return definition_.value()->validate(validation_logger, location);
}

bool lang::Type::validateSubscript(lang::Location    indexed_location,
                                   Type const&       index_type,
                                   lang::Location    index_location,
                                   ValidationLogger& validation_logger) const
{
    assert(isDefined());
    return definition_.value()->validateSubscript(indexed_location,
                                                  std::move(index_type),
                                                  index_location,
                                                  validation_logger);
}

bool lang::Type::validateOperator(lang::BinaryOperator op,
                                  lang::Type const&    other,
                                  lang::Location       left_location,
                                  lang::Location       right_location,
                                  ValidationLogger&    validation_logger) const
{
    assert(isDefined());
    return definition_.value()->validateOperator(op,
                                                 std::move(other),
                                                 left_location,
                                                 right_location,
                                                 validation_logger);
}

bool lang::Type::validateOperator(lang::UnaryOperator op,
                                  lang::Location      location,
                                  ValidationLogger&   validation_logger) const
{
    assert(isDefined());
    return definition_.value()->validateOperator(op, location, validation_logger);
}

bool lang::Type::validateImplicitConversion(lang::Type const& other,
                                            lang::Location    location,
                                            ValidationLogger& validation_logger) const
{
    assert(isDefined());
    return definition_.value()->validateImplicitConversion(std::move(other), location, validation_logger);
}

bool lang::Type::validateMemberAccess(lang::Identifier const& name, ValidationLogger& validation_logger) const
{
    assert(isDefined());
    return definition_.value()->validateMemberAccess(name, validation_logger);
}

bool lang::Type::validateIndirection(lang::Location location, ValidationLogger& validation_logger) const
{
    assert(isDefined());
    return definition_.value()->validateIndirection(location, validation_logger);
}

Shared<lang::Value> lang::Type::buildSubscript(Shared<Value> indexed, Shared<Value> index, CompileContext& context)
{
    assert(isDefined());
    return definition_.value()->buildSubscript(std::move(indexed), std::move(index), context);
}

Shared<lang::Value> lang::Type::buildOperator(lang::BinaryOperator op,
                                              Shared<Value>        left,
                                              Shared<Value>        right,
                                              CompileContext&      context)
{
    assert(isDefined());
    return definition_.value()->buildOperator(op, std::move(left), std::move(right), context);
}

Shared<lang::Value> lang::Type::buildOperator(lang::UnaryOperator op, Shared<Value> value, CompileContext& context)
{
    assert(isDefined());
    return definition_.value()->buildOperator(op, std::move(value), context);
}

Shared<lang::Value> lang::Type::buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                        Shared<Value>                     value,
                                                        CompileContext&                   context)
{
    assert(isDefined());
    return definition_.value()->buildImplicitConversion(other, std::move(value), context);
}

Shared<lang::Value> lang::Type::buildMemberAccess(Shared<Value>           value,
                                                  lang::Identifier const& name,
                                                  CompileContext&         context)
{
    assert(isDefined());
    return definition_.value()->buildMemberAccess(std::move(value), name, context);
}

Shared<lang::Value> lang::Type::buildIndirection(Shared<Value> value, CompileContext& context)
{
    assert(isDefined());
    return definition_.value()->buildIndirection(std::move(value), context);
}

void lang::Type::buildDefaultInitializer(llvm::Value* ptr, CompileContext& context)
{
    assert(isDefined());
    definition_.value()->buildDefaultInitializer(ptr, context);
}

void lang::Type::buildCopyInitializer(llvm::Value* ptr, llvm::Value* original, CompileContext& context)
{
    assert(isDefined());
    definition_.value()->buildCopyInitializer(ptr, original, context);
}

void lang::Type::buildDefaultInitializer(llvm::Value* ptr, llvm::Value* count, CompileContext& context)
{
    assert(isDefined());
    definition_.value()->buildDefaultInitializer(ptr, count, context);
}

void lang::Type::buildFinalizer(llvm::Value* ptr, CompileContext& context)
{
    assert(isDefined());
    definition_.value()->buildFinalizer(ptr, context);
}

void lang::Type::buildFinalizer(llvm::Value* ptr, llvm::Value* count, CompileContext& context)
{
    assert(isDefined());
    definition_.value()->buildFinalizer(ptr, count, context);
}

void lang::Type::buildNativeDeclaration(CompileContext& context)
{
    assert(isDefined());
    definition_.value()->buildNativeDeclaration(context);
}

void lang::Type::buildNativeDefinition(CompileContext& context)
{
    assert(isDefined());
    definition_.value()->buildNativeDefinition(context);
}

lang::TypeDefinition* lang::Type::getDefinition()
{
    return getPtr(definition_);
}

lang::TypeDefinition const* lang::Type::getDefinition() const
{
    return getPtr(definition_);
}

bool lang::Type::isMatching(lang::Type const& expected, lang::Type const& actual)
{
    if (areSame(expected, actual)) return true;

    if (actual.isImplicitlyConvertibleTo(expected)) return true;

    if (actual.isReferenceType())
    {
        lang::Type const& referenced_type = actual.getElementType();
        if (isMatching(expected, referenced_type)) return true;
    }

    return false;
}

bool lang::Type::checkMismatch(lang::Type const& expected,
                               lang::Type const& actual,
                               lang::Location    location,
                               ValidationLogger& validation_logger)
{
    bool matching = isMatching(expected, actual);

    if (!matching)
    {
        validation_logger.logError("Cannot implicitly convert " + actual.getAnnotatedName() + " to "
                                       + expected.getAnnotatedName(),
                                   location);
    }

    std::reference_wrapper<lang::Type const> start_type = actual;
    if (actual.isReferenceType()) start_type = actual.getElementType();

    if (start_type.get().isImplicitlyConvertibleTo(expected))
    {
        matching &= start_type.get().validateImplicitConversion(expected, location, validation_logger);
    }

    return matching;
}

Shared<lang::Value> lang::Type::makeMatching(lang::ResolvingHandle<lang::Type> expected,
                                             Shared<lang::Value>               value,
                                             CompileContext&                   context)
{
    if (areSame(expected, value->type())) return makeActual(value);

    if (value->type()->isImplicitlyConvertibleTo(expected))
        return value->type()->buildImplicitConversion(expected, value, context);

    if (value->type()->isReferenceType())
    {
        auto* reference_type           = dynamic_cast<lang::ReferenceType*>(value->type()->definition_.value().get());
        Shared<lang::Value> referenced = reference_type->getReferenced(value, context);

        return makeMatching(expected, referenced, context);
    }

    assert(false && "Cannot make the value matching, was mismatch checked before?");
    throw std::logic_error("Cannot make the value matching, was mismatch checked before?");
}

lang::ResolvingHandle<lang::Type> lang::Type::getReferencedType(lang::ResolvingHandle<lang::Type> type)
{
    if (type->isReferenceType()) type = type->getElementType();
    return type;
}

lang::Type const& lang::Type::getReferencedType(lang::Type const& type)
{
    if (type.isReferenceType()) return type.getElementType();
    return type;
}

Shared<lang::Value> lang::Type::getValueOrReferencedValue(Shared<lang::Value> value, CompileContext& context)
{
    if (value->type()->isReferenceType())
    {
        auto* reference_type = dynamic_cast<lang::ReferenceType*>(value->type()->definition_.value().get());
        return reference_type->getReferenced(value, context);
    }

    return value;
}

bool lang::Type::areSame(lang::Type const& lhs, lang::Type const& rhs)
{
    return lhs.getActualType() == rhs.getActualType();
}

Shared<lang::Value> lang::Type::makeActual(Shared<lang::Value> value)
{
    lang::ResolvingHandle<lang::Type> actual_type = value->type()->getActualType();
    if (actual_type == value->type()) return value;

    return makeShared<lang::RoughlyCastedValue>(actual_type, value);
}

lang::ResolvingHandle<lang::Type> lang::Type::createUndefinedClone(lang::Context& new_context) const
{
    if (isDefined() && !isCustom()) return definition_.value()->clone(new_context);

    return lang::makeHandled<lang::Type>(name());
}

lang::ResolvingHandle<lang::Type> lang::Type::getDetachedIfUndefined()
{
    return definition_.hasValue() ? self() : lang::makeHandled<lang::Type>(name());
}

template<typename IN, typename OUT>
struct GetCommonType {
    OUT operator()(IN types) const
    {
        OUT common_types;

        {// Check if all types are defined.
            for (auto& type : types)
            {
                if (!deref(type).isDefined()) { return common_types; }
            }
        }

        {// Check if all types are the same, which means we have a trivial common type.
            auto first = types.front();

            bool all_same = true;

            for (auto& current : types)
            {
                if (not lang::Type::areSame(first, current))
                {
                    all_same = false;
                    break;
                }
            }

            if (all_same)
            {
                common_types.emplace_back(first);
                return common_types;
            }
        }

        {// Check for each type if it is a type all other types are convertible to.
            std::set<lang::TypeDefinition const*> confirmed_candidates;

            for (auto& candidate : types)
            {
                bool is_confirmed = true;

                for (auto& current : types) { is_confirmed &= lang::Type::isMatching(candidate, current); }

                if (not is_confirmed) continue;

                auto [iterator, is_new] = confirmed_candidates.emplace(deref(candidate).getDefinition());
                if (is_new) { common_types.emplace_back(candidate); }
            }
        }

        return common_types;
    }
};

std::vector<lang::ResolvingHandle<lang::Type>> lang::Type::getCommonType(
    std::vector<lang::ResolvingHandle<lang::Type>>& types)
{
    return GetCommonType<std::vector<lang::ResolvingHandle<lang::Type>>,
                         std::vector<lang::ResolvingHandle<lang::Type>>>()(types);
}

std::vector<std::reference_wrapper<lang::Type const>> lang::Type::getCommonType(
    std::vector<std::reference_wrapper<lang::Type const>> const& types)
{
    return GetCommonType<std::vector<std::reference_wrapper<lang::Type const>>,
                         std::vector<std::reference_wrapper<lang::Type const>>>()(types);
}

bool lang::Type::operator==(lang::Type const& other) const
{
    return this->definition_.value().get() == other.definition_.value().get();
}

bool lang::Type::operator!=(lang::Type const& other) const
{
    return !(*this == other);
}

enum TypeClass : uint8_t
{
    CUSTOM,
    ARRAY,
    BOOLEAN,
    BUFFER,
    CHAR,
    DOUBLE,
    FIXED_WIDTH_INTEGER,
    HALF,
    NULL_POINTER,
    OPAQUE_POINTER,
    POINTER,
    QUAD,
    REFERENCE,
    SINGLE,
    SIZE,
    DIFF,
    UNSIGNED_INTEGER_POINTER,
    VECTOR,
    VOID
};

static TypeClass getTypeClass(lang::Type* type)
{
    if (!type->isDefined()) return TypeClass::CUSTOM;

    if (type->isCustom()) return TypeClass::CUSTOM;
    if (type->isArrayType()) return TypeClass::ARRAY;
    if (type->isBooleanType()) return TypeClass::BOOLEAN;
    if (type->isBufferType()) return TypeClass::BUFFER;
    if (type->isCharType()) return TypeClass::CHAR;
    if (type->isFloatingPointType(64)) return TypeClass::DOUBLE;
    if (type->isFixedWidthIntegerType()) return TypeClass::FIXED_WIDTH_INTEGER;
    if (type->isFloatingPointType(16)) return TypeClass::HALF;
    if (type->isNullValueType()) return TypeClass::NULL_POINTER;
    if (type->isOpaquePointerType()) return TypeClass::OPAQUE_POINTER;
    if (type->isPointerType()) return TypeClass::POINTER;
    if (type->isFloatingPointType(128)) return TypeClass::QUAD;
    if (type->isReferenceType()) return TypeClass::REFERENCE;
    if (type->isFloatingPointType(32)) return TypeClass::SINGLE;
    if (type->isSizeType()) return TypeClass::SIZE;
    if (type->isDiffType()) return TypeClass::DIFF;
    if (type->isUnsignedIntegerPointerType()) return TypeClass::UNSIGNED_INTEGER_POINTER;
    if (type->isVectorType()) return TypeClass::VECTOR;
    if (type->isVoidType()) return TypeClass::VOID;

    assert(false);
    return TypeClass::VOID;
}

void synchronize(lang::ResolvingHandle<lang::Type> type, Storage& storage)
{
    if (storage.isWriting()) assert(type->isDefined());
    if (storage.isReading()) assert(storage.data_.has_value());

    uint8_t type_class = getTypeClass(&*type);
    storage.sync(type_class);

    auto context = [&]() {
        assert(storage.isReading());
        return std::any_cast<lang::Context*>(storage.data_);
    };

    switch (type_class)
    {
        case TypeClass::CUSTOM:
        {
            lang::Identifier identifier = type->name();
            storage.sync(identifier);
            if (storage.isReading()) type.reroute(lang::makeHandled<lang::Type>(identifier));
            break;
        }
        case TypeClass::ARRAY:
        {
            uint64_t                          size         = 0;
            lang::ResolvingHandle<lang::Type> element_type = lang::Type::getUndefined();

            if (storage.isWriting())
            {
                size         = type->isArrayType()->getSize().value();
                element_type = type->getElementType();
            }

            storage.sync(size);
            storage.sync(element_type);

            if (storage.isReading()) { type.reroute(context()->getArrayType(element_type, size)); }
            break;
        }
        case TypeClass::BOOLEAN:
        {
            if (storage.isReading()) type.reroute(context()->getBooleanType());
            break;
        }
        case TypeClass::BUFFER:
        {
            lang::ResolvingHandle<lang::Type> element_type = lang::Type::getUndefined();

            if (storage.isWriting()) { element_type = type->getElementType(); }

            storage.sync(element_type);

            if (storage.isReading()) { type.reroute(context()->getBufferType(element_type)); }
            break;
        }
        case TypeClass::CHAR:
        {
            if (storage.isReading()) type.reroute(context()->getCharType());
            break;
        }
        case TypeClass::DOUBLE:
        {
            if (storage.isReading()) type.reroute(context()->getDoubleType());
            break;
        }
        case TypeClass::FIXED_WIDTH_INTEGER:
        {
            uint64_t bits      = 0;
            bool     is_signed = false;

            if (storage.isWriting())
            {
                bits      = type->isFixedWidthIntegerType()->getBitSize().value();
                is_signed = type->isSigned();
            }

            storage.sync(bits);
            storage.sync(is_signed);

            if (storage.isReading())
            { type.reroute(context()->getFixedWidthIntegerType(bits, is_signed)); }

            break;
        }
        case TypeClass::HALF:
        {
            if (storage.isReading()) type.reroute(context()->getHalfType());
            break;
        }
        case TypeClass::NULL_POINTER:
        {
            if (storage.isReading()) type.reroute(context()->getNullPointerType());
            break;
        }
        case TypeClass::OPAQUE_POINTER:
        {
            if (storage.isReading()) type.reroute(context()->getOpaquePointerType());
            break;
        }
        case TypeClass::POINTER:
        {
            lang::ResolvingHandle<lang::Type> element_type = lang::Type::getUndefined();

            if (storage.isWriting()) { element_type = type->getElementType(); }

            storage.sync(element_type);

            if (storage.isReading()) { type.reroute(context()->getPointerType(element_type)); }
            break;
        }
        case TypeClass::QUAD:
        {
            if (storage.isReading()) type.reroute(context()->getQuadType());
            break;
        }
        case TypeClass::REFERENCE:
        {
            lang::ResolvingHandle<lang::Type> element_type = lang::Type::getUndefined();

            if (storage.isWriting()) { element_type = type->getElementType(); }

            storage.sync(element_type);

            if (storage.isReading()) { type.reroute(context()->getReferenceType(element_type)); }
            break;
        }
        case TypeClass::SINGLE:
        {
            if (storage.isReading()) type.reroute(context()->getSingleType());
            break;
        }
        case TypeClass::SIZE:
        {
            if (storage.isReading()) type.reroute(context()->getSizeType());
            break;
        }
        case TypeClass::DIFF:
        {
            if (storage.isReading()) type.reroute(context()->getDiffType());
            break;
        }
        case TypeClass::UNSIGNED_INTEGER_POINTER:
        {
            if (storage.isReading()) type.reroute(context()->getUnsignedIntegerPointerType());
            break;
        }
        case TypeClass::VECTOR:
        {
            uint64_t                          size         = 0;
            lang::ResolvingHandle<lang::Type> element_type = lang::Type::getUndefined();

            if (storage.isWriting())
            {
                size         = type->isVectorType()->getSize().value();
                element_type = type->getElementType();
            }

            storage.sync(size);
            storage.sync(element_type);

            if (storage.isReading()) { type.reroute(context()->getVectorType(element_type, size)); }
            break;
        }
        case TypeClass::VOID:
        {
            if (storage.isReading()) type.reroute(context()->getVoidType());
            break;
        }
        default:
        {
            assert(false);
            break;
        }
    }
}
