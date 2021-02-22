#include "LocalScope.h"
#include "Constant.h"
#include "GlobalScope.h"

ance::LocalScope::LocalScope(ance::Scope* parent) : parent_(parent)
{
}

ance::GlobalScope* ance::LocalScope::get_global_scope()
{
	return parent_->get_global_scope();
}

bool ance::LocalScope::validate()
{
	return true;
}

void ance::LocalScope::define_local_variable(const std::string& identifier, ance::Type* type, ance::Value* value)
{
	assert(local_variables.find(identifier) == local_variables.end());
	local_variables[identifier] = nullptr; // todo
}

ance::Variable* ance::LocalScope::get_variable(const std::string identifier)
{
	if (local_variables.find(identifier) != local_variables.end())
	{
		return local_variables[identifier];
	}

	return get_global_scope()->get_variable(identifier);
}

void ance::LocalScope::build_variables(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
}