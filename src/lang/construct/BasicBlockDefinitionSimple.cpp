#include "BasicBlock.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"

lang::bb::def::Simple::Simple() = default;

lang::bb::def::Simple::Simple(Statement& statement)
{
    pushStatement(statement);
}

lang::BasicBlock const* lang::bb::def::Simple::next() const
{
    return next_;
}

void lang::bb::def::Simple::setLink(lang::BasicBlock& next)
{
    lang::BasicBlock* next_ptr = &next;

    assert(&next_ptr->definition() != this);
    assert(next_ == nullptr);

    next_ = next_ptr;
    next_->registerIncomingLink(*self());
}

void lang::bb::def::Simple::updateLink(lang::BasicBlock* former, lang::BasicBlock* updated)
{
    assert(next_ == former);
    assert(next_ != updated);

    next_ = updated;
    next_->registerIncomingLink(*self());
}

bool lang::bb::def::Simple::isSimplificationCandidate() const
{
    return true;
}

std::vector<lang::BasicBlock const*> lang::bb::def::Simple::getSuccessors() const
{
    std::vector<lang::BasicBlock const*> successors;

    if (next_) { successors.push_back(next_); }

    return successors;
}

std::vector<lang::BasicBlock*> lang::bb::def::Simple::getReachableNext()
{
    std::vector<lang::BasicBlock*> n;

    if (next_) { n.push_back(next_); }

    return n;
}

std::string lang::bb::def::Simple::getExitRepresentation() const
{
    return "// ---";
}
