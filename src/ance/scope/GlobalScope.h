#ifndef ANCE_GLOBALSCOPE_H
#define ANCE_GLOBALSCOPE_H
#include "Scope.h"

namespace ance
{
	class GlobalScope : public Scope
	{
	public:
		ance::GlobalScope* get_global_scope() override;

		bool validate() override;

		bool is_type_registered(std::string type_name);
		ance::Type* get_type(std::string type_name);
		void register_type(ance::Type* type);

		void define_global_constant(access_modifier access, std::string identifier, ance::Type* type, ance::Constant* constant);
		void define_global_variable(access_modifier access, std::string identifier, ance::Type* type, ance::Constant* value);

		ance::Variable* get_variable(std::string identifier) override;
		void build_variables(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);

		size_t FunctionCount() const;
		void AddFunctionName(std::string name);
		void AddAndEnterFunction(ance::Function* function);

		void PushStatementToCurrentFunction(Statement* statement);

		void BuildFunctionNames(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);
		void BuildFunctions(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);

		bool HasFunction(std::string identifier);
		ance::Function* GetFunction(std::string identifier);
		ance::Function* get_current_function() const;

	private:
		std::map<std::string, ance::Type*> types_;

		std::map<std::string, ance::GlobalVariable*> global_constants;
		std::map<std::string, ance::GlobalVariable*> global_variables;
		std::map<std::string, ance::GlobalVariable*> global_undefined;

		std::map<std::string, ance::Function*> functions;
		ance::Function* current = nullptr;
	};
}
#endif
