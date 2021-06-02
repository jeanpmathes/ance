#ifndef ANCE_SRC_ANCE_CONSTRUCT_PARAMETER_H_
#define ANCE_SRC_ANCE_CONSTRUCT_PARAMETER_H_

#include <string>

#include "LocalVariable.h"
#include "Value.h"

namespace ance
{
class Type;

class Parameter : public ance::Value
{
	public:
		Parameter(ance::Type* type, std::string name);

		ance::Type* getType() override;

		std::string name();

		void wrap(llvm::Argument* argument);

		void build(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

		llvm::Value* getNativeValue() override;

		llvm::Value* getContentValue(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

	private:
		ance::Type* type_;
		std::string name_;

		llvm::Argument* argument_{nullptr};
};
}
#endif