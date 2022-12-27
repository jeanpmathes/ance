#include "Expression.h"

#include <utility>

#include "compiler/CompileContext.h"
#include "lang/construct/value/Value.h"
#include "lang/statement/Statement.h"
#include "lang/type/Type.h"
#include "validation/ValidationLogger.h"

Expression::Expression(lang::Location location) : location_(location), type_(lang::Type::getUndefined()) {}

lang::Location Expression::location() const
{
    return location_;
}

lang::Scope* Expression::scope() const
{
    return containing_scope_;
}

lang::ResolvingHandle<lang::Type> Expression::type()
{
    if (not type_->isDefined()) defineType(type_);

    return type_;
}

lang::Type const& Expression::type() const
{
    return type_;
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

bool Expression::validateAssignment(lang::Value const& value,
                                    lang::Location     value_location,
                                    ValidationLogger&  validation_logger) const
{
    if (!validate(validation_logger)) return false;

    if (type().isReferenceType())
    {
        lang::Type const& target_type = type().getElementType();
        return lang::Type::checkMismatch(target_type, value.type(), value_location, validation_logger);
    }
    else
    {
        validation_logger.logError("Cannot assign to this expression", location());
        return false;
    }
}

void Expression::assign(Shared<lang::Value> value, CompileContext& context)
{
    context.setDebugLocation(location(), containing_scope_);
    doAssign(std::move(value), context);
    context.resetDebugLocation();
}

void Expression::doAssign(Shared<lang::Value> value, CompileContext& context)
{
    assert(type()->isReferenceType());

    lang::ResolvingHandle<lang::Type> target_type = type()->getElementType();
    value                                         = lang::Type::makeMatching(target_type, value, context);

    Shared<lang::Value> expression_return = getValue();

    expression_return->buildContentValue(context);
    value->buildNativeValue(context);

    target_type->buildCopyInitializer(expression_return->getContentValue(), value->getNativeValue(), context);
}

void Expression::addSubexpression(Expression& subexpression)
{
    subexpressions_.emplace_back(subexpression);
    addChild(subexpression);
}

std::tuple<Statements, Owned<Expression>, Statements> Expression::expand() const
{
    Statements before;
    Statements after;

    Expressions subexpressions;
    subexpressions.reserve(subexpressions_.size());

    for (auto& subexpression : subexpressions_)
    {
        auto [statements_before, expanded_expression, statements_after] = subexpression.get().expand();

        before.insert(before.end(),
                      std::make_move_iterator(statements_before.begin()),
                      std::make_move_iterator(statements_before.end()));
        after.insert(after.begin(),
                     std::make_move_iterator(statements_after.begin()),
                     std::make_move_iterator(statements_after.end()));

        subexpressions.push_back(std::move(expanded_expression));
    }

    auto [statements_before, expanded_expression, statements_after] = this->expandWith(std::move(subexpressions));

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
