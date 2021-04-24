#ifndef ANCE_SRC_ANCE_TYPE_DOUBLETYPE_H_
#define ANCE_SRC_ANCE_TYPE_DOUBLETYPE_H_

#include "FloatingPointType.h"

namespace ance
{
class Scope;

class DoubleType : public FloatingPointType
{
	public:
		std::string getName() override;

		llvm::Constant* getDefault(llvm::LLVMContext& c) override;

		llvm::Type* getNativeType(llvm::LLVMContext& c) override;

	private:
		inline static FloatingPointType* instance_ = nullptr;

	public:
		static ance::FloatingPointType* get(ance::Scope* scope);
};
}
#endif