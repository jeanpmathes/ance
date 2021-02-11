#ifndef ANCE_FUNCTION_H
#define ANCE_FUNCTION_H

#include <list>
#include <string>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DIBuilder.h"

#include "Statement.h"
#include "CompileState.h"

class Statement;
class CompileState;

namespace ance
{
	class Type;
	class Scope;

	class Function
	{
	public:
		Function(std::string fn_name, ance::Type* return_type, ance::Scope* scope, unsigned int l, unsigned int c);

		std::string GetName() const;
		ance::Type* get_return_type() const;
		ance::Scope* get_scope() const;

		void push_statement(Statement* statement);

		void BuildName(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);
		void Build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);
		llvm::CallInst* BuildCall(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);

	private:
		std::string name;
		unsigned int line, column;
		ance::Scope* scope_;

		std::list<Statement*> statements;

		ance::Type* return_type;
		llvm::FunctionType* llvmType;
		llvm::Function* llvmFunction;
	};
}

#endif