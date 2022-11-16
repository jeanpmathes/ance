#include "NullPointerType.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/type/Type.h"
#include "lang/utility/Values.h"

lang::NullPointerType::NullPointerType() : TypeDefinition(lang::Identifier::from("nullptr")) {}

bool lang::NullPointerType::isNullValueType() const
{
    return true;
}

bool lang::NullPointerType::isImplicitlyConvertibleTo(lang::ResolvingHandle<lang::Type> other)
{
    return other->isAddressType();
}

bool lang::NullPointerType::validateImplicitConversion(lang::ResolvingHandle<lang::Type>,
                                                       lang::Location,
                                                       ValidationLogger&) const
{
    return true;
}

std::shared_ptr<lang::Value> lang::NullPointerType::buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                                            std::shared_ptr<Value>,
                                                                            CompileContext& context)
{
    llvm::Type* other_type = other->getContentType(*context.llvmContext());
    assert(other_type->isPointerTy());

    llvm::Value* null         = llvm::ConstantPointerNull::get(llvm::dyn_cast<llvm::PointerType>(other_type));
    llvm::Value* native_value = lang::Values::contentToNative(other, null, context);

    return std::make_shared<lang::WrappedNativeValue>(other, native_value);
}

llvm::Constant* lang::NullPointerType::getDefaultContent(llvm::Module& m)
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

llvm::DIType* lang::NullPointerType::createDebugType(CompileContext& context)
{
    llvm::DataLayout const& dl = context.module()->getDataLayout();

    uint64_t size_in_bits = dl.getTypeSizeInBits(getContentType(*context.llvmContext()));

    std::string name     = std::string(this->name().text());
    auto        encoding = llvm::dwarf::DW_ATE_address;

    llvm::DIType* di_type = context.di()->createBasicType(name, size_in_bits, encoding);

    return di_type;
}

lang::ResolvingHandle<lang::Type> lang::NullPointerType::get()
{
    static lang::ResolvingHandle<lang::Type> instance =
        lang::makeHandled<lang::Type>(std::unique_ptr<lang::TypeDefinition>(new NullPointerType()));
    return instance;
}

std::optional<lang::ResolvingHandle<lang::Type>> lang::NullPointerType::getPointeeType() const
{
    return std::nullopt;
}
