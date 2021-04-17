#ifndef ANCE_SRC_ANCE_CONSTRUCT_GLOBALVARIABLE_H_
#define ANCE_SRC_ANCE_CONSTRUCT_GLOBALVARIABLE_H_
#include <string>

#include "Variable.h"

namespace llvm {
	class LLVMContext;
	class Module;
	class GlobalVariable;
}

enum class AccessModifier;

namespace ance
{
	class Constant;
	class Type;

	class GlobalVariable : public Variable
	{
	public:
		GlobalVariable(ance::Scope* containing_scope, AccessModifier access, std::string identifier, ance::Type* type, ance::Constant* constant_init, bool is_constant);
		explicit GlobalVariable(std::string identifier);

		void defineGlobal(ance::Scope* containing_scope, AccessModifier access, ance::Type* type, ance::Constant* constant_init, bool is_constant);
		void buildGlobal(llvm::LLVMContext& c, llvm::Module* m);

		llvm::Value* getValue(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) override;
		void setValue(llvm::Value* value, llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) override;

	private:
		AccessModifier access_;
		ance::Constant* constant_init_;
		llvm::GlobalVariable* native_variable_;
	};
}

#endif
