#ifndef ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_STRINGCONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_STRINGCONSTANT_H_

#include "Application.h"
#include "Constant.h"

namespace ance
{
class StringConstant : public Constant
{
	public:
		StringConstant(std::string prefix, std::string string, Application& app);

		ance::Type* getType() override;

		llvm::Constant* buildContent(llvm::Module* m) override;

		static std::string parse(const std::string& unparsed);

	private:
		static ance::Type* resolveType(std::string& prefix, std::string& string, Application& app);

	private:
		ance::Type* type_;
		std::string prefix_;
		std::string string_;
};
}

#endif
