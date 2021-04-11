#include "GlobalScope.h"

#include <iostream>
#include <ostream>

#include "Function.h"
#include "AccessModifier.h"

ance::GlobalScope* ance::GlobalScope::get_global_scope()
{
	return this;
}

bool ance::GlobalScope::validate()
{
	auto valid = true;

	for (auto const& [key, val] : functions)
	{
		if (val == nullptr)
		{
			std::cout << "A function is used but not defined: " << key << std::endl;

			valid = false;
		}
	}

	if (!global_undefined.empty())
	{
		std::cout << "Undefined global variables." << std::endl;

		valid = false;
	}

	return valid;
}

bool ance::GlobalScope::is_type_registered(std::string type_name)
{
	return types_.find(type_name) != types_.end();
}

ance::Type* ance::GlobalScope::get_type(std::string type_name)
{
	return types_.at(type_name);
}

void ance::GlobalScope::register_type(ance::Type* type)
{
	types_[type->get_name()] = type;
}

void ance::GlobalScope::define_global_constant(access_modifier access, std::string identifier, ance::Type* type, ance::Constant* constant)
{
	assert(global_variables.find(identifier) == global_variables.end());
	assert(global_constants.find(identifier) == global_constants.end());

	if (global_undefined.find(identifier) != global_undefined.end())
	{
		GlobalVariable* undefined = global_undefined[identifier];

		undefined->define_global(this, access, type, constant, true);
		global_constants[identifier] = undefined;

		global_undefined.erase(identifier);
	}
	else
	{
		global_constants[identifier] = new ance::GlobalVariable(this, access, identifier, type, constant, true);
	}
}

void ance::GlobalScope::define_global_variable(access_modifier access, std::string identifier, ance::Type* type, ance::Constant* value)
{
	assert(global_variables.find(identifier) == global_variables.end());
	assert(global_constants.find(identifier) == global_constants.end());

	if (global_undefined.find(identifier) != global_undefined.end())
	{
		GlobalVariable* undefined = global_undefined[identifier];

		undefined->define_global(this, access, type, value, false);
		global_variables[identifier] = undefined;

		global_undefined.erase(identifier);
	}
	else
	{
		global_variables[identifier] = new ance::GlobalVariable(this, access, identifier, type, value, false);
	}
}

ance::Variable* ance::GlobalScope::get_variable(std::string identifier)
{
	if (global_variables.find(identifier) != global_variables.end())
	{
		return global_variables[identifier];
	}

	if (global_constants.find(identifier) != global_constants.end())
	{
		return global_constants[identifier];
	}

	if (global_undefined.find(identifier) != global_undefined.end())
	{
		return global_undefined[identifier];
	}

	// Create an undefined global variable.
	auto* undefined = new GlobalVariable(identifier);
	global_undefined[identifier] = undefined;
	return undefined;
}

void ance::GlobalScope::build_variables(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	for (auto const& [identifier, constant] : global_constants)
	{
		if (!constant) continue;
		constant->build_global(c, m);
	}

	for (auto const& [identifier, variable] : global_variables)
	{
		if (!variable) continue;
		variable->build_global(c, m);
	}
}

size_t ance::GlobalScope::FunctionCount() const
{
	return functions.size();
}

void ance::GlobalScope::AddFunctionName(std::string name)
{
	if (functions.find(name) == functions.end()) functions[name] = nullptr;
}

void ance::GlobalScope::AddAndEnterFunction(ance::Function* function)
{
	functions[function->get_name()] = function;
	current = function;
}

void ance::GlobalScope::PushStatementToCurrentFunction(Statement* statement)
{
	current->push_statement(statement);
}

void ance::GlobalScope::BuildFunctionNames(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	for (auto const& [key, val] : functions)
	{
		val->build_name(c, m, state, ir, di);
	}
}

void ance::GlobalScope::BuildFunctions(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	for (auto const& [key, val] : functions)
	{
		val->build(c, m, state, ir, di);
	}
}

bool ance::GlobalScope::HasFunction(std::string identifier)
{
	if (functions.find(identifier) != functions.end())
		return true;
	return false;
}

ance::Function* ance::GlobalScope::GetFunction(std::string identifier)
{
	return functions.at(identifier);
}

ance::Function* ance::GlobalScope::get_current_function() const
{
	return current;
}