#include "MemberAccess.h"

#include "lang/ApplicationVisitor.h"
#include "lang/statement/Statement.h"
#include "lang/type/ReferenceType.h"
#include "validation/ValidationLogger.h"

MemberAccess::MemberAccess(Owned<Expression> value, lang::Identifier member, lang::Location location)
    : Expression(location)
    , value_(std::move(value))
    , member_(member)
{
    addSubexpression(*value_);
}

Expression const& MemberAccess::value() const
{
    return *value_;
}

lang::Identifier const& MemberAccess::member() const
{
    return member_;
}

void MemberAccess::walkDefinitions()
{
    Expression::walkDefinitions();

    type();
}

void MemberAccess::defineType(lang::ResolvingHandle<lang::Type> type)
{
    if (!isInitialized()) return;

    auto value_type = value_->type();

    if (value_type->isDefined() && value_type->hasMember(member_))
    {
        type.reroute(scope().context().getReferenceType(value_type->getMember(member_).type()));
    }
}

bool MemberAccess::validate(ValidationLogger& validation_logger) const
{
    if (!value_->validate(validation_logger)) return false;

    if (!value_->type().hasMember(member_))
    {
        validation_logger.logError("Type " + value_->type().getAnnotatedName() + " has no member '" + member_ + "'",
                                   member_.location());
        return false;
    }

    return value_->type().validateMemberAccess(member_, validation_logger);
}

Expression::Expansion MemberAccess::expandWith(Expressions subexpressions, lang::Context&) const
{
    return {Statements(), makeOwned<MemberAccess>(std::move(subexpressions[0]), member_, location()), Statements()};
}

MemberAccess::~MemberAccess() = default;
