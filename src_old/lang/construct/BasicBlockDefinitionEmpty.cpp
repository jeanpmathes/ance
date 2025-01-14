#include "BasicBlock.h"

#include "lang/ApplicationVisitor.h"

lang::BasicBlock const* lang::bb::def::Empty::next() const
{
    return next_;
}

bool lang::bb::def::Empty::isMeta() const
{
    return true;
}

void lang::bb::def::Empty::setLink(lang::BasicBlock& next)
{
    lang::BasicBlock* next_ptr = &next;

    assert(next_ptr != this);
    assert(next_ == nullptr);

    next_ = next_ptr;
    next_->registerIncomingLink(*this);
}

void lang::bb::def::Empty::updateLink(lang::BasicBlock* former, lang::BasicBlock* updated)
{
    assert(next_ == former);
    assert(next_ != updated);

    next_ = updated;
    next_->registerIncomingLink(*this);
}

std::vector<lang::BasicBlock const*> lang::bb::def::Empty::getSuccessors() const
{
    std::vector<lang::BasicBlock const*> successors;

    if (next_) { successors.push_back(next_); }

    return successors;
}

std::vector<lang::BasicBlock*> lang::bb::def::Empty::getReachableNext()
{
    std::vector<lang::BasicBlock*> n;

    if (next_) { n.push_back(next_); }

    return n;
}

std::string lang::bb::def::Empty::getExitRepresentation() const
{
    return "// meta ";
}

