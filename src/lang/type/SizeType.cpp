#include "SizeType.h"

#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/type/BooleanType.h"
#include "lang/type/VoidType.h"
#include "lang/utility/Values.h"

lang::SizeType::SizeType(std::string name, Kind kind, llvm::Type*& backing)
    : TypeDefinition(lang::Identifier::from(name))
    , kind_(kind)
    , backing_(backing)
{}

StateCount lang::SizeType::getStateCount() const
{
    return SpecialCount::PLATFORM_DEPENDENT;
}

llvm::Constant* lang::SizeType::getDefaultContent(llvm::Module& m)
{
    return llvm::ConstantInt::get(getContentType(m.getContext()), 0, false);
}

llvm::Type* lang::SizeType::getContentType(llvm::LLVMContext&) const
{
    return backing_;
}

bool lang::SizeType::isImplicitlyConvertibleTo(lang::ResolvingHandle<lang::Type> other)
{
    return self()->isSizeType() && other->isDiffType();
}

bool lang::SizeType::validateImplicitConversion(lang::ResolvingHandle<lang::Type>,
                                                lang::Location,
                                                ValidationLogger&) const
{
    return true;
}

std::shared_ptr<lang::Value> lang::SizeType::buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                                     std::shared_ptr<Value>            value,
                                                                     CompileContext*                   context)
{
    value->buildContentValue(context);
    llvm::Value* content_value = value->getContentValue();

    llvm::Value* converted_value      = context->ir()->CreateIntCast(content_value,
                                                                other->getContentType(*context->llvmContext()),
                                                                false,
                                                                content_value->getName() + ".icast");
    llvm::Value* native_content_value = lang::Values::contentToNative(other, converted_value, context);

    return std::make_shared<WrappedNativeValue>(other, native_content_value);
}

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

    return lang::VoidType::get();
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
                                                           CompileContext*        context)
{
    right = lang::Type::getValueOrReferencedValue(right, context);

    left->buildContentValue(context);
    right->buildContentValue(context);

    llvm::Value* left_value  = left->getContentValue();
    llvm::Value* right_value = right->getContentValue();

    llvm::Value* result;

    switch (op)
    {
        case lang::BinaryOperator::ADDITION:
            result = context->ir()->CreateAdd(left_value, right_value, left_value->getName() + ".add");
            break;
        case lang::BinaryOperator::SUBTRACTION:
            result = context->ir()->CreateSub(left_value, right_value, left_value->getName() + ".sub");
            break;
        case lang::BinaryOperator::MULTIPLICATION:
            result = context->ir()->CreateMul(left_value, right_value, left_value->getName() + ".mul");
            break;
        case lang::BinaryOperator::DIVISION:
            if (isSizeType())
                result = context->ir()->CreateUDiv(left_value, right_value, left_value->getName() + ".udiv");
            if (isDiffType())
                result = context->ir()->CreateSDiv(left_value, right_value, left_value->getName() + ".sdiv");
            break;
        case lang::BinaryOperator::REMAINDER:
            if (isSizeType())
                result = context->ir()->CreateURem(left_value, right_value, left_value->getName() + ".urem");
            if (isDiffType())
                result = context->ir()->CreateSRem(left_value, right_value, left_value->getName() + ".srem");
            break;
        case lang::BinaryOperator::LESS_THAN:
            if (isSizeType())
                result = context->ir()->CreateICmpULT(left_value, right_value, left_value->getName() + ".icmp");
            if (isDiffType())
                result = context->ir()->CreateICmpSLT(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::LESS_THAN_OR_EQUAL:
            if (isSizeType())
                result = context->ir()->CreateICmpULE(left_value, right_value, left_value->getName() + ".icmp");
            if (isDiffType())
                result = context->ir()->CreateICmpSLE(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::GREATER_THAN:
            if (isSizeType())
                result = context->ir()->CreateICmpUGT(left_value, right_value, left_value->getName() + ".icmp");
            if (isDiffType())
                result = context->ir()->CreateICmpSGT(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::GREATER_THAN_OR_EQUAL:
            if (isSizeType())
                result = context->ir()->CreateICmpUGE(left_value, right_value, left_value->getName() + ".icmp");
            if (isDiffType())
                result = context->ir()->CreateICmpSGE(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::EQUAL:
            result = context->ir()->CreateICmpEQ(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::NOT_EQUAL:
            result = context->ir()->CreateICmpNE(left_value, right_value, left_value->getName() + ".icmp");
            break;
    }

    lang::ResolvingHandle<lang::Type> result_type   = getOperatorResultType(op, right->type());
    llvm::Value*                      native_result = lang::Values::contentToNative(result_type, result, context);
    return std::make_shared<lang::WrappedNativeValue>(result_type, native_result);
}

bool lang::SizeType::acceptOverloadRequest(const std::vector<lang::ResolvingHandle<lang::Type>>& parameters)
{
    if (parameters.size() == 1)
    {
        if (parameters[0]->isIntegerType()) return true;
        if (parameters[0]->isSizeType()) return true;
        if (parameters[0]->isDiffType()) return true;
        if (parameters[0]->isBooleanType()) return true;
    }

    return false;
}

void lang::SizeType::buildRequestedOverload(const std::vector<lang::ResolvingHandle<lang::Type>>& parameters,
                                            lang::PredefinedFunction&                             function,
                                            CompileContext*                                       context)
{
    llvm::Function* native_function;
    std::tie(std::ignore, native_function) = function.getNativeRepresentation();

    auto build_integer_conversion_ctor = [&](bool is_signed) {
        llvm::BasicBlock* block = llvm::BasicBlock::Create(*context->llvmContext(), "block", native_function);
        context->ir()->SetInsertPoint(block);
        {
            llvm::Value* original = native_function->getArg(0);

            llvm::Value* converted = context->ir()->CreateIntCast(original,
                                                                  getContentType(*context->llvmContext()),
                                                                  is_signed,
                                                                  original->getName() + ".icast");
            context->ir()->CreateRet(converted);
        }
    };

    if (parameters.size() == 1)
    {
        if (parameters[0]->isIntegerType()) { build_integer_conversion_ctor(parameters[0]->isSigned()); }
        if (parameters[0]->isSizeType()) { build_integer_conversion_ctor(false); }
        if (parameters[0]->isDiffType()) { build_integer_conversion_ctor(true); }
        if (parameters[0]->isBooleanType()) { build_integer_conversion_ctor(false); }
    }
}

bool lang::SizeType::isSizeType() const
{
    return (kind_ == SIZE_KIND);
}

bool lang::SizeType::isDiffType() const
{
    return (kind_ == DIFF_KIND);
}

llvm::Value* lang::SizeType::buildContentValue(llvm::TypeSize size)
{
    return llvm::ConstantInt::get(size_backing_type_, size.getFixedSize(), false);
}

bool lang::SizeType::isTriviallyDefaultConstructible() const
{
    return true;
}

bool lang::SizeType::isTriviallyCopyConstructible() const
{
    return true;
}

bool lang::SizeType::isTriviallyDestructible() const
{
    return true;
}

std::string lang::SizeType::createMangledName() const
{
    return std::string(name().text());
}

llvm::DIType* lang::SizeType::createDebugType(CompileContext* context)
{
    const llvm::DataLayout& dl = context->module()->getDataLayout();

    std::string           name         = std::string(this->name().text());
    uint64_t              size_in_bits = dl.getTypeSizeInBits(getContentType(*context->llvmContext()));
    llvm::dwarf::TypeKind encoding;

    if (backing_ == size_backing_type_) encoding = llvm::dwarf::DW_ATE_unsigned;
    if (backing_ == diff_backing_type_) encoding = llvm::dwarf::DW_ATE_signed;

    return context->di()->createBasicType(name, size_in_bits, encoding);
}

void lang::SizeType::init(llvm::LLVMContext& c, Application& app)
{
    assert(!size_backing_type_);
    assert(!diff_backing_type_);

    size_width_ = std::max(app.getBitness(), static_cast<unsigned int>(MINIMUM_BIT_SIZE));
    diff_width_ = size_width_ * 2;

    size_backing_type_ = llvm::Type::getIntNTy(c, size_width_);
    diff_backing_type_ = llvm::Type::getIntNTy(c, diff_width_);
}

lang::ResolvingHandle<lang::Type> lang::SizeType::getSize()
{
    static lang::ResolvingHandle<lang::Type> instance = lang::makeHandled<lang::Type>(
        std::unique_ptr<lang::TypeDefinition>(new SizeType("size", SIZE_KIND, size_backing_type_)));
    return instance;
}

unsigned int lang::SizeType::getSizeWidth()
{
    return size_width_;
}

lang::ResolvingHandle<lang::Type> lang::SizeType::getDiff()
{
    static lang::ResolvingHandle<lang::Type> instance = lang::makeHandled<lang::Type>(
        std::unique_ptr<lang::TypeDefinition>(new SizeType("diff", DIFF_KIND, diff_backing_type_)));
    return instance;
}

unsigned int lang::SizeType::getDiffWidth()
{
    return diff_width_;
}
