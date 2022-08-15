#include "Expression.h"

#include <utility>

#include "lang/construct/value/Value.h"
#include "lang/statement/Statement.h"
#include "lang/type/Type.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

Expression::Expression(lang::Location location) : location_(location) {}

lang::Location Expression::location() const
{
    return location_;
}

lang::Scope* Expression::scope() const
{
    return containing_scope_;
}

lang::ResolvingHandle<lang::Type> Expression::type() const
{
    if (not type_.has_value())
    {
        type_ = tryGetType();
        assert(type_.has_value());
    }

    return type_.value();
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
}

void Expression::setScope(lang::Scope& scope)
{
    for (auto& subexpression : subexpressions_) { subexpression.get().setContainingScope(scope); }
}

bool Expression::isNamed()
{
    return type()->isReferenceType();
}

bool Expression::validateAssignment(const std::shared_ptr<lang::Value>& value,
                                    lang::Location                      value_location,
                                    ValidationLogger&                   validation_logger)
{
    if (!validate(validation_logger)) return false;

    if (type()->isReferenceType())
    {
        lang::ResolvingHandle<lang::Type> target_type = type()->getElementType();
        return lang::Type::checkMismatch(target_type, value->type(), value_location, validation_logger);
    }
    else {
        validation_logger.logError("Cannot assign to this expression", location());
        return false;
    }
}

void Expression::assign(std::shared_ptr<lang::Value> value, CompileContext& context)
{
    context.setDebugLocation(location(), containing_scope_);
    doAssign(std::move(value), context);
    context.resetDebugLocation();
}

void Expression::doAssign(std::shared_ptr<lang::Value> value, CompileContext& context)
{
    assert(type()->isReferenceType());

    lang::ResolvingHandle<lang::Type> target_type = type()->getElementType();
    value                                         = lang::Type::makeMatching(target_type, value, context);

    std::shared_ptr<lang::Value> expression_return = getValue();

    expression_return->buildContentValue(context);
    value->buildNativeValue(context);

    target_type->buildCopyInitializer(expression_return->getContentValue(), value->getNativeValue(), context);
}

void Expression::addSubexpression(Expression& subexpression)
{
    subexpressions_.emplace_back(subexpression);
    addChild(subexpression);
}

std::tuple<Statements, std::unique_ptr<Expression>, Statements> Expression::expand() const
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
