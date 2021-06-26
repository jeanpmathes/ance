#ifndef ANCE_SRC_ANCE_CONSTRUCT_EXTERNFUNCTION_H_
#define ANCE_SRC_ANCE_CONSTRUCT_EXTERNFUNCTION_H_

#include "Function.h"

namespace ance
{
class ExternFunction : public ance::Function
{
	public:
		ExternFunction(
			std::string function_name,
			ance::Type* return_type,
			std::vector<ance::Parameter*> parameters,
			unsigned int line,
			unsigned int column
		);

		void buildName(llvm::LLVMContext &c, llvm::Module *m, CompileState *state, llvm::IRBuilder<> &ir, llvm::DIBuilder *di) override;

		void build(llvm::LLVMContext &c, llvm::Module *m, CompileState *state, llvm::IRBuilder<> &ir, llvm::DIBuilder *di) override;

		ance::Value * buildCall(const std::vector<ance::Value *> &arguments, llvm::LLVMContext &c, llvm::Module *m, CompileState *state, llvm::IRBuilder<> &ir, llvm::DIBuilder *di) const override;

	protected:
		using Function::buildCall;

	private:
		std::vector<ance::Parameter*> parameters_;

		llvm::FunctionType* native_type_{nullptr};
		llvm::Function* native_function_{nullptr};
};
}

#endif
