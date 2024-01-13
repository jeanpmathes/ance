#include "Return.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/construct/constant/UnitConstant.h"
#include "lang/expression/Expression.h"
#include "validation/ValidationLogger.h"

Return::Return(Optional<Owned<Expression>> return_value, lang::Location location)
    : Statement(location)
    , return_value_(std::move(return_value))
{
    if (return_value_.hasValue()) addSubexpression(**return_value_);
}

Expression const* Return::expression() const
{
    return getPtr(return_value_);
}

std::vector<Owned<lang::BasicBlock>> Return::createBasicBlocks(lang::BasicBlock& entry, lang::Function& function)
{
    // Return statement without value is syntactic sugar and not allowed at later stages (like the current stage).
    assert(return_value_.hasValue());

    std::vector<Owned<lang::BasicBlock>> blocks;
    blocks.push_back(lang::BasicBlock::createReturning(scope(), **return_value_, function));

    entry.link(*blocks.front());

    return blocks;
}

void Return::validate(ValidationLogger& validation_logger) const
{
    if (return_value_.hasValue()) return_value_.value()->validate(validation_logger);
}

Statements Return::expandWith(Expressions subexpressions, Statements, lang::Context& new_context) const
{
    Statements statements;

    Optional<Owned<Expression>> return_value_access;

    if (return_value_.hasValue())
    {
        auto temp_name          = lang::Identifier::like(scope().getTemporaryName(), location());
        auto make_temp_variable = [&temp_name]() { return lang::makeHandled<lang::Variable>(temp_name); };

        statements.emplace_back(
            makeOwned<LocalVariableDefinition>(temp_name,
                                               expression()->type().getUndefinedTypeClone(new_context),
                                               location(),
                                               lang::Assigner::COPY_ASSIGNMENT,
                                               std::move(subexpressions[0]),
                                               location()));

        return_value_access = makeOwned<VariableAccess>(make_temp_variable(), true, location());
    }
    else { return_value_access = makeOwned<ConstantLiteral>(makeShared<lang::UnitConstant>(new_context), location()); }

    statements.emplace_back(makeOwned<Return>(std::move(return_value_access), location()));

    return statements;
}

Statements Return::arrangeExpandedStatements(Statements before, Statements expanded, Statements after) const
{
    size_t     return_statement_index = 0;
    Statements new_expanded;

    if (return_value_.hasValue())// Statements after the return would be unreachable without re-arranging them.
    {
        new_expanded.emplace_back(std::move(expanded[return_statement_index++]));// Emplace the variable definition.
    }

    after.emplace_back(std::move(expanded[return_statement_index++]));// Emplace the return statement.

    return Statement::arrangeExpandedStatements(std::move(before), std::move(new_expanded), std::move(after));
}

void Return::doBuild(CompileContext&)
{
    // Handled by basic block.
}
