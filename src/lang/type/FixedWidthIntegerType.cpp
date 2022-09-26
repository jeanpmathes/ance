#include "FixedWidthIntegerType.h"

#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/BooleanType.h"
#include "lang/type/SizeType.h"
#include "lang/utility/Values.h"
#include "validation/ValidationLogger.h"

lang::FixedWidthIntegerType::FixedWidthIntegerType(uint64_t bit_size, bool is_signed)
    : TypeDefinition(lang::Identifier::from((is_signed ? "i" : "ui") + std::to_string(bit_size)))
    , bit_size_(bit_size)
    , is_signed_(is_signed)
{}

const lang::FixedWidthIntegerType* lang::FixedWidthIntegerType::isFixedWidthIntegerType() const
{
    return this;
}

bool lang::FixedWidthIntegerType::isFixedWidthIntegerType(uint64_t bit_size, bool is_signed) const
{
    return (bit_size_ == bit_size) && (is_signed_ == is_signed);
}

bool lang::FixedWidthIntegerType::validate(ValidationLogger& validation_logger, lang::Location location) const
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

std::shared_ptr<lang::Value> lang::FixedWidthIntegerType::buildImplicitConversion(
    lang::ResolvingHandle<lang::Type> other,
    lang::ResolvingHandle<lang::Type> other_element,
    std::shared_ptr<Value>            value,
    CompileContext&                   context)
{
    llvm::Value* native_converted_value;

    bool can_directly_convert_to_size =
        other_element->isSizeType() && !is_signed_ && (bit_size_ == lang::SizeType::getSizeWidth());
    bool can_directly_convert_to_diff =
        other_element->isDiffType() && is_signed_ && (bit_size_ == lang::SizeType::getDiffWidth());

    if (can_directly_convert_to_size || can_directly_convert_to_diff)
    {
        value->buildNativeValue(context);
        native_converted_value = value->getNativeValue();
    }
    else
    {
        value->buildContentValue(context);
        llvm::Value* content_value = value->getContentValue();

        llvm::Value* converted_value = context.ir()->CreateIntCast(content_value,
                                                                   other->getContentType(*context.llvmContext()),
                                                                   is_signed_,
                                                                   content_value->getName() + ".icast");
        native_converted_value       = lang::Values::contentToNative(other, converted_value, context);
    }

    return std::make_shared<WrappedNativeValue>(other, native_converted_value);
}

bool lang::FixedWidthIntegerType::isOperatorDefined(lang::BinaryOperator, lang::ResolvingHandle<lang::Type> other)
{
    other = lang::Type::getReferencedType(other);

    if (other->isFixedWidthIntegerType())
    {
        auto* other_type = other->getActualType()->getDefinition();
        auto* this_type  = self()->getActualType()->getDefinition();
        return this_type == other_type;
    }

    return false;
}

lang::ResolvingHandle<lang::Type> lang::FixedWidthIntegerType::getOperatorResultType(lang::BinaryOperator op,
                                                                                     lang::ResolvingHandle<lang::Type>)
{
    if (op.isArithmetic()) return self()->getActualType();
    if (op.isRelational() || op.isEquality()) return lang::BooleanType::get();

    return lang::Type::getUndefined();
}

bool lang::FixedWidthIntegerType::validateOperator(lang::BinaryOperator,
                                                   lang::ResolvingHandle<lang::Type>,
                                                   lang::Location,
                                                   lang::Location,
                                                   ValidationLogger&) const
{
    return true;
}

std::shared_ptr<lang::Value> lang::FixedWidthIntegerType::buildOperator(lang::BinaryOperator   op,
                                                                        std::shared_ptr<Value> left,
                                                                        std::shared_ptr<Value> right,
                                                                        CompileContext&        context)
{
    return buildOperator(op, left, right, getOperatorResultType(op, right->type()), context);
}

std::shared_ptr<lang::Value> lang::FixedWidthIntegerType::buildOperator(lang::BinaryOperator              op,
                                                                        std::shared_ptr<Value>            left,
                                                                        std::shared_ptr<Value>            right,
                                                                        lang::ResolvingHandle<lang::Type> return_type,
                                                                        CompileContext&                   context)
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
            result = context.ir()->CreateAdd(left_value, right_value, left_value->getName() + ".add");
            break;
        case lang::BinaryOperator::SUBTRACTION:
            result = context.ir()->CreateSub(left_value, right_value, left_value->getName() + ".sub");
            break;
        case lang::BinaryOperator::MULTIPLICATION:
            result = context.ir()->CreateMul(left_value, right_value, left_value->getName() + ".mul");
            break;
        case lang::BinaryOperator::DIVISION:
            if (is_signed_) result = context.ir()->CreateSDiv(left_value, right_value, left_value->getName() + ".sdiv");
            else result = context.ir()->CreateUDiv(left_value, right_value, left_value->getName() + ".udiv");
            break;
        case lang::BinaryOperator::REMAINDER:
            if (is_signed_) result = context.ir()->CreateSRem(left_value, right_value, left_value->getName() + ".srem");
            else result = context.ir()->CreateURem(left_value, right_value, left_value->getName() + ".urem");
            break;
        case lang::BinaryOperator::LESS_THAN:
            if (is_signed_)
                result = context.ir()->CreateICmpSLT(left_value, right_value, left_value->getName() + ".icmp");
            else result = context.ir()->CreateICmpULT(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::LESS_THAN_OR_EQUAL:
            if (is_signed_)
                result = context.ir()->CreateICmpSLE(left_value, right_value, left_value->getName() + ".icmp");
            else result = context.ir()->CreateICmpULE(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::GREATER_THAN:
            if (is_signed_)
                result = context.ir()->CreateICmpSGT(left_value, right_value, left_value->getName() + ".icmp");
            else result = context.ir()->CreateICmpUGT(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::GREATER_THAN_OR_EQUAL:
            if (is_signed_)
                result = context.ir()->CreateICmpSGE(left_value, right_value, left_value->getName() + ".icmp");
            else result = context.ir()->CreateICmpUGE(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::EQUAL:
            result = context.ir()->CreateICmpEQ(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::NOT_EQUAL:
            result = context.ir()->CreateICmpNE(left_value, right_value, left_value->getName() + ".icmp");
            break;
    }

    llvm::Value* native_result = lang::Values::contentToNative(return_type, result, context);
    return std::make_shared<lang::WrappedNativeValue>(return_type, native_result);
}

void lang::FixedWidthIntegerType::buildRequestedOverload(lang::ResolvingHandle<lang::Type> parameter_element,
                                                         lang::ResolvingHandle<lang::Type> return_type,
                                                         lang::PredefinedFunction&         function,
                                                         CompileContext&                   context)
{
    IntegerType::buildRequestedOverload(parameter_element, return_type, function, context);
}

std::string lang::FixedWidthIntegerType::createMangledName() const
{
    return std::string(name().text());
}

lang::TypeRegistry<std::pair<uint64_t, bool>>& lang::FixedWidthIntegerType::getIntegerTypes()
{
    static TypeRegistry<std::pair<uint64_t, bool>> integer_types;
    return integer_types;
}

lang::TypeDefinitionRegistry* lang::FixedWidthIntegerType::getRegistry()
{
    return &getIntegerTypes();
}

lang::ResolvingHandle<lang::Type> lang::FixedWidthIntegerType::get(uint64_t bit_size, bool is_signed)
{
    std::vector<lang::ResolvingHandle<lang::Type>> used_types;

    std::optional<lang::ResolvingHandle<lang::Type>> defined_type =
        getIntegerTypes().get(used_types, std::make_pair(bit_size, is_signed));

    if (defined_type.has_value()) { return defined_type.value(); }
    else
    {
        auto*                             integer_type = new lang::FixedWidthIntegerType(bit_size, is_signed);
        lang::ResolvingHandle<lang::Type> type =
            lang::makeHandled<lang::Type>(std::unique_ptr<lang::FixedWidthIntegerType>(integer_type));
        getIntegerTypes().add(std::move(used_types), std::make_pair(bit_size, is_signed), type);

        return type;
    }
}

std::optional<size_t> lang::FixedWidthIntegerType::getBitSize() const
{
    return bit_size_;
}

size_t lang::FixedWidthIntegerType::getNativeBitSize() const
{
    return bit_size_;
}

bool lang::FixedWidthIntegerType::isSigned() const
{
    return is_signed_;
}

size_t lang::FixedWidthIntegerType::getMinimumBitSize() const
{
    return bit_size_;
}
