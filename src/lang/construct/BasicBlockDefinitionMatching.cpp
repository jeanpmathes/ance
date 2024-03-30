#include "BasicBlock.h"

#include "lang/ApplicationVisitor.h"
#include "lang/statement/Match.h"
#include "validation/ValidationLogger.h"

lang::bb::def::Matching::Matching(Match& match, std::vector<std::vector<LiteralExpression*>> cases)
    : match_(match)
    , cases_(std::move(cases))
{}

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

std::vector<lang::BasicBlock const*> lang::bb::def::Matching::getSuccessors() const
{
    std::vector<lang::BasicBlock const*> successors;

    successors.reserve(branches_.size());
    for (auto& branch : branches_) { successors.push_back(branch); }

    return successors;
}

std::vector<lang::BasicBlock*> lang::bb::def::Matching::getReachableNext()
{
    std::vector<lang::BasicBlock*> n;

    n.reserve(branches_.size());
    for (auto& branch : branches_) { n.push_back(branch); }

    return n;
}

std::string lang::bb::def::Matching::getExitRepresentation() const
{
    return "// match";
}
