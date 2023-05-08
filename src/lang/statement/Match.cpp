#include "Match.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/CodeBlock.h"
#include "lang/construct/constant/Constant.h"
#include "lang/expression/Expression.h"
#include "lang/expression/VariableAccess.h"
#include "lang/statement/Assignment.h"
#include "validation/ValidationLogger.h"

Case* Case::createDefault(Owned<Statement> code)
{
    return new Case(std::vector<Owned<ConstantExpression>>(), std::move(code));
}

Case* Case::createCase(std::vector<Owned<ConstantExpression>> conditions, Owned<Statement> code)
{
    return new Case(std::move(conditions), std::move(code));
}

Case* Case::createDefault(Owned<Expression> expression)
{
    return new Case(std::vector<Owned<ConstantExpression>>(), std::move(expression));
}

Case* Case::createCase(std::vector<Owned<ConstantExpression>> conditions, Owned<Expression> expression)
{
    return new Case(std::move(conditions), std::move(expression));
}

Case::Case(std::vector<Owned<ConstantExpression>> conditions, std::variant<Owned<Statement>, Owned<Expression>> code)
    : conditions_(std::move(conditions))
    , code_(std::move(code))
{
    for (auto& condition : conditions_)
    {
        Expression* condition_expression = condition.get();
        addChild(*condition_expression);
    }
}

std::vector<std::reference_wrapper<ConstantExpression const>> Case::conditions() const
{
    std::vector<std::reference_wrapper<ConstantExpression const>> result;

    for (auto& condition : conditions_) { result.emplace_back(*condition); }

    return result;
}

std::reference_wrapper<lang::Visitable<ANCE_CONSTRUCTS> const> Case::code() const
{
    if (std::holds_alternative<Owned<Statement>>(code_)) { return *std::get<Owned<Statement>>(code_); }

    if (std::holds_alternative<Owned<Expression>>(code_)) { return *std::get<Owned<Expression>>(code_); }

    throw std::runtime_error("Case::code() called on invalid case");
}

void Case::setContainingScope(lang::Scope& scope)
{
    for (auto& condition : conditions_) { condition->setContainingScope(scope); }

    if (std::holds_alternative<Owned<Statement>>(code_))
    {
        Statement* code = std::get<Owned<Statement>>(code_).get();
        code->setContainingScope(scope);
    }

    if (std::holds_alternative<Owned<Expression>>(code_))
    {
        Expression* code = std::get<Owned<Expression>>(code_).get();
        code->setContainingScope(scope);
    }
}

void Case::walkDefinitions()
{
    for (auto& condition : conditions_) { condition->walkDefinitions(); }

    if (std::holds_alternative<Owned<Statement>>(code_))
    {
        Statement* code = std::get<Owned<Statement>>(code_).get();
        code->walkDefinitions();
    }

    if (std::holds_alternative<Owned<Expression>>(code_))
    {
        Expression* code = std::get<Owned<Expression>>(code_).get();
        code->walkDefinitions();
    }
}

void Case::postResolve()
{
    for (auto& condition : conditions_) { condition->postResolve(); }

    if (std::holds_alternative<Owned<Statement>>(code_))
    {
        Statement* code = std::get<Owned<Statement>>(code_).get();
        code->postResolve();
    }

    if (std::holds_alternative<Owned<Expression>>(code_))
    {
        Expression* code = std::get<Owned<Expression>>(code_).get();
        code->postResolve();
    }
}

std::vector<std::pair<ConstantExpression*, Statement*>> Case::getConditions()
{
    std::vector<std::pair<ConstantExpression*, Statement*>> conditions;

    if (conditions_.empty()) { conditions.emplace_back(nullptr, std::get<Owned<Statement>>(code_).get()); }
    else
    {
        for (auto& condition : conditions_)
        {
            conditions.emplace_back(condition.get(), std::get<Owned<Statement>>(code_).get());
        }
    }

    return conditions;
}

bool Case::validateConflicts(Case const& other, ValidationLogger& validation_logger) const
{
    bool conflicts = false;

    for (auto& condition : conditions_)
    {
        for (auto& other_condition : other.conditions_)
        {
            lang::Constant const& condition_constant       = condition->getConstantValue();
            lang::Constant const& other_condition_constant = other_condition->getConstantValue();

            if (condition_constant.equals(&other_condition_constant))
            {
                validation_logger.logError("Match case '" + condition_constant.toString() + "' already covered",
                                           condition->location());

                conflicts = true;
            }
        }
    }

    return !conflicts;
}

bool Case::validate(lang::Type const& target_type, ssize_t* coverage_count, ValidationLogger& validation_logger) const
{
    assert(coverage_count != nullptr);

    bool valid = true;

    for (auto& condition : conditions_) { valid &= condition->validate(validation_logger); }

    if (std::holds_alternative<Owned<Statement>>(code_))
    {
        Statement const* code = std::get<Owned<Statement>>(code_).get();
        code->validate(validation_logger);
    }

    if (std::holds_alternative<Owned<Expression>>(code_))
    {
        Expression const* code = std::get<Owned<Expression>>(code_).get();
        valid &= code->validate(validation_logger);
    }

    if (!valid) return false;

    if (conditions_.empty())
    {
        *coverage_count = -1;
        return true;
    }

    *coverage_count = static_cast<ssize_t>(conditions_.size());

    std::vector<std::reference_wrapper<ConstantExpression const>> local_conditions;
    for (auto& condition : conditions_)
    {
        for (auto& local_condition : local_conditions)
        {
            lang::Constant const& condition_constant       = condition->getConstantValue();
            lang::Constant const& local_condition_constant = local_condition.get().getConstantValue();

            if (condition_constant.equals(&local_condition_constant))
            {
                validation_logger.logWarning("Match case '" + condition_constant.toString() + "' is duplicated",
                                             condition->location());

                (*coverage_count)--;
            }
        }

        local_conditions.emplace_back(*condition);

        if (!lang::Type::areSame(condition->type(), target_type))
        {
            validation_logger.logError("Cases must be of matched value type " + target_type.getAnnotatedName(),
                                       condition->location());

            valid = false;
        }
    }

    return valid;
}

bool Case::validateReturnTypes(lang::Location                  location,
                               std::vector<Owned<Case>> const& cases,
                               ValidationLogger&               validation_logger)
{
    std::vector<std::reference_wrapper<lang::Type const>> types;

    for (auto& case_instance : cases) { types.emplace_back(std::get<Owned<Expression>>(case_instance->code_)->type()); }

    std::vector<std::reference_wrapper<lang::Type const>> const common_types = lang::Type::getCommonType(types);

    if (common_types.empty() || common_types.size() > 1)
    {
        validation_logger.logError("Cases must have unambiguous common return type", location);
        return false;
    }

    return true;
}

std::vector<lang::ResolvingHandle<lang::Type>> Case::getCommonType(std::vector<Owned<Case>>& cases)
{
    std::vector<lang::ResolvingHandle<lang::Type>> types;

    for (auto& case_instance : cases) { types.emplace_back(std::get<Owned<Expression>>(case_instance->code_)->type()); }

    return lang::Type::getCommonType(types);
}

Owned<Case> Case::expand(lang::Context& new_context) const
{
    Statements expanded_statements = std::get<Owned<Statement>>(code_)->expand(new_context);

    std::vector<Owned<ConstantExpression>> expanded_conditions;

    for (auto& condition : conditions_)
    {
        auto [before, expanded_condition, after] = condition->expand(new_context);

        assert(before.empty());
        assert(after.empty());

        expanded_conditions.emplace_back(*(dynamic_cast<ConstantExpression*>(unwrap(std::move(expanded_condition)))));
    }

    Owned<lang::CodeBlock> new_block = lang::CodeBlock::wrapStatements(std::move(expanded_statements));
    return Owned<Case>(*(new Case(std::move(expanded_conditions), std::move(new_block))));
}

Owned<Case> Case::expand(lang::ResolvingHandle<lang::Variable> target, lang::Context& new_context) const
{
    auto [before, value_provider, after] = std::get<Owned<Expression>>(code_)->expand(new_context);

    lang::Location const location = std::get<Owned<Expression>>(code_)->location();

    Statements expanded_statements;
    expanded_statements.insert(expanded_statements.end(),
                               std::make_move_iterator(before.begin()),
                               std::make_move_iterator(before.end()));

    expanded_statements.emplace_back(makeOwned<Assignment>(makeOwned<VariableAccess>(target, location),
                                                           lang::Assigner::COPY_ASSIGNMENT,
                                                           std::move(value_provider),
                                                           location));

    expanded_statements.insert(expanded_statements.end(),
                               std::make_move_iterator(after.begin()),
                               std::make_move_iterator(after.end()));

    std::vector<Owned<ConstantExpression>> expanded_conditions;

    for (auto& condition : conditions_)
    {
        auto [before_condition, expanded_condition, after_condition] = condition->expand(new_context);

        assert(before_condition.empty());
        assert(after_condition.empty());

        expanded_conditions.emplace_back(*(dynamic_cast<ConstantExpression*>(unwrap(std::move(expanded_condition)))));
    }

    Owned<lang::CodeBlock> new_block = lang::CodeBlock::wrapStatements(std::move(expanded_statements));
    return Owned<Case>(*(new Case(std::move(expanded_conditions), std::move(new_block))));
}

Match::Match(std::vector<Owned<Case>> cases, Owned<Expression> expression, lang::Location location)
    : Statement(location)
    , expression_(std::move(expression))
    , cases_(std::move(cases))
{
    addSubexpression(*expression_);

    for (auto& case_instance : cases_) { addChild(*case_instance); }
}

Expression& Match::expression()
{
    return *expression_;
}

Expression const& Match::expression() const
{
    return *expression_;
}

std::vector<std::reference_wrapper<Case const>> Match::cases() const
{
    std::vector<std::reference_wrapper<Case const>> cases;

    for (auto& case_instance : cases_) { cases.emplace_back(*case_instance); }

    return cases;
}

std::vector<Owned<lang::BasicBlock>> Match::createBasicBlocks(lang::BasicBlock& entry, lang::Function& function)
{
    std::vector<std::pair<ConstantExpression*, Statement*>> conditions;

    for (auto& case_ptr : cases_)
    {
        auto additional_conditions = case_ptr->getConditions();
        conditions.insert(conditions.end(), additional_conditions.begin(), additional_conditions.end());
    }

    auto blocks = lang::BasicBlock::createMatching(*this, conditions, function);
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

void Match::postResolve()
{
    Statement::postResolve();

    for (auto& case_ptr : cases_) { case_ptr->postResolve(); }
}

Statements Match::expandWith(Expressions subexpressions, Statements, lang::Context& new_context) const
{
    std::vector<Owned<Case>> expanded_cases;
    for (auto& case_ptr : cases_)
    {
        auto expanded_case = case_ptr->expand(new_context);
        expanded_cases.push_back(std::move(expanded_case));
    }

    Statements statements;

    statements.emplace_back(makeOwned<Match>(std::move(expanded_cases), std::move(subexpressions[0]), location()));

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

bool Match::validateType(Expression const& expression, ValidationLogger& validation_logger)
{
    lang::Type const& type = expression.type();

    if (!type.isFixedWidthIntegerType() && !type.isBooleanType() && !type.isSizeType() && !type.isDiffType()
        && !type.isUnsignedIntegerPointerType())
    {
        validation_logger.logError("Cannot match non-integer or boolean type " + type.getAnnotatedName(),
                                   expression.location());

        return false;
    }

    return true;
}

bool Match::validateCases(lang::Location                  location,
                          Expression const&               expression,
                          std::vector<Owned<Case>> const& cases,
                          ValidationLogger&               validation_logger)
{
    bool valid = true;

    std::vector<std::reference_wrapper<Case const>> checked_cases;
    ssize_t                                         covered_cases = 0;

    for (auto& case_instance : cases)
    {
        ssize_t additional_coverage = 0;
        valid &= case_instance->validate(expression.type(), &additional_coverage, validation_logger);

        bool const has_default_case = additional_coverage == -1 || covered_cases == -1;
        covered_cases               = has_default_case ? -1 : covered_cases + additional_coverage;

        for (auto& checked_case : checked_cases)
        {
            if (!case_instance->validateConflicts(checked_case, validation_logger)) { valid = false; }
        }

        checked_cases.emplace_back(*case_instance);
    }

    StateCount state_count = expression.type().getStateCount();

    if (covered_cases != -1)
    {
        bool uncovered;

        if (auto* count = std::get_if<size_t>(&state_count))
        {
            uncovered = static_cast<ssize_t>(*count) != covered_cases;
        }
        else { uncovered = true; }

        if (uncovered)
        {
            validation_logger.logError("Match does not cover all possible states of type "
                                           + expression.type().getAnnotatedName(),
                                       location);
            valid = false;
        }
    }

    if (auto* count = std::get_if<SpecialCount>(&state_count))
    {
        if (*count == SpecialCount::UNCOUNTABLE)
        {
            validation_logger.logError("Cannot match uncountable type " + expression.type().getAnnotatedName(),
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
