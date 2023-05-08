#include "Statement.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/BasicBlock.h"
#include "lang/construct/Function.h"

Statement::Statement(lang::Location location) : location_(location) {}

void Statement::setContainingScope(lang::Scope& scope)
{
    assert(!containing_scope_);
    containing_scope_ = &scope;

    setScope(scope);
}

std::vector<Owned<lang::BasicBlock>> Statement::createBasicBlocks(lang::BasicBlock& entry, lang::Function& function)
{
    std::vector<Owned<lang::BasicBlock>> blocks;
    blocks.push_back(lang::BasicBlock::createSimple(this));

    entry.link(*blocks.front());

    for (auto& block : blocks) { block->setContainingFunction(function); }

    return blocks;
}

Statement const* Statement::parent() const
{
    return parent_;
}

bool Statement::isLoop() const
{
    return false;
}

std::pair<lang::BasicBlock*, lang::BasicBlock*> Statement::getLoopParts() const
{
    return {nullptr, nullptr};
}

void Statement::setScope(lang::Scope& scope)
{
    for (auto& subexpression : subexpressions_) { subexpression.get().setContainingScope(scope); }
    for (auto& substatement : substatements_) { substatement.get().setContainingScope(scope); }
}

lang::Scope* Statement::scope() const
{
    return containing_scope_;
}

lang::LocalScope* Statement::getBlockScope()
{
    return nullptr;
}

lang::LocalScope const* Statement::getBlockScope() const
{
    return nullptr;
}

bool Statement::isCompound() const
{
    return false;
}

void Statement::walkDefinitions()
{
    for (auto& subexpression : subexpressions_) { subexpression.get().walkDefinitions(); }
    for (auto& substatement : substatements_) { substatement.get().walkDefinitions(); }
}

void Statement::postResolve()
{
    for (auto& subexpression : subexpressions_) { subexpression.get().postResolve(); }
    for (auto& substatement : substatements_) { substatement.get().postResolve(); }

    for (auto& subexpression : subexpressions_) { subexpression.get().type(); }
}

lang::Location Statement::location() const
{
    return location_;
}

Statements Statement::expand(lang::Context& new_context) const
{
    Statements before;
    Statements after;

    Expressions subexpressions;
    subexpressions.reserve(subexpressions_.size());

    for (auto& subexpression : subexpressions_)
    {
        auto [statements_before, expanded_expression, statements_after] = subexpression.get().expand(new_context);

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
        Statements expanded_substatement = substatement.get().expand(new_context);
        substatements.insert(substatements.end(),
                             std::make_move_iterator(expanded_substatement.begin()),
                             std::make_move_iterator(expanded_substatement.end()));
    }

    auto expanded_statements = this->expandWith(std::move(subexpressions), std::move(substatements), new_context);

    return arrangeExpandedStatements(std::move(before), std::move(expanded_statements), std::move(after), new_context);
}

Statements Statement::arrangeExpandedStatements(Statements before,
                                                Statements expanded,
                                                Statements after,
                                                lang::Context&) const
{
    Statements final;

    final.insert(final.end(), std::make_move_iterator(before.begin()), std::make_move_iterator(before.end()));
    final.insert(final.end(), std::make_move_iterator(expanded.begin()), std::make_move_iterator(expanded.end()));
    final.insert(final.end(), std::make_move_iterator(after.begin()), std::make_move_iterator(after.end()));

    return final;
}

void Statement::build(CompileContext& context)
{
    context.setDebugLocation(location(), *scope());
    doBuild(context);
    context.resetDebugLocation();
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

    substatement.parent_ = this;
}
