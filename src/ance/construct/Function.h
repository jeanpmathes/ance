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
	Function(std::string function_name,
			 ance::Type* return_type,
			 unsigned int line,
			 unsigned int column);

	[[nodiscard]] std::string getName() const;

	[[nodiscard]] ance::Type* getReturnType() const;

	[[nodiscard]] unsigned int getLine() const;

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

protected:
		std::pair<llvm::FunctionType*, llvm::Function*> createNativeFunction(const std::vector<ance::Parameter*>& parameters, llvm::GlobalValue::LinkageTypes linkage, llvm::LLVMContext& c, llvm::Module* m);

		llvm::CallInst* buildCall(const std::vector<ance::Value*>& arguments, llvm::FunctionType* native_type, llvm::Function* native_function,
								  llvm::LLVMContext& c,
								  llvm::Module* m,
								  CompileState* state,
								  llvm::IRBuilder<>& ir,
								  llvm::DIBuilder* di) const;

	private:
		std::string name_;
		ance::Type* return_type_;
		unsigned int line_;
		[[maybe_unused]] unsigned int column_;
};
}

#endif