#include "BasicBlock.h"

#include "lang/ApplicationVisitor.h"
#include "lang/scope/Scope.h"

lang::bb::def::Finalizing::Finalizing(lang::Scope& scope, std::string info) : scope_(scope), info_(std::move(info)) {}

lang::BasicBlock const* lang::bb::def::Finalizing::next() const
{
    return next_;
}

lang::Scope const& lang::bb::def::Finalizing::scope() const
{
    return scope_;
}

bool lang::bb::def::Finalizing::isMeta() const
{
    return true;
}

void lang::bb::def::Finalizing::setLink(lang::BasicBlock& next)
{
    lang::BasicBlock* next_ptr = &next;

    assert(&next_ptr->definition() != this);
    assert(next_ == nullptr);

    next_ = next_ptr;
    next_->registerIncomingLink(*self());
}

void lang::bb::def::Finalizing::updateLink(lang::BasicBlock* former, lang::BasicBlock* updated)
{
    assert(next_ == former);
    assert(next_ != updated);

    next_ = updated;
    next_->registerIncomingLink(*self());
}

std::vector<lang::BasicBlock const*> lang::bb::def::Finalizing::getSuccessors() const
{
    std::vector<lang::BasicBlock const*> successors;

    if (next_) { successors.push_back(next_); }

    return successors;
}

std::vector<lang::BasicBlock*> lang::bb::def::Finalizing::getReachableNext()
{
    std::vector<lang::BasicBlock*> n;

    if (next_) { n.push_back(next_); }

    return n;
}

std::string lang::bb::def::Finalizing::getExitRepresentation() const
{
    return "// finalize (" + info_ + ")";
}
