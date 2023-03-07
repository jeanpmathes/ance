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

void MemberAccess::defineType(lang::ResolvingHandle<lang::Type>& type)
{
    auto value_type = value_->type();

    if (value_type->isDefined())
    {
        type.reroute(scope()->context().getReferenceType(value_type->getMemberType(member_)));
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

void MemberAccess::doBuild(CompileContext& context)
{
    Shared<lang::Value> value = value_->type()->buildMemberAccess(value_->getValue(), member_, context);
    setValue(value);
}

MemberAccess::~MemberAccess() = default;
