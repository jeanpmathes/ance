#ifndef ANCE_SRC_ANCE_SCOPE_SCOPE_H_
#define ANCE_SRC_ANCE_SCOPE_SCOPE_H_

#include <map>
#include <string>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/DIBuilder.h>

#include "GlobalVariable.h"
#include "Type.h"

enum class AccessModifier;
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
		virtual ance::GlobalScope* getGlobalScope() = 0;

		virtual bool validate() = 0;

		virtual ance::Variable* getVariable(std::string identifier) = 0;
	};
}
#endif