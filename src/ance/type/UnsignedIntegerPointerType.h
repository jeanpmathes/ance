#ifndef ANCE_SRC_ANCE_TYPE_UNSIGNEDINTEGERPOINTERTYPE_H_
#define ANCE_SRC_ANCE_TYPE_UNSIGNEDINTEGERPOINTERTYPE_H_

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/DIBuilder.h>

#include "Type.h"

class Application;

class CompileState;

namespace ance
{
class UnsignedIntegerPointerType : public Type
{
	public:
		std::string getName() override;

		llvm::Constant* getDefault(llvm::LLVMContext& c) override;

		llvm::Type* getNativeType(llvm::LLVMContext& c) override;

		static llvm::Value* buildValue(
			llvm::Value* pointer,
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		);

	private:
		inline static UnsignedIntegerPointerType* instance_ = nullptr;
		inline static llvm::Type* native_type_ = nullptr;

	public:
		static void init(llvm::LLVMContext& c, Application& app);

		static ance::UnsignedIntegerPointerType* get();
};
}

#endif
