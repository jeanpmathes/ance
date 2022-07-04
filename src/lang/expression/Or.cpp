#include "Or.h"

#include "lang/scope/Scope.h"
#include "lang/type/BooleanType.h"

#include "lang/expression/UnaryOperation.h"
#include "lang/expression/VariableAccess.h"
#include "lang/statement/Assignment.h"
#include "lang/statement/Drop.h"
#include "lang/statement/If.h"
#include "lang/statement/LocalVariableDefinition.h"

Or::Or(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right, lang::Location location)
    : UnexpandedExpression(location)
    , left_(std::move(left))
    , right_(std::move(right))
{
    addSubexpression(*left_);
    addSubexpression(*right_);
}

Expression& Or::left() const
{
    return *left_;
}

Expression& Or::right() const
{
    return *right_;
}

lang::ResolvingHandle<lang::Type> Or::type() const
{
    return lang::ResolvingHandle<lang::Type>(lang::BooleanType::get());
}

bool Or::validate(ValidationLogger& validation_logger) const
{
    bool valid = left_->validate(validation_logger) && right_->validate(validation_logger);

    if (!valid) return false;

    valid &= lang::Type::checkMismatch(lang::BooleanType::get(), left_->type(), left_->location(), validation_logger);
    valid &= lang::Type::checkMismatch(lang::BooleanType::get(), right_->type(), right_->location(), validation_logger);

    return valid;
}

Expression::Expansion Or::expandWith(Expressions subexpressions) const
{
    auto        temp_name          = lang::Identifier::from(scope()->getTemporaryName(), location());
    auto        make_temp_variable = [&temp_name]() { return lang::makeHandled<lang::Variable>(temp_name); };
    auto lhs = std::move(subexpressions[0]);
    auto        rhs                = std::move(subexpressions[1]);

    Statements before;

    before.push_back(std::make_unique<LocalVariableDefinition>(temp_name,
                                                               lang::BooleanType::get(),
                                                               location(),
                                                               lang::Assigner::COPY_ASSIGNMENT,
                                                               std::move(lhs),
                                                               location()));

    before.push_back(std::make_unique<If>(
        std::make_unique<UnaryOperation>(lang::UnaryOperator::NOT,
                                         std::make_unique<VariableAccess>(make_temp_variable(), location()),
                                         location()),
        std::make_unique<Assignment>(std::make_unique<VariableAccess>(make_temp_variable(), location()),
                                     lang::Assigner::COPY_ASSIGNMENT,
                                     std::move(rhs),
                                     location()),
        nullptr,
        location()));

    std::unique_ptr<Expression> result = std::make_unique<VariableAccess>(make_temp_variable(), location());

    Statements after;

    after.push_back(std::make_unique<Drop>(make_temp_variable(), location()));

    return {std::move(before), std::move(result), std::move(after)};
}

Or::~Or() = default;
