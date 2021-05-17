#ifndef ANCE_SRC_ANCE_CONSTRUCT_LOCALVARIABLE_H_
#define ANCE_SRC_ANCE_CONSTRUCT_LOCALVARIABLE_H_

#include "Variable.h"

namespace ance
{
class Value;

class LocalScope;

class LocalVariable : public ance::Variable
{
	public:
		LocalVariable(
			ance::LocalScope* containing_scope,
			std::string identifier,
			ance::Type* type,
			ance::Value* value
		);

		void build(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		);

		llvm::Value* getValue(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

		void setValue(
			llvm::Value* value,
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

	private:
		ance::Value* value_;
		llvm::Value* native_value_{nullptr};
};
}
#endif