#include "NullPointerType.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/type/Type.h"
#include "lang/utility/Values.h"

lang::NullPointerType::NullPointerType() : TypeDefinition(lang::Identifier::like("nullptr")) {}

bool lang::NullPointerType::isNullValueType() const
{
    return true;
}

bool lang::NullPointerType::isImplicitlyConvertibleTo(lang::Type const& other) const
{
    return other.isAddressType();
}

bool lang::NullPointerType::validateImplicitConversion(lang::Type const&, lang::Location, ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::NullPointerType::buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                                   Shared<Value>,
                                                                   CompileContext& context)
{
    llvm::Type* other_type = other->getContentType(context.llvmContext());
    assert(other_type->isPointerTy());

    llvm::Value* null         = llvm::ConstantPointerNull::get(llvm::dyn_cast<llvm::PointerType>(other_type));
    llvm::Value* native_value = lang::values::contentToNative(other, null, context);

    return makeShared<lang::WrappedNativeValue>(other, native_value);
}

llvm::Constant* lang::NullPointerType::getDefaultContent(llvm::Module& m) const
{
    return llvm::ConstantPointerNull::get(llvm::PointerType::get(llvm::Type::getInt8Ty(m.getContext()), 0));
}

llvm::Type* lang::NullPointerType::getContentType(llvm::LLVMContext& c) const
{
    return llvm::PointerType::get(llvm::Type::getInt8Ty(c), 0);
}

std::string lang::NullPointerType::createMangledName() const
{
    return "nullptr";
}

llvm::DIType* lang::NullPointerType::createDebugType(CompileContext& context) const
{
    llvm::DataLayout const& dl = context.llvmModule().getDataLayout();

    uint64_t const size_in_bits = dl.getTypeSizeInBits(getContentType(context.llvmContext()));

    std::string const name     = std::string(this->name().text());
    auto              encoding = llvm::dwarf::DW_ATE_address;

    llvm::DIType* di_type = context.di().createBasicType(name, size_in_bits, encoding);

    return di_type;
}

lang::ResolvingHandle<lang::Type> lang::NullPointerType::get()
{
#define MAKE lang::makeHandled<lang::Type>(Owned<lang::TypeDefinition>(*(new NullPointerType())))

    static lang::ResolvingHandle<lang::Type> instance = MAKE;

    if (!instance.valid()) instance = MAKE;

    return instance;
#undef MAKE
}

Optional<lang::ResolvingHandle<lang::Type>> lang::NullPointerType::getPointeeType()
{
    return std::nullopt;
}

lang::Type const* lang::NullPointerType::getPointeeType() const
{
    return nullptr;
}

lang::ResolvingHandle<lang::Type> lang::NullPointerType::clone() const
{
    return get();
}
