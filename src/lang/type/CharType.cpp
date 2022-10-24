#include "CharType.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/construct/value/Value.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/type/Type.h"
#include "lang/utility/Values.h"

lang::CharType::CharType() : TypeDefinition(lang::Identifier::from("char")) {}

StateCount lang::CharType::getStateCount() const
{
    size_t state_count = 1ULL << SIZE_IN_BITS;
    return state_count;
}

bool lang::CharType::isCharType() const
{
    return true;
}

llvm::Constant* lang::CharType::getDefaultContent(llvm::Module& m)
{
    return llvm::ConstantInt::get(getContentType(m.getContext()), 0, false);
}

llvm::Type* lang::CharType::getContentType(llvm::LLVMContext& c) const
{
    return llvm::Type::getIntNTy(c, static_cast<unsigned>(SIZE_IN_BITS));
}

bool lang::CharType::isTriviallyDefaultConstructible() const
{
    return true;
}

bool lang::CharType::isTriviallyCopyConstructible() const
{
    return true;
}

bool lang::CharType::isTriviallyDestructible() const
{
    return true;
}

std::string lang::CharType::createMangledName() const
{
    return "c";
}

llvm::DIType* lang::CharType::createDebugType(CompileContext& context)
{
    std::string name = std::string(this->name().text());

    return context.di()->createBasicType(name, SIZE_IN_BITS, llvm::dwarf::DW_ATE_unsigned_char);
}

lang::ResolvingHandle<lang::Type> lang::CharType::get()
{
    static lang::ResolvingHandle<lang::Type> instance =
        lang::makeHandled<lang::Type>(std::unique_ptr<lang::TypeDefinition>(new CharType()));
    return instance;
}
