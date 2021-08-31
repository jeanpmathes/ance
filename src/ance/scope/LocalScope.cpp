#include "LocalScope.h"

#include "ance/construct/constant/Constant.h"
#include "ance/expression/Expression.h"
#include "ance/scope/GlobalScope.h"

ance::LocalScope::LocalScope(ance::Scope* parent) : parent_(parent) {}

ance::GlobalScope* ance::LocalScope::getGlobalScope()
{
    return parent_->getGlobalScope();
}

llvm::DIScope* ance::LocalScope::getDebugScope(CompileContext* context)
{
    return parent_->getDebugScope(context);
}

void ance::LocalScope::validate(ValidationLogger& validation_logger)
{
    for (auto const& [key, val] : local_variables_) { val->validate(validation_logger); }
}

ance::Variable* ance::LocalScope::getVariable(std::string identifier)
{
    if (local_variables_.find(identifier) != local_variables_.end()) { return local_variables_[identifier]; }

    return getGlobalScope()->getVariable(identifier);
}

bool ance::LocalScope::isTypeRegistered(const std::string& type_name)
{
    return getGlobalScope()->isTypeRegistered(type_name);
}

ance::Type* ance::LocalScope::getType(const std::string& type_name)
{
    return getGlobalScope()->getType(type_name);
}

void ance::LocalScope::registerType(ance::Type* type)
{
    getGlobalScope()->registerType(type);
}

ance::LocalVariable* ance::LocalScope::defineAutoVariable(const std::string& identifier,
                                                          ance::Type*        type,
                                                          Assigner           assigner,
                                                          ance::Value*       value,
                                                          ance::Location     location)
{
    return defineLocalVariable(identifier, type, assigner, value, 0, location);
}

ance::LocalVariable* ance::LocalScope::defineParameterVariable(const std::string& identifier,
                                                               ance::Type*        type,
                                                               Assigner           assigner,
                                                               ance::Value*       value,
                                                               unsigned           parameter_no,
                                                               ance::Location     location)
{
    return defineLocalVariable(identifier, type, assigner, value, parameter_no, location);
}

ance::LocalVariable* ance::LocalScope::defineLocalVariable(const std::string& identifier,
                                                           ance::Type*        type,
                                                           Assigner           assigner,
                                                           ance::Value*       value,
                                                           unsigned           parameter_no,
                                                           ance::Location     location)
{
    assert(local_variables_.find(identifier) == local_variables_.end());

    bool is_final = assigner.isFinal();

    auto* variable               = new LocalVariable(this, identifier, type, value, is_final, parameter_no, location);
    local_variables_[identifier] = variable;

    return variable;
}
