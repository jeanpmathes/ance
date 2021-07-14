#ifndef ANCE_SRC_ANCE_SCOPE_GLOBALSCOPE_H_
#define ANCE_SRC_ANCE_SCOPE_GLOBALSCOPE_H_

#include "Scope.h"

#include "Assigner.h"

class ConstantExpression;

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

        void defineGlobalVariable(
            AccessModifier      access,
            bool                is_constant,
            const std::string&  identifier,
            ance::Type*         type,
            Assigner            assigner,
            ConstantExpression* initializer);

        ance::Variable* getVariable(std::string identifier) override;

        void buildVariables(
            llvm::LLVMContext& c,
            llvm::Module*      m,
            CompileContext*    state,
            llvm::IRBuilder<>& ir,
            llvm::DIBuilder*   di);

        [[nodiscard]] size_t functionCount() const;

        void addFunctionName(const std::string& name);

        void addFunction(ance::Function* function);

        bool hasFunction(const std::string& identifier);

        bool isFunctionDefined(const std::string& identifier);

        ance::Function* getFunction(const std::string& identifier);

        void buildFunctionNames(CompileContext* context);

        void buildFunctions(CompileContext* context);

      private:
        std::map<std::string, ance::Type*> types_;

        std::map<std::string, ance::GlobalVariable*> global_constants_;
        std::map<std::string, ance::GlobalVariable*> global_variables_;
        std::map<std::string, ance::GlobalVariable*> global_undefined_;

        std::map<std::string, ance::Function*> functions_;
    };
}
#endif
