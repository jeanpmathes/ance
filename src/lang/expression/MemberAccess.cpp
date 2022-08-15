#include "MemberAccess.h"

#include "lang/statement/Statement.h"
#include "lang/type/ReferenceType.h"
#include "validation/ValidationLogger.h"

MemberAccess::MemberAccess(std::unique_ptr<Expression> value, lang::Identifier member, lang::Location location)
    : Expression(location)
    , value_(std::move(value))
    , member_(member)
{
    addSubexpression(*value_);
}

Expression& MemberAccess::value() const
{
    return *value_;
}

const lang::Identifier& MemberAccess::member() const
{
    return member_;
}

std::optional<lang::ResolvingHandle<lang::Type>> MemberAccess::tryGetType() const
{
    auto value_type_opt = value_->tryGetType();
    if (!value_type_opt) return std::nullopt;
    auto value_type = *value_type_opt;

    return lang::ReferenceType::get(value_type->getMemberType(member_));
}

bool MemberAccess::validate(ValidationLogger& validation_logger) const
{
    if (!value_->validate(validation_logger)) return false;

    if (!value_->type()->hasMember(member_))
    {
        validation_logger.logError("Type " + value_->type()->getAnnotatedName() + " has no member '" + member_ + "'",
                                   member_.location());
        return false;
    }

    return value_->type()->validateMemberAccess(member_, validation_logger);
}

Expression::Expansion MemberAccess::expandWith(Expressions subexpressions) const
{
    return {Statements(),
            std::make_unique<MemberAccess>(std::move(subexpressions[0]), member_, location()),
            Statements()};
}

void MemberAccess::doBuild(CompileContext& context)
{
    std::shared_ptr<lang::Value> value = value_->type()->buildMemberAccess(value_->getValue(), member_, context);
    setValue(value);
}

MemberAccess::~MemberAccess() = default;
