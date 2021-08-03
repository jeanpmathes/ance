#ifndef ANCE_SRC_ANCE_CONSTRUCT_DEFINEDFUNCTION_H_
#define ANCE_SRC_ANCE_CONSTRUCT_DEFINEDFUNCTION_H_

#include "Function.h"

#include <list>
#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "ance/construct/Parameter.h"

#include "ance/AccessModifier.h"
#include "ance/expression/Expression.h"
#include "ance/statement/Statement.h"
#include "compiler/CompileContext.h"

class CompileContext;

namespace ance
{
    class DefinedFunction : public virtual ance::Function, public virtual ance::Scope
    {
      public:
        DefinedFunction(AccessModifier                access,
                        std::string                   function_name,
                        ance::Type*                   return_type,
                        std::vector<ance::Parameter*> parameters,
                        ance::Scope*                  scope,
                        unsigned int                  line,
                        unsigned int                  column);

        void pushStatement(Statement* statement);

        void buildName(CompileContext* context) override;
        void build(CompileContext* context) override;

        void addReturn(ance::Value* value = nullptr);

        ance::Value* buildCall(const std::vector<ance::Value*>& arguments, CompileContext* context) const override;

        llvm::DISubprogram* debugSubprogram();

        ance::GlobalScope* getGlobalScope() override;
        ance::LocalScope* getFunctionScope();
        llvm::DIScope* getDebugScope(CompileContext *context) override;

        bool validate() override;

        ance::Variable* getVariable(std::string identifier) override;

        bool        isTypeRegistered(const std::string& type_name) override;
        ance::Type* getType(const std::string& type_name) override;
        void        registerType(ance::Type* type) override;

      protected:
        using Function::buildCall;

      private:
        AccessModifier access_;

        std::vector<ance::Parameter*> parameters_;

        ance::Scope* containing_scope_;
        ance::LocalScope*             function_scope_;

        std::vector<ance::LocalVariable*> arguments_;
        std::list<Statement*>             statements_;

        llvm::FunctionType* native_type_ {nullptr};
        llvm::Function*     native_function_ {nullptr};

        ance::Value* return_value_ {nullptr};
        bool         has_return_ {false};
    };
}

#endif
