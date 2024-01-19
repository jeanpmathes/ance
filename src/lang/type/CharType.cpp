#include "CharType.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/construct/value/RoughlyCastedValue.h"
#include "lang/construct/value/Value.h"
#include "lang/type/Type.h"

lang::CharType::CharType() : TypeDefinition(lang::Identifier::like("char")) {}

StateCount lang::CharType::getStateCount() const
{
    size_t const state_count = 1ULL << SIZE_IN_BITS;
    return state_count;
}

bool lang::CharType::isCharType() const
{
    return true;
}

bool lang::CharType::isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const
{
    if (lang::Type::getReferencedType(other).isCharType() && op.isEquality()) return true;
    return false;
}

lang::ResolvingHandle<lang::Type> lang::CharType::getOperatorResultType(lang::BinaryOperator op,
                                                                        lang::ResolvingHandle<lang::Type>)
{
    if (op.isEquality()) return scope().context().getBooleanType();

    return lang::Type::getUndefined();
}

bool lang::CharType::validateOperator(lang::BinaryOperator,
                                      lang::Type const&,
                                      lang::Location,
                                      lang::Location,
                                      ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::CharType::buildOperator(lang::BinaryOperator op,
                                                  Shared<lang::Value>  left,
                                                  Shared<lang::Value>  right,
                                                  CompileContext&      context)
{
    if (right->type()->isReferenceType()) right = context.exec().performDereference(right);

    lang::ResolvingHandle<lang::Type> int_type = context.ctx().getFixedWidthIntegerType(SIZE_IN_BITS, false);

    Shared<lang::Value> left_as_int  = makeShared<lang::RoughlyCastedValue>(int_type, left, context);
    Shared<lang::Value> right_as_int = makeShared<lang::RoughlyCastedValue>(int_type, right, context);

    return context.exec().performOperator(op, left_as_int, right_as_int);
}

bool lang::CharType::isCastingPossibleTo(lang::Type const& other) const
{
    if (other.isFixedWidthIntegerType(SIZE_IN_BITS, false)) return true;

    return TypeDefinition::isCastingPossibleTo(other);
}

bool lang::CharType::validateCast(lang::Type const& other,
                                  lang::Location    location,
                                  ValidationLogger& validation_logger) const
{
    return TypeDefinition::validateCast(other, location, validation_logger);
}

Shared<lang::Value> lang::CharType::buildCast(lang::ResolvingHandle<lang::Type> other,
                                              Shared<lang::Value>               value,
                                              CompileContext&                   context)
{
    if (other->isFixedWidthIntegerType(SIZE_IN_BITS, false))
    {
        return makeShared<lang::RoughlyCastedValue>(other, value, context);
    }

    return TypeDefinition::buildCast(other, value, context);
}

bool lang::CharType::isTriviallyDefaultConstructible() const
{
    return true;
}

bool lang::CharType::isTriviallyCopyConstructible() const
{
    return true;
}

bool lang::CharType::isTriviallyDestructible() const
{
    return true;
}

std::string lang::CharType::createMangledName() const
{
    return "c";
}

Execution::Type lang::CharType::createExecutionType(CompileContext& context) const
{
    return context.exec().registerCodepointType(self());
}

lang::ResolvingHandle<lang::Type> lang::CharType::clone(lang::Context& new_context) const
{
    return new_context.getCharType();
}
