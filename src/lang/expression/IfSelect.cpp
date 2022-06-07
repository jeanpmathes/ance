#include "IfSelect.h"

#include "lang/scope/Scope.h"
#include "lang/type/BooleanType.h"
#include "validation/ValidationLogger.h"

#include "lang/expression/DefaultValue.h"
#include "lang/expression/VariableAccess.h"
#include "lang/statement/Assignment.h"
#include "lang/statement/Drop.h"
#include "lang/statement/If.h"
#include "lang/statement/LocalVariableDefinition.h"

IfSelect::IfSelect(std::unique_ptr<Expression> condition,
                   std::unique_ptr<Expression> then_expression,
                   std::unique_ptr<Expression> else_expression,
                   lang::Location              location)
    : UnexpandedExpression(location)
    , condition_(std::move(condition))
    , then_expression_(std::move(then_expression))
    , else_expression_(std::move(else_expression))
{
    addSubexpression(*condition_);
    addSubexpression(*then_expression_);
    addSubexpression(*else_expression_);
}

Expression& IfSelect::condition() const
{
    return *condition_;
}

Expression& IfSelect::thenExpression() const
{
    return *then_expression_;
}

Expression& IfSelect::elseExpression() const
{
    return *else_expression_;
}

lang::ResolvingHandle<lang::Type> IfSelect::type() const
{
    return then_expression_->type();
}

bool IfSelect::validate(ValidationLogger& validation_logger)
{
    bool valid = true;

    valid &= condition_->validate(validation_logger);
    valid &= then_expression_->validate(validation_logger);
    valid &= else_expression_->validate(validation_logger);

    if (!valid) return false;

    valid &= lang::Type::checkMismatch(lang::BooleanType::get(),
                                       condition_->type(),
                                       condition_->location(),
                                       validation_logger);

    if (!lang::Type::areSame(then_expression_->type(), else_expression_->type()))
    {
        validation_logger.logError("Both branches must have same type", location());
        valid = false;
    }

    return valid;
}

Expression::Expansion IfSelect::expandWith(Expressions subexpressions) const
{
    std::string temp_name          = scope()->getTemporaryName();
    auto        make_temp_variable = [&temp_name]() { return lang::makeHandled<lang::Variable>(temp_name); };
    auto        condition          = std::move(subexpressions[0]);
    auto        then_expression    = std::move(subexpressions[1]);
    auto        else_expression    = std::move(subexpressions[2]);

    Statements before;

    before.push_back(
        std::make_unique<LocalVariableDefinition>(temp_name,
                                                               type()->toUndefined(),
                                                               location(),
                                                               lang::Assigner::COPY_ASSIGNMENT,
                                                               nullptr,
                                                               location()));

    before.push_back(std::make_unique<If>(
        std::move(condition),
        std::make_unique<Assignment>(std::make_unique<VariableAccess>(make_temp_variable(), location()),
                                     lang::Assigner::COPY_ASSIGNMENT,
                                     std::move(then_expression),
                                     location()),
        std::make_unique<Assignment>(std::make_unique<VariableAccess>(make_temp_variable(), location()),
                                     lang::Assigner::COPY_ASSIGNMENT,
                                     std::move(else_expression),
                                     location()),
        location()));

    std::unique_ptr<Expression> result = std::make_unique<VariableAccess>(make_temp_variable(), location());

    Statements after;

    after.push_back(std::make_unique<Drop>(make_temp_variable(), location()));

    return {std::move(before), std::move(result), std::move(after)};
}

IfSelect::~IfSelect() = default;
