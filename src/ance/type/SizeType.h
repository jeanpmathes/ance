#ifndef ANCE_SRC_ANCE_TYPE_SIZETYPE_H_
#define ANCE_SRC_ANCE_TYPE_SIZETYPE_H_

#include "Type.h"

class Application;

namespace ance
{
class SizeType : public ance::Type
{
	public:
		std::string getName() override;

		llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;

		llvm::Type* getContentType(llvm::LLVMContext& c) override;

		static llvm::Value* buildValue(llvm::TypeSize size);

	private:
		inline static SizeType* instance_ = nullptr;
		inline static llvm::Type* native_type_ = nullptr;

	public:
		static void init(llvm::LLVMContext& c, Application& app);

		static ance::SizeType* get();
};
}
#endif