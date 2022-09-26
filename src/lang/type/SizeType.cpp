#include "SizeType.h"

#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/type/BooleanType.h"
#include "lang/utility/Values.h"

lang::SizeType::SizeType(std::string name, Kind kind) : TypeDefinition(lang::Identifier::from(name)), kind_(kind) {}

bool lang::SizeType::isOperatorDefined(lang::BinaryOperator, lang::ResolvingHandle<lang::Type> other)
{
    other = lang::Type::getReferencedType(other);

    if (isSizeType()) return other->isSizeType();
    if (isDiffType()) return other->isDiffType();

    return false;
}

lang::ResolvingHandle<lang::Type> lang::SizeType::getOperatorResultType(lang::BinaryOperator op,
                                                                        lang::ResolvingHandle<lang::Type>)
{
    if (op.isArithmetic()) return self()->getActualType();
    if (op.isRelational() || op.isEquality()) return lang::BooleanType::get();

    return lang::Type::getUndefined();
}

bool lang::SizeType::validateOperator(lang::BinaryOperator,
                                      lang::ResolvingHandle<lang::Type>,
                                      lang::Location,
                                      lang::Location,
                                      ValidationLogger&) const
{
    return true;
}

std::shared_ptr<lang::Value> lang::SizeType::buildOperator(lang::BinaryOperator   op,
                                                           std::shared_ptr<Value> left,
                                                           std::shared_ptr<Value> right,
                                                           CompileContext&        context)
{
    right = lang::Type::getValueOrReferencedValue(right, context);

    left->buildContentValue(context);
    right->buildContentValue(context);

    llvm::Value* left_value  = left->getContentValue();
    llvm::Value* right_value = right->getContentValue();

    llvm::Value* result = nullptr;

    switch (op)
    {
        case lang::BinaryOperator::ADDITION:
            result = context.ir()->CreateAdd(left_value, right_value, left_value->getName() + ".add");
            break;
        case lang::BinaryOperator::SUBTRACTION:
            result = context.ir()->CreateSub(left_value, right_value, left_value->getName() + ".sub");
            break;
        case lang::BinaryOperator::MULTIPLICATION:
            result = context.ir()->CreateMul(left_value, right_value, left_value->getName() + ".mul");
            break;
        case lang::BinaryOperator::DIVISION:
            if (isSizeType())
                result = context.ir()->CreateUDiv(left_value, right_value, left_value->getName() + ".udiv");
            if (isDiffType())
                result = context.ir()->CreateSDiv(left_value, right_value, left_value->getName() + ".sdiv");
            break;
        case lang::BinaryOperator::REMAINDER:
            if (isSizeType())
                result = context.ir()->CreateURem(left_value, right_value, left_value->getName() + ".urem");
            if (isDiffType())
                result = context.ir()->CreateSRem(left_value, right_value, left_value->getName() + ".srem");
            break;
        case lang::BinaryOperator::LESS_THAN:
            if (isSizeType())
                result = context.ir()->CreateICmpULT(left_value, right_value, left_value->getName() + ".icmp");
            if (isDiffType())
                result = context.ir()->CreateICmpSLT(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::LESS_THAN_OR_EQUAL:
            if (isSizeType())
                result = context.ir()->CreateICmpULE(left_value, right_value, left_value->getName() + ".icmp");
            if (isDiffType())
                result = context.ir()->CreateICmpSLE(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::GREATER_THAN:
            if (isSizeType())
                result = context.ir()->CreateICmpUGT(left_value, right_value, left_value->getName() + ".icmp");
            if (isDiffType())
                result = context.ir()->CreateICmpSGT(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::GREATER_THAN_OR_EQUAL:
            if (isSizeType())
                result = context.ir()->CreateICmpUGE(left_value, right_value, left_value->getName() + ".icmp");
            if (isDiffType())
                result = context.ir()->CreateICmpSGE(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::EQUAL:
            result = context.ir()->CreateICmpEQ(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::NOT_EQUAL:
            result = context.ir()->CreateICmpNE(left_value, right_value, left_value->getName() + ".icmp");
            break;
    }

    lang::ResolvingHandle<lang::Type> result_type   = getOperatorResultType(op, right->type());
    llvm::Value*                      native_result = lang::Values::contentToNative(result_type, result, context);
    return std::make_shared<lang::WrappedNativeValue>(result_type, native_result);
}

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
