#include "BasicBlock.h"

#include "lang/ApplicationVisitor.h"
#include "lang/statement/Match.h"
#include "validation/ValidationLogger.h"

lang::bb::def::Matching::Matching(Match& match, std::vector<std::vector<LiteralExpression*>> cases)
    : match_(match)
    , cases_(std::move(cases))
{}

std::list<Statement*> const& lang::bb::def::Matching::statements() const
{
    return statements_;
}

Expression const& lang::bb::def::Matching::matched() const
{
    return match_.expression();
}

std::vector<std::vector<LiteralExpression*>> const& lang::bb::def::Matching::cases() const
{
    return cases_;
}

std::vector<lang::BasicBlock*> const& lang::bb::def::Matching::branches() const
{
    return branches_;
}

void lang::bb::def::Matching::complete(size_t& index)
{
    for (auto& statement : statements_) { self()->addChild(*statement); }
    for (auto& branch : branches_) { branch->complete(index); }
}

void lang::bb::def::Matching::setLink(lang::BasicBlock& next)
{
    branches_.push_back(&next);
    next.registerIncomingLink(*self());
}

void lang::bb::def::Matching::updateLink(lang::BasicBlock* former, lang::BasicBlock* updated)
{
    for (auto& branch : branches_)
    {
        if (branch == former)
        {
            branch = updated;
            updated->registerIncomingLink(*self());

            return;
        }
    }
}

void lang::bb::def::Matching::simplify()
{
    for (auto& branch : branches_) { branch->simplify(); }
}

void lang::bb::def::Matching::transferStatements(std::list<Statement*>& statements)
{
    statements_.splice(statements_.begin(), statements);
}

std::list<lang::BasicBlock const*> lang::bb::def::Matching::getLeaves() const
{
    std::list<lang::BasicBlock const*> leaves;

    for (auto& branch : branches_)
    {
        for (auto& leaf : branch->getLeaves()) { leaves.push_back(leaf); }
    }

    return leaves;
}
std::vector<lang::BasicBlock const*> lang::bb::def::Matching::getSuccessors() const
{
    std::vector<lang::BasicBlock const*> successors;

    successors.reserve(branches_.size());
    for (auto& branch : branches_) { successors.push_back(branch); }

    return successors;
}

lang::Location lang::bb::def::Matching::getStartLocation() const
{
    if (statements_.empty()) { return lang::Location::global(); }

    return statements_.front()->location();
}

lang::Location lang::bb::def::Matching::getEndLocation() const
{
    if (statements_.empty()) { return lang::Location::global(); }

    return statements_.back()->location();
}

void lang::bb::def::Matching::reach() const
{
    for (auto& branch : branches_) { branch->reach(); }
}

std::string lang::bb::def::Matching::getExitRepresentation() const
{
    return "// match";
}
