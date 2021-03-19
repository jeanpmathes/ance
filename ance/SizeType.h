#ifndef ANCE_SIZETYPE_H
#define ANCE_SIZETYPE_H

#include "Type.h"

class Application;

namespace ance
{
	class SizeType : public ance::Type
	{
	public:
		std::string get_name() override;
		llvm::Constant* get_default(llvm::LLVMContext& c) override;
		llvm::Type* get_native_type(llvm::LLVMContext& c) override;

		llvm::Value* build_value(llvm::TypeSize size);

	private:
		inline static SizeType* instance = nullptr;
		inline static llvm::Type* native_type_ = nullptr;

	public:
		static void init(llvm::LLVMContext& c, Application& app);
		static ance::SizeType* get(Application& app);
	};
}
#endif