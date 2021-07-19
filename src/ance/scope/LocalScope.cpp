#include "LocalScope.h"

#include "ance/construct/constant/Constant.h"
#include "ance/scope/GlobalScope.h"
#include "ance/construct/value//WrappedNativeValue.h"
#include "ance/expression/Expression.h"

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
    Assigner           assigner,
    Expression*        expression)
{
    return defineLocalVariable(identifier, type, assigner, expression->getValue());
}

ance::LocalVariable* ance::LocalScope::defineLocalVariable(
    const std::string& identifier,
    ance::Type*        type,
    Assigner           assigner,
    ance::Value*       value)
{
    assert(local_variables_.find(identifier) == local_variables_.end());

    bool is_final = IsFinal(assigner);

    auto* variable               = new LocalVariable(this, identifier, type, value, is_final);
    local_variables_[identifier] = variable;

    return variable;
}

ance::Variable* ance::LocalScope::getVariable(std::string identifier)
{
    if (local_variables_.find(identifier) != local_variables_.end())
    {
        return local_variables_[identifier];
    }

    return getGlobalScope()->getVariable(identifier);
}