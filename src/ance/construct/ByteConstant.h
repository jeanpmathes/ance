#ifndef ANCE_SRC_ANCE_CONSTRUCT_BYTECONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_BYTECONSTANT_H_

#include <string>

#include "Constant.h"
#include "Application.h"

namespace ance
{

class Type;

class ByteConstant : public Constant
{
	public:
		explicit ByteConstant(uint8_t byte, Application& app);

		ance::Type* getType() override;

		llvm::Constant* buildContent(llvm::LLVMContext& c) override;

		static char resolveEscaped(char content);

		static uint8_t parse(const std::string& unparsed);

	private:
		ance::Type* type_;
		uint8_t byte_;
};
}

#endif
