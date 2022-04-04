#include "FloatingPointType.h"

#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/type/IntegerType.h"
#include "lang/type/Type.h"
#include "lang/type/VoidType.h"
#include "lang/utility/Values.h"
#include "compiler/CompileContext.h"

std::string lang::FloatingPointType::createMangledName()
{
    return getName();
}

llvm::DIType* lang::FloatingPointType::createDebugType(CompileContext* context)
{
    const llvm::DataLayout& dl = context->module()->getDataLayout();

    std::string name         = getName();
    uint64_t    size_in_bits = dl.getTypeSizeInBits(getContentType(*context->llvmContext()));
    auto        encoding     = llvm::dwarf::DW_ATE_float;

    return context->di()->createBasicType(name, size_in_bits, encoding);
}

bool lang::FloatingPointType::isFloatingPointType() const
{
    return true;
}

bool lang::FloatingPointType::isFloatingPointType(size_t precision) const
{
    return precision == getPrecision();
}

bool lang::FloatingPointType::isImplicitlyConvertibleTo(lang::ResolvingHandle<lang::Type> other)
{
    if (!other->isFloatingPointType()) return false;

    auto* other_float = dynamic_cast<FloatingPointType*>(other->getDefinition());

    if (!other_float) return false;// Cloned floating point types do not allow implicit conversion.

    return getPrecision() < other_float->getPrecision();
}

bool lang::FloatingPointType::validateImplicitConversion(lang::ResolvingHandle<lang::Type>,
                                                         lang::Location,
                                                         ValidationLogger&)
{
    return true;
}

std::shared_ptr<lang::Value> lang::FloatingPointType::buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                                              std::shared_ptr<Value>            value,
                                                                              CompileContext*                   context)
{
    value->buildContentValue(context);
    llvm::Value* content_value = value->getContentValue();

    llvm::Value* converted_value =
        context->ir()->CreateFPCast(content_value, other->getContentType(*context->llvmContext()));
    llvm::Value* native_content_value = lang::Values::contentToNative(other, converted_value, context);

    return std::make_shared<WrappedNativeValue>(other, native_content_value);
}

bool lang::FloatingPointType::isOperatorDefined(lang::BinaryOperator, lang::ResolvingHandle<lang::Type> other)
{
    other = lang::Type::getDereferencedType(other);

    if (other->isFloatingPointType())
    {
        auto* other_type = dynamic_cast<FloatingPointType*>(other->getActualType()->getDefinition());
        return this == other_type;
    }

    return false;
}

lang::ResolvingHandle<lang::Type> lang::FloatingPointType::getOperatorResultType(lang::BinaryOperator op,
                                                                                 lang::ResolvingHandle<lang::Type>)
{
    if (op.isArithmetic()) return self()->getActualType();
    if (op.isRelational() || op.isEquality()) return lang::IntegerType::getBooleanType();

    return lang::VoidType::get();
}

bool lang::FloatingPointType::validateOperator(lang::BinaryOperator,
                                               lang::ResolvingHandle<lang::Type>,
                                               lang::Location,
                                               lang::Location,
                                               ValidationLogger&)
{
    return true;
}

std::shared_ptr<lang::Value> lang::FloatingPointType::buildOperator(lang::BinaryOperator   op,
                                                                    std::shared_ptr<Value> left,
                                                                    std::shared_ptr<Value> right,
                                                                    CompileContext*        context)
{
    right = lang::Type::getValueOrDereference(right, context);

    left->buildContentValue(context);
    right->buildContentValue(context);

    llvm::Value* left_value  = left->getContentValue();
    llvm::Value* right_value = right->getContentValue();

    llvm::Value* result;

    switch (op)
    {
        case lang::BinaryOperator::ADDITION:
            result = context->ir()->CreateFAdd(left_value, right_value);
            break;
        case lang::BinaryOperator::SUBTRACTION:
            result = context->ir()->CreateFSub(left_value, right_value);
            break;
        case lang::BinaryOperator::MULTIPLICATION:
            result = context->ir()->CreateFMul(left_value, right_value);
            break;
        case lang::BinaryOperator::DIVISION:
            result = context->ir()->CreateFDiv(left_value, right_value);
            break;
        case lang::BinaryOperator::REMAINDER:
            result = context->ir()->CreateFRem(left_value, right_value);
            break;
        case lang::BinaryOperator::LESS_THAN:
            result = context->ir()->CreateFCmpOLT(left_value, right_value);
            break;
        case lang::BinaryOperator::LESS_THAN_OR_EQUAL:
            result = context->ir()->CreateFCmpOLE(left_value, right_value);
            break;
        case lang::BinaryOperator::GREATER_THAN:
            result = context->ir()->CreateFCmpOGT(left_value, right_value);
            break;
        case lang::BinaryOperator::GREATER_THAN_OR_EQUAL:
            result = context->ir()->CreateFCmpOGE(left_value, right_value);
            break;
        case lang::BinaryOperator::EQUAL:
            result = context->ir()->CreateFCmpOEQ(left_value, right_value);
            break;
        case lang::BinaryOperator::NOT_EQUAL:
            result = context->ir()->CreateFCmpONE(left_value, right_value);
            break;
    }

    lang::ResolvingHandle<lang::Type> result_type   = getOperatorResultType(op, right->type());
    llvm::Value*                      native_result = lang::Values::contentToNative(result_type, result, context);
    return std::make_shared<lang::WrappedNativeValue>(result_type, native_result);
}
