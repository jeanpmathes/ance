#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H
#include <string>

namespace llvm {
	class LLVMContext;
	class Module;
	class GlobalVariable;
}

enum class access_modifier;

namespace ance
{
	class Constant;
	class Type;

	class GlobalVariable
	{
	public:
		GlobalVariable(access_modifier access, std::string identifier, ance::Type* type, ance::Constant* constant_init, bool is_constant);
		llvm::GlobalVariable* Build(llvm::LLVMContext& c, llvm::Module* m);

		ance::Type* type();

	private:
		access_modifier access_;
		std::string identifier_;
		ance::Type* type_;
		ance::Constant* constant_init_;
		bool is_constant_;
	};
}

#endif // GLOBAL_VARIABLE_H
