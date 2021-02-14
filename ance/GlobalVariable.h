#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H
#include <string>

#include "Variable.h"

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

	class GlobalVariable : public Variable
	{
	public:
		GlobalVariable(ance::Scope* containing_scope, access_modifier access, std::string identifier, ance::Type* type, ance::Constant* constant_init, bool is_constant);
		explicit GlobalVariable(std::string identifier);

		void define_global(ance::Scope* containing_scope, access_modifier access, ance::Type* type, ance::Constant* constant_init, bool is_constant);
		void build_global(llvm::LLVMContext& c, llvm::Module* m);

		llvm::Value* get_value(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);
		void set_value(llvm::Value* value, llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);
	private:
		access_modifier access_;
		ance::Constant* constant_init_;
		llvm::GlobalVariable* native_variable_;
	};
}

#endif // GLOBAL_VARIABLE_H
