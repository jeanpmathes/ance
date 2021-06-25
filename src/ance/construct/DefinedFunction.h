#ifndef ANCE_SRC_ANCE_CONSTRUCT_DEFINEDFUNCTION_H_
#define ANCE_SRC_ANCE_CONSTRUCT_DEFINEDFUNCTION_H_

#include "Function.h"

#include <list>
#include <string>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/DIBuilder.h>

#include "Parameter.h"

#include "Statement.h"
#include "CompileState.h"
#include "Expression.h"

class CompileState;

namespace ance
{
class DefinedFunction : public ance::Function
{
	public:
		DefinedFunction(
		AccessModifier access,
		std::string fn_name,
		ance::Type* return_type,
		std::vector<ance::Parameter*> parameters,
		ance::Scope* scope,
		unsigned int l,
		unsigned int c
		);

		[[nodiscard]] ance::LocalScope* getScope() const;

		void pushStatement(Statement* statement);

		void buildName(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

		void build(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

		void addReturn(ance::Value* value = nullptr);

		ance::Value* buildCall(
			const std::vector<ance::Value*>& arguments,
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) const override;

	private:
		AccessModifier access_;

		std::vector<ance::Parameter*> parameters_;
		ance::LocalScope* local_scope_;

		std::vector<ance::LocalVariable*> arguments_;
		std::list<Statement*> statements_;

		llvm::FunctionType* native_type_{nullptr};
		llvm::Function* native_function_{nullptr};

		ance::Value* return_value_{nullptr};
		bool has_return_{false};
};
}

#endif
