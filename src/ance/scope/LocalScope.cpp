#include "LocalScope.h"

#include <utility>

#include "ance/scope/GlobalScope.h"
#include "ance/type/ReferenceType.h"

ance::LocalScope::LocalScope(ance::Scope* parent) : parent_(parent) {}

ance::Scope* ance::LocalScope::scope()
{
    return parent_;
}

ance::GlobalScope* ance::LocalScope::getGlobalScope()
{
    return parent_->getGlobalScope();
}

llvm::DIScope* ance::LocalScope::getDebugScope(CompileContext* context)
{
    return parent_->getDebugScope(context);
}

ance::Scope* ance::LocalScope::scope() const
{
    return parent_;
}

void ance::LocalScope::validate(ValidationLogger& validation_logger)
{
    for (auto const& [key, val] : local_variables_) { val->validate(validation_logger); }
}

ance::Variable* ance::LocalScope::getVariable(std::string identifier)
{
    if (local_variables_.find(identifier) != local_variables_.end()) { return local_variables_[identifier].get(); }

    return getGlobalScope()->getVariable(identifier);
}

void ance::LocalScope::buildDeclarations(CompileContext* context)
{
    for (auto& [identifier, variable] : local_variables_) { variable->buildDeclaration(context); }
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

ance::Variable* ance::LocalScope::defineAutoVariable(const std::string&                  identifier,
                                                     ance::Type*                         type,
                                                     Assigner                            assigner,
                                                     const std::shared_ptr<ance::Value>& value,
                                                     ance::Location                      location)
{
    return defineLocalVariable(identifier, type, assigner, value, 0, location);
}

ance::Variable* ance::LocalScope::defineParameterVariable(const std::string&                  identifier,
                                                          ance::Type*                         type,
                                                          Assigner                            assigner,
                                                          const std::shared_ptr<ance::Value>& value,
                                                          unsigned                            parameter_no,
                                                          ance::Location                      location)
{
    return defineLocalVariable(identifier, type, assigner, value, parameter_no, location);
}

ance::Variable* ance::LocalScope::defineLocalVariable(const std::string&                  identifier,
                                                      ance::Type*                         type,
                                                      Assigner                            assigner,
                                                      const std::shared_ptr<ance::Value>& value,
                                                      unsigned                            parameter_no,
                                                      ance::Location                      location)
{
    if (local_variables_.find(identifier) == local_variables_.end())
    {

        bool is_final = assigner.isFinal();

        std::unique_ptr<ance::Variable> variable = std::make_unique<ance::Variable>(identifier);
        variable->defineAsLocal(type, this, is_final, value, parameter_no, location);

        local_variables_[identifier] = std::move(variable);
        return local_variables_[identifier].get();
    }
    else
    {
        return nullptr;
    }
}
