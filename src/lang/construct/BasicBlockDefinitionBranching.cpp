#include "BasicBlock.h"

#include <set>

#include "lang/ApplicationVisitor.h"
#include "lang/construct/Value.h"
#include "lang/expression/Expression.h"
#include "lang/type/BooleanType.h"

lang::bb::def::Branching::Branching(Expression& condition) : condition_(condition) {}

std::list<Statement*> const& lang::bb::def::Branching::statements() const
{
    return statements_;
}

Expression const& lang::bb::def::Branching::condition() const
{
    return condition_;
}

lang::BasicBlock const* lang::bb::def::Branching::trueNext() const
{
    return true_next_;
}

lang::BasicBlock const* lang::bb::def::Branching::falseNext() const
{
    return false_next_;
}

void lang::bb::def::Branching::complete(size_t& index)
{
    for (auto& statement : statements_) { self()->addChild(*statement); }

    true_next_->complete(index);
    false_next_->complete(index);
}

void lang::bb::def::Branching::setLink(lang::BasicBlock& next)
{
    lang::BasicBlock* next_ptr = &next;

    assert(!true_next_ || !false_next_);

    if (!true_next_)
    {
        true_next_ = next_ptr;
        next.registerIncomingLink(*self());

        return;
    }

    if (!false_next_)
    {
        false_next_ = next_ptr;
        next.registerIncomingLink(*self());

        return;
    }

    assert(false);
}

void lang::bb::def::Branching::updateLink(lang::BasicBlock* former, lang::BasicBlock* updated)
{
    auto update = [&](lang::BasicBlock*& target) {
        assert(target != updated);

        target = updated;
        updated->registerIncomingLink(*self());
    };

    if (true_next_ == former) { update(true_next_); }
    if (false_next_ == former) { update(false_next_); }
}

void lang::bb::def::Branching::simplify()
{
    true_next_->simplify();
    false_next_->simplify();
}

void lang::bb::def::Branching::transferStatements(std::list<Statement*>& statements)
{
    statements_.splice(statements_.begin(), statements);
}

std::list<lang::BasicBlock const*> lang::bb::def::Branching::getLeaves() const
{
    std::set<lang::BasicBlock const*> leaves;

    for (auto leaf : true_next_->getLeaves()) { leaves.insert(leaf); }

    for (auto leaf : false_next_->getLeaves()) { leaves.insert(leaf); }

    return {leaves.begin(), leaves.end()};
}

std::vector<lang::BasicBlock const*> lang::bb::def::Branching::getSuccessors() const
{
    return {true_next_, false_next_};
}

lang::Location lang::bb::def::Branching::getStartLocation() const
{
    if (statements_.empty()) { return lang::Location::global(); }

    return statements_.front()->location();
}

lang::Location lang::bb::def::Branching::getEndLocation() const
{
    if (statements_.empty()) { return lang::Location::global(); }

    return statements_.back()->location();
}

void lang::bb::def::Branching::reach() const
{
    true_next_->reach();
    false_next_->reach();
}

std::string lang::bb::def::Branching::getExitRepresentation() const
{
    return "// branch";
}
