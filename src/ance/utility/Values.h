#ifndef ANCE_SRC_ANCE_UTILITY_VALUES_H_
#define ANCE_SRC_ANCE_UTILITY_VALUES_H_

#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/DIBuilder.h>

class CompileContext;

namespace ance
{

class Type;

class Values
{
	public:
		static llvm::Value* nativeToContent(ance::Type* type, llvm::Value* native, CompileContext* context);

		static llvm::Value* contentToNative(ance::Type* type, llvm::Value* content, CompileContext* context);
};
}

#endif
