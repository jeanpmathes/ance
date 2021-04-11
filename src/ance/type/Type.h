#ifndef TYPE_H
#define TYPE_H

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
		virtual std::string get_name() = 0;
		virtual llvm::Constant* get_default(llvm::LLVMContext& c) = 0;
		virtual llvm::Type* get_native_type(llvm::LLVMContext& c) = 0;

		llvm::TypeSize get_size(llvm::Module* m);
	};

	inline llvm::TypeSize Type::get_size(llvm::Module* m)
	{
		return m->getDataLayout().getTypeAllocSize(get_native_type(m->getContext()));
	}
}
#endif