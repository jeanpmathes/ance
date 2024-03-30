#include "BasicBlock.h"

#include <set>

#include "lang/ApplicationVisitor.h"
#include "lang/construct/Value.h"
#include "lang/expression/Expression.h"
#include "lang/type/BooleanType.h"

lang::bb::def::Branching::Branching(Expression& condition) : condition_(condition) {}

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

std::vector<lang::BasicBlock const*> lang::bb::def::Branching::getSuccessors() const
{
    return {true_next_, false_next_};
}

std::vector<lang::BasicBlock*> lang::bb::def::Branching::getReachableNext()
{
    return {true_next_, false_next_};
}

std::string lang::bb::def::Branching::getExitRepresentation() const
{
    return "// branch";
}
