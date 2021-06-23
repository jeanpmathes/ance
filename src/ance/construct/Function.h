#ifndef ANCE_SRC_ANCE_CONSTRUCT_FUNCTION_H_
#define ANCE_SRC_ANCE_CONSTRUCT_FUNCTION_H_

#include <string>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/DIBuilder.h>

#include "Parameter.h"

#include "CompileState.h"
#include "Expression.h"

class CompileState;

namespace ance
{
class LocalScope;

class Type;

class LocalScope;

class Function
{
public:
	[[nodiscard]] virtual std::string getName() const = 0;

	[[nodiscard]] virtual ance::Type* getReturnType() const = 0;

	[[nodiscard]] virtual ance::LocalScope* getScope() const = 0;

	virtual void buildName(
		llvm::LLVMContext& c,
		llvm::Module* m,
		CompileState* state,
		llvm::IRBuilder<>& ir,
		llvm::DIBuilder* di
	) = 0;

	virtual void build(
		llvm::LLVMContext& c,
		llvm::Module* m,
		CompileState* state,
		llvm::IRBuilder<>& ir,
		llvm::DIBuilder* di
	) = 0;

	virtual ance::Value* buildCall(
		const std::vector<ance::Value*>& arguments,
		llvm::LLVMContext& c,
		llvm::Module* m,
		CompileState* state,
		llvm::IRBuilder<>& ir,
		llvm::DIBuilder* di
	) const = 0;
};
}

#endif