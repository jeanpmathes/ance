#ifndef ANCE_SRC_ANCE_TYPE_VOIDTYPE_H_
#define ANCE_SRC_ANCE_TYPE_VOIDTYPE_H_

#include "Type.h"

namespace ance
{
class VoidType : public Type
{
	public:

		std::string getName() override;

		llvm::Constant* getDefault(llvm::LLVMContext& c) override;

		llvm::Type* getNativeType(llvm::LLVMContext& c) override;

	private:
		VoidType() = default;

	public:
		static VoidType* get();

	private:
		static VoidType* instance_;
};
}
#endif
