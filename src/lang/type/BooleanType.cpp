#include "BooleanType.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/construct/value/Value.h"
#include "lang/type/Type.h"
#include "lang/type/VectorType.h"

lang::BooleanType::BooleanType() : TypeDefinition(lang::Identifier::like("bool")) {}

StateCount lang::BooleanType::getStateCount() const
{
    size_t const count = 2;
    return count;
}

bool lang::BooleanType::isBooleanType() const
{
    return true;
}

bool lang::BooleanType::isTriviallyDefaultConstructible() const
{
    return true;
}

bool lang::BooleanType::isTriviallyCopyConstructible() const
{
    return true;
}

bool lang::BooleanType::isTriviallyDestructible() const
{
    return true;
}

std::string lang::BooleanType::createMangledName() const
{
    return "b";
}

Execution::Type lang::BooleanType::createExecutionType(CompileContext& context) const
{
    return context.exec().registerBooleanType(self());
}

bool lang::BooleanType::isOperatorDefined(lang::UnaryOperator op) const
{
    return op == lang::UnaryOperator::NOT || op == lang::UnaryOperator::BITWISE_NOT;
}

lang::ResolvingHandle<lang::Type> lang::BooleanType::getOperatorResultType(lang::UnaryOperator)
{
    return self();
}

bool lang::BooleanType::validateOperator(lang::UnaryOperator, lang::Location, ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::BooleanType::buildOperator(lang::UnaryOperator op,
                                                     Shared<lang::Value> value,
                                                     CompileContext&     context)
{
    return context.exec().performOperator(op, value);
}

bool lang::BooleanType::isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const
{
    if (!op.isEquality() && !op.isBitwise()) return false;

    return lang::Type::getReferencedType(other).isBooleanType();
}

lang::ResolvingHandle<lang::Type> lang::BooleanType::getOperatorResultType(lang::BinaryOperator op,
                                                                           lang::ResolvingHandle<lang::Type>)
{
    if (op.isEquality() || op.isBitwise()) return self();

    return lang::Type::getUndefined();
}

bool lang::BooleanType::validateOperator(lang::BinaryOperator,
                                         lang::Type const&,
                                         lang::Location,
                                         lang::Location,
                                         ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::BooleanType::buildOperator(lang::BinaryOperator op,
                                                     Shared<lang::Value>  left,
                                                     Shared<lang::Value>  right,
                                                     CompileContext&      context)
{
    if (right->type()->isReferenceType()) right = context.exec().performDereference(right);

    return context.exec().performOperator(op, left, right);
}

bool lang::BooleanType::acceptOverloadRequest(std::vector<ResolvingHandle<lang::Type>> parameters)
{
    if (parameters.size() == 1)
    {
        return parameters[0]->isFixedWidthIntegerType() || parameters[0]->isSizeType() || parameters[0]->isDiffType();
    }

    return false;
}

void lang::BooleanType::buildRequestedOverload(std::vector<lang::ResolvingHandle<lang::Type>> parameters,
                                               lang::PredefinedFunction&                      function,
                                               CompileContext&                                context)
{
    if (parameters.size() == 1) { buildRequestedOverload(parameters[0], self(), function, context); }
}

void lang::BooleanType::buildRequestedOverload(lang::ResolvingHandle<lang::Type> parameter_element,
                                               lang::ResolvingHandle<lang::Type> return_type,
                                               lang::PredefinedFunction&         function,
                                               CompileContext&                   context)
{
    if (parameter_element->isFixedWidthIntegerType() || parameter_element->isSizeType()
        || parameter_element->isDiffType())
    {
        context.exec().enterFunctionBody(function.getFunctionHandle(context));
        {
            Shared<lang::Value> original = function.getArgument(0);

            Shared<lang::Constant> zero = context.exec().getZero(original->type());
            Shared<lang::Value>    is_nonzero =
                context.exec().performOperator(lang::BinaryOperator::NOT_EQUAL, original, zero);

            Shared<lang::Constant> true_const  = context.exec().getBoolean(true, return_type);
            Shared<lang::Constant> false_const = context.exec().getBoolean(false, return_type);
            Shared<lang::Value>    converted   = context.exec().performSelect(is_nonzero, true_const, false_const);

            context.exec().performReturn(converted);
        }
    }
}

lang::ResolvingHandle<lang::Type> lang::BooleanType::clone(lang::Context& new_context) const
{
    return new_context.getBooleanType();
}
