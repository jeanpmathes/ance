#include "Member.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/Constant.h"
#include "lang/construct/Value.h"
#include "lang/scope/Scope.h"
#include "lang/utility/Storage.h"
#include "validation/ValidationLogger.h"

lang::Member::Member(lang::AccessModifier               access,
                     lang::Identifier                   name,
                     lang::ResolvingHandle<lang::Type>  type,
                     lang::Assigner                     assigner,
                     Optional<Owned<LiteralExpression>> constant_init,
                     lang::Location                     location,
                     lang::Location                     type_location)
    : access_(access)
    , name_(name)
    , type_(type)
    , assigner_(assigner)
    , constant_init_(std::move(constant_init))
    , location_(location)
    , type_location_(type_location)
{}

lang::AccessModifier lang::Member::access() const
{
    return access_;
}

lang::Identifier const& lang::Member::name() const
{
    return name_;
}

lang::ResolvingHandle<lang::Type> lang::Member::type()
{
    return type_;
}

lang::Type const& lang::Member::type() const
{
    return type_;
}

lang::Assigner lang::Member::assigner() const
{
    return assigner_;
}

lang::Location lang::Member::location() const
{
    return location_;
}

void lang::Member::setIndex(size_t index)
{
    assert(index_ == std::numeric_limits<size_t>::max());
    assert(index != std::numeric_limits<size_t>::max());

    index_ = index;
}

size_t lang::Member::index() const
{
    assert(index_ != std::numeric_limits<size_t>::max());
    return index_;
}

void lang::Member::setScope(lang::Scope* scope)
{
    scope->registerUsage(type());
    if (constant_init_.hasValue()) { constant_init_.value()->type(); }
}

bool lang::Member::validate(ValidationLogger& validation_logger) const
{
    if (!type_->validate(validation_logger, type_location_)) return false;

    if (constant_init_.hasValue() && assigner_ != lang::Assigner::COPY_ASSIGNMENT)
    {
        validation_logger.logError("Only copy assignment currently supported for member initializers", location());
        return false;
    }

    if (constant_init_.hasValue())
    {
        if (!constant_init_.value()->validate(validation_logger)) return false;

        if (!lang::Type::areSame(type(), constant_init_.value()->type()))
        {
            validation_logger.logError("Member initializer with type "
                                           + constant_init_.value()->type().getAnnotatedName()
                                           + " must be of member type " + type().getAnnotatedName(),
                                       constant_init_.value()->location());
            return false;
        }
    }

    return true;
}

Shared<lang::Constant> lang::Member::getConstantInitializer(Execution& exec)
{
    if (constant_init_.hasValue()) { return constant_init_.value()->constant(exec); }
    else { return exec.getDefault(type()); }
}

void lang::Member::buildInitialization(Shared<lang::Value> ptr, Execution& exec)
{
    if (constant_init_.hasValue())
    {
        Shared<lang::Value> value_ptr = exec.performStackAllocation(type());
        exec.performStoreToAddress(value_ptr, constant_init_.value()->constant(exec));

        type()->performCopyInitializer(ptr, value_ptr, exec);
    }
    else { type()->performDefaultInitializer(ptr, exec); }
}

Owned<lang::Member> lang::Member::expand(lang::Context& new_context) const
{
    lang::ResolvingHandle<lang::Type> type = type_->getUndefinedTypeClone(new_context);

    Optional<Owned<LiteralExpression>> expanded_init_expression;

    if (constant_init_.hasValue())
    {
        auto [leading_statements, new_expression, following_statements] = constant_init_.value()->expand(new_context);

        assert(leading_statements.empty());
        assert(following_statements.empty());

        Expression* expanded_init_expression_ptr = unwrap(std::move(new_expression));
        expanded_init_expression =
            Owned<LiteralExpression>(*dynamic_cast<LiteralExpression*>(expanded_init_expression_ptr));
    }

    return makeOwned<Member>(access_,
                             name_,
                             type,
                             assigner_,
                             std::move(expanded_init_expression),
                             location_,
                             type_location_);
}

void lang::Member::synchronize(lang::Member* member, Storage& storage)
{
    storage.sync(member->name_);
    storage.sync(member->access_);
    storage.sync(member->type_);
}
