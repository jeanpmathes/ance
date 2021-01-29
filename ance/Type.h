#ifndef TYPE_H
#define TYPE_H

#include <string>
#include <llvm/IR/Constant.h>

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
	};
}
#endif