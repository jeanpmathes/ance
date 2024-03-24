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

void lang::bb::def::Empty::complete(size_t& index)
{
    if (next_) next_->complete(index);
}

void lang::bb::def::Empty::setLink(lang::BasicBlock& next)
{
    lang::BasicBlock* next_ptr = &next;

    assert(&next_ptr->definition() != this);
    assert(next_ == nullptr);

    next_ = next_ptr;
    next_->registerIncomingLink(*self());
}

void lang::bb::def::Empty::updateLink(lang::BasicBlock* former, lang::BasicBlock* updated)
{
    assert(next_ == former);
    assert(next_ != updated);

    next_ = updated;
    next_->registerIncomingLink(*self());
}

void lang::bb::def::Empty::transferStatements(std::list<Statement*>&)
{
    assert(false);
}

void lang::bb::def::Empty::simplify()
{
    if (next_) next_->simplify();
}

std::list<lang::BasicBlock const*> lang::bb::def::Empty::getLeaves() const
{
    std::list<lang::BasicBlock const*> leaves;

    if (next_) { leaves.splice(leaves.end(), next_->getLeaves()); }
    else { leaves.push_back(self()); }

    return leaves;
}

std::vector<lang::BasicBlock const*> lang::bb::def::Empty::getSuccessors() const
{
    std::vector<lang::BasicBlock const*> successors;

    if (next_) { successors.push_back(next_); }

    return successors;
}

lang::Location lang::bb::def::Empty::getStartLocation() const
{
    return lang::Location::global();
}

lang::Location lang::bb::def::Empty::getEndLocation() const
{
    return lang::Location::global();
}

void lang::bb::def::Empty::reach() const
{
    if (next_) next_->reach();
}

std::string lang::bb::def::Empty::getExitRepresentation() const
{
    return "// meta ";
}
