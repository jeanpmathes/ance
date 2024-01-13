#include "Cast.h"

#include "lang/ApplicationVisitor.h"
#include "lang/type/TypeDefinition.h"

Cast::Cast(Owned<Expression>                 value,
           lang::ResolvingHandle<lang::Type> type,
           lang::Location                    location,
           lang::Location                    type_location)
    : Expression(location)
    , value_(std::move(value))
    , type_(std::move(type))
    , type_location_(type_location)
{
    addSubexpression(*value_);
}

Expression const& Cast::value() const
{
    return *value_;
}

lang::Type const& Cast::type() const
{
    return *type_.as<lang::Type>();
}

void Cast::defineType(lang::ResolvingHandle<lang::Type> type)
{
    if (type_.is<lang::Type>()) type.reroute(*type_.as<lang::Type>());
}

void Cast::walkDefinitions()
{
    Expression::walkDefinitions();

    scope().registerUsage(type_);
}

bool Cast::validate(ValidationLogger& validation_logger) const
{
    if (lang::Type::checkMismatch<lang::Type>(type_, "type", type_location_, validation_logger)) return false;
    if (!value_->validate(validation_logger)) return false;

    auto const& source_type      = value_->type();
    auto const& destination_type = *type_.as<lang::Type>();

    if (!source_type.isCastingPossibleTo(destination_type))
    {
        validation_logger.logError("No cast defined from type " + source_type.getAnnotatedName() + " to "
                                       + destination_type.getAnnotatedName(),
                                   location());
        return false;
    }

    bool const valid = source_type.validateCast(destination_type, location(), validation_logger);

    if (valid)
    {
        if (lang::Type::areSame(source_type, destination_type))
        {
            validation_logger.logWarning("Cast is redundant", location());
        }
        else if (source_type.isImplicitlyConvertibleTo(destination_type))
        {
            validation_logger.logWarning("Cast can be replaced with implicit conversion", location());
        }
    }

    return valid;
}

Expression::Expansion Cast::expandWith(Expressions subexpressions, lang::Context& new_context) const
{
    return {Statements(),
            makeOwned<Cast>(std::move(subexpressions[0]),
                            type_->getUndefinedClone<lang::Type>(new_context),
                            type_location_,
                            location()),
            Statements()};
}

void Cast::doBuild(CompileContext& context)
{
    auto target_type = lang::Type::makeMatching<lang::Type>(type_);

    Shared<lang::Value> value = value_->getValue();

    if (lang::Type::areSame(value->type(), *target_type)) { setValue(value); }
    else
    {
        Shared<lang::Value> casted_value = value->type()->buildCast(target_type, value, context);
        setValue(casted_value);
    }
}

Cast::~Cast() = default;
