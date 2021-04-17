#ifndef ANCE_SRC_ANCE_CONSTRUCT_VARIABLE_H_
#define ANCE_SRC_ANCE_CONSTRUCT_VARIABLE_H_
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
		bool isDefined();

	public:
		[[nodiscard]] std::string identifier() const;
		[[nodiscard]] ance::Type* type() const;
		[[nodiscard]] bool isConstant() const;

		virtual llvm::Value* getValue(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) = 0;
		virtual void setValue(llvm::Value* value, llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) = 0;

	private:
		std::string identifier_;
		bool is_defined_;

		ance::Scope* scope_;
		ance::Type* type_;
		bool is_constant_;
	};
}
#endif