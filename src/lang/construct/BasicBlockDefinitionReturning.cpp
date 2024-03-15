#include <utility>

#include "BasicBlock.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "lang/type/Type.h"
#include "validation/ValidationLogger.h"

lang::bb::def::Returning::Returning(lang::Scope& scope, Expression& return_value)
    : return_value_(return_value)
    , scope_(scope)
{}

std::list<Statement*> const& lang::bb::def::Returning::statements() const
{
    return statements_;
}

lang::Scope const& lang::bb::def::Returning::scope() const
{
    return scope_;
}

Expression const& lang::bb::def::Returning::ret() const
{
    return return_value_;
}

void lang::bb::def::Returning::complete(size_t& index)
{
    for (auto& statement : statements_) { self()->addStatement(*statement); }

    if (unreachable_next_) unreachable_next_->complete(index);
}

void lang::bb::def::Returning::setLink(lang::BasicBlock& next)
{
    lang::BasicBlock* next_ptr = &next;

    assert(&next_ptr->definition() != this);
    assert(unreachable_next_ == nullptr);

    unreachable_next_ = next_ptr;
    unreachable_next_->registerIncomingLink(*self());
}

void lang::bb::def::Returning::updateLink(lang::BasicBlock* former, lang::BasicBlock* updated)
{
    assert(unreachable_next_ == former);
    assert(unreachable_next_ != updated);

    unreachable_next_ = updated;
    unreachable_next_->registerIncomingLink(*self());
}

void lang::bb::def::Returning::simplify()
{
    if (unreachable_next_) unreachable_next_->simplify();
}

void lang::bb::def::Returning::transferStatements(std::list<Statement*>& statements)
{
    statements_.splice(statements_.begin(), statements);
}

std::list<lang::BasicBlock const*> lang::bb::def::Returning::getLeaves() const
{
    std::list<lang::BasicBlock const*> leaves;

    leaves.push_back(self());

    return leaves;
}

std::vector<lang::BasicBlock const*> lang::bb::def::Returning::getSuccessors() const
{
    return {};
}

Optional<std::pair<std::reference_wrapper<lang::Type const>, lang::Location>> lang::bb::def::Returning::getReturnType()
    const
{
    std::reference_wrapper<lang::Type const> const return_type = return_value_.type();
    lang::Location const location = return_value_.location();

    std::pair<std::reference_wrapper<lang::Type const>, lang::Location> const pair =
        std::make_pair(return_type, location);

    return pair;
}

lang::Location lang::bb::def::Returning::getStartLocation() const
{
    if (statements_.empty()) { return lang::Location::global(); }

    return statements_.front()->location();
}

lang::Location lang::bb::def::Returning::getEndLocation() const
{
    if (statements_.empty()) { return lang::Location::global(); }

    return statements_.back()->location();
}

void lang::bb::def::Returning::reach() const {}

std::string lang::bb::def::Returning::getExitRepresentation() const
{
    return "// return";
}
