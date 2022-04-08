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

bool Match::Case::validate(ValidationLogger& validation_logger)
{
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
            }
        }

        local_conditions.push_back(condition.get());
    }

    return true;
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

    for (auto& case_ptr : cases_)
    {
        valid &= case_ptr->validate(validation_logger);

        for (auto& checked_case : checked_cases)
        {
            if (!case_ptr->validateConflicts(checked_case, validation_logger)) { valid = false; }
        }

        checked_cases.push_back(case_ptr.get());
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
