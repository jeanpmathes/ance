#include "SizeType.h"

#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/IntegerType.h"
#include "lang/type/VoidType.h"
#include "lang/utility/Values.h"
#include "compiler/Application.h"
#include "compiler/CompileContext.h"

lang::SizeType::SizeType(std::string name, llvm::Type*& backing) : TypeDefinition(std::move(name)), backing_(backing) {}

llvm::Constant* lang::SizeType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantInt::get(getContentType(c), 0, false);
}

llvm::Type* lang::SizeType::getContentType(llvm::LLVMContext&)
{
    return backing_;
}

bool lang::SizeType::isImplicitlyConvertibleTo(lang::ResolvingHandle<lang::Type> other)
{
    return self()->isSizeType() && other->isDiffType();
}

bool lang::SizeType::validateImplicitConversion(lang::ResolvingHandle<lang::Type>, lang::Location, ValidationLogger&)
{
    return true;
}

std::shared_ptr<lang::Value> lang::SizeType::buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                                     std::shared_ptr<Value>            value,
                                                                     CompileContext*                   context)
{
    value->buildContentValue(context);
    llvm::Value* content_value = value->getContentValue();

    llvm::Value* converted_value =
        context->ir()->CreateIntCast(content_value, other->getContentType(*context->llvmContext()), false);
    llvm::Value* native_content_value = lang::Values::contentToNative(other, converted_value, context);

    return std::make_shared<WrappedNativeValue>(other, native_content_value);
}

bool lang::SizeType::isOperatorDefined(lang::BinaryOperator, lang::ResolvingHandle<lang::Type> other)
{
    if (isSizeType()) return other->isSizeType();
    if (isDiffType()) return other->isDiffType();

    return false;
}

lang::ResolvingHandle<lang::Type> lang::SizeType::getOperatorResultType(lang::BinaryOperator op,
                                                                        lang::ResolvingHandle<lang::Type>)
{
    if (op.isArithmetic()) return self();
    if (op.isRelational() || op.isEquality()) return lang::IntegerType::getBooleanType();

    return lang::VoidType::get();
}

bool lang::SizeType::validateOperator(lang::BinaryOperator,
                                      lang::ResolvingHandle<lang::Type>,
                                      lang::Location,
                                      lang::Location,
                                      ValidationLogger&)
{
    return true;
}

std::shared_ptr<lang::Value> lang::SizeType::buildOperator(lang::BinaryOperator   op,
                                                           std::shared_ptr<Value> left,
                                                           std::shared_ptr<Value> right,
                                                           CompileContext*        context)
{
    left->buildContentValue(context);
    right->buildContentValue(context);

    llvm::Value* left_value  = left->getContentValue();
    llvm::Value* right_value = right->getContentValue();

    llvm::Value* result;

    switch (op)
    {
        case lang::BinaryOperator::ADDITION:
            result = context->ir()->CreateAdd(left_value, right_value);
            break;
        case lang::BinaryOperator::SUBTRACTION:
            result = context->ir()->CreateSub(left_value, right_value);
            break;
        case lang::BinaryOperator::MULTIPLICATION:
            result = context->ir()->CreateMul(left_value, right_value);
            break;
        case lang::BinaryOperator::DIVISION:
            if (isSizeType()) result = context->ir()->CreateUDiv(left_value, right_value);
            if (isDiffType()) result = context->ir()->CreateSDiv(left_value, right_value);
            break;
        case lang::BinaryOperator::REMAINDER:
            if (isSizeType()) result = context->ir()->CreateURem(left_value, right_value);
            if (isDiffType()) result = context->ir()->CreateSRem(left_value, right_value);
            break;
        case lang::BinaryOperator::LESS_THAN:
            if (isSizeType()) result = context->ir()->CreateICmpULT(left_value, right_value);
            if (isDiffType()) result = context->ir()->CreateICmpSLT(left_value, right_value);
            break;
        case lang::BinaryOperator::LESS_THAN_OR_EQUAL:
            if (isSizeType()) result = context->ir()->CreateICmpULE(left_value, right_value);
            if (isDiffType()) result = context->ir()->CreateICmpSLE(left_value, right_value);
            break;
        case lang::BinaryOperator::GREATER_THAN:
            if (isSizeType()) result = context->ir()->CreateICmpUGT(left_value, right_value);
            if (isDiffType()) result = context->ir()->CreateICmpSGT(left_value, right_value);
            break;
        case lang::BinaryOperator::GREATER_THAN_OR_EQUAL:
            if (isSizeType()) result = context->ir()->CreateICmpUGE(left_value, right_value);
            if (isDiffType()) result = context->ir()->CreateICmpSGE(left_value, right_value);
            break;
        case lang::BinaryOperator::EQUAL:
            result = context->ir()->CreateICmpEQ(left_value, right_value);
            break;
        case lang::BinaryOperator::NOT_EQUAL:
            result = context->ir()->CreateICmpNE(left_value, right_value);
            break;
    }

    lang::ResolvingHandle<lang::Type> result_type   = getOperatorResultType(op, right->type());
    llvm::Value*                      native_result = lang::Values::contentToNative(result_type, result, context);
    return std::make_shared<lang::WrappedNativeValue>(result_type, native_result);
}

bool lang::SizeType::isSizeType() const
{
    return (backing_ == size_backing_type_);
}

bool lang::SizeType::isDiffType() const
{
    return (backing_ == diff_backing_type_);
}

llvm::Value* lang::SizeType::buildValue(llvm::TypeSize size)
{
    return llvm::ConstantInt::get(size_backing_type_, size.getFixedSize(), false);
}

std::string lang::SizeType::createMangledName()
{
    return getName();
}

llvm::DIType* lang::SizeType::createDebugType(CompileContext* context)
{
    const llvm::DataLayout& dl = context->module()->getDataLayout();

    std::string           name         = getName();
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

    size_width_ = app.getBitness();
    diff_width_ = size_width_ * 2;

    size_backing_type_ = llvm::Type::getIntNTy(c, size_width_);
    diff_backing_type_ = llvm::Type::getIntNTy(c, diff_width_);
}

lang::ResolvingHandle<lang::Type> lang::SizeType::getSize()
{
    static lang::ResolvingHandle<lang::Type> instance =
        lang::makeHandled<lang::Type>(std::unique_ptr<lang::TypeDefinition>(new SizeType("size", size_backing_type_)));
    return instance;
}

unsigned int lang::SizeType::getSizeWidth()
{
    return size_width_;
}

lang::ResolvingHandle<lang::Type> lang::SizeType::getDiff()
{
    static lang::ResolvingHandle<lang::Type> instance =
        lang::makeHandled<lang::Type>(std::unique_ptr<lang::TypeDefinition>(new SizeType("diff", diff_backing_type_)));
    return instance;
}

unsigned int lang::SizeType::getDiffWidth()
{
    return diff_width_;
}