#ifndef ANCE_VOIDTYPE_H
#define ANCE_VOIDTYPE_H
#include "Type.h"

namespace ance
{
	class VoidType : public Type
	{
	public:

		std::string get_name() override;
		llvm::Constant* get_default(llvm::LLVMContext& c) override;
		llvm::Type* get_native_type(llvm::LLVMContext& c) override;

	private:
		VoidType() = default;

	public:
		static VoidType* get();

	private:
		static VoidType* instance_;
	};
}
#endif // ANCE_VOIDTYPE_H
