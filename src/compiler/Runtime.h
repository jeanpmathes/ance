#ifndef ANCE_SRC_COMPILER_RUNTIME_H_
#define ANCE_SRC_COMPILER_RUNTIME_H_

#include <string>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/DIBuilder.h>

class CompileState;

namespace ance
{
class Type;

class Value;
}

class Runtime
{
	public:
		void init(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		);

	private:
		llvm::FunctionType* allocate_dynamic_type_;
		llvm::Function* allocate_dynamic_;

		llvm::FunctionType* delete_dynamic_type_;
		llvm::Function* delete_dynamic_;

	public:

		enum Allocator
		{
				AUTOMATIC,
				DYNAMIC
		};

		ance::Value* allocate(
			Allocator allocation,
			ance::Type* type,
			ance::Value* count,
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		);

		void deleteDynamic(
			ance::Value* value,
			bool delete_buffer,
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		);

	private:
		llvm::Value* allocateAutomatic(
			ance::Type* type,
			ance::Value* count,
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		);

		llvm::Value* allocateDynamic(
			ance::Type* type,
			ance::Value* count,
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		);
};

#endif
