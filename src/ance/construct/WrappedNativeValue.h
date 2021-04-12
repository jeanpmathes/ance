#ifndef ANCE_VALUEWRAPPER_H
#define ANCE_VALUEWRAPPER_H
#include "Value.h"

namespace ance
{
	class WrappedNativeValue : public Value
	{
	public:
		WrappedNativeValue(ance::Type* type, llvm::Value* value = nullptr);

		void set_value(llvm::Value* value);

		ance::Type* get_type() override;
		llvm::Value* get_value(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) override;

	private:
		ance::Type* type_;
		llvm::Value* value_;
	};
}
#endif
