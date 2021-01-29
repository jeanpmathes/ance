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

	global_constants[identifier] = new ance::GlobalVariable(access, identifier, type, constant, true);
}

void ance::Scope::DeclareGlobalVariable(access_modifier access, std::string identifier, ance::Type* type, ance::Constant* value)
{
	assert(global_variables.find(identifier) == global_variables.end());
	assert(global_constants.find(identifier) == global_constants.end());

	global_variables[identifier] = new ance::GlobalVariable(access, identifier, type, value, false);
}

ance::Type* ance::Scope::GetVariableOrConstantType(std::string identifier)
{
	if (global_variables.find(identifier) != global_variables.end())
	{
		return global_variables[identifier]->type();
	}

	if (global_constants.find(identifier) != global_constants.end())
	{
		return global_constants[identifier]->type();
	}

	return nullptr;
}

void ance::Scope::BuildConstantsAndVariables(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	for (auto const& [identifier, constant] : global_constants)
	{
		if (!constant) continue;
		llvm_global_constants[identifier] = constant->Build(c, m);
	}

	for (auto const& [identifier, variable] : global_variables)
	{
		if (!variable) continue;
		llvm_global_variables[identifier] = variable->Build(c, m);
	}
}

llvm::Value* ance::Scope::GetConstant(std::string identifier, llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	llvm::Value* const_ptr = llvm_global_constants.at(identifier);
	assert(const_ptr != nullptr);

	llvm::Type* const_type = static_cast<llvm::PointerType*>(const_ptr->getType())->getElementType();
	return ir.CreateLoad(const_type, const_ptr);
}

llvm::Value* ance::Scope::GetVariable(std::string identifier, llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	llvm::Value* value_ptr = llvm_global_constants.at(identifier);
	assert(value_ptr != nullptr);

	llvm::Type* value_type = static_cast<llvm::PointerType*>(value_ptr->getType())->getElementType();
	return ir.CreateLoad(value_type, value_ptr);
}

llvm::Value* ance::Scope::GetConstantOrVariable(std::string identifier, llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	llvm::Value* value_ptr = llvm_global_constants[identifier];
	if (value_ptr == nullptr) value_ptr = llvm_global_variables[identifier];
	assert(value_ptr != nullptr);

	llvm::Type* value_type = static_cast<llvm::PointerType*>(value_ptr->getType())->getElementType();
	return ir.CreateLoad(value_type, value_ptr);
}

void ance::Scope::set_variable(std::string identifier, llvm::Value* value, llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	llvm::Value* value_ptr = llvm_global_variables[identifier];
	assert(value_ptr != nullptr);

	ir.CreateStore(value, value_ptr);
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