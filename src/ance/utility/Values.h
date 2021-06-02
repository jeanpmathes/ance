#ifndef ANCE_SRC_ANCE_UTILITY_VALUES_H_
#define ANCE_SRC_ANCE_UTILITY_VALUES_H_

#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/DIBuilder.h>

class CompileState;

namespace ance
{

class Type;

class Values
{
	public:
		static llvm::Value* nativeToContent(
			ance::Type* type,
			llvm::Value* native,
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		);

		static llvm::Value* contentToNative(
			ance::Type* type,
			llvm::Value* content,
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		);
};
}

#endif
