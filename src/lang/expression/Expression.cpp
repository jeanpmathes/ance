#include "Expression.h"

#include <utility>

#include "lang/ApplicationVisitor.h"
#include "lang/construct/Value.h"
#include "lang/type/Type.h"
#include "validation/ValidationLogger.h"

Expression::Expression(lang::Location location) : location_(location), type_(lang::Type::getUndefined()) {}

lang::Location Expression::location() const
{
    return location_;
}

lang::Scope& Expression::scope()
{
    assert(containing_scope_ != nullptr);
    return *containing_scope_;
}

lang::Scope const& Expression::scope() const
{
    assert(containing_scope_ != nullptr);
    return *containing_scope_;
}

bool Expression::isInitialized() const
{
    return containing_scope_ != nullptr;
}

lang::CMP Expression::cmp() const
{
    lang::CMP result = rootCMP();

    for (auto& subexpression : subexpressions_) { result = result & subexpression.get().cmp(); }

    return result;
}

lang::CMP Expression::rootCMP() const
{
    return lang::CMP::NO_CMP;
}

lang::ResolvingHandle<lang::Type> Expression::type()
{
    if (!type_->isDefined()) defineType(type_);

    return type_;
}

lang::Type const& Expression::type() const
{
    return type_;
}

lang::Type const& Expression::assignableType() const
{
    if (type().isReferenceType()) return type().getElementType();

    throw std::logic_error("Expression is not assignable");
}

void Expression::setContainingScope(lang::Scope& scope)
{
    containing_scope_ = &scope;
    setScope(scope);
}

void Expression::walkDefinitions()
{
    for (auto& subexpression : subexpressions_) { subexpression.get().walkDefinitions(); }
}

void Expression::postResolve()
{
    for (auto& subexpression : subexpressions_) { subexpression.get().postResolve(); }
    type();// Trigger rerouting / defining of type.
}

void Expression::setScope(lang::Scope& scope)
{
    for (auto& subexpression : subexpressions_) { subexpression.get().setContainingScope(scope); }
}

bool Expression::isNamed() const
{
    return type().isReferenceType();
}

bool Expression::validateAssignment(lang::Type const& value_type,
                                    lang::Location    value_location,
                                    ValidationLogger& validation_logger) const
{
    if (!validate(validation_logger)) return false;
    if (!type().isDefined()) return false;
    if (!value_type.isDefined()) return false;

    if (type().isReferenceType())
    {
        lang::Type const& target_type = type().getElementType();
        return lang::Type::checkMismatch(target_type, value_type, value_location, validation_logger);
    }
    else
    {
        validation_logger.logError("Cannot assign to this expression", location());
        return false;
    }
}

void Expression::addSubexpression(Expression& subexpression)
{
    subexpressions_.emplace_back(subexpression);
    addChild(subexpression);
}

Expression::Expansion Expression::expand(lang::Context& new_context) const
{
    Statements before;
    Statements after;

    Expressions subexpressions;
    subexpressions.reserve(subexpressions_.size());

    for (auto& subexpression : subexpressions_)
    {
        auto [statements_before, expanded_expression, statements_after] = subexpression.get().expand(new_context);

        before.insert(before.end(),
                      std::make_move_iterator(statements_before.begin()),
                      std::make_move_iterator(statements_before.end()));
        after.insert(after.begin(),
                     std::make_move_iterator(statements_after.begin()),
                     std::make_move_iterator(statements_after.end()));

        subexpressions.push_back(std::move(expanded_expression));
    }

    assert(subexpressions.size() == subexpressions_.size());

    auto [statements_before, expanded_expression, statements_after] =
        this->expandWith(std::move(subexpressions), new_context);

    before.insert(before.end(),
                  std::make_move_iterator(statements_before.begin()),
                  std::make_move_iterator(statements_before.end()));
    after.insert(after.begin(),
                 std::make_move_iterator(statements_after.begin()),
                 std::make_move_iterator(statements_after.end()));

    return std::make_tuple(std::move(before), std::move(expanded_expression), std::move(after));
}

std::vector<lang::ResolvingHandle<lang::Type>> Expression::getTypes(std::vector<Owned<Expression>>& expressions)
{
    std::vector<lang::ResolvingHandle<lang::Type>> types;
    types.reserve(expressions.size());

    for (auto& expression : expressions) { types.push_back(expression->type()); }

    return types;
}

std::vector<std::reference_wrapper<lang::Type const>> Expression::getTypes(
    std::vector<Owned<Expression>> const& expressions)
{
    std::vector<std::reference_wrapper<lang::Type const>> types;
    types.reserve(expressions.size());

    for (auto& expression : expressions) { types.emplace_back(expression->type()); }

    return types;
}
