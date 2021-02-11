#ifndef ANCE_SCOPE_H
#define ANCE_SCOPE_H

#include <map>
#include <string>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/DIBuilder.h>

#include "GlobalVariable.h"
#include "Type.h"

enum class access_modifier;
class Statement;
class CompileState;

namespace ance
{
	class Constant;
	class Function;
	class Value;

	class Scope
	{
	public:
		bool Validate();

		bool is_type_registered(std::string type_name);
		ance::Type* get_type(std::string type_name);
		void register_type(ance::Type* type);

		void DeclareConstant(access_modifier access, std::string identifier, ance::Type* type, ance::Constant* constant);
		void DeclareGlobalVariable(access_modifier access, std::string identifier, ance::Type* type, ance::Constant* value);
		ance::Type* GetVariableOrConstantType(std::string identifier);
		void BuildConstantsAndVariables(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);

		llvm::Value* GetConstant(std::string identifier, llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);
		llvm::Value* GetVariable(std::string identifier, llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);
		llvm::Value* GetConstantOrVariable(std::string identifier, llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);
		void set_variable(std::string identifier, llvm::Value* value, llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);

		size_t FunctionCount() const;
		void AddFunctionName(std::string name);
		void AddAndEnterFunction(ance::Function* function);

		void PushStatementToCurrentFunction(Statement* statement);

		void BuildFunctionNames(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);
		void BuildFunctions(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);

		bool HasFunction(std::string identifier);
		ance::Function* GetFunction(std::string identifier);
		ance::Function* get_current_function() const;

	private:
		std::map<std::string, ance::Type*> types_;

		std::map<std::string, ance::GlobalVariable*> global_constants;
		std::map<std::string, ance::GlobalVariable*> global_variables;
		std::map<std::string, llvm::Value*> llvm_global_constants;
		std::map<std::string, llvm::Value*> llvm_global_variables;

		std::map<std::string, ance::Function*> functions;
		ance::Function* current;
	};
}
#endif