#include "Context.h"

#include <utility>

#include "ApplicationVisitor.h"
#include "lang/type/ArrayType.h"
#include "lang/type/BooleanType.h"
#include "lang/type/BufferType.h"
#include "lang/type/CharType.h"
#include "lang/type/DoubleType.h"
#include "lang/type/FixedWidthIntegerType.h"
#include "lang/type/HalfType.h"
#include "lang/type/NullValueType.h"
#include "lang/type/OpaquePointerType.h"
#include "lang/type/PointerType.h"
#include "lang/type/QuadType.h"
#include "lang/type/ReferenceType.h"
#include "lang/type/SingleType.h"
#include "lang/type/SizeType.h"
#include "lang/type/UnitType.h"
#include "lang/type/UnsignedIntegerPointerType.h"
#include "lang/type/VectorType.h"
#include "validation/ValidationLogger.h"

lang::Context::Context(lang::GlobalScope& global_scope, bool contains_runtime)
    : global_scope_(global_scope)
    , contains_runtime_(contains_runtime)
{
    type_registries_.push_back(&array_types_);
    type_registries_.push_back(&buffer_types_);
    type_registries_.push_back(&fixed_width_integer_types_);
    type_registries_.push_back(&pointer_types_);
    type_registries_.push_back(&reference_types_);
    type_registries_.push_back(&vector_types_);

    for (auto& registry : type_registries_) registry->setDefaultContainingScope(global_scope_);
}

void lang::Context::initialize()
{
    // These types are keyword types, which means that the global scope resolves them by name:

    auto register_type = [&](lang::ResolvingHandle<lang::Type> type) {
        global_scope_.addEntity(lang::OwningHandle<lang::Type>::takeOwnership(type));
    };

    register_type(getHalfType());
    register_type(getSingleType());
    register_type(getDoubleType());
    register_type(getQuadType());

    register_type(getUnitType());
    register_type(getBooleanType());
    register_type(getCharType());
    register_type(getSizeType());
    register_type(getDiffType());
    register_type(getUnsignedIntegerPointerType());
    register_type(getOpaquePointerType());
    register_type(getNullValueType());
}

void lang::Context::resolve()
{
    for (auto& registry : type_registries_) registry->resolve();
}

void lang::Context::postResolve()
{
    for (auto& registry : type_registries_) registry->postResolve();
}

void lang::Context::registerDeclarations(Execution& exec)
{
    for (auto& registry : type_registries_) registry->registerDeclarations(exec);
}

void lang::Context::registerDefinitions(Execution& exec)
{
    for (auto& registry : type_registries_) registry->registerDefinitions(exec);
}

lang::ResolvingHandle<lang::Type> lang::Context::getArrayType(lang::ResolvingHandle<lang::Type> element_type,
                                                              uint64_t                          size) const
{
    element_type = element_type->getDetachedIfUndefined();

    std::vector<lang::ResolvingHandle<lang::Type>> used_types;
    used_types.emplace_back(element_type);

    Optional<lang::ResolvingHandle<lang::Type>> defined_type = array_types_.get(used_types, size);

    if (defined_type.hasValue()) { return defined_type.value(); }
    else
    {
        auto&                             array_type = *(new lang::ArrayType(element_type, size));
        lang::ResolvingHandle<lang::Type> type = lang::makeHandled<lang::Type>(Owned<lang::ArrayType>(array_type));
        array_types_.add(std::move(used_types), size, type);

        return type;
    }
}

lang::Type const& lang::Context::getArrayType(lang::Type const& element_type, uint64_t size) const
{
    assert(element_type.isDefined());

    lang::ResolvingHandle<lang::Type> element_type_handle =
        const_cast<lang::Type&>(element_type).getDetachedIfUndefined();

    return getArrayType(element_type_handle, size);
}

lang::ResolvingHandle<lang::Type> lang::Context::getBooleanType() const
{
    if (!boolean_type_.hasValue())
        boolean_type_ = lang::makeHandled<lang::Type>(Owned<lang::TypeDefinition>(*(new BooleanType())));

    return boolean_type_.value();
}

lang::ResolvingHandle<lang::Type> lang::Context::getBufferType(lang::ResolvingHandle<lang::Type> element_type) const
{
    element_type = element_type->getDetachedIfUndefined();

    std::vector<lang::ResolvingHandle<lang::Type>> used_types;
    used_types.emplace_back(element_type);

    Optional<lang::ResolvingHandle<lang::Type>> defined_type = buffer_types_.get(used_types, lang::Empty());

    if (defined_type.hasValue()) { return defined_type.value(); }
    else
    {
        auto&                             buffer_type = *(new lang::BufferType(element_type));
        lang::ResolvingHandle<lang::Type> type = lang::makeHandled<lang::Type>(Owned<lang::BufferType>(buffer_type));
        buffer_types_.add(std::move(used_types), lang::Empty(), type);

        return type;
    }
}

lang::Type const& lang::Context::getBufferType(lang::Type const& element_type) const
{
    assert(element_type.isDefined());

    lang::ResolvingHandle<lang::Type> element_type_handle =
        const_cast<lang::Type&>(element_type).getDetachedIfUndefined();

    return getBufferType(element_type_handle);
}

lang::ResolvingHandle<lang::Type> lang::Context::getCharType() const
{
    if (!char_type_.hasValue())
        char_type_ = lang::makeHandled<lang::Type>(Owned<lang::TypeDefinition>(*(new CharType())));

    return char_type_.value();
}

lang::ResolvingHandle<lang::Type> lang::Context::getDoubleType() const
{
    if (!double_type_.hasValue())
        double_type_ = lang::makeHandled<lang::Type>(Owned<lang::TypeDefinition>(*(new DoubleType())));

    return double_type_.value();
}

lang::ResolvingHandle<lang::Type> lang::Context::getFixedWidthIntegerType(uint64_t bit_size, bool is_signed) const
{
    std::vector<lang::ResolvingHandle<lang::Type>> used_types;

    Optional<lang::ResolvingHandle<lang::Type>> defined_type =
        fixed_width_integer_types_.get(used_types, std::make_pair(bit_size, is_signed));

    if (defined_type.hasValue()) { return defined_type.value(); }
    else
    {
        auto&                             integer_type = *(new lang::FixedWidthIntegerType(bit_size, is_signed));
        lang::ResolvingHandle<lang::Type> type =
            lang::makeHandled<lang::Type>(Owned<lang::FixedWidthIntegerType>(integer_type));
        fixed_width_integer_types_.add(std::move(used_types), std::make_pair(bit_size, is_signed), type);

        return type;
    }
}

lang::ResolvingHandle<lang::Type> lang::Context::getHalfType() const
{
    if (!half_type_.hasValue())
        half_type_ = lang::makeHandled<lang::Type>(Owned<lang::TypeDefinition>(*(new HalfType())));

    return half_type_.value();
}

lang::ResolvingHandle<lang::Type> lang::Context::getNullValueType() const
{
    if (!null_pointer_type_.hasValue())
        null_pointer_type_ = lang::makeHandled<lang::Type>(Owned<lang::TypeDefinition>(*(new NullValueType())));

    return null_pointer_type_.value();
}

lang::ResolvingHandle<lang::Type> lang::Context::getOpaquePointerType() const
{
    if (!opaque_pointer_type_.hasValue())
        opaque_pointer_type_ = lang::makeHandled<lang::Type>(Owned<lang::TypeDefinition>(*(new OpaquePointerType())));

    return opaque_pointer_type_.value();
}

lang::ResolvingHandle<lang::Type> lang::Context::getPointerType(lang::ResolvingHandle<lang::Type> element_type) const
{
    element_type = element_type->getDetachedIfUndefined();

    std::vector<lang::ResolvingHandle<lang::Type>> used_types;
    used_types.emplace_back(element_type);

    Optional<lang::ResolvingHandle<lang::Type>> defined_type = pointer_types_.get(used_types, lang::Empty());

    if (defined_type.hasValue()) { return defined_type.value(); }
    else
    {
        auto&                             pointer_type = *(new lang::PointerType(element_type));
        lang::ResolvingHandle<lang::Type> type = lang::makeHandled<lang::Type>(Owned<lang::PointerType>(pointer_type));
        pointer_types_.add(std::move(used_types), lang::Empty(), type);

        return type;
    }
}

lang::Type const& lang::Context::getPointerType(lang::Type const& element_type) const
{
    assert(element_type.isDefined());

    lang::ResolvingHandle<lang::Type> element_type_handle =
        const_cast<lang::Type&>(element_type).getDetachedIfUndefined();

    return getPointerType(element_type_handle);
}

lang::ResolvingHandle<lang::Type> lang::Context::getQuadType() const
{
    if (!quad_type_.hasValue())
        quad_type_ = lang::makeHandled<lang::Type>(Owned<lang::TypeDefinition>(*(new QuadType())));

    return quad_type_.value();
}

lang::ResolvingHandle<lang::Type> lang::Context::getReferenceType(lang::ResolvingHandle<lang::Type> element_type) const
{
    element_type = element_type->getDetachedIfUndefined();

    std::vector<lang::ResolvingHandle<lang::Type>> used_types;
    used_types.emplace_back(element_type);

    Optional<lang::ResolvingHandle<lang::Type>> defined_type = reference_types_.get(used_types, lang::Empty());

    if (defined_type.hasValue()) { return defined_type.value(); }
    else
    {
        auto&                             reference_type = *(new lang::ReferenceType(element_type));
        lang::ResolvingHandle<lang::Type> type =
            lang::makeHandled<lang::Type>(Owned<lang::ReferenceType>(reference_type));
        reference_types_.add(std::move(used_types), lang::Empty(), type);

        return type;
    }
}

lang::Type const& lang::Context::getReferenceType(lang::Type const& element_type) const
{
    assert(element_type.isDefined());

    lang::ResolvingHandle<lang::Type> element_type_handle =
        const_cast<lang::Type&>(element_type).getDetachedIfUndefined();

    return getReferenceType(element_type_handle);
}

lang::ResolvingHandle<lang::Type> lang::Context::getSingleType() const
{
    if (!single_type_.hasValue())
        single_type_ = lang::makeHandled<lang::Type>(Owned<lang::TypeDefinition>(*(new SingleType())));

    return single_type_.value();
}

lang::ResolvingHandle<lang::Type> lang::Context::getSizeType() const
{
    if (!size_type_.hasValue())
        size_type_ = lang::makeHandled<lang::Type>(
            Owned<lang::TypeDefinition>(*(new SizeType("size", SizeType::Kind::SIZE_KIND))));

    return size_type_.value();
}

lang::ResolvingHandle<lang::Type> lang::Context::getDiffType() const
{
    if (!diff_type_.hasValue())
        diff_type_ = lang::makeHandled<lang::Type>(
            Owned<lang::TypeDefinition>(*(new SizeType("diff", SizeType::Kind::DIFF_KIND))));

    return diff_type_.value();
}

lang::ResolvingHandle<lang::Type> lang::Context::getUnsignedIntegerPointerType() const
{
    if (!unsigned_integer_pointer_type_.hasValue())
        unsigned_integer_pointer_type_ =
            lang::makeHandled<lang::Type>(Owned<lang::TypeDefinition>(*(new UnsignedIntegerPointerType())));

    return unsigned_integer_pointer_type_.value();
}

lang::ResolvingHandle<lang::Type> lang::Context::getVectorType(lang::ResolvingHandle<lang::Type> element_type,
                                                               uint64_t                          size) const
{
    element_type = element_type->getDetachedIfUndefined();

    std::vector<lang::ResolvingHandle<lang::Type>> used_types;
    used_types.emplace_back(element_type);

    Optional<lang::ResolvingHandle<lang::Type>> defined_type = vector_types_.get(used_types, size);

    if (defined_type.hasValue()) { return defined_type.value(); }
    else
    {
        auto&                             vector_type = *(new lang::VectorType(element_type, size));
        lang::ResolvingHandle<lang::Type> type = lang::makeHandled<lang::Type>(Owned<lang::VectorType>(vector_type));
        vector_types_.add(std::move(used_types), size, type);

        return type;
    }
}

lang::Type const& lang::Context::getVectorType(lang::Type const& element_type, uint64_t size) const
{
    assert(element_type.isDefined());

    lang::ResolvingHandle<lang::Type> element_type_handle =
        const_cast<lang::Type&>(element_type).getDetachedIfUndefined();

    return getVectorType(element_type_handle, size);
}

lang::ResolvingHandle<lang::Type> lang::Context::getUnitType() const
{
    if (!unit_type_.hasValue())
        unit_type_ = lang::makeHandled<lang::Type>(Owned<lang::TypeDefinition>(*(new UnitType())));

    return unit_type_.value();
}

bool lang::Context::isContainingRuntime() const
{
    return contains_runtime_;
}

bool lang::Context::validateRuntimeDependency(lang::Location location, ValidationLogger& validation_logger) const
{
    if (isContainingRuntime()) return true;

    validation_logger.logError("Not allowed in runtime-excluded project", location);

    return false;
}

void lang::Context::setCurrentDescriptionSource(Optional<DescriptionSource> source)
{
    current_description_source_ = std::move(source);
}

Optional<std::string> lang::Context::getCurrentDescriptionSourceName() const
{
    if (current_description_source_.hasValue()) return current_description_source_.value().name;
    else return std::nullopt;
}

bool lang::Context::isCurrentDescriptionSourcePublic() const
{
    assert(current_description_source_.hasValue());
    return current_description_source_.value().is_public;
}
