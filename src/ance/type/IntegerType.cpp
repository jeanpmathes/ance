#include "IntegerType.h"

#include "ance/construct/value/WrappedNativeValue.h"
#include "ance/scope/GlobalScope.h"
#include "ance/type/VoidType.h"
#include "ance/utility/Values.h"
#include "compiler/Application.h"
#include "compiler/CompileContext.h"

ance::IntegerType::IntegerType(uint64_t bit_size, bool is_signed)
    : TypeDefinition((is_signed ? "i" : "ui") + std::to_string(bit_size))
    , bit_size_(bit_size)
    , is_signed_(is_signed)
{}

bool ance::IntegerType::isIntegerType() const
{
    return true;
}

bool ance::IntegerType::isIntegerType(uint64_t bit_size, bool is_signed) const
{
    return (bit_size_ == bit_size) && (is_signed_ == is_signed);
}

llvm::Constant* ance::IntegerType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantInt::get(getContentType(c), 0, is_signed_);
}

llvm::Type* ance::IntegerType::getContentType(llvm::LLVMContext& c)
{
    if (!type_) { type_ = llvm::Type::getIntNTy(c, bit_size_); }

    return type_;
}

bool ance::IntegerType::isOperatorDefined(BinaryOperator, ance::ResolvingHandle<ance::Type> other)
{
    if (other->isIntegerType())
    {
        auto other_type = dynamic_cast<IntegerType*>(other->getActualType()->getDefinition());
        return this == other_type;
    }

    return false;
}

ance::ResolvingHandle<ance::Type> ance::IntegerType::getOperatorResultType(BinaryOperator op,
                                                                           ance::ResolvingHandle<ance::Type>)
{
    if (op.isArithmetic()) return self();
    if (op.isRelational() || op.isEquality()) return ance::IntegerType::getBooleanType();

    return ance::VoidType::get();
}

bool ance::IntegerType::validateOperator(BinaryOperator,
                                         ance::ResolvingHandle<ance::Type>,
                                         ance::Location,
                                         ance::Location,
                                         ValidationLogger&)
{
    return true;
}

std::shared_ptr<ance::Value> ance::IntegerType::buildOperator(BinaryOperator         op,
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
            if (is_signed_) result = context->ir()->CreateSDiv(left_value, right_value);
            else result = context->ir()->CreateUDiv(left_value, right_value);
            break;
        case BinaryOperator::REMAINDER:
            if (is_signed_) result = context->ir()->CreateSRem(left_value, right_value);
            else result = context->ir()->CreateURem(left_value, right_value);
            break;
        case BinaryOperator::LESS_THAN:
            if (is_signed_) result = context->ir()->CreateICmpSLT(left_value, right_value);
            else result = context->ir()->CreateICmpULT(left_value, right_value);
            break;
        case BinaryOperator::LESS_THAN_OR_EQUAL:
            if (is_signed_) result = context->ir()->CreateICmpSLE(left_value, right_value);
            else result = context->ir()->CreateICmpULE(left_value, right_value);
            break;
        case BinaryOperator::GREATER_THAN:
            if (is_signed_) result = context->ir()->CreateICmpSGT(left_value, right_value);
            else result = context->ir()->CreateICmpUGT(left_value, right_value);
            break;
        case BinaryOperator::GREATER_THAN_OR_EQUAL:
            if (is_signed_) result = context->ir()->CreateICmpSGE(left_value, right_value);
            else result = context->ir()->CreateICmpUGE(left_value, right_value);
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

std::string ance::IntegerType::createMangledName()
{
    return getName();
}

llvm::DIType* ance::IntegerType::createDebugType(CompileContext* context)
{
    const llvm::DataLayout& dl = context->module()->getDataLayout();

    std::string name         = getName();
    uint64_t    size_in_bits = dl.getTypeSizeInBits(getContentType(*context->llvmContext()));
    auto        encoding     = is_signed_ ? llvm::dwarf::DW_ATE_signed : llvm::dwarf::DW_ATE_unsigned;

    return context->di()->createBasicType(name, size_in_bits, encoding);
}

ance::TypeRegistry<std::pair<uint64_t, bool>>& ance::IntegerType::getIntegerTypes()
{
    static TypeRegistry<std::pair<uint64_t, bool>> integer_types;
    return integer_types;
}

bool ance::IntegerType::isBooleanType() const
{
    return bit_size_ == 1;
}

ance::TypeDefinitionRegistry* ance::IntegerType::getRegistry()
{
    return &getIntegerTypes();
}

ance::ResolvingHandle<ance::Type> ance::IntegerType::get(uint64_t bit_size, bool is_signed)
{
    std::vector<ance::ResolvingHandle<ance::Type>> used_types;

    std::optional<ance::ResolvingHandle<ance::Type>> defined_type =
        getIntegerTypes().get(used_types, std::make_pair(bit_size, is_signed));

    if (defined_type.has_value()) { return defined_type.value(); }
    else {
        auto*                             integer_type = new ance::IntegerType(bit_size, is_signed);
        ance::ResolvingHandle<ance::Type> type =
            ance::makeHandled<ance::Type>(std::unique_ptr<ance::IntegerType>(integer_type));
        getIntegerTypes().add(std::move(used_types), std::make_pair(bit_size, is_signed), type);

        return type;
    }
}

ance::ResolvingHandle<ance::Type> ance::IntegerType::getBooleanType()
{
    return get(1, true);// Use true so that i1 instead of ui1 can be used. (it is shorter)
}
