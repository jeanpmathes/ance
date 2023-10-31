#include "AddressType.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/construct/value/Value.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/scope/Scope.h"
#include "lang/type/SizeType.h"
#include "lang/type/Type.h"
#include "lang/utility/Values.h"

lang::AddressType const* lang::AddressType::isAddressType() const
{
    return this;
}

StateCount lang::AddressType::getStateCount() const
{
    return SpecialCount::ABSTRACT;
}

bool lang::AddressType::isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const
{
    lang::Type const& real_other = lang::Type::getReferencedType(other);

    if (op.isEquality() || (op == lang::BinaryOperator::SUBTRACTION && getPointeeType() != nullptr))
    {
        return lang::Type::areSame(real_other, self());
    }

    if (op == lang::BinaryOperator::ADDITION && getPointeeType() != nullptr)
    {
        // The size is only required because implicit operator argument casting does not work yet.
        return real_other.isDiffType() || real_other.isSizeType();
    }

    return false;
}

bool lang::AddressType::isCastingPossibleTo(lang::Type const& other) const
{
    if (getStateCount().isUnit()) return false;

    auto* other_address = other.isAddressType();

    bool const cast_to_other_address = other.isAddressType()
                                    && (this->getPointeeType() == nullptr || other_address->getPointeeType() == nullptr
                                        || lang::Type::areSame(*getPointeeType(), *other_address->getPointeeType()));

    return cast_to_other_address || other.isUnsignedIntegerPointerType();
}

bool lang::AddressType::validateCast(lang::Type const&, lang::Location, ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::AddressType::buildCast(lang::ResolvingHandle<lang::Type> other,
                                                 Shared<Value>                     value,
                                                 CompileContext&                   context)
{
    if (other->isAddressType())
    {
        value->buildContentValue(context);
        llvm::Value* content = value->getContentValue();

        llvm::Value* result_content = context.ir().CreateBitCast(content,
                                                                 other->getContentType(context.llvmContext()),
                                                                 content->getName() + ".bitcast");

        llvm::Value* result_native = lang::values::contentToNative(other, result_content, context);

        return makeShared<lang::WrappedNativeValue>(other, result_native);
    }

    if (other->isUnsignedIntegerPointerType())
    {
        value->buildContentValue(context);
        llvm::Value* content = value->getContentValue();

        llvm::Value* result_content = context.ir().CreatePtrToInt(content,
                                                                  other->getContentType(context.llvmContext()),
                                                                  content->getName() + ".ptrtoint");

        llvm::Value* result_native = lang::values::contentToNative(other, result_content, context);

        return makeShared<lang::WrappedNativeValue>(other, result_native);
    }

    throw std::logic_error("Invalid cast");
}

lang::ResolvingHandle<lang::Type> lang::AddressType::getOperatorResultType(lang::BinaryOperator op,
                                                                           lang::ResolvingHandle<lang::Type>)
{
    if (op.isEquality()) return scope()->context().getBooleanType();

    if (op == lang::BinaryOperator::ADDITION) return self();

    if (op == lang::BinaryOperator::SUBTRACTION) return scope()->context().getDiffType();

    return lang::Type::getUndefined();
}

bool lang::AddressType::validateOperator(lang::BinaryOperator,
                                         lang::Type const&,
                                         lang::Location,
                                         lang::Location,
                                         ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::AddressType::buildOperator(lang::BinaryOperator op,
                                                     Shared<Value>        left,
                                                     Shared<Value>        right,
                                                     CompileContext&      context)
{
    right = lang::Type::getValueOrReferencedValue(right, context);

    left->buildContentValue(context);
    right->buildContentValue(context);

    llvm::Value* left_value  = left->getContentValue();
    llvm::Value* right_value = right->getContentValue();

    llvm::Value* result;

    switch (op)
    {
        case lang::BinaryOperator::EQUAL:
            result = context.ir().CreateICmpEQ(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::NOT_EQUAL:
            result = context.ir().CreateICmpNE(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::ADDITION:
            if (getPointeeType().value()->getStateCount().isUnit())
                result = getOperatorResultType(op, right->type())->getDefaultContent(context.llvmModule());
            else
                result = context.ir().CreateGEP(getPointeeType().value()->getContentType(context.llvmContext()),
                                                left_value,
                                                right_value,
                                                left_value->getName() + ".gep");
            break;
        case lang::BinaryOperator::SUBTRACTION:
            if (getPointeeType().value()->getStateCount().isUnit())
                result = getOperatorResultType(op, right->type())->getDefaultContent(context.llvmModule());
            else
            {
                result = context.ir().CreatePtrDiff(getPointeeType().value()->getContentType(context.llvmContext()),
                                                    left_value,
                                                    right_value,
                                                    left_value->getName() + ".ptrdiff");
                result =
                    context.ir().CreateIntCast(result,
                                               context.types().getDiffType()->getContentType(context.llvmContext()),
                                               true,
                                               left_value->getName() + ".icast");
            }
            break;

        default:
            throw std::logic_error("Invalid operator for address type");
    }

    lang::ResolvingHandle<lang::Type> result_type   = getOperatorResultType(op, right->type());
    llvm::Value*                      native_result = lang::values::contentToNative(result_type, result, context);

    return makeShared<lang::WrappedNativeValue>(result_type, native_result);
}
