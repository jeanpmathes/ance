#include "GlobalScope.h"

#include <iostream>
#include <ostream>

#include "Function.h"
#include "AccessModifier.h"

ance::GlobalScope* ance::GlobalScope::getGlobalScope()
{
	return this;
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

void ance::GlobalScope::defineGlobalConstant(AccessModifier access, const std::string& identifier, ance::Type* type, ance::Constant* constant)
{
	assert(global_variables_.find(identifier) == global_variables_.end());
	assert(global_constants_.find(identifier) == global_constants_.end());

	if (global_undefined_.find(identifier) != global_undefined_.end())
	{
		GlobalVariable* undefined = global_undefined_[identifier];

        undefined->defineGlobal(this, access, type, constant, true);
        global_constants_[identifier] = undefined;

		global_undefined_.erase(identifier);
	}
	else
	{
        global_constants_[identifier] = new ance::GlobalVariable(this, access, identifier, type, constant, true);
	}
}

void ance::GlobalScope::defineGlobalVariable(AccessModifier access, const std::string& identifier, ance::Type* type, ance::Constant* value)
{
	assert(global_variables_.find(identifier) == global_variables_.end());
	assert(global_constants_.find(identifier) == global_constants_.end());

	if (global_undefined_.find(identifier) != global_undefined_.end())
	{
		GlobalVariable* undefined = global_undefined_[identifier];

        undefined->defineGlobal(this, access, type, value, false);
        global_variables_[identifier] = undefined;

		global_undefined_.erase(identifier);
	}
	else
	{
        global_variables_[identifier] = new ance::GlobalVariable(this, access, identifier, type, value, false);
	}
}

ance::Variable* ance::GlobalScope::getVariable(std::string identifier)
{
	if (global_variables_.find(identifier) != global_variables_.end())
	{
		return global_variables_[identifier];
	}

	if (global_constants_.find(identifier) != global_constants_.end())
	{
		return global_constants_[identifier];
	}

	if (global_undefined_.find(identifier) != global_undefined_.end())
	{
		return global_undefined_[identifier];
	}

	// Create an undefined global variable.
	auto* undefined = new GlobalVariable(identifier);
    global_undefined_[identifier] = undefined;
	return undefined;
}

void ance::GlobalScope::buildVariables(llvm::LLVMContext& c, llvm::Module* m, CompileState*, llvm::IRBuilder<>&, llvm::DIBuilder*)
{
	for (auto const& [identifier, constant] : global_constants_)
	{
		if (!constant) continue;
        constant->buildGlobal(c, m);
	}

	for (auto const& [identifier, variable] : global_variables_)
	{
		if (!variable) continue;
        variable->buildGlobal(c, m);
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

void ance::GlobalScope::addAndEnterFunction(ance::Function* function)
{
    functions_[function->getName()] = function;
    current_ = function;
}

void ance::GlobalScope::pushStatementToCurrentFunction(Statement* statement)
{
    current_->pushStatement(statement);
}

void ance::GlobalScope::buildFunctionNames(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	for (auto const& [key, val] : functions_)
	{
        val->buildName(c, m, state, ir, di);
	}
}

void ance::GlobalScope::buildFunctions(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	for (auto const& [key, val] : functions_)
	{
		val->build(c, m, state, ir, di);
	}
}

bool ance::GlobalScope::hasFunction(const std::string& identifier)
{
	if (functions_.find(identifier) != functions_.end())
		return true;
	return false;
}

ance::Function* ance::GlobalScope::getFunction(const std::string& identifier)
{
	return functions_.at(identifier);
}

ance::Function* ance::GlobalScope::getCurrentFunction() const
{
	return current_;
}