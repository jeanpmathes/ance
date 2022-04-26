#include "Statement.h"

#include "lang/construct/Function.h"
#include "compiler/CompileContext.h"
#include "lang/construct/BasicBlock.h"

Statement::Statement(lang::Location location) : location_(location) {}

void Statement::setContainingScope(lang::Scope* scope)
{
    assert(!containing_scope_);
    containing_scope_ = scope;

    setScope(scope);
}

std::vector<std::unique_ptr<lang::BasicBlock>> Statement::createBasicBlocks(lang::BasicBlock& entry,
                                                                            lang::Function*   function)
{
    std::vector<std::unique_ptr<lang::BasicBlock>> blocks;
    blocks.push_back(lang::BasicBlock::createSimple(this));

    entry.link(*blocks.front());

    for (auto& block : blocks) { block->setContainingFunction(function); }

    return blocks;
}

void Statement::setScope(lang::Scope* scope)
{
    for (auto& subexpression : subexpressions_) { subexpression.get().setContainingScope(scope); }
    for (auto& substatement : substatements_) { substatement.get().setContainingScope(scope); }
}

lang::Scope* Statement::scope() const
{
    return containing_scope_;
}

void Statement::walkDefinitions()
{
    for (auto& subexpression : subexpressions_) { subexpression.get().walkDefinitions(); }
    for (auto& substatement : substatements_) { substatement.get().walkDefinitions(); }
}

lang::Location Statement::location() const
{
    return location_;
}

Statements Statement::expand() const
{
    Statements before;
    Statements after;

    Expressions subexpressions;
    subexpressions.reserve(subexpressions_.size());

    for (auto& subexpression : subexpressions_)
    {
        auto [statements_before, expanded_expression, statements_after] = subexpression.get().expand();

        before.insert(before.end(),
                      std::make_move_iterator(statements_before.begin()),
                      std::make_move_iterator(statements_before.end()));
        after.insert(after.begin(),
                     std::make_move_iterator(statements_after.begin()),
                     std::make_move_iterator(statements_after.end()));

        subexpressions.push_back(std::move(expanded_expression));
    }

    Statements substatements;
    substatements.reserve(substatements_.size());

    for (auto& substatement : substatements_)
    {
        Statements expanded_substatement = substatement.get().expand();
        substatements.insert(substatements.end(),
                             std::make_move_iterator(expanded_substatement.begin()),
                             std::make_move_iterator(expanded_substatement.end()));
    }

    auto expanded_statements = this->expandWith(std::move(subexpressions), std::move(substatements));

    Statements final;

    final.insert(final.end(), std::make_move_iterator(before.begin()), std::make_move_iterator(before.end()));
    final.insert(final.end(),
                 std::make_move_iterator(expanded_statements.begin()),
                 std::make_move_iterator(expanded_statements.end()));
    final.insert(final.end(), std::make_move_iterator(after.begin()), std::make_move_iterator(after.end()));

    return final;
}

void Statement::build(CompileContext* context)
{
    context->setDebugLocation(location(), scope());
    doBuild(context);
    context->resetDebugLocation();
}

void Statement::addSubexpression(Expression& subexpression)
{
    subexpressions_.emplace_back(subexpression);
    addChild(subexpression);
}

void Statement::addSubstatement(Statement& substatement)
{
    substatements_.emplace_back(substatement);
    addChild(substatement);
}
