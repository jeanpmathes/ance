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
	protected:
		Variable(ance::Scope* containing_scope, std::string identifier, ance::Type* type, bool is_constant);
		explicit Variable(std::string identifier);

		void define(ance::Scope* containing_scope, ance::Type* type, bool is_constant);
		bool is_defined();

	public:
		std::string identifier() const;
		ance::Type* type() const;
		bool is_constant() const;

		virtual llvm::Value* get_value(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) = 0;
		virtual void set_value(llvm::Value* value, llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) = 0;

	private:
		std::string identifier_;
		bool is_defined_;

		ance::Scope* scope_;
		ance::Type* type_;
		bool is_constant_;
	};
}
#endif