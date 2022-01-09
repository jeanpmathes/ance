#include "SizeType.h"

#include "ance/construct/value/WrappedNativeValue.h"
#include "ance/scope/GlobalScope.h"
#include "ance/type/IntegerType.h"
#include "ance/type/VoidType.h"
#include "ance/utility/Values.h"
#include "compiler/Application.h"
#include "compiler/CompileContext.h"

ance::SizeType::SizeType(std::string name, llvm::Type*& backing) : TypeDefinition(std::move(name)), backing_(backing) {}

llvm::Constant* ance::SizeType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantInt::get(getContentType(c), 0, false);
}

llvm::Type* ance::SizeType::getContentType(llvm::LLVMContext&)
{
    return backing_;
}

bool ance::SizeType::isOperatorDefined(BinaryOperator, ance::ResolvingHandle<ance::Type> other)
{
    if (isSizeType()) return other->isSizeType();
    if (isDiffType()) return other->isDiffType();

    return false;
}

ance::ResolvingHandle<ance::Type> ance::SizeType::getOperatorResultType(BinaryOperator op,
                                                                        ance::ResolvingHandle<ance::Type>)
{
    if (op.isArithmetic()) return self();
    if (op.isRelational() || op.isEquality()) return ance::IntegerType::getBooleanType();

    return ance::VoidType::get();
}

bool ance::SizeType::validateOperator(BinaryOperator,
                                      ance::ResolvingHandle<ance::Type>,
                                      ance::Location,
                                      ance::Location,
                                      ValidationLogger&)
{
    return true;
}

std::shared_ptr<ance::Value> ance::SizeType::buildOperator(BinaryOperator         op,
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
        case BinaryOperator::ADDITION:
            result = context->ir()->CreateAdd(left_value, right_value);
            break;
        case BinaryOperator::SUBTRACTION:
            result = context->ir()->CreateSub(left_value, right_value);
            break;
        case BinaryOperator::MULTIPLICATION:
            result = context->ir()->CreateMul(left_value, right_value);
            break;
        case BinaryOperator::DIVISION:
            if (isSizeType()) result = context->ir()->CreateUDiv(left_value, right_value);
            if (isDiffType()) result = context->ir()->CreateSDiv(left_value, right_value);
            break;
        case BinaryOperator::REMAINDER:
            if (isSizeType()) result = context->ir()->CreateURem(left_value, right_value);
            if (isDiffType()) result = context->ir()->CreateSRem(left_value, right_value);
            break;
        case BinaryOperator::LESS_THAN:
            if (isSizeType()) result = context->ir()->CreateICmpULT(left_value, right_value);
            if (isDiffType()) result = context->ir()->CreateICmpSLT(left_value, right_value);
            break;
        case BinaryOperator::LESS_THAN_OR_EQUAL:
            if (isSizeType()) result = context->ir()->CreateICmpULE(left_value, right_value);
            if (isDiffType()) result = context->ir()->CreateICmpSLE(left_value, right_value);
            break;
        case BinaryOperator::GREATER_THAN:
            if (isSizeType()) result = context->ir()->CreateICmpUGT(left_value, right_value);
            if (isDiffType()) result = context->ir()->CreateICmpSGT(left_value, right_value);
            break;
        case BinaryOperator::GREATER_THAN_OR_EQUAL:
            if (isSizeType()) result = context->ir()->CreateICmpUGE(left_value, right_value);
            if (isDiffType()) result = context->ir()->CreateICmpSGE(left_value, right_value);
            break;
        case BinaryOperator::EQUAL:
            result = context->ir()->CreateICmpEQ(left_value, right_value);
            break;
        case BinaryOperator::NOT_EQUAL:
            result = context->ir()->CreateICmpNE(left_value, right_value);
            break;
    }

    ance::ResolvingHandle<ance::Type> result_type   = getOperatorResultType(op, right->type());
    llvm::Value*                      native_result = ance::Values::contentToNative(result_type, result, context);
    return std::make_shared<ance::WrappedNativeValue>(result_type, native_result);
}

bool ance::SizeType::isSizeType() const
{
    return (backing_ == size_backing_type_);
}

bool ance::SizeType::isDiffType() const
{
    return (backing_ == diff_backing_type_);
}

llvm::Value* ance::SizeType::buildValue(llvm::TypeSize size)
{
    return llvm::ConstantInt::get(size_backing_type_, size.getFixedSize(), false);
}

std::string ance::SizeType::createMangledName()
{
    return getName();
}

llvm::DIType* ance::SizeType::createDebugType(CompileContext* context)
{
    const llvm::DataLayout& dl = context->module()->getDataLayout();

    std::string           name         = getName();
    uint64_t              size_in_bits = dl.getTypeSizeInBits(getContentType(*context->llvmContext()));
    llvm::dwarf::TypeKind encoding;

    if (backing_ == size_backing_type_) encoding = llvm::dwarf::DW_ATE_unsigned;
    if (backing_ == diff_backing_type_) encoding = llvm::dwarf::DW_ATE_signed;

    return context->di()->createBasicType(name, size_in_bits, encoding);
}

void ance::SizeType::init(llvm::LLVMContext& c, Application& app)
{
    assert(!size_backing_type_);
    assert(!diff_backing_type_);

    size_width_ = app.getBitness();
    diff_width_ = size_width_ * 2;

    size_backing_type_ = llvm::Type::getIntNTy(c, size_width_);
    diff_backing_type_ = llvm::Type::getIntNTy(c, diff_width_);
}

ance::ResolvingHandle<ance::Type> ance::SizeType::getSize()
{
    static ance::ResolvingHandle<ance::Type> instance =
        ance::makeHandled<ance::Type>(std::unique_ptr<ance::TypeDefinition>(new SizeType("size", size_backing_type_)));
    return instance;
}

unsigned int ance::SizeType::getSizeWidth()
{
    return size_width_;
}

ance::ResolvingHandle<ance::Type> ance::SizeType::getDiff()
{
    static ance::ResolvingHandle<ance::Type> instance =
        ance::makeHandled<ance::Type>(std::unique_ptr<ance::TypeDefinition>(new SizeType("diff", diff_backing_type_)));
    return instance;
}

unsigned int ance::SizeType::getDiffWidth()
{
    return diff_width_;
}
