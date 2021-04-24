#ifndef ANCE_SRC_ANCE_TYPE_ARRAYTYPE_H_
#define ANCE_SRC_ANCE_TYPE_ARRAYTYPE_H_

#include "Type.h"

namespace llvm
{
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
		std::string getName() override;

		llvm::Constant* getDefault(llvm::LLVMContext& c) override;

		llvm::Type* getNativeType(llvm::LLVMContext& c) override;

		~ArrayType() override = default;

	private:
		uint64_t size_;
		ance::Type* element_type_;
		llvm::ArrayType* type_{nullptr};

	public:
		static ance::Type* get(ance::Scope* scope, Type* element_type, uint64_t size);
};
}

#endif
