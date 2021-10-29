#include "GlobalScope.h"

#include <ostream>

#include "ance/expression/ConstantExpression.h"
#include "ance/type/IntegerType.h"
#include "ance/type/VoidType.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

ance::Scope* ance::GlobalScope::scope()
{
    return this;
}

ance::GlobalScope* ance::GlobalScope::getGlobalScope()
{
    return this;
}

llvm::DIScope* ance::GlobalScope::getDebugScope(CompileContext* context)
{
    return context->unit();
}

void ance::GlobalScope::validate(ValidationLogger& validation_logger)
{
    for (auto [message, location] : errors_) { validation_logger.logError(message, location); }

    for (auto const& [key, fn] : functions_)
    {
        if (fn) { fn->validate(validation_logger); }
    }

    for (auto const& [key, val] : global_constants_) { val->validate(validation_logger); }

    for (auto const& [key, val] : global_variables_) { val->validate(validation_logger); }
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
    assert(assigner != Assigner::REFERENCE_BINDING);

    if (global_variables_.find(identifier) != global_variables_.end()
        || global_constants_.find(identifier) != global_constants_.end())
    {
        errors_.emplace_back("Name '" + identifier + "' already defined in the current context", location);
        return;
    }

    if (!initializer)
    {
        errors_.emplace_back("Constants require an explicit initializer", location);
        return;
    }

    bool is_final = assigner.isFinal();

    if (is_constant && !is_final)
    {
        errors_.emplace_back("Assignment to constants must be final", location);
        return;
    }

    std::unique_ptr<ance::Variable> undefined;

    if (global_undefined_.find(identifier) != global_undefined_.end())
    {
        undefined = std::move(global_undefined_[identifier]);
        global_undefined_.erase(identifier);
    }
    else
    {
        undefined = std::make_unique<ance::Variable>(identifier);
    }

    undefined->defineAsGlobal(type, this, access, initializer, is_final, is_constant, location);
    std::unique_ptr<ance::Variable> defined = std::move(undefined);

    if (is_constant) { global_constants_[identifier] = std::move(defined); }
    else
    {
        global_variables_[identifier] = std::move(defined);
    }
}

ance::Variable* ance::GlobalScope::getVariable(std::string identifier)
{
    if (global_variables_.find(identifier) != global_variables_.end()) { return global_variables_[identifier].get(); }

    if (global_constants_.find(identifier) != global_constants_.end()) { return global_constants_[identifier].get(); }

    if (global_undefined_.find(identifier) != global_undefined_.end()) { return global_undefined_[identifier].get(); }

    // Create an undefined global variable.
    global_undefined_[identifier] = std::make_unique<ance::Variable>(identifier);
    return global_undefined_[identifier].get();
}

size_t ance::GlobalScope::functionCount() const
{
    return functions_.size();
}

void ance::GlobalScope::addFunctionName(const std::string& name)
{
    if (functions_.find(name) == functions_.end()) functions_[name] = nullptr;
}

void ance::GlobalScope::addFunction(std::unique_ptr<ance::Function> function)
{
    assert(!isFunctionDefined(function->name()));

    const std::string& name = function->name();

    functions_[name] = std::move(function);
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

bool ance::GlobalScope::hasEntry()
{
    auto c = functions_.find("main");
    if (c == functions_.end()) return false;

    ance::Function* function = c->second.get();

    return function->parameterCount() == 0 && ance::IntegerType::isIntegerType(function->returnType(), 32, false);
}

bool ance::GlobalScope::hasExit()
{
    auto c = functions_.find("exit");
    if (c == functions_.end()) return false;

    ance::Function* function = c->second.get();

    return function->parameterCount() == 1 && ance::IntegerType::isIntegerType(function->parameterType(0), 32, false)
        && function->returnType() == ance::VoidType::get();
}

ance::Function* ance::GlobalScope::getFunction(const std::string& identifier)
{
    return functions_.at(identifier).get();
}

void ance::GlobalScope::createNativeBacking(CompileContext* context)
{
    for (auto const& [key, val] : functions_) { val->createNativeBacking(context); }

    for (auto const& [identifier, constant] : global_constants_)
    {
        if (!constant) continue;

        constant->buildDeclaration(context);
        constant->buildDefinition(context);
    }

    for (auto const& [identifier, variable] : global_variables_)
    {
        if (!variable) continue;

        variable->buildDeclaration(context);
        variable->buildDefinition(context);
    }
}

void ance::GlobalScope::buildFunctions(CompileContext* context)
{
    for (auto const& [key, val] : functions_) { val->build(context); }
}
