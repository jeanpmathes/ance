#include "LocalScope.h"
#include "Constant.h"
#include "GlobalScope.h"
#include "WrappedNativeValue.h"

ance::LocalScope::LocalScope(ance::Scope* parent)
    : parent_(parent)
{
}

ance::GlobalScope* ance::LocalScope::getGlobalScope()
{
    return parent_->getGlobalScope();
}

bool ance::LocalScope::validate()
{
    return true;
}

ance::LocalVariable* ance::LocalScope::defineLocalVariable(
    const std::string& identifier,
    ance::Type*        type,
    Expression*        expression)
{
    assert(local_variables.find(identifier) == local_variables.end());

    auto* variable              = new LocalVariable(this, identifier, type, expression->getValue());
    local_variables[identifier] = variable;

    return variable;
}

ance::LocalVariable* ance::LocalScope::defineLocalVariable(
    const std::string& identifier,
    ance::Type*        type,
    ance::Value*       value)
{
    assert(local_variables.find(identifier) == local_variables.end());

    auto* variable              = new LocalVariable(this, identifier, type, value);
    local_variables[identifier] = variable;

    return variable;
}

ance::Variable* ance::LocalScope::getVariable(std::string identifier)
{
    if (local_variables.find(identifier) != local_variables.end())
    {
        return local_variables[identifier];
    }

    return getGlobalScope()->getVariable(identifier);
}