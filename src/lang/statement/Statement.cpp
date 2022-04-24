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
    for (auto& subexpression : subexpressions_) { subexpression->setContainingScope(scope); }
    for (auto& substatement : substatements_) { substatement->setContainingScope(scope); }
}

lang::Scope* Statement::scope() const
{
    return containing_scope_;
}

void Statement::walkDefinitions()
{
    for (auto& subexpression : subexpressions_) { subexpression->walkDefinitions(); }
    for (auto& substatement : substatements_) { substatement->walkDefinitions(); }
}

lang::Location Statement::location() const
{
    return location_;
}

void Statement::build(CompileContext* context)
{
    context->setDebugLocation(location(), scope());
    doBuild(context);
    context->resetDebugLocation();
}

void Statement::addSubexpression(Expression& subexpression)
{
    subexpressions_.push_back(&subexpression);
    addChild(subexpression);
}

void Statement::addSubstatement(Statement& substatement)
{
    substatements_.push_back(&substatement);
    addChild(substatement);
}
