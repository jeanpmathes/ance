#ifndef ANCE_FUNCTION_H
#define ANCE_FUNCTION_H

#include <list>
#include <string>

#include "Parameter.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DIBuilder.h"

#include "Statement.h"
#include "CompileState.h"
#include "Expression.h"

class Statement;
class CompileState;

namespace ance
{
	class LocalScope;
	class Type;
	class LocalScope;

	class Function
	{
	public:
		Function(access_modifier access, std::string fn_name, ance::Type* return_type, std::vector<ance::Parameter*> parameters, ance::Scope* scope, unsigned int l, unsigned int c);

		std::string get_name() const;
		ance::Type* get_return_type() const;
		ance::LocalScope* get_scope() const;

		void push_statement(Statement* statement);

		void build_name(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);
		void build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);
		llvm::CallInst* build_call(const std::vector<ance::Value*>& arguments, llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) const;

	private:
		access_modifier access_;
		std::string name_;
		std::vector<ance::Parameter*> parameters_;
		unsigned int line_, column_;
		ance::LocalScope* local_scope_;

		std::vector<ance::LocalVariable*> arguments_;
		std::list<Statement*> statements_;

		ance::Type* return_type_;
		llvm::FunctionType* native_type_;
		llvm::Function* native_function_;
	};
}

#endif