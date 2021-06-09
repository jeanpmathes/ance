#ifndef ANCE_SRC_ANCE_TYPE_INTEGERTYPE_H_
#define ANCE_SRC_ANCE_TYPE_INTEGERTYPE_H_

#include "Application.h"
#include "Type.h"

namespace ance
{
class Scope;

class IntegerType : public Type
{
	private:
		IntegerType(uint64_t bit_size, bool is_signed);

	public:
		std::string getName() override;

		llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;

		llvm::Type* getContentType(llvm::LLVMContext& c) override;

	private:
		uint64_t bit_size_;
		bool is_signed_;
		llvm::Type* type_{nullptr};

	public:
		static ance::Type* get(Application& app, uint64_t bit_size, bool is_signed);
};
}

#endif