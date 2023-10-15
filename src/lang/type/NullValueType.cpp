#include "NullValueType.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/type/Type.h"
#include "lang/utility/Values.h"

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
    llvm::Type* other_type = other->getContentType(context.llvmContext());
    assert(other_type->isPointerTy());

    llvm::Value* null         = llvm::ConstantPointerNull::get(llvm::dyn_cast<llvm::PointerType>(other_type));
    llvm::Value* native_value = lang::values::contentToNative(other, null, context);

    return makeShared<lang::WrappedNativeValue>(other, native_value);
}

llvm::Constant* lang::NullValueType::getDefaultContent(llvm::Module& m) const
{
    return llvm::ConstantPointerNull::get(llvm::PointerType::get(llvm::Type::getInt8Ty(m.getContext()), 0));
}

llvm::Type* lang::NullValueType::getContentType(llvm::LLVMContext& c) const
{
    return llvm::PointerType::get(llvm::Type::getInt8Ty(c), 0);
}

std::string lang::NullValueType::createMangledName() const
{
    return "nullptr";
}

llvm::DIType* lang::NullValueType::createDebugType(CompileContext& context) const
{
    llvm::DataLayout const& dl = context.llvmModule().getDataLayout();

    uint64_t const size_in_bits = dl.getTypeSizeInBits(getContentType(context.llvmContext()));

    std::string const name     = std::string(this->name().text());
    auto              encoding = llvm::dwarf::DW_ATE_address;

    llvm::DIType* di_type = context.di().createBasicType(name, size_in_bits, encoding);

    return di_type;
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
