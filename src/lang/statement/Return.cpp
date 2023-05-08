#include "Return.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "validation/ValidationLogger.h"

Return::Return(Optional<Owned<Expression>> return_value, lang::Location location)
    : Statement(location)
    , return_value_(std::move(return_value))
{
    if (return_value_.hasValue()) addSubexpression(*return_value_.value());
}

Expression const* Return::expression() const
{
    return getPtr(return_value_);
}

std::vector<Owned<lang::BasicBlock>> Return::createBasicBlocks(lang::BasicBlock& entry, lang::Function& function)
{
    std::vector<Owned<lang::BasicBlock>> blocks;
    blocks.push_back(
        lang::BasicBlock::createReturning(*scope()->asLocalScope(), return_value_.value().get(), location(), function));

    entry.link(*blocks.front());

    return blocks;
}

void Return::validate(ValidationLogger& validation_logger) const
{
    if (return_value_.hasValue()) return_value_.value()->validate(validation_logger);
}

Statements Return::expandWith(Expressions subexpressions, Statements, lang::Context&) const
{
    Statements statements;

    if (return_value_.hasValue())
    {
        statements.emplace_back(makeOwned<Return>(std::move(subexpressions[0]), location()));
    }
    else { statements.emplace_back(makeOwned<Return>(std::nullopt, location())); }

    return statements;
}

Statements Return::arrangeExpandedStatements(Statements     before,
                                             Statements     expanded,
                                             Statements     after,
                                             lang::Context& new_context) const
{
    assert(expanded.size() == 1);
    assert(dynamic_cast<Return*>(expanded.front().get()));

    auto& return_statement = *dynamic_cast<Return*>(expanded.front().get());

    if (not after.empty())// Statements after the return would be unreachable without re-arranging them.
    {
        Optional<Owned<Expression>> return_value = std::move(return_statement.return_value_);
        expanded.clear();

        Optional<Owned<Expression>> return_value_access;

        if (return_value.hasValue())
        {
            auto temp_name          = lang::Identifier::like(scope()->getTemporaryName(), location());
            auto make_temp_variable = [&temp_name]() { return lang::makeHandled<lang::Variable>(temp_name); };

            expanded.emplace_back(
                makeOwned<LocalVariableDefinition>(temp_name,
                                                   expression()->type().createUndefinedClone(new_context),
                                                   location(),
                                                   lang::Assigner::COPY_ASSIGNMENT,
                                                   std::move(return_value),
                                                   location()));

            return_value_access = makeOwned<VariableAccess>(make_temp_variable(), location());
        }

        after.emplace_back(makeOwned<Return>(std::move(return_value_access), location()));
    }

    return Statement::arrangeExpandedStatements(std::move(before), std::move(expanded), std::move(after), new_context);
}

void Return::doBuild(CompileContext&)
{
    // Handled by basic block.
}
