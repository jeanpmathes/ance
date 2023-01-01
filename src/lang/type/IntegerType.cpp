#include "IntegerType.h"

#include "BooleanType.h"
#include "compiler/CompileContext.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/utility/Values.h"

StateCount lang::IntegerType::getStateCount() const
{
    auto bit_size = getBitSize();
    if (bit_size.hasValue())
    {
        size_t state_count = 1 << bit_size.value();
        return state_count;
    }

    return SpecialCount::PLATFORM_DEPENDENT;
}

llvm::Constant* lang::IntegerType::getDefaultContent(llvm::Module& m) const
{
    return llvm::ConstantInt::get(getContentType(m.getContext()), 0, false);
}

llvm::Type* lang::IntegerType::getContentType(llvm::LLVMContext& c) const
{
    return llvm::Type::getIntNTy(c, static_cast<unsigned>(getNativeBitSize()));
}

lang::IntegerType const* lang::IntegerType::isIntegerType() const
{
    return this;
}

bool lang::IntegerType::isImplicitlyConvertibleTo(lang::Type const& other) const
{
    auto other_integer = other.isIntegerType();
    if (not other_integer) return false;

    auto         this_bit_size  = getBitSize();
    size_t const other_bit_size = other_integer->getBitSize().valueOr(other_integer->getMinimumBitSize());

    if (this_bit_size.hasValue())
    {
        bool const can_enlarge = (this_bit_size.value() <= other_bit_size) && (isSigned() == other_integer->isSigned());
        bool const can_gain_sign = (this_bit_size.value() < other_bit_size) && !isSigned() && other_integer->isSigned();

        return can_enlarge || can_gain_sign;
    }

    return self()->isSizeType() && other_integer->isDiffType();
}

bool lang::IntegerType::validateImplicitConversion(lang::Type const&, lang::Location, ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::IntegerType::buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                               Shared<Value>                     value,
                                                               CompileContext&                   context)
{
    value->buildContentValue(context);
    llvm::Value* content_value = value->getContentValue();

    llvm::Value* converted_value        = context.ir().CreateIntCast(content_value,
                                                              other->getContentType(context.llvmContext()),
                                                              isSigned(),
                                                              content_value->getName() + ".icast");
    llvm::Value* native_converted_value = lang::values::contentToNative(other, converted_value, context);

    return makeShared<WrappedNativeValue>(other, native_converted_value);
}

bool lang::IntegerType::acceptOverloadRequest(std::vector<ResolvingHandle<lang::Type>> parameters)
{
    if (parameters.size() == 1)
    {
        if (parameters[0]->isIntegerType()) return true;
        if (parameters[0]->isBooleanType()) return true;
        if (parameters[0]->isFloatingPointType()) return true;
    }

    return false;
}

void lang::IntegerType::buildRequestedOverload(std::vector<lang::ResolvingHandle<lang::Type>> parameters,
                                               lang::PredefinedFunction&                      function,
                                               CompileContext&                                context)
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
        llvm::BasicBlock* block = llvm::BasicBlock::Create(context.llvmContext(), "block", native_function);
        context.ir().SetInsertPoint(block);
        {
            llvm::Value* original = native_function->getArg(0);

            llvm::Value* converted = context.ir().CreateIntCast(original,
                                                                return_type->getContentType(context.llvmContext()),
                                                                parameter_element->isSigned(),
                                                                original->getName() + ".icast");
            context.ir().CreateRet(converted);
        }
    }

    if (parameter_element->isFloatingPointType())
    {
        llvm::BasicBlock* block = llvm::BasicBlock::Create(context.llvmContext(), "block", native_function);
        context.ir().SetInsertPoint(block);
        {
            llvm::Value* original = native_function->getArg(0);
            llvm::Value* converted;

            if (isSigned())
            {
                converted = context.ir().CreateFPToSI(original,
                                                      return_type->getContentType(context.llvmContext()),
                                                      original->getName() + ".fptosi");
            }
            else
            {
                converted = context.ir().CreateFPToUI(original,
                                                      return_type->getContentType(context.llvmContext()),
                                                      original->getName() + ".fptoui");
            }

            context.ir().CreateRet(converted);
        }
    }
}

bool lang::IntegerType::isOperatorDefined(lang::UnaryOperator op) const
{
    return op == lang::UnaryOperator::BITWISE_NOT || op == lang::UnaryOperator::NEGATION;
}

lang::ResolvingHandle<lang::Type> lang::IntegerType::getOperatorResultType(lang::UnaryOperator)
{
    return self();
}

bool lang::IntegerType::validateOperator(lang::UnaryOperator, lang::Location, ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::IntegerType::buildOperator(lang::UnaryOperator op,
                                                     Shared<Value>       value,
                                                     CompileContext&     context)
{
    return buildOperator(op, value, getOperatorResultType(op), context);
}

Shared<lang::Value> lang::IntegerType::buildOperator(lang::UnaryOperator               op,
                                                     Shared<Value>                     value,
                                                     lang::ResolvingHandle<lang::Type> return_type,
                                                     CompileContext&                   context)
{
    value->buildContentValue(context);
    llvm::Value* content_value = value->getContentValue();

    llvm::Value* result;

    switch (op)
    {
        case lang::UnaryOperator::BITWISE_NOT:
            result = context.ir().CreateNot(content_value, content_value->getName() + ".not");
            break;

        case lang::UnaryOperator::NEGATION:
            result = context.ir().CreateNeg(content_value, content_value->getName() + ".neg");
            break;

        default:
            assert(false);
            result = nullptr;
    }

    llvm::Value* native_result = lang::values::contentToNative(return_type, result, context);
    return makeShared<lang::WrappedNativeValue>(return_type, native_result);
}

bool lang::IntegerType::isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const
{
    if (!op.isArithmetic() && !op.isBitwise() && !op.isRelational() && !op.isEquality() && !op.isShift()) return false;

    lang::Type const& real_other = lang::Type::getReferencedType(other);

    if (auto other_integer = real_other.isIntegerType())
    {
        if (op.isShift()) return !other_integer->isSigned();

        if (this == other_integer) return true;

        auto this_bit_size  = getBitSize();
        auto other_bit_size = other_integer->getBitSize();

        if (this_bit_size.hasValue() && other_bit_size.hasValue())
        {
            return (this_bit_size.value() == other_bit_size.value()) && (isSigned() == other_integer->isSigned());
        }
    }

    return false;
}

lang::ResolvingHandle<lang::Type> lang::IntegerType::getOperatorResultType(lang::BinaryOperator op,
                                                                           lang::ResolvingHandle<lang::Type>)
{
    if (op.isArithmetic() || op.isBitwise() || op.isShift()) return self()->getActualType();
    if (op.isRelational() || op.isEquality()) return lang::BooleanType::get();

    return lang::Type::getUndefined();
}

bool lang::IntegerType::validateOperator(lang::BinaryOperator,
                                         lang::Type const&,
                                         lang::Location,
                                         lang::Location,
                                         ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::IntegerType::buildOperator(lang::BinaryOperator op,
                                                     Shared<Value>        left,
                                                     Shared<Value>        right,
                                                     CompileContext&      context)
{
    return buildOperator(op, left, right, getOperatorResultType(op, right->type()), context);
}

Shared<lang::Value> lang::IntegerType::buildOperator(lang::BinaryOperator              op,
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
            result = context.ir().CreateAdd(left_value, right_value, left_value->getName() + ".add");
            break;
        case lang::BinaryOperator::SUBTRACTION:
            result = context.ir().CreateSub(left_value, right_value, left_value->getName() + ".sub");
            break;
        case lang::BinaryOperator::MULTIPLICATION:
            result = context.ir().CreateMul(left_value, right_value, left_value->getName() + ".mul");
            break;
        case lang::BinaryOperator::DIVISION:
            if (isSigned()) result = context.ir().CreateSDiv(left_value, right_value, left_value->getName() + ".sdiv");
            else result = context.ir().CreateUDiv(left_value, right_value, left_value->getName() + ".udiv");
            break;
        case lang::BinaryOperator::REMAINDER:
            if (isSigned()) result = context.ir().CreateSRem(left_value, right_value, left_value->getName() + ".srem");
            else result = context.ir().CreateURem(left_value, right_value, left_value->getName() + ".urem");
            break;
        case lang::BinaryOperator::LESS_THAN:
            if (isSigned())
                result = context.ir().CreateICmpSLT(left_value, right_value, left_value->getName() + ".icmp");
            else result = context.ir().CreateICmpULT(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::LESS_THAN_OR_EQUAL:
            if (isSigned())
                result = context.ir().CreateICmpSLE(left_value, right_value, left_value->getName() + ".icmp");
            else result = context.ir().CreateICmpULE(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::GREATER_THAN:
            if (isSigned())
                result = context.ir().CreateICmpSGT(left_value, right_value, left_value->getName() + ".icmp");
            else result = context.ir().CreateICmpUGT(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::GREATER_THAN_OR_EQUAL:
            if (isSigned())
                result = context.ir().CreateICmpSGE(left_value, right_value, left_value->getName() + ".icmp");
            else result = context.ir().CreateICmpUGE(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::EQUAL:
            result = context.ir().CreateICmpEQ(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::NOT_EQUAL:
            result = context.ir().CreateICmpNE(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::BITWISE_AND:
            result = context.ir().CreateAnd(left_value, right_value, left_value->getName() + ".and");
            break;
        case lang::BinaryOperator::BITWISE_OR:
            result = context.ir().CreateOr(left_value, right_value, left_value->getName() + ".or");
            break;
        case lang::BinaryOperator::BITWISE_XOR:
            result = context.ir().CreateXor(left_value, right_value, left_value->getName() + ".xor");
            break;
        case lang::BinaryOperator::SHIFT_LEFT:
            right_value = context.ir().CreateIntCast(right_value, left_value->getType(), false);
            result      = context.ir().CreateShl(left_value, right_value, left_value->getName() + ".shl");
            break;
        case lang::BinaryOperator::SHIFT_RIGHT:
            right_value = context.ir().CreateIntCast(right_value, left_value->getType(), false);
            if (isSigned()) result = context.ir().CreateAShr(left_value, right_value, left_value->getName() + ".ashr");
            else result = context.ir().CreateLShr(left_value, right_value, left_value->getName() + ".lshr");
            break;
    }

    llvm::Value* native_result = lang::values::contentToNative(return_type, result, context);
    return makeShared<lang::WrappedNativeValue>(return_type, native_result);
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

llvm::DIType* lang::IntegerType::createDebugType(CompileContext& context) const
{
    llvm::DataLayout const& dl = context.llvmModule().getDataLayout();

    std::string const name         = std::string(this->name().text());
    uint64_t const    size_in_bits = dl.getTypeSizeInBits(getContentType(context.llvmContext()));
    auto              encoding     = isSigned() ? llvm::dwarf::DW_ATE_signed : llvm::dwarf::DW_ATE_unsigned;

    return context.di().createBasicType(name, size_in_bits, encoding);
}
