#ifndef ANCE_SRC_ANCE_CONSTRUCT_EXTERNFUNCTION_H_
#define ANCE_SRC_ANCE_CONSTRUCT_EXTERNFUNCTION_H_

#include "FunctionDefinition.h"

namespace ance
{
    class Function;
}

namespace ance
{
    /**
     * A function that is just declared, the actual definition is provided externally when linking.
     */
    class ExternFunction : public ance::FunctionDefinition
    {
      public:
        ExternFunction(ance::Function*                               function,
                       ance::Scope*                                  containing_scope,
                       ance::Type*                                   return_type,
                       std::vector<std::shared_ptr<ance::Parameter>> parameters,
                       ance::Location                                location);

        void pushStatement(Statement* statement) override;
        void addReturn(const std::shared_ptr<ance::Value>& value) override;

        void validate(ValidationLogger& validation_logger) override;

        void                         createNativeBacking(CompileContext* context) override;
        void                         build(CompileContext* context) override;
        std::shared_ptr<ance::Value> buildCall(const std::vector<std::shared_ptr<ance::Value>>& arguments,
                                               CompileContext*                                  context) const override;

        llvm::DIScope*  getDebugScope(CompileContext* context) override;
        ance::Variable* getVariable(std::string identifier) override;
        bool            isTypeRegistered(const std::string& type_name) override;
        ance::Type*     getType(const std::string& type_name) override;
        void            registerType(ance::Type* type) override;

        ance::LocalScope* getInsideScope() override;

      protected:
        using FunctionDefinition::buildCall;

      private:
        llvm::FunctionType* native_type_ {nullptr};
        llvm::Function*     native_function_ {nullptr};
    };
}

#endif
