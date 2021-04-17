#ifndef ANCE_SRC_ANCE_CONSTRUCT_FUNCTION_H_
#define ANCE_SRC_ANCE_CONSTRUCT_FUNCTION_H_

#include <list>
#include <string>

#include "Parameter.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DIBuilder.h"

#include "Statement.h"
#include "CompileState.h"
#include "Expression.h"

class Statement;
class CompileState;

namespace ance
{
	class LocalScope;
	class Type;
	class LocalScope;

	class Function
	{
	public:
		Function(AccessModifier access, std::string fn_name, ance::Type* return_type, std::vector<ance::Parameter*> parameters, ance::Scope* scope, unsigned int l, unsigned int c);

		[[nodiscard]] std::string getName() const;
		[[nodiscard]] ance::Type* getReturnType() const;
		[[nodiscard]] ance::LocalScope* getScope() const;

		void pushStatement(Statement* statement);

		void buildName(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);
		void build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);

		void addReturn(ance::Value* value = nullptr);

		llvm::CallInst* buildCall(const std::vector<ance::Value*>& arguments, llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) const;

	private:
		AccessModifier access_;
		std::string name_;
		std::vector<ance::Parameter*> parameters_;
		unsigned int line_, column_;
		ance::LocalScope* local_scope_;

		std::vector<ance::LocalVariable*> arguments_;
		std::list<Statement*> statements_;

		ance::Type* return_type_;
		llvm::FunctionType* native_type_;
		llvm::Function* native_function_;

		ance::Value* return_value_;
		bool has_return_;
	};
}

#endif