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

bool lang::AddressType::isAddressType() const
{
    return true;
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
            result = context.ir().CreateGEP(getPointeeType().value()->getContentType(context.llvmContext()),
                                            left_value,
                                            right_value,
                                            left_value->getName() + ".gep");
            break;
        case lang::BinaryOperator::SUBTRACTION:
            result = context.ir().CreatePtrDiff(getPointeeType().value()->getContentType(context.llvmContext()),
                                                left_value,
                                                right_value,
                                                left_value->getName() + ".ptrdiff");
            result = context.ir().CreateIntCast(result,
                                                context.types().getDiffType()->getContentType(context.llvmContext()),
                                                true,
                                                left_value->getName() + ".icast");
            break;

        default:
            throw std::logic_error("Invalid operator for address type");
    }

    lang::ResolvingHandle<lang::Type> result_type   = getOperatorResultType(op, right->type());
    llvm::Value*                      native_result = lang::values::contentToNative(result_type, result, context);

    return makeShared<lang::WrappedNativeValue>(result_type, native_result);
}

bool lang::AddressType::acceptOverloadRequest(std::vector<ResolvingHandle<lang::Type>> parameters)
{
    return parameters.size() == 1 && (parameters[0]->isAddressType() || parameters[0]->isUnsignedIntegerPointerType());
}

void lang::AddressType::buildRequestedOverload(std::vector<lang::ResolvingHandle<lang::Type>> parameters,
                                               lang::PredefinedFunction&                      function,
                                               CompileContext&                                context)
{
    if (parameters.size() == 1) { buildRequestedOverload(parameters[0], self(), function, context); }
}

void lang::AddressType::buildRequestedOverload(lang::ResolvingHandle<lang::Type> parameter_element,
                                               lang::ResolvingHandle<lang::Type> return_type,
                                               lang::PredefinedFunction&         function,
                                               CompileContext&                   context)
{
    llvm::Function* native_function;
    std::tie(std::ignore, native_function) = function.getNativeRepresentation();

    if (parameter_element->isAddressType())
    {
        llvm::BasicBlock* block = llvm::BasicBlock::Create(context.llvmContext(), "block", native_function);
        context.ir().SetInsertPoint(block);
        {
            llvm::Value* original = native_function->getArg(0);

            llvm::Value* converted = context.ir().CreateBitCast(original,
                                                                return_type->getContentType(context.llvmContext()),
                                                                original->getName() + ".bitcast");

            context.ir().CreateRet(converted);
        }
    }

    if (parameter_element->isUnsignedIntegerPointerType())
    {
        llvm::BasicBlock* block = llvm::BasicBlock::Create(context.llvmContext(), "block", native_function);
        context.ir().SetInsertPoint(block);
        {
            llvm::Value* original = native_function->getArg(0);

            llvm::Value* converted = context.ir().CreateIntToPtr(original,
                                                                 return_type->getContentType(context.llvmContext()),
                                                                 original->getName() + ".inttoptr");

            context.ir().CreateRet(converted);
        }
    }
}
