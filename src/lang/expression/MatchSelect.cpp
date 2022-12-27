#include "MatchSelect.h"

#include "lang/ApplicationVisitor.h"
#include "lang/expression/VariableAccess.h"
#include "lang/scope/Scope.h"
#include "lang/statement/LocalVariableDefinition.h"
#include "lang/statement/Match.h"
#include "validation/ValidationLogger.h"

MatchSelect::MatchSelect(Owned<Expression> condition, std::vector<Owned<Case>> cases, lang::Location location)
    : UnexpandedExpression(location)
    , condition_(std::move(condition))
    , cases_(std::move(cases))
{
    addSubexpression(*condition_);
}

Expression const& MatchSelect::condition() const
{
    return *condition_;
}

std::vector<std::reference_wrapper<Case const>> MatchSelect::cases() const
{
    std::vector<std::reference_wrapper<Case const>> cases;

    for (auto& c : cases_) { cases.emplace_back(*c); }

    return cases;
}

void MatchSelect::defineType(lang::ResolvingHandle<lang::Type>& type)
{
    auto common_types = Case::getCommonType(cases_);

    if (common_types.size() == 1 && common_types.front()->isDefined()) { type.reroute(common_types.front()); }
}

void MatchSelect::walkDefinitions()
{
    Expression::walkDefinitions();
    for (auto& c : cases_) { c->walkDefinitions(); }
}

void MatchSelect::postResolve()
{
    Expression::postResolve();
    for (auto& c : cases_) { c->postResolve(); }
}

bool MatchSelect::validate(ValidationLogger& validation_logger) const
{
    bool valid = true;

    valid &= condition_->validate(validation_logger);

    if (!valid) return false;

    valid &= Match::validateType(*condition_, validation_logger);

    if (!valid) return false;

    valid &= Match::validateCases(location(), *condition_, cases_, validation_logger);
    valid &= Case::validateReturnTypes(location(), cases_, validation_logger);

    return valid;
}

Expression::Expansion MatchSelect::expandWith(Expressions subexpressions) const
{
    auto temp_name = lang::Identifier::like(scope()->getTemporaryName(), location());
    auto condition = std::move(subexpressions[0]);

    auto variable = lang::makeHandled<lang::Variable>(temp_name);

    std::vector<Owned<Case>> cases;
    for (auto& original_case : cases_) { cases.push_back(original_case->expand(variable)); }

    Statements statements;

    statements.emplace_back(makeOwned<LocalVariableDefinition>(temp_name,
                                                               type().createUndefinedClone(),
                                                               location(),
                                                               lang::Assigner::COPY_ASSIGNMENT,
                                                               std::nullopt,
                                                               location()));

    statements.emplace_back(makeOwned<Match>(std::move(cases), std::move(condition), location()));

    auto result = makeOwned<VariableAccess>(variable->toUndefined(), location());

    return {std::move(statements), std::move(result), Statements()};
}

MatchSelect::~MatchSelect() = default;
