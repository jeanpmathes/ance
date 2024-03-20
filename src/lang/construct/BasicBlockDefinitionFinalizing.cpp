#include "BasicBlock.h"

#include "compiler/CompileContext.h"
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

void lang::bb::def::Finalizing::complete(size_t& index)
{
    if (next_) next_->complete(index);
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

void lang::bb::def::Finalizing::transferStatements(std::list<Statement*>& list)
{
    assert(list.empty());
}

void lang::bb::def::Finalizing::simplify()
{
    if (next_) next_->simplify();
}

std::list<lang::BasicBlock const*> lang::bb::def::Finalizing::getLeaves() const
{
    std::list<lang::BasicBlock const*> leaves;

    if (next_) { leaves.splice(leaves.end(), next_->getLeaves()); }
    else { leaves.push_back(self()); }

    return leaves;
}

std::vector<lang::BasicBlock const*> lang::bb::def::Finalizing::getSuccessors() const
{
    std::vector<lang::BasicBlock const*> successors;

    if (next_) { successors.push_back(next_); }

    return successors;
}

lang::Location lang::bb::def::Finalizing::getStartLocation() const
{
    return lang::Location::global();
}

lang::Location lang::bb::def::Finalizing::getEndLocation() const
{
    return lang::Location::global();
}

void lang::bb::def::Finalizing::reach() const
{
    if (next_) next_->reach();
}

std::string lang::bb::def::Finalizing::getExitRepresentation() const
{
    return "// finalize (" + info_ + ")";
}
