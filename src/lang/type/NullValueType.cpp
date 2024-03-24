#include "NullValueType.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/type/Type.h"

lang::NullValueType::NullValueType() : TypeDefinition(lang::Identifier::like("nullptr")) {}

bool lang::NullValueType::isNullValueType() const
{
    return true;
}

StateCount lang::NullValueType::getStateCount() const
{
    return StateCount::unit();
}

bool lang::NullValueType::isImplicitlyConvertibleTo(lang::Type const& other) const
{
    return other.isAddressType();
}

bool lang::NullValueType::validateImplicitConversion(lang::Type const&, lang::Location, ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::NullValueType::buildImplicitConversion(lang::Type const& other,
                                                                 Shared<lang::Value>,
                                                                 Execution& exec) const
{
    return exec.getNull(other);
}

std::string lang::NullValueType::createMangledName() const
{
    return "nullptr";
}

void lang::NullValueType::registerExecutionType(Execution& exec) const
{
    return exec.registerOpaqueAddressType(self());
}

Optional<lang::ResolvingHandle<lang::Type>> lang::NullValueType::getPointeeType()
{
    return std::nullopt;
}

lang::Type const* lang::NullValueType::getPointeeType() const
{
    return nullptr;
}

bool lang::NullValueType::isTriviallyDefaultConstructible() const
{
    return true;
}

bool lang::NullValueType::isTriviallyCopyConstructible() const
{
    return true;
}
bool lang::NullValueType::isTriviallyDestructible() const
{
    return true;
}

lang::ResolvingHandle<lang::Type> lang::NullValueType::clone(lang::Context& new_context) const
{
    return new_context.getNullValueType();
}
