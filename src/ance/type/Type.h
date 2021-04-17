#ifndef ANCE_SRC_ANCE_TYPE_TYPE_H_
#define ANCE_SRC_ANCE_TYPE_TYPE_H_

#include <string>
#include <llvm/IR/Constant.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/Module.h>

namespace llvm {
	class LLVMContext;
	class Type;
}

namespace ance
{
	class Type
	{
	public:
		virtual std::string getName() = 0;
		virtual llvm::Constant* getDefault(llvm::LLVMContext& c) = 0;
		virtual llvm::Type* getNativeType(llvm::LLVMContext& c) = 0;

		llvm::TypeSize getSize(llvm::Module* m);
	};

	inline llvm::TypeSize Type::getSize(llvm::Module* m)
	{
		return m->getDataLayout().getTypeAllocSize(getNativeType(m->getContext()));
	}
}
#endif