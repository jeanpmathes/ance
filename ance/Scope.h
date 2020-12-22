#ifndef ANCE_SCOPE_H
#define ANCE_SCOPE_H

#include <map>
#include <string>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DIBuilder.h"

#include "Statement.h"
#include "Function.h"
#include "CompileState.h"
#include "Value.h"

class Statement;
class CompileState;

namespace ance
{
	class Function;
	class Value;

	class Scope
	{
	public:
		bool Validate();

		void DeclareConstant(std::string identifier, ance::Value* value);

		void BuildVariables(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);
		llvm::Value* GetVariable(std::string identifier);

		size_t FunctionCount() const;
		void AddFunctionName(std::string name);
		void AddAndEnterFunction(ance::Function* function);

		void PushStatementToCurrentFunction(Statement* statement);

		void BuildFunctionNames(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);
		void BuildFunctions(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);

		bool HasFunction(std::string identifier);
		ance::Function* GetFunction(std::string identifier);

	private:
		std::map<std::string, ance::Value*> variables;
		std::map<std::string, llvm::Value*> llvm_variables;

		std::map<std::string, ance::Function*> functions;
		ance::Function* current;
	};
}
#endif