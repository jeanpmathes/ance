#include "OpaquePointerType.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/type/Type.h"

lang::OpaquePointerType::OpaquePointerType() : TypeDefinition(lang::Identifier::like("ptr")) {}

bool lang::OpaquePointerType::isOpaquePointerType() const
{
    return true;
}

std::string lang::OpaquePointerType::createMangledName() const
{
    return "ptr";
}

void lang::OpaquePointerType::registerExecutionType(Execution& exec) const
{
    return exec.registerOpaqueAddressType(self());
}

Optional<lang::ResolvingHandle<lang::Type>> lang::OpaquePointerType::getPointeeType()
{
    return std::nullopt;
}

lang::Type const* lang::OpaquePointerType::getPointeeType() const
{
    return nullptr;
}

bool lang::OpaquePointerType::isTriviallyDefaultConstructible() const
{
    return true;
}

bool lang::OpaquePointerType::isTriviallyCopyConstructible() const
{
    return true;
}

bool lang::OpaquePointerType::isTriviallyDestructible() const
{
    return true;
}

lang::ResolvingHandle<lang::Type> lang::OpaquePointerType::clone(lang::Context& new_context) const
{
    return new_context.getOpaquePointerType();
}
