#ifndef ANCE_SRC_ANCE_CONSTRUCT_WRAPPEDNATIVECONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_WRAPPEDNATIVECONSTANT_H_

#include "Constant.h"

namespace ance
{
class WrappedNativeConstant : public Constant
{
	public:
		WrappedNativeConstant(ance::Type* type, llvm::Constant* constant = nullptr);

		void setNativeConstant(llvm::Constant* constant);

		ance::Type* getType() override;

		void build(llvm::LLVMContext& c) override;

		llvm::Constant * getNativeConstant() override;

	private:
		ance::Type* type_;
		llvm::Constant* constant_;
};
}

#endif
