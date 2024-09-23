#include "Statement.h"

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

bool Statement::isRootCMP() const
{
    return false;
}

lang::Scope& Statement::scope()
{
    return *containing_scope_;
}

lang::Scope const& Statement::scope() const
{
    return *containing_scope_;
}

bool Statement::isCMP() const
{
    if (!isRootCMP()) return false;

    for (Statement const& substatement : substatements_)
    {
        if (!substatement.isCMP()) return false;
    }

    for (Expression const& subexpression : subexpressions_)
    {
        if (!subexpression.isCMP()) return false;
    }

    return true;
}

lang::OrderedScope* Statement::getBlockScope()
{
    return nullptr;
}

lang::Scope const* Statement::getBlockScope() const
{
    return nullptr;
}

std::vector<std::reference_wrapper<lang::OrderedScope>> Statement::getSubScopesInOrder()
{
    std::vector<std::reference_wrapper<lang::OrderedScope>> sub_scopes;

    for (auto& substatement : substatements_)
    {
        if (auto sub_scope = substatement.get().getBlockScope()) { sub_scopes.emplace_back(*sub_scope); }
        else
        {
            auto sub_sub_scopes = substatement.get().getSubScopesInOrder();
            sub_scopes.insert(sub_scopes.end(),
                              std::make_move_iterator(sub_sub_scopes.begin()),
                              std::make_move_iterator(sub_sub_scopes.end()));
        }
    }

    return sub_scopes;
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
        Statements expanded_substatements = substatement.get().expand(new_context);

        if (isCompound())
        {
            substatements.insert(substatements.end(),
                                 std::make_move_iterator(expanded_substatements.begin()),
                                 std::make_move_iterator(expanded_substatements.end()));
        }
        else if (expanded_substatements.size() == 1)
        {
            substatements.push_back(std::move(expanded_substatements.front()));
        }
        else
        {
            auto code_block = lang::CodeBlock::makeScoped(location());
            code_block->append(lang::CodeBlock::wrapStatements(std::move(expanded_substatements)));

            substatements.emplace_back(std::move(code_block));
        }
    }

    // All statements expect the same amount of subexpressions and substatements they previously registered.
    // The only exception is compound statements, which can handle any amount of substatements.

    assert(subexpressions.size() == subexpressions_.size());
    assert(substatements.size() == substatements_.size() || isCompound());

    auto expanded_statements = expandWith(std::move(subexpressions), std::move(substatements), new_context);
    return arrangeExpandedStatements(std::move(before), std::move(expanded_statements), std::move(after));
}

Statements Statement::arrangeExpandedStatements(Statements before, Statements expanded, Statements after) const
{
    Statements final;

    final.insert(final.end(), std::make_move_iterator(before.begin()), std::make_move_iterator(before.end()));
    final.insert(final.end(), std::make_move_iterator(expanded.begin()), std::make_move_iterator(expanded.end()));
    final.insert(final.end(), std::make_move_iterator(after.begin()), std::make_move_iterator(after.end()));

    return final;
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
