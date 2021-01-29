#ifndef INTEGER_TYPE_H
#define INTEGER_TYPE_H

#include "Type.h"

namespace ance
{
	class Scope;

	class IntegerType : public Type
	{
	private:
		IntegerType(uint64_t bit_size, bool is_signed);

	public:
		std::string get_name() override;
		llvm::Constant* get_default(llvm::LLVMContext& c) override;
		llvm::Type* get_native_type(llvm::LLVMContext& c) override;

	private:
		uint64_t bit_size_;
		bool is_signed_;
		llvm::Type* type_;

	public:
		static ance::Type* get(ance::Scope* scope, uint64_t bit_size, bool is_signed);
	};
}

#endif