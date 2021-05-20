#ifndef ANCE_SRC_ANCE_TYPE_FLOATINGPOINTTYPE_H_
#define ANCE_SRC_ANCE_TYPE_FLOATINGPOINTTYPE_H_

#include "Type.h"

namespace ance
{
class FloatingPointType : public Type
{
	public:
		std::string getName() override = 0;

		llvm::Constant* getDefault(llvm::LLVMContext& c) override = 0;

		llvm::Type* getContentType(llvm::LLVMContext& c) override = 0;
};
}
#endif