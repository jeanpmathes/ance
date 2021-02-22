#ifndef ANCE_LOCALSCOPE_H
#define ANCE_LOCALSCOPE_H

#include "Scope.h"

namespace ance
{
	class LocalScope : public Scope
	{
	public:
		explicit LocalScope(ance::Scope* parent);

		ance::GlobalScope* get_global_scope() override;

		bool validate() override;

		void define_local_variable(const std::string& identifier, ance::Type* type, ance::Value* value);

		ance::Variable* get_variable(std::string identifier) override;
		void build_variables(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) override;

	private:
		ance::Scope* parent_;

		std::map<std::string, ance::Variable*> local_variables;
	};
}
#endif
