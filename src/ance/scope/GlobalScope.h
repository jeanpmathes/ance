#ifndef ANCE_SRC_ANCE_SCOPE_GLOBALSCOPE_H_
#define ANCE_SRC_ANCE_SCOPE_GLOBALSCOPE_H_

#include "Scope.h"

namespace ance
{
	class GlobalScope : public Scope
	{
	public:
		ance::GlobalScope* getGlobalScope() override;

		bool validate() override;

		bool isTypeRegistered(const std::string& type_name);
		ance::Type* getType(const std::string& type_name);
		void registerType(ance::Type* type);

		void defineGlobalConstant(AccessModifier access, const std::string& identifier, ance::Type* type, ance::Constant* constant);
		void defineGlobalVariable(AccessModifier access, const std::string& identifier, ance::Type* type, ance::Constant* value);

		ance::Variable* getVariable(std::string identifier) override;
		void buildVariables(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);

		size_t functionCount() const;
		void addFunctionName(const std::string& name);
		void addAndEnterFunction(ance::Function* function);

		void pushStatementToCurrentFunction(Statement* statement);

		void buildFunctionNames(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);
		void buildFunctions(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);

		bool hasFunction(const std::string& identifier);
		ance::Function* getFunction(const std::string& identifier);
		[[nodiscard]] ance::Function* getCurrentFunction() const;

	private:
		std::map<std::string, ance::Type*> types_;

		std::map<std::string, ance::GlobalVariable*> global_constants_;
		std::map<std::string, ance::GlobalVariable*> global_variables_;
		std::map<std::string, ance::GlobalVariable*> global_undefined_;

		std::map<std::string, ance::Function*> functions_;
		ance::Function* current_ = nullptr;
	};
}
#endif
