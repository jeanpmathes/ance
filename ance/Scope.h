#ifndef ANCE_SCOPE_H
#define ANCE_SCOPE_H

#include <map>
#include <string>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/DIBuilder.h>

#include "GlobalVariable.h"
#include "Type.h"

enum class access_modifier;
class Statement;
class CompileState;

namespace ance
{
	class Constant;
	class Function;
	class Value;
	class GlobalScope;

	class Scope
	{
	public:
		virtual ance::GlobalScope* get_global_scope() = 0;

		virtual bool validate() = 0;

		virtual ance::Variable* get_variable(std::string identifier) = 0;
		virtual void build_variables(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) = 0;
	};
}
#endif