#ifndef ANCE_DOUBLETYPE_H
#define ANCE_DOUBLETYPE_H

#include "FloatingPointType.h"

namespace ance
{
	class Scope;

	class DoubleType : public FloatingPointType
	{
	public:
		std::string get_name() override;
		llvm::Constant* get_default(llvm::LLVMContext& c) override;
		llvm::Type* get_native_type(llvm::LLVMContext& c) override;

	private:
		inline static FloatingPointType* instance = nullptr;

	public:
		static ance::FloatingPointType* get(ance::Scope* scope);
	};
}
#endif