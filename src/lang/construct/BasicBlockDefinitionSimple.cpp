#include "BasicBlock.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"

lang::bb::def::Simple::Simple() = default;

lang::bb::def::Simple::Simple(Statement& statement)
{
    statements_.push_back(&statement);
}

lang::BasicBlock const* lang::bb::def::Simple::next() const
{
    return next_;
}

std::list<Statement*> const& lang::bb::def::Simple::statements() const
{
    return statements_;
}

void lang::bb::def::Simple::complete(size_t& index)
{
    for (auto& statement : statements_) { self()->addChild(*statement); }

    if (next_) next_->complete(index);
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

void lang::bb::def::Simple::simplify()
{
    if (!next_) { return; }

    // This block is the only block entering the next (real) block, or this block is unnecessary.
    bool const can_simplify = (next_->getIncomingLinkCount() == 1 && !next_->isMeta()) || statements_.empty();

    if (can_simplify)
    {
        next_->transferStatements(statements_);
        this->updateIncomingLinks(next_);

        self()->markAsUnused();
    }

    next_->simplify();
}

void lang::bb::def::Simple::transferStatements(std::list<Statement*>& statements)
{
    statements_.splice(statements_.begin(), statements);
}

std::list<lang::BasicBlock const*> lang::bb::def::Simple::getLeaves() const
{
    std::list<lang::BasicBlock const*> leaves;

    if (next_) { leaves.splice(leaves.end(), next_->getLeaves()); }
    else { leaves.push_back(self()); }

    return leaves;
}

std::vector<lang::BasicBlock const*> lang::bb::def::Simple::getSuccessors() const
{
    std::vector<lang::BasicBlock const*> successors;

    if (next_) { successors.push_back(next_); }

    return successors;
}

lang::Location lang::bb::def::Simple::getStartLocation() const
{
    if (statements_.empty()) { return lang::Location::global(); }

    return statements_.front()->location();
}

lang::Location lang::bb::def::Simple::getEndLocation() const
{
    if (statements_.empty()) { return lang::Location::global(); }

    return statements_.back()->location();
}

void lang::bb::def::Simple::reach() const
{
    if (next_) { next_->reach(); }
}

std::string lang::bb::def::Simple::getExitRepresentation() const
{
    return "// ---";
}
