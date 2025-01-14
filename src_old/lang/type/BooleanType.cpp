#include "BooleanType.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/construct/Value.h"
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

void lang::BooleanType::registerExecutionType(Execution& exec) const
{
    return exec.registerBooleanType(self());
}

bool lang::BooleanType::isOperatorDefined(lang::UnaryOperator op) const
{
    return op == lang::UnaryOperator::NOT || op == lang::UnaryOperator::BITWISE_NOT;
}

lang::Type const& lang::BooleanType::getOperatorResultType(lang::UnaryOperator) const
{
    return self();
}

bool lang::BooleanType::validateOperator(lang::UnaryOperator, lang::Location, ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::BooleanType::execOperator(lang::UnaryOperator op,
                                                    Shared<lang::Value> value,
                                                     Execution&          exec) const
{
    return exec.performOperator(op, value);
}

bool lang::BooleanType::isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const
{
    if (!op.isEquality() && !op.isBitwise()) return false;

    return lang::Type::getReferencedType(other).isBooleanType();
}

lang::Type const& lang::BooleanType::getOperatorResultType(lang::BinaryOperator op, lang::Type const&) const
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

Shared<lang::Value> lang::BooleanType::execOperator(lang::BinaryOperator op,
                                                    Shared<lang::Value>  left,
                                                     Shared<lang::Value>  right,
                                                     Execution&           exec) const
{
    if (right->type().isReferenceType()) right = exec.performDereference(right);

    return exec.performOperator(op, left, right);
}

bool lang::BooleanType::acceptOverloadRequest(std::vector<ResolvingHandle<lang::Type>> parameters)
{
    if (parameters.size() == 1)
    {
        return parameters[0]->isFixedWidthIntegerType() || parameters[0]->isSizeType() || parameters[0]->isDiffType();
    }

    return false;
}

void lang::BooleanType::execRequestedOverload(std::vector<std::reference_wrapper<lang::Type const>> parameters,
                                              lang::PredefinedFunction&                             function,
                                               Execution&                                            exec) const
{
    if (parameters.size() == 1) { execRequestedOverload(parameters[0], self(), function, exec); }
}

void lang::BooleanType::execRequestedOverload(lang::Type const&         parameter_element,
                                              lang::Type const&         return_type,
                                               lang::PredefinedFunction& function,
                                               Execution&                exec) const
{
    if (parameter_element.isFixedWidthIntegerType() || parameter_element.isSizeType() || parameter_element.isDiffType())
    {
        lang::Type const* return_type_ptr = &return_type;

        exec.defineFunctionBody(function.function(), [return_type_ptr](Execution::FnCtx& ctx) {
            Shared<lang::Value> original = ctx.getParameterValue(0);

            Shared<lang::Constant> zero = ctx.exec().getZero(original->type());
            Shared<lang::Value>    is_nonzero =
                ctx.exec().performOperator(lang::BinaryOperator::NOT_EQUAL, original, zero);

            Shared<lang::Constant> true_const  = ctx.exec().getBoolean(true, *return_type_ptr);
            Shared<lang::Constant> false_const = ctx.exec().getBoolean(false, *return_type_ptr);
            Shared<lang::Value>    converted   = ctx.exec().performSelect(is_nonzero, true_const, false_const);

            ctx.exec().performReturn(converted);
        });
    }
}

lang::ResolvingHandle<lang::Type> lang::BooleanType::clone(lang::Context& new_context) const
{
    return new_context.getBooleanType();
}
