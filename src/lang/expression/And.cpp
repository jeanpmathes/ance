#include "And.h"

#include "lang/scope/Scope.h"
#include "lang/type/BooleanType.h"

#include "lang/ApplicationVisitor.h"
#include "lang/expression/UnaryOperation.h"
#include "lang/expression/VariableAccess.h"
#include "lang/statement/Assignment.h"
#include "lang/statement/Erase.h"
#include "lang/statement/If.h"
#include "lang/statement/LocalVariableDefinition.h"

And::And(bool negate, Owned<Expression> left, Owned<Expression> right, lang::Location location)
    : Expression(location)
    , negate_(negate)
    , left_(std::move(left))
    , right_(std::move(right))
{
    addSubexpression(*left_);
    addSubexpression(*right_);
}

bool And::negate() const
{
    return negate_;
}

Expression const& And::left() const
{
    return *left_;
}

Expression const& And::right() const
{
    return *right_;
}

void And::defineType(lang::ResolvingHandle<lang::Type> type)
{
    if (!isInitialized()) return;
    type.reroute(scope().context().getBooleanType());
}

bool And::validate(ValidationLogger& validation_logger) const
{
    bool valid = left_->validate(validation_logger) && right_->validate(validation_logger);

    if (!valid) return false;

    valid &= lang::Type::checkMismatch(scope().context().getBooleanType(),
                                       left_->type(),
                                       left_->location(),
                                       validation_logger);
    valid &= lang::Type::checkMismatch(scope().context().getBooleanType(),
                                       right_->type(),
                                       right_->location(),
                                       validation_logger);

    return valid;
}

Expression::Expansion And::expandWith(Expressions subexpressions, lang::Context& new_context) const
{
    auto temp_name          = lang::Identifier::like(scope().getTemporaryName(), location());
    auto make_temp_variable = [&temp_name]() { return lang::makeHandled<lang::Variable>(temp_name); };
    auto lhs                = std::move(subexpressions[0]);
    auto rhs                = std::move(subexpressions[1]);

    Statements before;

    before.emplace_back(makeOwned<LocalVariableDefinition>(temp_name,
                                                           new_context.getBooleanType(),
                                                           location(),
                                                           lang::Assigner::COPY_ASSIGNMENT,
                                                           std::move(lhs),
                                                           location()));

    before.emplace_back(
        makeOwned<If>(makeOwned<VariableAccess>(make_temp_variable(), true, location()),
                      makeOwned<Assignment>(makeOwned<VariableAccess>(make_temp_variable(), true, location()),
                                            lang::Assigner::COPY_ASSIGNMENT,
                                            std::move(rhs),
                                            location()),
                      std::nullopt,
                      location()));

    Owned<Expression> result = makeOwned<VariableAccess>(make_temp_variable(), true, location());

    if (negate_) { result = makeOwned<UnaryOperation>(lang::UnaryOperator::NOT, std::move(result), location()); }

    Statements after;

    after.emplace_back(makeOwned<Erase>(make_temp_variable(), location()));

    return {std::move(before), std::move(result), std::move(after)};
}

And::~And() = default;
