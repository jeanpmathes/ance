#ifndef ANCE_SCOPE_H
#define ANCE_SCOPE_H

#include <map>
#include <string>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DIBuilder.h"

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

		void DeclareConstant(std::string identifier, ance::Constant* constant);

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
		std::map<std::string, ance::Constant*> constants;
		std::map<std::string, llvm::Value*> llvm_variables;

		std::map<std::string, ance::Function*> functions;
		ance::Function* current;
	};
}
#endif