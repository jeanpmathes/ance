#include "IntegerType.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/scope/Scope.h"
#include "lang/type/VectorType.h"

StateCount lang::IntegerType::getStateCount() const
{
    auto bit_size = getBitSize();
    if (bit_size.hasValue())
    {
        size_t const state_count = 1LL << bit_size.value();
        return state_count > 1 ? state_count : std::numeric_limits<size_t>::max();
    }

    return SpecialCount::PLATFORM_DEPENDENT;
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

    return self().isSizeType() && other_integer->isDiffType();
}

bool lang::IntegerType::validateImplicitConversion(lang::Type const&, lang::Location, ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::IntegerType::buildImplicitConversion(lang::Type const&   other,
                                                               Shared<lang::Value> value,
                                                               CompileContext&     context) const
{
    return context.exec().computeConversionOnI(value, other);
}

bool lang::IntegerType::isCastingPossibleTo(lang::Type const& other) const
{
    return other.isIntegerType() || (this->isUnsignedIntegerPointerType() && other.isAddressType())
        || other.isCharType();
}

bool lang::IntegerType::validateCast(lang::Type const&, lang::Location, ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::IntegerType::buildCast(lang::Type const&   other,
                                                 Shared<lang::Value> value,
                                                 CompileContext&     context) const
{
    if (other.isXOrVectorOfX([](auto& t) { return t.isIntegerType(); }))
    {
        return context.exec().computeConversionOnI(value, other);
    }

    if (other.isXOrVectorOfX([](auto& t) { return t.isAddressType(); }))
    {
        return context.exec().computeIntegerToPointer(value, other);
    }

    throw std::logic_error("Invalid cast");
}

bool lang::IntegerType::acceptOverloadRequest(std::vector<ResolvingHandle<lang::Type>> parameters)
{
    if (parameters.size() == 1)
    {
        if (parameters[0]->isIntegerType()) return true;
        if (parameters[0]->isBooleanType()) return true;
    }

    return false;
}

void lang::IntegerType::buildRequestedOverload(std::vector<std::reference_wrapper<lang::Type const>> parameters,
                                               lang::PredefinedFunction&                             function,
                                               CompileContext&                                       context) const
{
    if (parameters.size() == 1) { buildRequestedOverload(parameters[0], self(), function, context); }
}

void lang::IntegerType::buildRequestedOverload(lang::Type const&         parameter_element,
                                               lang::Type const&         return_type,
                                               lang::PredefinedFunction& function,
                                               CompileContext&           context) const
{
    if (parameter_element.isIntegerType() || parameter_element.isBooleanType())
    {
        lang::Type const* parameter_element_ptr = &parameter_element;
        lang::Type const* return_type_ptr       = &return_type;
        lang::Function*   fn                    = &function.function();

        context.exec().defineFunctionBody(
            function.function(),
            [this, parameter_element_ptr, return_type_ptr, fn](CompileContext& cc) {
                Shared<lang::Value> original   = cc.exec().getParameterValue(*fn, 0);
                auto const&         other_type = original->type();

            // Determine whether the value fits into the return type without loss of information.
            // Abort if it doesn't.

                if (auto other_integer_type = parameter_element_ptr->isIntegerType())
                {
                auto this_size      = static_cast<unsigned>(getMinimumBitSize());
                auto other_size     = static_cast<unsigned>(other_integer_type->getMinimumBitSize());
                auto other_capacity = static_cast<unsigned>(other_integer_type->getNativeBitSize());

                std::string const error_message = "Integer conversion would lose information";

                if (this->isSigned() == other_integer_type->isSigned())
                {
                    if (this_size < other_size)
                    {
                        if (isSigned())
                        {
                            llvm::APInt const   min = llvm::APInt::getSignedMinValue(this_size).sext(other_capacity);
                            Shared<lang::Value> min_value = cc.exec().getInteger(min, other_type);
                            Shared<lang::Value> fits_min =
                                cc.exec().performOperator(lang::BinaryOperator::GREATER_THAN_OR_EQUAL,
                                                          original,
                                                               min_value);

                            llvm::APInt const   max = llvm::APInt::getSignedMaxValue(this_size).sext(other_capacity);
                            Shared<lang::Value> max_value = cc.exec().getInteger(max, other_type);
                            Shared<lang::Value> fits_max =
                                cc.exec().performOperator(lang::BinaryOperator::LESS_THAN_OR_EQUAL,
                                                          original,
                                                               max_value);

                            Shared<lang::Value> fits =
                                cc.exec().performOperator(lang::BinaryOperator::BITWISE_AND, fits_min, fits_max);
                            cc.runtime().buildAssert(fits, error_message, cc);
                        }
                        else
                        {
                            llvm::APInt const   max       = llvm::APInt::getMaxValue(this_size).zext(other_capacity);
                            Shared<lang::Value> max_value = cc.exec().getInteger(max, other_type);

                            Shared<lang::Value> fits =
                                cc.exec().performOperator(lang::BinaryOperator::LESS_THAN_OR_EQUAL,
                                                          original,
                                                               max_value);
                            cc.runtime().buildAssert(fits, error_message, cc);
                        }
                    }
                }
                else if (isSigned())// this is signed and original is unsigned.
                {
                    if (this_size <= other_size)
                    {
                        llvm::APInt const   max = llvm::APInt::getSignedMaxValue(this_size).zextOrSelf(other_capacity);
                        Shared<lang::Value> max_value = cc.exec().getInteger(max, other_type);

                        Shared<lang::Value> fits =
                            cc.exec().performOperator(lang::BinaryOperator::LESS_THAN_OR_EQUAL, original,
                                                           max_value);
                        cc.runtime().buildAssert(fits, error_message, cc);
                    }
                }
                else// this is unsigned and original is signed.
                {
                    llvm::APInt const   zero       = llvm::APInt::getNullValue(other_capacity);
                    Shared<lang::Value> zero_value = cc.exec().getInteger(zero, other_type);

                    Shared<lang::Value> fits =
                        cc.exec().performOperator(lang::BinaryOperator::GREATER_THAN_OR_EQUAL, original,
                                                       zero_value);

                    if (this_size < other_size)
                    {
                        llvm::APInt const   max       = llvm::APInt::getMaxValue(this_size).zext(other_capacity);
                        Shared<lang::Value> max_value = cc.exec().getInteger(max, other_type);

                        Shared<lang::Value> fits_max =
                            cc.exec().performOperator(lang::BinaryOperator::LESS_THAN_OR_EQUAL, original,
                                                           max_value);
                        fits = cc.exec().performOperator(lang::BinaryOperator::BITWISE_AND, fits, fits_max);
                    }

                    cc.runtime().buildAssert(fits, error_message, cc);
                }
            }

                if (parameter_element_ptr->isIntegerType())
                {
                    Shared<lang::Value> result = cc.exec().computeConversionOnI(original, *return_type_ptr);
                    cc.exec().performReturn(result);
                }
                else if (parameter_element_ptr->isBooleanType())
                {
                    Shared<lang::Constant> zero = cc.exec().getZero(*return_type_ptr);
                    Shared<lang::Constant> one  = cc.exec().getOne(*return_type_ptr);

                    Shared<lang::Value> result = cc.exec().performSelect(original, one, zero);
                    cc.exec().performReturn(result);
                }
            });
    }
}

bool lang::IntegerType::isOperatorDefined(lang::UnaryOperator op) const
{
    return op == lang::UnaryOperator::BITWISE_NOT || op == lang::UnaryOperator::NEGATION;
}

lang::Type const& lang::IntegerType::getOperatorResultType(lang::UnaryOperator) const
{
    return self();
}

bool lang::IntegerType::validateOperator(lang::UnaryOperator, lang::Location, ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::IntegerType::buildOperator(lang::UnaryOperator op,
                                                     Shared<lang::Value> value,
                                                     CompileContext&     context) const
{
    return context.exec().performOperator(op, value);
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

lang::Type const& lang::IntegerType::getOperatorResultType(lang::BinaryOperator op, lang::Type const&) const
{
    if (op.isArithmetic() || op.isBitwise() || op.isShift()) return self().getActualType();
    if (op.isRelational() || op.isEquality()) return scope().context().getBooleanType();

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
                                                     Shared<lang::Value>  left,
                                                     Shared<lang::Value>  right,
                                                     CompileContext&      context) const
{
    if (right->type().isReferenceType()) right = context.exec().performDereference(right);

    right = context.exec().computeConversionOnI(right, left->type());

    return context.exec().performOperator(op, left, right);
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

void lang::IntegerType::registerExecutionType(CompileContext& context) const
{
    return context.exec().registerIntegerType(self());
}
