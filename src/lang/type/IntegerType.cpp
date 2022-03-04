#include "IntegerType.h"

#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/VoidType.h"
#include "lang/utility/Values.h"
#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

lang::IntegerType::IntegerType(uint64_t bit_size, bool is_signed)
    : TypeDefinition((is_signed ? "i" : "ui") + std::to_string(bit_size))
    , bit_size_(bit_size)
    , is_signed_(is_signed)
{}

bool lang::IntegerType::isIntegerType() const
{
    return true;
}

bool lang::IntegerType::isIntegerType(uint64_t bit_size, bool is_signed) const
{
    return (bit_size_ == bit_size) && (is_signed_ == is_signed);
}

llvm::Constant* lang::IntegerType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantInt::get(getContentType(c), 0, is_signed_);
}

llvm::Type* lang::IntegerType::getContentType(llvm::LLVMContext& c)
{
    if (!type_) { type_ = llvm::Type::getIntNTy(c, bit_size_); }

    return type_;
}

bool lang::IntegerType::validate(ValidationLogger& validation_logger, lang::Location location)
{
    if (bit_size_ == 0)
    {
        validation_logger.logError("Integer type size must be positive", location);
        return false;
    }

    if (bit_size_ > MAX_INTEGER_SIZE)
    {
        validation_logger.logError("Integer type size cannot be larger than " + std::to_string(MAX_INTEGER_SIZE),
                                   location);
        return false;
    }

    return true;
}

bool lang::IntegerType::isImplicitlyConvertibleTo(lang::ResolvingHandle<lang::Type> other)
{
    if (!other->isIntegerType()) return false;

    auto* other_type = dynamic_cast<IntegerType*>(other->getActualType()->getDefinition());

    bool can_enlarge     = (bit_size_ < other_type->bit_size_) && (is_signed_ == other_type->is_signed_);
    bool can_change_sign = (bit_size_ < other_type->bit_size_) && !is_signed_ && other_type->is_signed_;

    return can_enlarge || can_change_sign;
}

bool lang::IntegerType::validateImplicitConversion(lang::ResolvingHandle<lang::Type>, lang::Location, ValidationLogger&)
{
    return true;
}

std::shared_ptr<lang::Value> lang::IntegerType::buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                                        std::shared_ptr<Value>            value,
                                                                        CompileContext*                   context)
{
    value->buildContentValue(context);
    llvm::Value* content_value = value->getContentValue();

    llvm::Value* converted_value =
        context->ir()->CreateIntCast(content_value, other->getContentType(*context->llvmContext()), is_signed_);
    llvm::Value* native_converted_value = lang::Values::contentToNative(other, converted_value, context);

    return std::make_shared<WrappedNativeValue>(other, native_converted_value);
}

bool lang::IntegerType::isOperatorDefined(lang::BinaryOperator, lang::ResolvingHandle<lang::Type> other)
{
    if (other->isIntegerType())
    {
        auto other_type = dynamic_cast<IntegerType*>(other->getActualType()->getDefinition());
        return this == other_type;
    }

    return false;
}

lang::ResolvingHandle<lang::Type> lang::IntegerType::getOperatorResultType(lang::BinaryOperator op,
                                                                           lang::ResolvingHandle<lang::Type>)
{
    if (op.isArithmetic()) return self();
    if (op.isRelational() || op.isEquality()) return lang::IntegerType::getBooleanType();

    return lang::VoidType::get();
}

bool lang::IntegerType::validateOperator(lang::BinaryOperator,
                                         lang::ResolvingHandle<lang::Type>,
                                         lang::Location,
                                         lang::Location,
                                         ValidationLogger&)
{
    return true;
}

std::shared_ptr<lang::Value> lang::IntegerType::buildOperator(lang::BinaryOperator   op,
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
            if (is_signed_) result = context->ir()->CreateSDiv(left_value, right_value);
            else result = context->ir()->CreateUDiv(left_value, right_value);
            break;
        case lang::BinaryOperator::REMAINDER:
            if (is_signed_) result = context->ir()->CreateSRem(left_value, right_value);
            else result = context->ir()->CreateURem(left_value, right_value);
            break;
        case lang::BinaryOperator::LESS_THAN:
            if (is_signed_) result = context->ir()->CreateICmpSLT(left_value, right_value);
            else result = context->ir()->CreateICmpULT(left_value, right_value);
            break;
        case lang::BinaryOperator::LESS_THAN_OR_EQUAL:
            if (is_signed_) result = context->ir()->CreateICmpSLE(left_value, right_value);
            else result = context->ir()->CreateICmpULE(left_value, right_value);
            break;
        case lang::BinaryOperator::GREATER_THAN:
            if (is_signed_) result = context->ir()->CreateICmpSGT(left_value, right_value);
            else result = context->ir()->CreateICmpUGT(left_value, right_value);
            break;
        case lang::BinaryOperator::GREATER_THAN_OR_EQUAL:
            if (is_signed_) result = context->ir()->CreateICmpSGE(left_value, right_value);
            else result = context->ir()->CreateICmpUGE(left_value, right_value);
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

std::string lang::IntegerType::createMangledName()
{
    return getName();
}

llvm::DIType* lang::IntegerType::createDebugType(CompileContext* context)
{
    const llvm::DataLayout& dl = context->module()->getDataLayout();

    std::string name         = getName();
    uint64_t    size_in_bits = dl.getTypeSizeInBits(getContentType(*context->llvmContext()));
    auto        encoding     = is_signed_ ? llvm::dwarf::DW_ATE_signed : llvm::dwarf::DW_ATE_unsigned;

    return context->di()->createBasicType(name, size_in_bits, encoding);
}

lang::TypeRegistry<std::pair<uint64_t, bool>>& lang::IntegerType::getIntegerTypes()
{
    static TypeRegistry<std::pair<uint64_t, bool>> integer_types;
    return integer_types;
}

bool lang::IntegerType::isBooleanType() const
{
    return bit_size_ == 1;
}

lang::TypeDefinitionRegistry* lang::IntegerType::getRegistry()
{
    return &getIntegerTypes();
}

lang::ResolvingHandle<lang::Type> lang::IntegerType::get(uint64_t bit_size, bool is_signed)
{
    std::vector<lang::ResolvingHandle<lang::Type>> used_types;

    std::optional<lang::ResolvingHandle<lang::Type>> defined_type =
        getIntegerTypes().get(used_types, std::make_pair(bit_size, is_signed));

    if (defined_type.has_value()) { return defined_type.value(); }
    else {
        auto*                             integer_type = new lang::IntegerType(bit_size, is_signed);
        lang::ResolvingHandle<lang::Type> type =
            lang::makeHandled<lang::Type>(std::unique_ptr<lang::IntegerType>(integer_type));
        getIntegerTypes().add(std::move(used_types), std::make_pair(bit_size, is_signed), type);

        return type;
    }
}

lang::ResolvingHandle<lang::Type> lang::IntegerType::getBooleanType()
{
    return get(1, true);// Use true so that i1 instead of ui1 can be used. (it is shorter)
}