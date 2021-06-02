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

		llvm::Constant* buildContent(llvm::LLVMContext& c) override;

	private:
		ance::Type* type_;
		llvm::APFloat float_;
};
}

#endif
