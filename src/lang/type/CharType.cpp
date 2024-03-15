#include "CharType.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/construct/Value.h"
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

lang::Type const& lang::CharType::getOperatorResultType(lang::BinaryOperator op,
                                                                        lang::Type const&) const
{
    if (op.isEquality()) return scope().context().getBooleanType();

    static lang::ResolvingHandle<lang::Type> undefined = lang::Type::getUndefined();
    return undefined;
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
                                                  CompileContext&      context) const
{
    if (right->type().isReferenceType()) right = context.exec().performDereference(right);

    lang::ResolvingHandle<lang::Type> int_type = context.ctx().getFixedWidthIntegerType(SIZE_IN_BITS, false);

    Shared<lang::Value> left_as_int  = context.exec().performIntegerReinterpretation(left, int_type);
    Shared<lang::Value> right_as_int = context.exec().performIntegerReinterpretation(right, int_type);

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

Shared<lang::Value> lang::CharType::buildCast(lang::Type const& other,
                                              Shared<lang::Value>               value,
                                              CompileContext&                   context) const
{
    if (other.isFixedWidthIntegerType(SIZE_IN_BITS, false))
    {
        return context.exec().performIntegerReinterpretation(value, other);
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

void lang::CharType::registerExecutionType(CompileContext& context) const
{
    return context.exec().registerCodepointType(self());
}

lang::ResolvingHandle<lang::Type> lang::CharType::clone(lang::Context& new_context) const
{
    return new_context.getCharType();
}
