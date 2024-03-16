#include "SizeType.h"

#include "compiler/CompileContext.h"
#include "compiler/Unit.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/type/BooleanType.h"

lang::SizeType::SizeType(std::string const& name, Kind kind) : TypeDefinition(lang::Identifier::like(name)), kind_(kind)
{}

bool lang::SizeType::isSizeType() const
{
    return (kind_ == SIZE_KIND);
}

bool lang::SizeType::isDiffType() const
{
    return (kind_ == DIFF_KIND);
}

std::string lang::SizeType::createMangledName() const
{
    return std::string(name().text());
}

void lang::SizeType::init(Unit& app)
{
    size_width_ = static_cast<unsigned int>(std::max(app.getTarget().getPointerSize() * 8, MINIMUM_BIT_SIZE));
    diff_width_ = size_width_ * 2;
}

unsigned int lang::SizeType::getSizeWidth()
{
    return size_width_;
}

unsigned int lang::SizeType::getDiffWidth()
{
    return diff_width_;
}

Optional<size_t> lang::SizeType::getBitSize() const
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

lang::ResolvingHandle<lang::Type> lang::SizeType::clone(lang::Context& new_context) const
{
    if (kind_ == SIZE_KIND) return new_context.getSizeType();
    if (kind_ == DIFF_KIND) return new_context.getDiffType();

    assert(false);
    throw std::logic_error("Invalid size type kind");
}
