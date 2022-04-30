#include "Match.h"

#include "lang/construct/CodeBlock.h"
#include "lang/construct/constant/Constant.h"
#include "validation/ValidationLogger.h"
#include "lang/expression/Expression.h"

Case* Case::createDefault(std::unique_ptr<Statement> code)
{
    return new Case(std::vector<std::unique_ptr<ConstantExpression>>(), std::move(code));
}

Case* Case::createCase(std::vector<std::unique_ptr<ConstantExpression>> conditions, std::unique_ptr<Statement> code)
{
    return new Case(std::move(conditions), std::move(code));
}

Case::Case(std::vector<std::unique_ptr<ConstantExpression>> conditions, std::unique_ptr<Statement> code)
    : conditions_(std::move(conditions))
    , code_(std::move(code))
{
    for (auto& condition : conditions_)
    {
        Expression* condition_expression = condition.get();
        addChild(*condition_expression);
    }
}

void Case::setContainingScope(lang::Scope* scope)
{
    for (auto& condition : conditions_) { condition->setContainingScope(scope); }

    code_->setContainingScope(scope);
}

void Case::walkDefinitions()
{
    for (auto& condition : conditions_) { condition->walkDefinitions(); }

    code_->walkDefinitions();
}

std::vector<std::pair<ConstantExpression*, Statement*>> Case::getConditions()
{
    std::vector<std::pair<ConstantExpression*, Statement*>> conditions;

    if (conditions_.empty()) { conditions.emplace_back(nullptr, code_.get()); }
    else {
        for (auto& condition : conditions_) { conditions.emplace_back(condition.get(), code_.get()); }
    }

    return conditions;
}

bool Case::validateConflicts(Case* other, ValidationLogger& validation_logger)
{
    bool conflicts = false;

    for (auto& condition : conditions_)
    {
        for (auto& other_condition : other->conditions_)
        {
            std::shared_ptr<lang::Constant> condition_constant       = condition->getConstantValue();
            std::shared_ptr<lang::Constant> other_condition_constant = other_condition->getConstantValue();

            if (condition_constant->equals(other_condition_constant.get()))
            {
                validation_logger.logError("Match case '" + condition_constant->toString() + "' already covered",
                                           condition->location());

                conflicts = true;
            }
        }
    }

    return !conflicts;
}

bool Case::validate(lang::ResolvingHandle<lang::Type> target_type, ValidationLogger& validation_logger)
{
    bool valid = true;

    for (auto& condition : conditions_) { valid &= condition->validate(validation_logger); }
    code_->validate(validation_logger);

    if (!valid) return false;

    coverage_count_ = static_cast<ssize_t>(conditions_.size());

    std::vector<ConstantExpression*> local_conditions;
    for (auto& condition : conditions_)
    {
        for (auto& local_condition : local_conditions)
        {
            std::shared_ptr<lang::Constant> condition_constant       = condition->getConstantValue();
            std::shared_ptr<lang::Constant> local_condition_constant = local_condition->getConstantValue();

            if (condition_constant->equals(local_condition_constant.get()))
            {
                validation_logger.logWarning("Match case '" + condition_constant->toString() + "' is duplicated",
                                             condition->location());

                coverage_count_--;
            }
        }

        local_conditions.push_back(condition.get());

        if (!lang::Type::areSame(condition->type(), target_type))
        {
            validation_logger.logError("Cases must be of matched value type " + target_type->getAnnotatedName(),
                                       condition->location());

            valid = false;
        }
    }

    return valid;
}

std::unique_ptr<Case> Case::expand() const
{
    Statements expanded_statements = code_->expand();
    assert(expanded_statements.size() == 1);

    std::vector<std::unique_ptr<ConstantExpression>> expanded_conditions;

    for (auto& condition : conditions_)
    {
        auto [before, expanded_condition, after] = condition->expand();

        assert(before.empty());
        assert(after.empty());

        expanded_conditions.push_back(
            std::unique_ptr<ConstantExpression>(dynamic_cast<ConstantExpression*>(expanded_condition.release())));
    }

    return std::unique_ptr<Case>(new Case(std::move(expanded_conditions), std::move(expanded_statements.front())));
}

ssize_t Case::getCoverageCount()
{
    if (conditions_.empty()) { return -1; }
    return coverage_count_;
}

Match::Match(std::vector<std::unique_ptr<Case>> cases, std::unique_ptr<Expression> expression, lang::Location location)
    : Statement(location)
    , expression_(std::move(expression))
    , cases_(std::move(cases))
{
    addSubexpression(*expression_);
}

Expression& Match::expression()
{
    return *expression_;
}

std::vector<std::unique_ptr<lang::BasicBlock>> Match::createBasicBlocks(lang::BasicBlock& entry,
                                                                        lang::Function*   function)
{
    std::vector<std::pair<ConstantExpression*, Statement*>> conditions;

    for (auto& case_ptr : cases_)
    {
        auto additional_conditions = case_ptr->getConditions();
        conditions.insert(conditions.end(), additional_conditions.begin(), additional_conditions.end());
    }

    auto blocks = lang::BasicBlock::createMatching(this, std::move(conditions), function);
    entry.link(*blocks.front());

    return blocks;
}

void Match::setScope(lang::Scope* scope)
{
    Statement::setScope(scope);

    for (auto& case_ptr : cases_) { case_ptr->setContainingScope(scope); }
}

void Match::walkDefinitions()
{
    Statement::walkDefinitions();

    for (auto& case_ptr : cases_) { case_ptr->walkDefinitions(); }
}

bool Match::validateCases(ValidationLogger& validation_logger)
{
    bool valid = true;

    std::vector<Case*> checked_cases;
    ssize_t            covered_cases = 0;

    for (auto& case_ptr : cases_)
    {
        valid &= case_ptr->validate(expression_->type(), validation_logger);

        ssize_t additional_coverage = case_ptr->getCoverageCount();
        bool    has_default_case    = additional_coverage == -1 || covered_cases == -1;
        covered_cases               = has_default_case ? -1 : covered_cases + additional_coverage;

        for (auto& checked_case : checked_cases)
        {
            if (!case_ptr->validateConflicts(checked_case, validation_logger)) { valid = false; }
        }

        checked_cases.push_back(case_ptr.get());
    }

    StateCount state_count = expression_->type()->getStateCount();

    if (covered_cases != -1)
    {
        bool uncovered;

        if (auto* count = std::get_if<size_t>(&state_count))
        {
            uncovered = static_cast<ssize_t>(*count) != covered_cases;
        }
        else {
            uncovered = true;
        }

        if (uncovered)
        {
            validation_logger.logError("Match does not cover all possible states of type "
                                           + expression_->type()->getAnnotatedName(),
                                       location());
            valid = false;
        }
    }

    if (auto* count = std::get_if<SpecialCount>(&state_count))
    {
        if (*count == SpecialCount::UNCOUNTABLE)
        {
            validation_logger.logError("Cannot match uncountable type " + expression_->type()->getAnnotatedName(),
                                       location());
            valid = false;
        }
    }

    return valid;
}

Statements Match::expandWith(Expressions subexpressions, Statements) const
{
    std::vector<std::unique_ptr<Case>> expanded_cases;
    for (auto& case_ptr : cases_)
    {
        auto expanded_case = case_ptr->expand();
        expanded_cases.push_back(std::move(expanded_case));
    }

    Statements statements;

    statements.push_back(std::make_unique<Match>(std::move(expanded_cases), std::move(subexpressions[0]), location()));

    return statements;
}

void Match::validate(ValidationLogger& validation_logger)
{
    bool valid = true;

    valid &= expression_->validate(validation_logger);

    if (!valid) return;

    lang::ResolvingHandle<lang::Type> type = expression_->type();

    if (!type->isIntegerType() && !type->isBooleanType() && !type->isSizeType() && !type->isDiffType())
    {
        validation_logger.logError("Cannot match non-numeric or logical type " + type->getAnnotatedName(),
                                   expression_->location());
        valid = false;
    }

    if (!valid) return;

    validateCases(validation_logger);
}

void Match::doBuild(CompileContext*)
{
    // Handled by basic block.
}
