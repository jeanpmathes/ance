#ifndef ANCE_SRC_ANCE_CONSTRUCT_BOOLEANCONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_BOOLEANCONSTANT_H_

#include "Constant.h"

class Application;

namespace ance
{
class BooleanConstant : public Constant
{
	private:
		explicit BooleanConstant(bool boolean, Application& app);

	public:
		ance::Type* getType() override;

		llvm::Constant* getConstant(llvm::LLVMContext& c) override;

		static ance::BooleanConstant* createFalse(Application& app);

		static ance::BooleanConstant* createTrue(Application& app);

	private:
		ance::Type* type_;
		bool boolean_;
		llvm::Constant* constant_{nullptr};
};
}

#endif
