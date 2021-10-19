#include "LocalScope.h"

#include <utility>

#include "ance/ApplicationVisitor.h"
#include "ance/construct/LocalVariable.h"
#include "ance/construct/constant/Constant.h"
#include "ance/scope/GlobalScope.h"
#include "ance/type/ReferenceType.h"

ance::LocalScope::LocalScope(ance::Scope* parent) : parent_(parent) {}

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

ance::Location ance::LocalScope::location() const
{
    return parent_->location();
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

ance::LocalVariable* ance::LocalScope::defineAutoVariable(const std::string&                  identifier,
                                                          ance::Type*                         type,
                                                          Assigner                            assigner,
                                                          const std::shared_ptr<ance::Value>& value,
                                                          ance::Location                      location)
{
    return defineLocalVariable(identifier, type, assigner, value, 0, location);
}

ance::LocalVariable* ance::LocalScope::defineParameterVariable(const std::string&                  identifier,
                                                               ance::Type*                         type,
                                                               Assigner                            assigner,
                                                               const std::shared_ptr<ance::Value>& value,
                                                               unsigned                            parameter_no,
                                                               ance::Location                      location)
{
    return defineLocalVariable(identifier, type, assigner, value, parameter_no, location);
}

ance::LocalVariable* ance::LocalScope::defineLocalVariable(const std::string&                  identifier,
                                                           ance::Type*                         type,
                                                           Assigner                            assigner,
                                                           const std::shared_ptr<ance::Value>& value,
                                                           unsigned                            parameter_no,
                                                           ance::Location                      location)
{
    if (local_variables_.find(identifier) == local_variables_.end())
    {

        bool is_final = assigner.isFinal();

        local_variables_[identifier] =
            std::make_unique<ance::LocalVariable>(this, identifier, type, value, is_final, parameter_no, location);
        addChild(*local_variables_[identifier]);

        return local_variables_[identifier].get();
    }
    else
    {
        return nullptr;
    }
}

bool ance::LocalScope::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitLocalScope(*this);
}
