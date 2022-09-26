#include "SizeType.h"

#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/type/BooleanType.h"

lang::SizeType::SizeType(std::string name, Kind kind) : TypeDefinition(lang::Identifier::from(name)), kind_(kind) {}

bool lang::SizeType::isSizeType() const
{
    return (kind_ == SIZE_KIND);
}

bool lang::SizeType::isDiffType() const
{
    return (kind_ == DIFF_KIND);
}

llvm::Value* lang::SizeType::buildContentValue(llvm::TypeSize size, CompileContext& contex)
{
    return llvm::ConstantInt::get(getSize()->getContentType(*contex.llvmContext()), size.getFixedSize(), false);
}

std::string lang::SizeType::createMangledName() const
{
    return std::string(name().text());
}

void lang::SizeType::init(llvm::LLVMContext&, Application& app)
{
    assert(size_width_ == 0);
    assert(diff_width_ == 0);

    size_width_ = std::max(app.getBitness(), static_cast<unsigned int>(MINIMUM_BIT_SIZE));
    diff_width_ = size_width_ * 2;
}

lang::ResolvingHandle<lang::Type> lang::SizeType::getSize()
{
    static lang::ResolvingHandle<lang::Type> instance =
        lang::makeHandled<lang::Type>(std::unique_ptr<lang::TypeDefinition>(new SizeType("size", SIZE_KIND)));
    return instance;
}

unsigned int lang::SizeType::getSizeWidth()
{
    return size_width_;
}

lang::ResolvingHandle<lang::Type> lang::SizeType::getDiff()
{
    static lang::ResolvingHandle<lang::Type> instance =
        lang::makeHandled<lang::Type>(std::unique_ptr<lang::TypeDefinition>(new SizeType("diff", DIFF_KIND)));
    return instance;
}

unsigned int lang::SizeType::getDiffWidth()
{
    return diff_width_;
}

std::optional<size_t> lang::SizeType::getBitSize() const
{
    return std::nullopt;
}

size_t lang::SizeType::getNativeBitSize() const
{
    if (kind_ == SIZE_KIND) return size_width_;
    if (kind_ == DIFF_KIND) return diff_width_;

    assert(false);
    return 0;
}

bool lang::SizeType::isSigned() const
{
    return (kind_ == DIFF_KIND);
}

size_t lang::SizeType::getMinimumBitSize() const
{
    if (kind_ == SIZE_KIND) return MINIMUM_BIT_SIZE;
    if (kind_ == DIFF_KIND) return MINIMUM_DIFF_BIT_SIZE;

    assert(false);
    return 0;
}

std::string lang::SizeType::getSuffix() const
{
    if (kind_ == SIZE_KIND) return "size";
    if (kind_ == DIFF_KIND) return "diff";

    assert(false);
    return "";
}
