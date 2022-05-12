#include "MatchSelect.h"

#include "lang/expression/DefaultValue.h"
#include "lang/expression/VariableAccess.h"
#include "lang/scope/Scope.h"
#include "lang/statement/LocalVariableDefinition.h"
#include "lang/statement/Match.h"
#include "validation/ValidationLogger.h"

MatchSelect::MatchSelect(std::unique_ptr<Expression>        condition,
                         std::vector<std::unique_ptr<Case>> cases,
                         lang::Location                     location)
    : UnexpandedExpression(location)
    , condition_(std::move(condition))
    , cases_(std::move(cases))
{
    addSubexpression(*condition_);
}

Expression& MatchSelect::condition() const
{
    return *condition_;
}

lang::ResolvingHandle<lang::Type> MatchSelect::type()
{
    return Case::getCommonType(cases_);
}

lang::ResolvingHandle<lang::Type> MatchSelect::type() const
{
    return Case::getCommonType(cases_);
}

bool MatchSelect::validate(ValidationLogger& validation_logger)
{
    bool valid = true;

    valid &= condition_->validate(validation_logger);

    if (!valid) return false;

    valid &= Match::validateType(*condition_, validation_logger);

    if (!valid) return false;

    std::vector<std::reference_wrapper<Case>> cases;
    cases.reserve(cases_.size());
    std::for_each(cases_.begin(), cases_.end(), [&cases](auto& case_ptr) { cases.push_back(*case_ptr); });

    valid &= Match::validateCases(location(), *condition_, cases, validation_logger);

    return valid;
}

Expression::Expansion MatchSelect::expandWith(Expressions subexpressions) const
{
    std::string temp_name = scope()->getTemporaryName();
    auto        condition = std::move(subexpressions[0]);

    auto variable = lang::makeHandled<lang::Variable>(temp_name);

    std::vector<std::unique_ptr<Case>> cases;
    for (auto& original_case : cases_) { cases.push_back(original_case->expand(variable)); }

    Statements statements;

    statements.push_back(
        std::make_unique<LocalVariableDefinition>(temp_name,
                                                  type()->toUndefined(),
                                                  location(),
                                                  lang::Assigner::COPY_ASSIGNMENT,
                                                  std::make_unique<DefaultValue>(type()->toUndefined(), location()),
                                                  location()));

    statements.push_back(std::make_unique<Match>(std::move(cases), std::move(condition), location()));

    auto result = std::make_unique<VariableAccess>(variable->toUndefined(), location());

    return {std::move(statements), std::move(result), Statements()};
}

MatchSelect::~MatchSelect() = default;
