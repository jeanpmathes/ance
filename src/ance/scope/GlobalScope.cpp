#include "GlobalScope.h"

#include <iostream>
#include <ostream>

#include "ance/AccessModifier.h"
#include "ance/construct/Function.h"
#include "ance/expression/ConstantExpression.h"

ance::GlobalScope* ance::GlobalScope::getGlobalScope()
{
    return this;
}

llvm::DIScope* ance::GlobalScope::getDebugScope(CompileContext* context)
{
    return context->unit();
}

bool ance::GlobalScope::validate()
{
    auto valid = true;

    for (auto const& [key, val] : functions_)
    {
        if (val == nullptr)
        {
            std::cout << "A function is used but not defined: " << key << std::endl;

            valid = false;
        }
    }

    if (!global_undefined_.empty())
    {
        std::cout << "Undefined global variables." << std::endl;

        valid = false;
    }

    return valid;
}

bool ance::GlobalScope::isTypeRegistered(const std::string& type_name)
{
    return types_.find(type_name) != types_.end();
}

ance::Type* ance::GlobalScope::getType(const std::string& type_name)
{
    return types_.at(type_name);
}

void ance::GlobalScope::registerType(ance::Type* type)
{
    types_[type->getName()] = type;
}

void ance::GlobalScope::defineGlobalVariable(AccessModifier      access,
                                             bool                is_constant,
                                             const std::string&  identifier,
                                             ance::Type*         type,
                                             Assigner            assigner,
                                             ConstantExpression* initializer,
                                             ance::Location      location)
{
    assert(global_variables_.find(identifier) == global_variables_.end()
           && "A variable identifier may be used just once.");
    assert(global_constants_.find(identifier) == global_constants_.end()
           && "A constant identifier may be used just once.");

    assert(initializer && "Variables require an initial value, which has to be explicit for constants.");

    bool is_final = assigner.isFinal();

    assert((!is_constant || is_final) && "A constant must be final.");

    if (global_undefined_.find(identifier) != global_undefined_.end())
    {
        ance::GlobalVariable* undefined = global_undefined_[identifier];

        undefined->defineGlobal(this, access, type, initializer, is_final, is_constant, location);

        if (is_constant) { global_constants_[identifier] = undefined; }
        else
        {
            global_variables_[identifier] = undefined;
        }

        global_undefined_.erase(identifier);
    }
    else
    {
        auto* defined =
            new ance::GlobalVariable(this, access, identifier, type, initializer, is_final, is_constant, location);

        if (is_constant) { global_constants_[identifier] = defined; }
        else
        {
            global_variables_[identifier] = defined;
        }
    }
}

ance::Variable* ance::GlobalScope::getVariable(std::string identifier)
{
    if (global_variables_.find(identifier) != global_variables_.end()) { return global_variables_[identifier]; }

    if (global_constants_.find(identifier) != global_constants_.end()) { return global_constants_[identifier]; }

    if (global_undefined_.find(identifier) != global_undefined_.end()) { return global_undefined_[identifier]; }

    // Create an undefined global variable.
    auto* undefined               = new GlobalVariable(identifier);
    global_undefined_[identifier] = undefined;
    return undefined;
}

void ance::GlobalScope::buildVariables(CompileContext* context)
{
    for (auto const& [identifier, constant] : global_constants_)
    {
        if (!constant) continue;
        constant->buildGlobal(context);
    }

    for (auto const& [identifier, variable] : global_variables_)
    {
        if (!variable) continue;
        variable->buildGlobal(context);
    }
}

size_t ance::GlobalScope::functionCount() const
{
    return functions_.size();
}

void ance::GlobalScope::addFunctionName(const std::string& name)
{
    if (functions_.find(name) == functions_.end()) functions_[name] = nullptr;
}

void ance::GlobalScope::addFunction(ance::Function* function)
{
    assert(!isFunctionDefined(function->name()));
    functions_[function->name()] = function;
}

bool ance::GlobalScope::hasFunction(const std::string& identifier)
{
    if (functions_.find(identifier) != functions_.end()) return true;
    return false;
}

bool ance::GlobalScope::isFunctionDefined(const std::string& identifier)
{
    return hasFunction(identifier) && functions_[identifier] != nullptr;
}

ance::Function* ance::GlobalScope::getFunction(const std::string& identifier)
{
    return functions_.at(identifier);
}

void ance::GlobalScope::buildFunctionNames(CompileContext* context)
{
    for (auto const& [key, val] : functions_) { val->buildName(context); }
}

void ance::GlobalScope::buildFunctions(CompileContext* context)
{
    for (auto const& [key, val] : functions_) { val->build(context); }
}
