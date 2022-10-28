#include "FloatingPointType.h"

#include "compiler/CompileContext.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/type/BooleanType.h"
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

llvm::DIType* lang::FloatingPointType::createDebugType(CompileContext& context)
{
    const llvm::DataLayout& dl = context.module()->getDataLayout();

    std::string name         = std::string(this->name().text());
    uint64_t    size_in_bits = dl.getTypeSizeInBits(getContentType(*context.llvmContext()));
    auto        encoding     = llvm::dwarf::DW_ATE_float;

    return context.di()->createBasicType(name, size_in_bits, encoding);
}

const lang::FloatingPointType* lang::FloatingPointType::isFloatingPointType() const
{
    return this;
}

bool lang::FloatingPointType::isFloatingPointType(size_t precision) const
{
    return precision == getPrecision();
}

bool lang::FloatingPointType::isImplicitlyConvertibleTo(lang::ResolvingHandle<lang::Type> other)
{
    if (auto other_float = other->isFloatingPointType()) { return getPrecision() < other_float->getPrecision(); }

    return false;
}

bool lang::FloatingPointType::validateImplicitConversion(lang::ResolvingHandle<lang::Type>,
                                                         lang::Location,
                                                         ValidationLogger&) const
{
    return true;
}

std::shared_ptr<lang::Value> lang::FloatingPointType::buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                                              std::shared_ptr<Value>            value,
                                                                              CompileContext&                   context)
{
    value->buildContentValue(context);
    llvm::Value* content_value = value->getContentValue();

    llvm::Value* converted_value      = context.ir()->CreateFPCast(content_value,
                                                              other->getContentType(*context.llvmContext()),
                                                              content_value->getName() + ".fcast");
    llvm::Value* native_content_value = lang::Values::contentToNative(other, converted_value, context);

    return std::make_shared<WrappedNativeValue>(other, native_content_value);
}

bool lang::FloatingPointType::isOperatorDefined(lang::BinaryOperator op, lang::ResolvingHandle<lang::Type> other)
{
    if (!op.isArithmetic() && !op.isRelational() && !op.isEquality()) return false;

    other = lang::Type::getReferencedType(other);

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
    if (op.isRelational() || op.isEquality()) return lang::BooleanType::get();

    return lang::Type::getUndefined();
}

bool lang::FloatingPointType::validateOperator(lang::BinaryOperator,
                                               lang::ResolvingHandle<lang::Type>,
                                               lang::Location,
                                               lang::Location,
                                               ValidationLogger&) const
{
    return true;
}

std::shared_ptr<lang::Value> lang::FloatingPointType::buildOperator(lang::BinaryOperator   op,
                                                                    std::shared_ptr<Value> left,
                                                                    std::shared_ptr<Value> right,
                                                                    CompileContext&        context)
{
    return buildOperator(op, left, right, getOperatorResultType(op, right->type()), context);
}

std::shared_ptr<lang::Value> lang::FloatingPointType::buildOperator(lang::BinaryOperator              op,
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
            result = context.ir()->CreateFAdd(left_value, right_value, left_value->getName() + ".fadd");
            break;
        case lang::BinaryOperator::SUBTRACTION:
            result = context.ir()->CreateFSub(left_value, right_value, left_value->getName() + ".fsub");
            break;
        case lang::BinaryOperator::MULTIPLICATION:
            result = context.ir()->CreateFMul(left_value, right_value, left_value->getName() + ".fmul");
            break;
        case lang::BinaryOperator::DIVISION:
            result = context.ir()->CreateFDiv(left_value, right_value, left_value->getName() + ".fdiv");
            break;
        case lang::BinaryOperator::REMAINDER:
            result = context.ir()->CreateFRem(left_value, right_value, left_value->getName() + ".frem");
            break;
        case lang::BinaryOperator::LESS_THAN:
            result = context.ir()->CreateFCmpOLT(left_value, right_value, left_value->getName() + ".fcmp");
            break;
        case lang::BinaryOperator::LESS_THAN_OR_EQUAL:
            result = context.ir()->CreateFCmpOLE(left_value, right_value, left_value->getName() + ".fcmp");
            break;
        case lang::BinaryOperator::GREATER_THAN:
            result = context.ir()->CreateFCmpOGT(left_value, right_value, left_value->getName() + ".fcmp");
            break;
        case lang::BinaryOperator::GREATER_THAN_OR_EQUAL:
            result = context.ir()->CreateFCmpOGE(left_value, right_value, left_value->getName() + ".fcmp");
            break;
        case lang::BinaryOperator::EQUAL:
            result = context.ir()->CreateFCmpOEQ(left_value, right_value, left_value->getName() + ".fcmp");
            break;
        case lang::BinaryOperator::NOT_EQUAL:
            result = context.ir()->CreateFCmpONE(left_value, right_value, left_value->getName() + ".fcmp");
            break;

        default:
            assert(false);
            result = nullptr;
    }

    llvm::Value* native_result = lang::Values::contentToNative(return_type, result, context);
    return std::make_shared<lang::WrappedNativeValue>(return_type, native_result);
}

bool lang::FloatingPointType::acceptOverloadRequest(const std::vector<lang::ResolvingHandle<lang::Type>>& parameters)
{
    if (parameters.size() == 1)
    {
        if (parameters[0]->isFloatingPointType()) return true;
        if (parameters[0]->isFixedWidthIntegerType()) return true;
    }

    return false;
}

void lang::FloatingPointType::buildRequestedOverload(const std::vector<lang::ResolvingHandle<lang::Type>>& parameters,
                                                     lang::PredefinedFunction&                             function,
                                                     CompileContext&                                       context)
{
    if (parameters.size() == 1) { buildRequestedOverload(parameters[0], self(), function, context); }
}

void lang::FloatingPointType::buildRequestedOverload(lang::ResolvingHandle<lang::Type> parameter_element,
                                                     lang::ResolvingHandle<lang::Type> return_type,
                                                     lang::PredefinedFunction&         function,
                                                     CompileContext&                   context)
{
    llvm::Function* native_function;
    std::tie(std::ignore, native_function) = function.getNativeRepresentation();

    if (parameter_element->isFloatingPointType())
    {
        llvm::BasicBlock* block = llvm::BasicBlock::Create(*context.llvmContext(), "block", native_function);
        context.ir()->SetInsertPoint(block);
        {
            llvm::Value* original = native_function->getArg(0);

            llvm::Value* converted = context.ir()->CreateFPCast(original,
                                                                return_type->getContentType(*context.llvmContext()),
                                                                original->getName() + ".fcast");

            context.ir()->CreateRet(converted);
        }
    }

    if (parameter_element->isFixedWidthIntegerType())
    {
        llvm::BasicBlock* block = llvm::BasicBlock::Create(*context.llvmContext(), "block", native_function);
        context.ir()->SetInsertPoint(block);
        {
            llvm::Value* original = native_function->getArg(0);

            llvm::Value* converted;

            if (parameter_element->isSigned())
            {
                converted = context.ir()->CreateSIToFP(original,
                                                       return_type->getContentType(*context.llvmContext()),
                                                       original->getName() + ".sitofp");
            }
            else
            {
                converted = context.ir()->CreateUIToFP(original,
                                                       return_type->getContentType(*context.llvmContext()),
                                                       original->getName() + ".uitofp");
            }

            context.ir()->CreateRet(converted);
        }
    }
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

