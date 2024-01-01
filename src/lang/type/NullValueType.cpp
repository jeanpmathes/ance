#include "NullValueType.h"

#include "compiler/CompileContext.h"
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

Shared<lang::Value> lang::NullValueType::buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                                 Shared<Value>,
                                                                 CompileContext& context)
{
    return context.exec().getNull(other);
}

llvm::Constant* lang::NullValueType::getDefaultContent(CompileContext& context) const
{
    return llvm::ConstantPointerNull::get(
        llvm::PointerType::get(llvm::Type::getInt8Ty(context.exec().llvmContext()), 0));
}

llvm::Type* lang::NullValueType::getContentType(CompileContext& context) const
{
    return llvm::PointerType::get(llvm::Type::getInt8Ty(context.exec().llvmContext()), 0);
}

std::string lang::NullValueType::createMangledName() const
{
    return "nullptr";
}

Execution::Type lang::NullValueType::createDebugType(CompileContext& context) const
{
    return context.exec().registerOpaqueAddressType(self());
}

Optional<lang::ResolvingHandle<lang::Type>> lang::NullValueType::getPointeeType()
{
    return std::nullopt;
}

lang::Type const* lang::NullValueType::getPointeeType() const
{
    return nullptr;
}

lang::ResolvingHandle<lang::Type> lang::NullValueType::clone(lang::Context& new_context) const
{
    return new_context.getNullValueType();
}