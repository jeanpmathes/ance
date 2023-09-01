#include "IfSelect.h"

#include "lang/scope/Scope.h"
#include "lang/type/BooleanType.h"
#include "validation/ValidationLogger.h"

#include "lang/ApplicationVisitor.h"
#include "lang/expression/VariableAccess.h"
#include "lang/statement/Assignment.h"
#include "lang/statement/Drop.h"
#include "lang/statement/If.h"
#include "lang/statement/LocalVariableDefinition.h"

IfSelect::IfSelect(Owned<Expression> condition,
                   Owned<Expression> then_expression,
                   Owned<Expression> else_expression,
                   lang::Location    location)
    : UnexpandedExpression(location)
    , condition_(std::move(condition))
    , then_expression_(std::move(then_expression))
    , else_expression_(std::move(else_expression))
{
    addSubexpression(*condition_);
    addSubexpression(*then_expression_);
    addSubexpression(*else_expression_);
}

Expression const& IfSelect::condition() const
{
    return *condition_;
}

Expression const& IfSelect::thenExpression() const
{
    return *then_expression_;
}

Expression const& IfSelect::elseExpression() const
{
    return *else_expression_;
}

void IfSelect::defineType(lang::ResolvingHandle<lang::Type> type)
{
    auto then_type = then_expression_->type();
    auto else_type = else_expression_->type();

    if (then_type->isDefined() && else_type->isDefined())
    {
        std::vector<lang::ResolvingHandle<lang::Type>> types;

        types.emplace_back(then_type);
        types.emplace_back(else_type);

        auto common_types = lang::Type::getCommonType(types);

        if (common_types.size() == 1) { type.reroute(common_types.front()); }
    }
}

bool IfSelect::validate(ValidationLogger& validation_logger) const
{
    bool valid = true;

    valid &= condition_->validate(validation_logger);
    valid &= then_expression_->validate(validation_logger);
    valid &= else_expression_->validate(validation_logger);

    if (!valid) return false;

    valid &= lang::Type::checkMismatch(scope()->context().getBooleanType(),
                                       condition_->type(),
                                       condition_->location(),
                                       validation_logger);

    auto common_types = lang::Type::getCommonType({then_expression_->type(), else_expression_->type()});

    if (common_types.empty() || common_types.size() > 1)
    {
        validation_logger.logError("Branches must have unambiguous common return type", location());
        return false;
    }

    return valid;
}

Expression::Expansion IfSelect::expandWith(Expressions subexpressions, lang::Context& new_context) const
{
    auto temp_name          = lang::Identifier::like(scope()->getTemporaryName(), location());
    auto make_temp_variable = [&temp_name]() { return lang::makeHandled<lang::Variable>(temp_name); };
    auto condition          = std::move(subexpressions[0]);
    auto then_expression    = std::move(subexpressions[1]);
    auto else_expression    = std::move(subexpressions[2]);

    Statements before;

    before.emplace_back(makeOwned<LocalVariableDefinition>(temp_name,
                                                           type().getUndefinedTypeClone(new_context),
                                                           location(),
                                                           lang::Assigner::COPY_ASSIGNMENT,
                                                           std::nullopt,
                                                           location()));

    before.emplace_back(makeOwned<If>(std::move(condition),
                      makeOwned<Assignment>(makeOwned<VariableAccess>(make_temp_variable(), true, location()),
                                            lang::Assigner::COPY_ASSIGNMENT,
                                            std::move(then_expression),
                                            location()),
                                      makeOptional<Owned<Statement>>(makeOwned<Assignment>(makeOwned<VariableAccess>(make_temp_variable(), true, location()),
                                                lang::Assigner::COPY_ASSIGNMENT,
                                                std::move(else_expression),
                                                location())),
                                      location()));

    Owned<Expression> result = makeOwned<VariableAccess>(make_temp_variable(), true, location());

    Statements after;

    after.emplace_back(makeOwned<Drop>(make_temp_variable(), location()));

    return {std::move(before), std::move(result), std::move(after)};
}

IfSelect::~IfSelect() = default;
