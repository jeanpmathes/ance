#ifndef ANCE_SRC_ANCE_TYPE_INTEGERTYPE_H_
#define ANCE_SRC_ANCE_TYPE_INTEGERTYPE_H_

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
		llvm::Constant* getDefault(llvm::LLVMContext& c) override;
		llvm::Type* getNativeType(llvm::LLVMContext& c) override;

	private:
		uint64_t bit_size_;
		bool is_signed_;
		llvm::Type* type_;

	public:
		static ance::Type* get(ance::Scope* scope, uint64_t bit_size, bool is_signed);
	};
}

#endif