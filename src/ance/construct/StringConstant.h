#ifndef ANCE_SRC_ANCE_CONSTRUCT_STRINGCONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_STRINGCONSTANT_H_

#include "Application.h"
#include "Constant.h"

namespace ance
{
class StringConstant : public Constant
{
	public:
		StringConstant(std::string string, Application& app);

		ance::Type* getType() override;

		llvm::Constant * buildStored(llvm::LLVMContext &c) override;

		static std::string parse(const std::string& unparsed);

	private:
		ance::Type* type_;
		std::string string_;
};
}

#endif
