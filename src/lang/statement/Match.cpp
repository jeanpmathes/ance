#include "Match.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/CodeBlock.h"
#include "lang/construct/constant/Constant.h"
#include "lang/expression/Expression.h"
#include "lang/expression/VariableAccess.h"
#include "lang/statement/Assignment.h"
#include "validation/ValidationLogger.h"

Case* Case::createDefault(std::unique_ptr<Statement> code)
{
    return new Case(std::vector<std::unique_ptr<ConstantExpression>>(), std::move(code));
}

Case* Case::createCase(std::vector<std::unique_ptr<ConstantExpression>> conditions, std::unique_ptr<Statement> code)
{
    return new Case(std::move(conditions), std::move(code));
}

Case* Case::createDefault(std::unique_ptr<Expression> expression)
{
    return new Case(std::vector<std::unique_ptr<ConstantExpression>>(), std::move(expression));
}

Case* Case::createCase(std::vector<std::unique_ptr<ConstantExpression>> conditions,
                       std::unique_ptr<Expression>                      expression)
{
    return new Case(std::move(conditions), std::move(expression));
}

Case::Case(std::vector<std::unique_ptr<ConstantExpression>>                      conditions,
           std::variant<std::unique_ptr<Statement>, std::unique_ptr<Expression>> code)
    : conditions_(std::move(conditions))
    , code_(std::move(code))
{
    for (auto& condition : conditions_)
    {
        Expression* condition_expression = condition.get();
        addChild(*condition_expression);
    }
}

std::vector<std::reference_wrapper<ConstantExpression>> Case::conditions() const
{
    std::vector<std::reference_wrapper<ConstantExpression>> result;

    for (auto& condition : conditions_) { result.emplace_back(*condition); }

    return result;
}

std::reference_wrapper<lang::Visitable<ANCE_CONSTRUCTS>> Case::code() const
{
    if (std::holds_alternative<std::unique_ptr<Statement>>(code_))
    {
        return *std::get<std::unique_ptr<Statement>>(code_);
    }

    if (std::holds_alternative<std::unique_ptr<Expression>>(code_))
    {
        return *std::get<std::unique_ptr<Expression>>(code_);
    }

    throw std::runtime_error("Case::code() called on invalid case");
}

void Case::setContainingScope(lang::Scope& scope)
{
    for (auto& condition : conditions_) { condition->setContainingScope(scope); }

    if (std::holds_alternative<std::unique_ptr<Statement>>(code_))
    {
        Statement* code = std::get<std::unique_ptr<Statement>>(code_).get();
        code->setContainingScope(scope);
    }

    if (std::holds_alternative<std::unique_ptr<Expression>>(code_))
    {
        Expression* code = std::get<std::unique_ptr<Expression>>(code_).get();
        code->setContainingScope(scope);
    }
}

void Case::walkDefinitions()
{
    for (auto& condition : conditions_) { condition->walkDefinitions(); }

    if (std::holds_alternative<std::unique_ptr<Statement>>(code_))
    {
        Statement* code = std::get<std::unique_ptr<Statement>>(code_).get();
        code->walkDefinitions();
    }

    if (std::holds_alternative<std::unique_ptr<Expression>>(code_))
    {
        Expression* code = std::get<std::unique_ptr<Expression>>(code_).get();
        code->walkDefinitions();
    }
}

std::vector<std::pair<ConstantExpression*, Statement*>> Case::getConditions()
{
    std::vector<std::pair<ConstantExpression*, Statement*>> conditions;

    if (conditions_.empty()) { conditions.emplace_back(nullptr, std::get<std::unique_ptr<Statement>>(code_).get()); }
    else {
        for (auto& condition : conditions_)
        {
            conditions.emplace_back(condition.get(), std::get<std::unique_ptr<Statement>>(code_).get());
        }
    }

    return conditions;
}

bool Case::validateConflicts(Case& other, ValidationLogger& validation_logger)
{
    bool conflicts = false;

    for (auto& condition : conditions_)
    {
        for (auto& other_condition : other.conditions_)
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

    if (std::holds_alternative<std::unique_ptr<Statement>>(code_))
    {
        Statement* code = std::get<std::unique_ptr<Statement>>(code_).get();
        code->validate(validation_logger);
    }

    if (std::holds_alternative<std::unique_ptr<Expression>>(code_))
    {
        Expression* code = std::get<std::unique_ptr<Expression>>(code_).get();
        valid &= code->validate(validation_logger);
    }

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

std::vector<lang::ResolvingHandle<lang::Type>> Case::getCommonType(const std::vector<std::unique_ptr<Case>>& cases)
{
    std::vector<lang::ResolvingHandle<lang::Type>> types;

    for (auto& case_instance : cases)
    {
        types.push_back(std::get<std::unique_ptr<Expression>>(case_instance->code_)->type());
    }

    return lang::Type::getCommonType(types);
}

std::optional<std::vector<lang::ResolvingHandle<lang::Type>>> Case::tryGetCommonType(
    const std::vector<std::unique_ptr<Case>>& cases)
{
    std::vector<lang::ResolvingHandle<lang::Type>> types;

    for (auto& case_instance : cases)
    {
        auto type = std::get<std::unique_ptr<Expression>>(case_instance->code_)->tryGetType();
        if (type.has_value()) { types.push_back(type.value()); }
        else { return std::nullopt; }
    }

    return lang::Type::getCommonType(types);
}

bool Case::validateReturnTypes(lang::Location                            location,
                               const std::vector<std::unique_ptr<Case>>& cases,
                               ValidationLogger&                         validation_logger)
{
    std::vector<lang::ResolvingHandle<lang::Type>> common_types = getCommonType(cases);

    if (common_types.empty() || common_types.size() > 1)
    {
        validation_logger.logError("Cases must have unambiguous common return type", location);
        return false;
    }

    return true;
}

std::unique_ptr<Case> Case::expand() const
{
    Statements expanded_statements = std::get<std::unique_ptr<Statement>>(code_)->expand();

    std::vector<std::unique_ptr<ConstantExpression>> expanded_conditions;

    for (auto& condition : conditions_)
    {
        auto [before, expanded_condition, after] = condition->expand();

        assert(before.empty());
        assert(after.empty());

        expanded_conditions.push_back(
            std::unique_ptr<ConstantExpression>(dynamic_cast<ConstantExpression*>(expanded_condition.release())));
    }

    std::unique_ptr<lang::CodeBlock> new_block = lang::CodeBlock::wrapStatements(std::move(expanded_statements));
    return std::unique_ptr<Case>(new Case(std::move(expanded_conditions), std::move(new_block)));
}

std::unique_ptr<Case> Case::expand(lang::ResolvingHandle<lang::Variable> target) const
{
    auto [before, value_provider, after] = std::get<std::unique_ptr<Expression>>(code_)->expand();

    lang::Location location = std::get<std::unique_ptr<Expression>>(code_)->location();

    Statements expanded_statements;
    expanded_statements.insert(expanded_statements.end(),
                               std::make_move_iterator(before.begin()),
                               std::make_move_iterator(before.end()));

    expanded_statements.push_back(
        std::make_unique<Assignment>(std::make_unique<VariableAccess>(target->toUndefined(), location),
                                     lang::Assigner::COPY_ASSIGNMENT,
                                     std::move(value_provider),
                                     location));

    expanded_statements.insert(expanded_statements.end(),
                               std::make_move_iterator(after.begin()),
                               std::make_move_iterator(after.end()));

    std::vector<std::unique_ptr<ConstantExpression>> expanded_conditions;

    for (auto& condition : conditions_)
    {
        auto [before_condition, expanded_condition, after_condition] = condition->expand();

        assert(before_condition.empty());
        assert(after_condition.empty());

        expanded_conditions.push_back(
            std::unique_ptr<ConstantExpression>(dynamic_cast<ConstantExpression*>(expanded_condition.release())));
    }

    std::unique_ptr<lang::CodeBlock> new_block = lang::CodeBlock::wrapStatements(std::move(expanded_statements));
    return std::unique_ptr<Case>(new Case(std::move(expanded_conditions), std::move(new_block)));
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

    for (auto& case_instance : cases_) { addChild(*case_instance); }
}

Expression& Match::expression() const
{
    return *expression_;
}

std::vector<std::reference_wrapper<Case>> Match::cases() const
{
    std::vector<std::reference_wrapper<Case>> cases;

    for (auto& case_instance : cases_) { cases.emplace_back(*case_instance); }

    return cases;
}

std::vector<std::unique_ptr<lang::BasicBlock>> Match::createBasicBlocks(lang::BasicBlock& entry,
                                                                        lang::Function&   function)
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

void Match::setScope(lang::Scope& scope)
{
    Statement::setScope(scope);

    for (auto& case_ptr : cases_) { case_ptr->setContainingScope(scope); }
}

void Match::walkDefinitions()
{
    Statement::walkDefinitions();

    for (auto& case_ptr : cases_) { case_ptr->walkDefinitions(); }
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

void Match::validate(ValidationLogger& validation_logger) const
{
    bool valid = true;

    valid &= expression_->validate(validation_logger);

    if (!valid) return;

    valid &= validateType(*expression_, validation_logger);

    if (!valid) return;

    validateCases(location(), *expression_, cases_, validation_logger);
}

bool Match::validateType(Expression& expression, ValidationLogger& validation_logger)
{
    lang::ResolvingHandle<lang::Type> type = expression.type();

    if (!type->isFixedWidthIntegerType() && !type->isBooleanType() && !type->isSizeType() && !type->isDiffType()
        && !type->isUnsignedIntegerPointerType())
    {
        validation_logger.logError("Cannot match non-integer or boolean type " + type->getAnnotatedName(),
                                   expression.location());

        return false;
    }

    return true;
}

bool Match::validateCases(lang::Location                            location,
                          Expression&                               expression,
                          const std::vector<std::unique_ptr<Case>>& cases,
                          ValidationLogger&                         validation_logger)
{
    bool valid = true;

    std::vector<std::reference_wrapper<Case>> checked_cases;
    ssize_t                                   covered_cases = 0;

    for (auto& case_instance : cases)
    {
        valid &= case_instance->validate(expression.type(), validation_logger);

        ssize_t additional_coverage = case_instance->getCoverageCount();
        bool    has_default_case    = additional_coverage == -1 || covered_cases == -1;
        covered_cases               = has_default_case ? -1 : covered_cases + additional_coverage;

        for (auto& checked_case : checked_cases)
        {
            if (!case_instance->validateConflicts(checked_case, validation_logger)) { valid = false; }
        }

        checked_cases.emplace_back(*case_instance);
    }

    StateCount state_count = expression.type()->getStateCount();

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
                                           + expression.type()->getAnnotatedName(),
                                       location);
            valid = false;
        }
    }

    if (auto* count = std::get_if<SpecialCount>(&state_count))
    {
        if (*count == SpecialCount::UNCOUNTABLE)
        {
            validation_logger.logError("Cannot match uncountable type " + expression.type()->getAnnotatedName(),
                                       location);
            valid = false;
        }
    }

    return valid;
}

void Match::doBuild(CompileContext&)
{
    // Handled by basic block.
}
