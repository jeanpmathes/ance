#include "FloatingPointType.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/scope/Scope.h"
#include "lang/type/BooleanType.h"
#include "lang/type/FixedWidthIntegerType.h"
#include "lang/type/Type.h"
#include "lang/utility/Values.h"

StateCount lang::FloatingPointType::getStateCount() const
{
    return SpecialCount::UNCOUNTABLE;
}

std::string lang::FloatingPointType::createMangledName() const
{
    return std::string(name().text());
}

llvm::DIType* lang::FloatingPointType::createDebugType(CompileContext& context) const
{
    llvm::DataLayout const& dl = context.llvmModule().getDataLayout();

    std::string const name         = std::string(this->name().text());
    uint64_t const    size_in_bits = dl.getTypeSizeInBits(getContentType(context.llvmContext()));
    auto              encoding     = llvm::dwarf::DW_ATE_float;

    return context.di().createBasicType(name, size_in_bits, encoding);
}

lang::FloatingPointType const* lang::FloatingPointType::isFloatingPointType() const
{
    return this;
}

bool lang::FloatingPointType::isFloatingPointType(size_t precision) const
{
    return precision == getPrecision();
}

bool lang::FloatingPointType::isImplicitlyConvertibleTo(lang::Type const& other) const
{
    if (auto other_float = other.isFloatingPointType()) { return getPrecision() < other_float->getPrecision(); }

    return false;
}

bool lang::FloatingPointType::validateImplicitConversion(lang::Type const&, lang::Location, ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::FloatingPointType::buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                                     Shared<Value>                     value,
                                                                     CompileContext&                   context)
{
    value->buildContentValue(context);
    llvm::Value* content_value = value->getContentValue();

    llvm::Value* converted_value      = context.ir().CreateFPCast(content_value,
                                                             other->getContentType(context.llvmContext()),
                                                             content_value->getName() + ".fcast");
    llvm::Value* native_content_value = lang::values::contentToNative(other, converted_value, context);

    return makeShared<WrappedNativeValue>(other, native_content_value);
}

bool lang::FloatingPointType::isCastingPossibleTo(lang::Type const& other) const
{
    return other.isFloatingPointType() || other.isFixedWidthIntegerType();
}

bool lang::FloatingPointType::validateCast(lang::Type const&, lang::Location, ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::FloatingPointType::buildCast(lang::ResolvingHandle<lang::Type> other,
                                                       Shared<Value>                     value,
                                                       CompileContext&                   context)
{
    return buildCast(other, value, other, context);
}

Shared<lang::Value> lang::FloatingPointType::buildCast(lang::ResolvingHandle<lang::Type> other,
                                                       Shared<Value>                     value,
                                                       lang::ResolvingHandle<lang::Type> element_type,
                                                       CompileContext&                   context)
{
    if (element_type->isFloatingPointType())
    {
        value->buildContentValue(context);
        llvm::Value* content_value = value->getContentValue();

        llvm::Value* converted_value      = context.ir().CreateFPCast(content_value,
                                                                 other->getContentType(context.llvmContext()),
                                                                 content_value->getName() + ".fcast");
        llvm::Value* native_content_value = lang::values::contentToNative(other, converted_value, context);

        return makeShared<WrappedNativeValue>(other, native_content_value);
    }

    if (element_type->isFixedWidthIntegerType())
    {
        value->buildContentValue(context);
        llvm::Value* content_value = value->getContentValue();

        llvm::Value* converted_value;

        if (other->isSigned())
        {
            converted_value = context.ir().CreateFPToSI(content_value,
                                                        other->getContentType(context.llvmContext()),
                                                        content_value->getName() + ".fcast");
        }
        else
        {
            converted_value = context.ir().CreateFPToUI(content_value,
                                                        other->getContentType(context.llvmContext()),
                                                        content_value->getName() + ".fcast");
        }

        llvm::Value* native_content_value = lang::values::contentToNative(other, converted_value, context);

        return makeShared<WrappedNativeValue>(other, native_content_value);
    }

    throw std::runtime_error("Invalid cast");
}

bool lang::FloatingPointType::isOperatorDefined(lang::UnaryOperator op) const
{
    return op == lang::UnaryOperator::NEGATION;
}

lang::ResolvingHandle<lang::Type> lang::FloatingPointType::getOperatorResultType(lang::UnaryOperator)
{
    return self();
}

bool lang::FloatingPointType::validateOperator(lang::UnaryOperator, lang::Location, ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::FloatingPointType::buildOperator(lang::UnaryOperator op,
                                                           Shared<Value>       value,
                                                           CompileContext&     context)
{
    return buildOperator(op, value, getOperatorResultType(op), context);
}

Shared<lang::Value> lang::FloatingPointType::buildOperator(lang::UnaryOperator               op,
                                                           Shared<Value>                     value,
                                                           lang::ResolvingHandle<lang::Type> return_type,
                                                           CompileContext&                   context)
{
    value->buildContentValue(context);
    llvm::Value* content_value = value->getContentValue();

    llvm::Value* result;

    switch (op)
    {
        case lang::UnaryOperator::NEGATION:
            result = context.ir().CreateFNeg(content_value, content_value->getName() + ".neg");
            break;

        default:
            assert(false);
            result = nullptr;
    }

    llvm::Value* native_result = lang::values::contentToNative(return_type, result, context);
    return makeShared<lang::WrappedNativeValue>(return_type, native_result);
}

bool lang::FloatingPointType::isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const
{
    if (!op.isArithmetic() && !op.isRelational() && !op.isEquality()) return false;

    lang::Type const& real_other = lang::Type::getReferencedType(other);

    if (real_other.isFloatingPointType()) { return this == real_other.isFloatingPointType(); }

    return false;
}

lang::ResolvingHandle<lang::Type> lang::FloatingPointType::getOperatorResultType(lang::BinaryOperator op,
                                                                                 lang::ResolvingHandle<lang::Type>)
{
    if (op.isArithmetic()) return self()->getActualType();
    if (op.isRelational() || op.isEquality()) return scope()->context().getBooleanType();

    return lang::Type::getUndefined();
}

bool lang::FloatingPointType::validateOperator(lang::BinaryOperator,
                                               lang::Type const&,
                                               lang::Location,
                                               lang::Location,
                                               ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::FloatingPointType::buildOperator(lang::BinaryOperator op,
                                                           Shared<Value>        left,
                                                           Shared<Value>        right,
                                                           CompileContext&      context)
{
    return buildOperator(op, left, right, getOperatorResultType(op, right->type()), context);
}

Shared<lang::Value> lang::FloatingPointType::buildOperator(lang::BinaryOperator              op,
                                                           Shared<Value>                     left,
                                                           Shared<Value>                     right,
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
            result = context.ir().CreateFAdd(left_value, right_value, left_value->getName() + ".fadd");
            break;
        case lang::BinaryOperator::SUBTRACTION:
            result = context.ir().CreateFSub(left_value, right_value, left_value->getName() + ".fsub");
            break;
        case lang::BinaryOperator::MULTIPLICATION:
            result = context.ir().CreateFMul(left_value, right_value, left_value->getName() + ".fmul");
            break;
        case lang::BinaryOperator::DIVISION:
            result = context.ir().CreateFDiv(left_value, right_value, left_value->getName() + ".fdiv");
            break;
        case lang::BinaryOperator::REMAINDER:
            result = context.ir().CreateFRem(left_value, right_value, left_value->getName() + ".frem");
            break;
        case lang::BinaryOperator::LESS_THAN:
            result = context.ir().CreateFCmpOLT(left_value, right_value, left_value->getName() + ".fcmp");
            break;
        case lang::BinaryOperator::LESS_THAN_OR_EQUAL:
            result = context.ir().CreateFCmpOLE(left_value, right_value, left_value->getName() + ".fcmp");
            break;
        case lang::BinaryOperator::GREATER_THAN:
            result = context.ir().CreateFCmpOGT(left_value, right_value, left_value->getName() + ".fcmp");
            break;
        case lang::BinaryOperator::GREATER_THAN_OR_EQUAL:
            result = context.ir().CreateFCmpOGE(left_value, right_value, left_value->getName() + ".fcmp");
            break;
        case lang::BinaryOperator::EQUAL:
            result = context.ir().CreateFCmpOEQ(left_value, right_value, left_value->getName() + ".fcmp");
            break;
        case lang::BinaryOperator::NOT_EQUAL:
            result = context.ir().CreateFCmpONE(left_value, right_value, left_value->getName() + ".fcmp");
            break;

        default:
            assert(false);
            result = nullptr;
    }

    llvm::Value* native_result = lang::values::contentToNative(return_type, result, context);
    return makeShared<lang::WrappedNativeValue>(return_type, native_result);
}

bool lang::FloatingPointType::isTriviallyDefaultConstructible() const
{
    return true;
}

bool lang::FloatingPointType::isTriviallyCopyConstructible() const
{
    return true;
}

bool lang::FloatingPointType::isTriviallyDestructible() const
{
    return true;
}
