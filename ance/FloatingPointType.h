#ifndef ANCE_FLOATINGPOINTTYPE_H
#define ANCE_FLOATINGPOINTTYPE_H

#include "Type.h"

namespace ance
{
	class FloatingPointType : public Type
	{
	public:
		std::string get_name() override = 0;
		llvm::Constant* get_default(llvm::LLVMContext& c) override = 0;
		llvm::Type* get_native_type(llvm::LLVMContext& c) override = 0;
	};
}
#endif