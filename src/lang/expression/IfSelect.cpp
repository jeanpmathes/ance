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

std::optional<lang::ResolvingHandle<lang::Type>> IfSelect::tryGetType() const
{
    auto then_type = thenExpression().tryGetType();
    auto else_type = elseExpression().tryGetType();

    if (then_type.has_value() && else_type.has_value())
    {
        std::vector<lang::ResolvingHandle<lang::Type>> types;

        types.push_back(then_type.value());
        types.push_back(else_type.value());

        auto common_types = lang::Type::getCommonType(types);

        if (common_types.size() == 1) { return common_types.front(); }
    }

    return std::nullopt;
}

bool IfSelect::validate(ValidationLogger& validation_logger) const
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

    auto common_types = lang::Type::getCommonType({then_expression_->type(), else_expression_->type()});

    if (common_types.empty() || common_types.size() > 1)
    {
        validation_logger.logError("Branches must have unambiguous common return type", location());
        return false;
    }

    return valid;
}

Expression::Expansion IfSelect::expandWith(Expressions subexpressions) const
{
    auto        temp_name          = lang::Identifier::from(scope()->getTemporaryName(), location());
    auto        make_temp_variable = [&temp_name]() { return lang::makeHandled<lang::Variable>(temp_name); };
    auto        condition          = std::move(subexpressions[0]);
    auto        then_expression    = std::move(subexpressions[1]);
    auto        else_expression    = std::move(subexpressions[2]);

    Statements before;

    before.push_back(std::make_unique<LocalVariableDefinition>(temp_name,
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

