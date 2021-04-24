#ifndef ANCE_SRC_ANCE_CONSTRUCT_WRAPPEDNATIVECONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_WRAPPEDNATIVECONSTANT_H_

#include "Constant.h"

namespace ance
{
class WrappedNativeConstant : public Constant
{
	public:
		WrappedNativeConstant(ance::Type* type, llvm::Constant* constant = nullptr);

		void setConstant(llvm::Constant* constant);

		ance::Type* getType() override;

		llvm::Constant* getConstant(llvm::LLVMContext& c) override;

	private:
		ance::Type* type_;
		llvm::Constant* constant_;
};
}

#endif
