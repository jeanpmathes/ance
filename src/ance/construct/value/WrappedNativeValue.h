#ifndef ANCE_SRC_ANCE_CONSTRUCT_VALUE_WRAPPEDNATIVEVALUE_H_
#define ANCE_SRC_ANCE_CONSTRUCT_VALUE_WRAPPEDNATIVEVALUE_H_

#include "Value.h"

namespace ance
{
class WrappedNativeValue : public Value
{
	public:
		explicit WrappedNativeValue(ance::Type* type, llvm::Value* value = nullptr);

		void setValue(llvm::Value* value);

		ance::Type* getType() override;

		void buildNativeValue(CompileContext* context) override;

		llvm::Value* getNativeValue() override;

	private:
		ance::Type* type_;
		llvm::Value* value_;
};
}
#endif
