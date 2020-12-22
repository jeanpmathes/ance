#include "Scope.h"

#include <iostream>

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

void ance::Scope::DeclareConstant(std::string identifier, ance::Value* value)
{
	assert(variables[identifier] == nullptr);
	variables[identifier] = value;
}

void ance::Scope::BuildVariables(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	for (auto const& [identifier, variable] : variables)
	{
		llvm::Constant* init = static_cast<llvm::Constant*>(variable->get_value(c, m, state, ir, di));
		llvm_variables[identifier] = new llvm::GlobalVariable(*m, init->getType(), true, llvm::GlobalValue::LinkageTypes::PrivateLinkage, init, identifier);
	}
}

llvm::Value* ance::Scope::GetVariable(std::string identifier)
{
	return llvm_variables.at(identifier);
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