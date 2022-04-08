#include "Match.h"

#include "lang/construct/CodeBlock.h"
#include "lang/construct/constant/Constant.h"
#include "validation/ValidationLogger.h"

Match::Case* Match::Case::createDefault(std::unique_ptr<lang::CodeBlock> code)
{
    return new Match::Case(std::vector<std::unique_ptr<ConstantExpression>>(), std::move(code));
}

Match::Case* Match::Case::createCase(std::vector<std::unique_ptr<ConstantExpression>> conditions,
                                     std::unique_ptr<lang::CodeBlock>                 code)
{
    return new Match::Case(std::move(conditions), std::move(code));
}

Match::Case::Case(std::vector<std::unique_ptr<ConstantExpression>> conditions, std::unique_ptr<lang::CodeBlock> code)
    : conditions_(std::move(conditions))
    , code_(std::move(code))
{}

void Match::Case::setContainingScope(lang::Scope* scope)
{
    for (auto& condition : conditions_) { condition->setContainingScope(scope); }

    code_->createScopes(scope);
}

void Match::Case::walkDefinitions()
{
    for (auto& condition : conditions_) { condition->walkDefinitions(); }

    code_->walkDefinitions();
}

std::vector<std::pair<ConstantExpression*, lang::CodeBlock*>> Match::Case::getConditions()
{
    std::vector<std::pair<ConstantExpression*, lang::CodeBlock*>> conditions;

    if (conditions_.empty()) { conditions.emplace_back(nullptr, code_.get()); }
    else {
        for (auto& condition : conditions_) { conditions.emplace_back(condition.get(), code_.get()); }
    }

    return conditions;
}

bool Match::Case::validateConflicts(Match::Case* other, ValidationLogger& validation_logger)
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

bool Match::Case::validate(lang::ResolvingHandle<lang::Type> target_type, ValidationLogger& validation_logger)
{
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
        }
    }

    return true;
}

ssize_t Match::Case::getCoverageCount()
{
    if (conditions_.empty()) { return -1; }
    return coverage_count_;
}

Match::Match(std::vector<std::unique_ptr<Match::Case>> cases,
             std::unique_ptr<Expression>               expression,
             lang::Location                            location)
    : Statement(location)
    , expression_(std::move(expression))
    , cases_(std::move(cases))
{}

Expression& Match::expression()
{
    return *expression_;
}

std::vector<std::unique_ptr<lang::BasicBlock>> Match::createBlocks(lang::BasicBlock& entry, lang::Function* function)
{
    std::vector<std::pair<ConstantExpression*, lang::CodeBlock*>> conditions;

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
    expression_->setContainingScope(scope);

    for (auto& case_ptr : cases_) { case_ptr->setContainingScope(scope); }
}

void Match::walkDefinitions()
{
    expression_->walkDefinitions();

    for (auto& case_ptr : cases_) { case_ptr->walkDefinitions(); }
}

bool Match::validateCases(ValidationLogger& validation_logger)
{
    bool valid = true;

    std::vector<Match::Case*> checked_cases;
    ssize_t                   covered_cases = 0;

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

void Match::validate(ValidationLogger&)
{
    // Handled by basic block.
}

void Match::doBuild(CompileContext*)
{
    // Handled by basic block.
}
