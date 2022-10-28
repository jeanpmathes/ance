#include "IntegerType.h"

#include "BooleanType.h"
#include "compiler/CompileContext.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/utility/Values.h"

StateCount lang::IntegerType::getStateCount() const
{
    auto bit_size = getBitSize();
    if (bit_size.has_value())
    {
        size_t state_count = 1 << bit_size.value();
        return state_count;
    }

    return SpecialCount::PLATFORM_DEPENDENT;
}

llvm::Constant* lang::IntegerType::getDefaultContent(llvm::Module& m)
{
    return llvm::ConstantInt::get(getContentType(m.getContext()), 0, false);
}

llvm::Type* lang::IntegerType::getContentType(llvm::LLVMContext& c) const
{
    return llvm::Type::getIntNTy(c, static_cast<unsigned>(getNativeBitSize()));
}

const lang::IntegerType* lang::IntegerType::isIntegerType() const
{
    return this;
}

bool lang::IntegerType::isImplicitlyConvertibleTo(lang::ResolvingHandle<lang::Type> other)
{
    auto other_integer = other->isIntegerType();
    if (not other_integer) return false;

    auto   this_bit_size  = getBitSize();
    size_t other_bit_size = other_integer->getBitSize().value_or(other_integer->getMinimumBitSize());

    if (this_bit_size.has_value())
    {
        bool can_enlarge   = (this_bit_size.value() <= other_bit_size) && (isSigned() == other_integer->isSigned());
        bool can_gain_sign = (this_bit_size.value() < other_bit_size) && !isSigned() && other_integer->isSigned();

        return can_enlarge || can_gain_sign;
    }

    return self()->isSizeType() && other_integer->isDiffType();
}

bool lang::IntegerType::validateImplicitConversion(lang::ResolvingHandle<lang::Type>,
                                                   lang::Location,
                                                   ValidationLogger&) const
{
    return true;
}

std::shared_ptr<lang::Value> lang::IntegerType::buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                                        std::shared_ptr<Value>            value,
                                                                        CompileContext&                   context)
{
    value->buildContentValue(context);
    llvm::Value* content_value = value->getContentValue();

    llvm::Value* converted_value        = context.ir()->CreateIntCast(content_value,
                                                               other->getContentType(*context.llvmContext()),
                                                               isSigned(),
                                                               content_value->getName() + ".icast");
    llvm::Value* native_converted_value = lang::Values::contentToNative(other, converted_value, context);

    return std::make_shared<WrappedNativeValue>(other, native_converted_value);
}

bool lang::IntegerType::acceptOverloadRequest(const std::vector<lang::ResolvingHandle<lang::Type>>& parameters)
{
    if (parameters.size() == 1)
    {
        if (parameters[0]->isIntegerType()) return true;
        if (parameters[0]->isBooleanType()) return true;
        if (parameters[0]->isFloatingPointType()) return true;
    }

    return false;
}

void lang::IntegerType::buildRequestedOverload(const std::vector<lang::ResolvingHandle<lang::Type>>& parameters,
                                               lang::PredefinedFunction&                             function,
                                               CompileContext&                                       context)
{
    if (parameters.size() == 1) { buildRequestedOverload(parameters[0], self(), function, context); }
}

void lang::IntegerType::buildRequestedOverload(lang::ResolvingHandle<lang::Type> parameter_element,
                                               lang::ResolvingHandle<lang::Type> return_type,
                                               lang::PredefinedFunction&         function,
                                               CompileContext&                   context)
{
    llvm::Function* native_function;
    std::tie(std::ignore, native_function) = function.getNativeRepresentation();

    if (parameter_element->isIntegerType() || parameter_element->isBooleanType())
    {
        llvm::BasicBlock* block = llvm::BasicBlock::Create(*context.llvmContext(), "block", native_function);
        context.ir()->SetInsertPoint(block);
        {
            llvm::Value* original = native_function->getArg(0);

            llvm::Value* converted = context.ir()->CreateIntCast(original,
                                                                 return_type->getContentType(*context.llvmContext()),
                                                                 parameter_element->isSigned(),
                                                                 original->getName() + ".icast");
            context.ir()->CreateRet(converted);
        }
    }

    if (parameter_element->isFloatingPointType())
    {
        llvm::BasicBlock* block = llvm::BasicBlock::Create(*context.llvmContext(), "block", native_function);
        context.ir()->SetInsertPoint(block);
        {
            llvm::Value* original = native_function->getArg(0);
            llvm::Value* converted;

            if (isSigned())
            {
                converted = context.ir()->CreateFPToSI(original,
                                                       return_type->getContentType(*context.llvmContext()),
                                                       original->getName() + ".fptosi");
            }
            else
            {
                converted = context.ir()->CreateFPToUI(original,
                                                       return_type->getContentType(*context.llvmContext()),
                                                       original->getName() + ".fptoui");
            }

            context.ir()->CreateRet(converted);
        }
    }
}

bool lang::IntegerType::isOperatorDefined(lang::UnaryOperator op)
{
    return op == lang::UnaryOperator::BITWISE_NOT;
}

lang::ResolvingHandle<lang::Type> lang::IntegerType::getOperatorResultType(lang::UnaryOperator)
{
    return self();
}

bool lang::IntegerType::validateOperator(lang::UnaryOperator, lang::Location, ValidationLogger&) const
{
    return true;
}

std::shared_ptr<lang::Value> lang::IntegerType::buildOperator(lang::UnaryOperator    op,
                                                              std::shared_ptr<Value> value,
                                                              CompileContext&        context)
{
    value->buildContentValue(context);
    llvm::Value* content_value = value->getContentValue();

    llvm::Value* result;

    switch (op)
    {
        case lang::UnaryOperator::BITWISE_NOT:
            result = context.ir()->CreateNot(content_value, content_value->getName() + ".not");
            break;

        default:
            assert(false);
            result = nullptr;
    }

    lang::ResolvingHandle<lang::Type> result_type   = getOperatorResultType(op);
    llvm::Value*                      native_result = lang::Values::contentToNative(result_type, result, context);
    return std::make_shared<lang::WrappedNativeValue>(result_type, native_result);
}

bool lang::IntegerType::isOperatorDefined(lang::BinaryOperator op, lang::ResolvingHandle<lang::Type> other)
{
    if (!op.isArithmetic() && !op.isBitwise() && !op.isRelational() && !op.isEquality()) return false;

    other = lang::Type::getReferencedType(other);

    if (auto other_integer = other->isIntegerType())
    {
        if (this == other_integer) return true;

        auto this_bit_size  = getBitSize();
        auto other_bit_size = other_integer->getBitSize();

        if (this_bit_size.has_value() && other_bit_size.has_value())
        {
            return (this_bit_size.value() == other_bit_size.value()) && (isSigned() == other_integer->isSigned());
        }
    }

    return false;
}

lang::ResolvingHandle<lang::Type> lang::IntegerType::getOperatorResultType(lang::BinaryOperator op,
                                                                           lang::ResolvingHandle<lang::Type>)
{
    if (op.isArithmetic() || op.isBitwise()) return self()->getActualType();
    if (op.isRelational() || op.isEquality()) return lang::BooleanType::get();

    return lang::Type::getUndefined();
}

bool lang::IntegerType::validateOperator(lang::BinaryOperator,
                                         lang::ResolvingHandle<lang::Type>,
                                         lang::Location,
                                         lang::Location,
                                         ValidationLogger&) const
{
    return true;
}

std::shared_ptr<lang::Value> lang::IntegerType::buildOperator(lang::BinaryOperator   op,
                                                              std::shared_ptr<Value> left,
                                                              std::shared_ptr<Value> right,
                                                              CompileContext&        context)
{
    return buildOperator(op, left, right, getOperatorResultType(op, right->type()), context);
}

std::shared_ptr<lang::Value> lang::IntegerType::buildOperator(lang::BinaryOperator              op,
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
            if (isSigned()) result = context.ir()->CreateSDiv(left_value, right_value, left_value->getName() + ".sdiv");
            else result = context.ir()->CreateUDiv(left_value, right_value, left_value->getName() + ".udiv");
            break;
        case lang::BinaryOperator::REMAINDER:
            if (isSigned()) result = context.ir()->CreateSRem(left_value, right_value, left_value->getName() + ".srem");
            else result = context.ir()->CreateURem(left_value, right_value, left_value->getName() + ".urem");
            break;
        case lang::BinaryOperator::LESS_THAN:
            if (isSigned())
                result = context.ir()->CreateICmpSLT(left_value, right_value, left_value->getName() + ".icmp");
            else result = context.ir()->CreateICmpULT(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::LESS_THAN_OR_EQUAL:
            if (isSigned())
                result = context.ir()->CreateICmpSLE(left_value, right_value, left_value->getName() + ".icmp");
            else result = context.ir()->CreateICmpULE(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::GREATER_THAN:
            if (isSigned())
                result = context.ir()->CreateICmpSGT(left_value, right_value, left_value->getName() + ".icmp");
            else result = context.ir()->CreateICmpUGT(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::GREATER_THAN_OR_EQUAL:
            if (isSigned())
                result = context.ir()->CreateICmpSGE(left_value, right_value, left_value->getName() + ".icmp");
            else result = context.ir()->CreateICmpUGE(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::EQUAL:
            result = context.ir()->CreateICmpEQ(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::NOT_EQUAL:
            result = context.ir()->CreateICmpNE(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::BITWISE_AND:
            result = context.ir()->CreateAnd(left_value, right_value, left_value->getName() + ".and");
            break;
        case lang::BinaryOperator::BITWISE_OR:
            result = context.ir()->CreateOr(left_value, right_value, left_value->getName() + ".or");
            break;
        case lang::BinaryOperator::BITWISE_XOR:
            result = context.ir()->CreateXor(left_value, right_value, left_value->getName() + ".xor");
            break;
    }

    llvm::Value* native_result = lang::Values::contentToNative(return_type, result, context);
    return std::make_shared<lang::WrappedNativeValue>(return_type, native_result);
}

bool lang::IntegerType::isTriviallyDefaultConstructible() const
{
    return true;
}

bool lang::IntegerType::isTriviallyCopyConstructible() const
{
    return true;
}

bool lang::IntegerType::isTriviallyDestructible() const
{
    return true;
}

llvm::DIType* lang::IntegerType::createDebugType(CompileContext& context)
{
    const llvm::DataLayout& dl = context.module()->getDataLayout();

    std::string name         = std::string(this->name().text());
    uint64_t    size_in_bits = dl.getTypeSizeInBits(getContentType(*context.llvmContext()));
    auto        encoding     = isSigned() ? llvm::dwarf::DW_ATE_signed : llvm::dwarf::DW_ATE_unsigned;

    return context.di()->createBasicType(name, size_in_bits, encoding);
}
