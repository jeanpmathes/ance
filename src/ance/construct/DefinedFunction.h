#ifndef ANCE_SRC_ANCE_CONSTRUCT_DEFINEDFUNCTION_H_
#define ANCE_SRC_ANCE_CONSTRUCT_DEFINEDFUNCTION_H_

#include "FunctionDefinition.h"

#include <list>
#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "ance/AccessModifier.h"

namespace ance
{
    class LocalScope;
    class Function;
    class Variable;
}

class Statement;
class CompileContext;

namespace ance
{
    /**
     * A function that is defined in code.
     */
    class DefinedFunction : public ance::FunctionDefinition
    {
      public:
        DefinedFunction(ance::Function*                               function,
                        AccessModifier                                access,
                        ance::Type*                                   return_type,
                        std::vector<std::shared_ptr<ance::Parameter>> parameters,
                        ance::Scope*                                  containing_scope,
                        ance::Location                                declaration_location,
                        ance::Location                                definition_location);

        void pushStatement(Statement* statement) override;
        void addReturn(const std::shared_ptr<ance::Value>& value) override;

        void validate(ValidationLogger& validation_logger) override;

        void                         createNativeBacking(CompileContext* context) override;
        void                         build(CompileContext* context) override;
        std::shared_ptr<ance::Value> buildCall(const std::vector<std::shared_ptr<ance::Value>>& arguments,
                                               CompileContext*                                  context) const override;

        /**
         * Get the debug subprogram.
         * @return The debug subprogram.
         */
        llvm::DISubprogram* debugSubprogram();

        llvm::DIScope*  getDebugScope(CompileContext* context) override;
        ance::Variable* getVariable(std::string identifier) override;
        bool            isTypeRegistered(const std::string& type_name) override;
        ance::Type*     getType(const std::string& type_name) override;
        void            registerType(ance::Type* type) override;

        ance::LocalScope* getInsideScope() override;

      protected:
        using FunctionDefinition::buildCall;

      private:
        AccessModifier access_;
        ance::Location definition_location_;

        std::unique_ptr<ance::LocalScope> inside_scope_;

        std::vector<ance::Variable*> arguments_;
        std::list<Statement*>        statements_;

        llvm::FunctionType* native_type_ {nullptr};
        llvm::Function*     native_function_ {nullptr};

        std::shared_ptr<ance::Value> return_value_ {};
        bool                         has_return_ {false};
    };
}

#endif
