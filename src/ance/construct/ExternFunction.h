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
                       ance::ResolvingHandle<ance::Type>             return_type,
                       ance::Location                                return_type_location,
                       std::vector<std::shared_ptr<ance::Parameter>> parameters,
                       ance::Location                                location);

        [[nodiscard]] bool isMangled() const override;

        void pushStatement(Statement* statement) override;
        void addReturn(const std::shared_ptr<ance::Value>& value) override;

        void validate(ValidationLogger& validation_logger) override;

        void                         createNativeBacking(CompileContext* context) override;
        void                         build(CompileContext* context) override;
        std::shared_ptr<ance::Value> buildCall(const std::vector<std::shared_ptr<ance::Value>>& arguments,
                                               CompileContext*                                  context) const override;

        llvm::DIScope*  getDebugScope(CompileContext* context) override;
        ance::LocalScope* getInsideScope() override;

      protected:
        using FunctionDefinition::buildCall;

      private:
        llvm::FunctionType* native_type_ {nullptr};
        llvm::Function*     native_function_ {nullptr};
    };
}

#endif
