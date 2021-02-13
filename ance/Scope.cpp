#include "Scope.h"

#include <iostream>

#include "llvm/IR/Constant.h"

#include "Function.h"
#include "Constant.h"

bool ance::Scope::Validate()
{
	bool valid = true;

	for (auto const& [key, val] : functions)
	{
		if (val == nullptr)
		{
			std::cout << "A function is used but not defined: " << key << std::endl;

			valid = false;
		}
	}

	return valid;
}

bool ance::Scope::is_type_registered(std::string type_name)
{
	return types_.find(type_name) != types_.end();
}

ance::Type* ance::Scope::get_type(std::string type_name)
{
	return types_.at(type_name);
}

void ance::Scope::register_type(ance::Type* type)
{
	types_[type->get_name()] = type;
}

void ance::Scope::DeclareConstant(access_modifier access, std::string identifier, ance::Type* type, ance::Constant* constant)
{
	assert(global_variables.find(identifier) == global_variables.end());
	assert(global_constants.find(identifier) == global_constants.end());

	global_constants[identifier] = new ance::GlobalVariable(this, access, identifier, type, constant, true);
}

void ance::Scope::DeclareGlobalVariable(access_modifier access, std::string identifier, ance::Type* type, ance::Constant* value)
{
	assert(global_variables.find(identifier) == global_variables.end());
	assert(global_constants.find(identifier) == global_constants.end());

	global_variables[identifier] = new ance::GlobalVariable(this, access, identifier, type, value, false);
}

ance::Variable* ance::Scope::get_variable(std::string identifier)
{
	if (global_variables.find(identifier) != global_variables.end())
	{
		return global_variables[identifier];
	}

	if (global_constants.find(identifier) != global_constants.end())
	{
		return global_constants[identifier];
	}

	return nullptr;
}

void ance::Scope::BuildConstantsAndVariables(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
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

size_t ance::Scope::FunctionCount() const
{
	return functions.size();
}

void ance::Scope::AddFunctionName(std::string name)
{
	if (functions.find(name) == functions.end()) functions[name] = nullptr;
}

void ance::Scope::AddAndEnterFunction(ance::Function* function)
{
	functions[function->GetName()] = function;
	current = function;
}

void ance::Scope::PushStatementToCurrentFunction(Statement* statement)
{
	current->push_statement(statement);
}

void ance::Scope::BuildFunctionNames(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	for (auto const& [key, val] : functions)
	{
		val->BuildName(c, m, state, ir, di);
	}
}

void ance::Scope::BuildFunctions(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	for (auto const& [key, val] : functions)
	{
		val->Build(c, m, state, ir, di);
	}
}

bool ance::Scope::HasFunction(std::string identifier)
{
	if (functions.find(identifier) != functions.end())
		return true;
	return false;
}

ance::Function* ance::Scope::GetFunction(std::string identifier)
{
	return functions.at(identifier);
}

ance::Function* ance::Scope::get_current_function() const
{
	return current;
}