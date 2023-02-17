#include "Description.h"

void lang::Description::setScope(lang::Scope& scope)
{
    assert(scope_ == nullptr);
    scope_ = &scope;
}

void lang::Description::initialize(lang::Scope& scope)
{
    setScope(scope);
    performInitialization();
}

lang::Scope& lang::Description::scope()
{
    assert(scope_ != nullptr);
    return *scope_;
}

lang::Scope const& lang::Description::scope() const
{
    assert(scope_ != nullptr);
    return *scope_;
}
