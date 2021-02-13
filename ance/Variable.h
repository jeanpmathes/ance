#ifndef ANCE_VARIABLE_H
#define ANCE_VARIABLE_H
#include <string>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>

class CompileState;

namespace llvm {
	class DIBuilder;
	class LLVMContext;
}

namespace ance
{
	class Scope;
	class Type;

	class Variable
	{
	public:
		Variable(ance::Scope* containing_scope, std::string identifier, ance::Type* type, bool is_constant);

		std::string identifier() const;
		ance::Type* type() const;
		bool is_constant() const;

		virtual llvm::Value* get_value(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) = 0;
		virtual void set_value(llvm::Value* value, llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) = 0;

	private:
		ance::Scope* scope_;
		std::string identifier_;
		ance::Type* type_;
		bool is_constant_;
	};
}
#endif