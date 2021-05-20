#ifndef ANCE_SRC_ANCE_CONSTRUCT_FLOATCONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_FLOATCONSTANT_H_

#include "Constant.h"
#include "FloatingPointType.h"

namespace ance
{
class FloatConstant : public Constant
{
	public:
		FloatConstant(llvm::APFloat number, ance::FloatingPointType* type);

		ance::Type* getType() override;

		void build(llvm::LLVMContext& c) override;

		llvm::Constant * getNativeConstant() override;

	private:
		ance::Type* type_;
		llvm::APFloat float_;
		llvm::Constant* constant_{nullptr};
};
}

#endif
