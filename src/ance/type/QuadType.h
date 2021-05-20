#ifndef ANCE_SRC_ANCE_TYPE_QUADTYPE_H_
#define ANCE_SRC_ANCE_TYPE_QUADTYPE_H_

#include "FloatingPointType.h"

namespace ance
{
class Scope;

class QuadType : public FloatingPointType
{
	public:
		std::string getName() override;

		llvm::Constant* getDefault(llvm::LLVMContext& c) override;

		llvm::Type* getContentType(llvm::LLVMContext& c) override;

	private:
		inline static FloatingPointType* instance_ = nullptr;

	public:
		static ance::FloatingPointType* get();
};
}
#endif