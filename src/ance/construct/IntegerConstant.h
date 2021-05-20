#ifndef ANCE_SRC_ANCE_CONSTRUCT_INTEGERCONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_INTEGERCONSTANT_H_

#include "Application.h"
#include "Constant.h"

namespace ance
{
class IntegerConstant : public Constant
{
	public:
		IntegerConstant(llvm::APInt integer, bool is_signed, Application& app);

		ance::Type* getType() override;

		void build(llvm::LLVMContext& c) override;

		llvm::Constant * getNativeConstant() override;

	private:
		ance::Type* type_;
		llvm::APInt integer_;
		llvm::Constant* constant_{nullptr};
};
}

#endif
