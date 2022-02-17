#ifndef ANCE_SRC_LANG_CONSTRUCT_EXTERNFUNCTION_H_
#define ANCE_SRC_LANG_CONSTRUCT_EXTERNFUNCTION_H_

#include "FunctionDefinition.h"

namespace lang
{
    class Function;
}

namespace lang
{
    /**
     * A function that is just declared, the actual definition is provided externally when linking.
     */
    class ExternFunction : public lang::FunctionDefinition
    {
      public:
        ExternFunction(lang::Function*                               function,
                       lang::Scope*                                  containing_scope,
                       lang::ResolvingHandle<lang::Type>             return_type,
                       lang::Location                                return_type_location,
                       std::vector<std::shared_ptr<lang::Parameter>> parameters,
                       lang::Location                                location);

        [[nodiscard]] bool isMangled() const override;

        void pushStatement(std::unique_ptr<Statement> statement) override;
        void addReturn(const std::shared_ptr<lang::Value>& value) override;

        void validate(ValidationLogger& validation_logger) override;

        void                         createNativeBacking(CompileContext* context) override;
        void                         build(CompileContext* context) override;
        std::shared_ptr<lang::Value> buildCall(const std::vector<std::shared_ptr<lang::Value>>& arguments,
                                               CompileContext*                                  context) const override;

        llvm::DIScope*    getDebugScope(CompileContext* context) override;
        lang::LocalScope* getInsideScope() override;

      protected:
        using FunctionDefinition::buildCall;

      private:
        llvm::FunctionType* native_type_ {nullptr};
        llvm::Function*     native_function_ {nullptr};
    };
}

#endif
