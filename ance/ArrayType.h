#ifndef ARRAY_TYPE_H
#define ARRAY_TYPE_H

#include "Type.h"

namespace llvm {
	class ArrayType;
}

namespace ance
{
	class Scope;

	class ArrayType : public Type
	{
	private:
		ArrayType(Type* element_type, uint64_t size);

	public:
		std::string get_name() override;
		llvm::Constant* get_default(llvm::LLVMContext& c) override;
		llvm::Type* get_native_type(llvm::LLVMContext& c) override;

	private:
		uint64_t size_;
		ance::Type* element_type_;
		llvm::ArrayType* type_;

	public:
		static ance::Type* get(ance::Scope* scope, Type* element_type, uint64_t size);
	};
}

#endif
