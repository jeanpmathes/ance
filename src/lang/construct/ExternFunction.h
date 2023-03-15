#ifndef ANCE_SRC_LANG_CONSTRUCT_EXTERNFUNCTION_H_
#define ANCE_SRC_LANG_CONSTRUCT_EXTERNFUNCTION_H_

#include "FunctionDefinition.h"

#include "lang/Element.h"

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
        ExternFunction(Function&                            function,
                       Scope&                               containing_scope,
                       lang::ResolvingHandle<lang::Type>    return_type,
                       lang::Location                       return_type_location,
                       std::vector<Shared<lang::Parameter>> parameters,
                       lang::Location                       location);

        [[nodiscard]] bool isMangled() const override;
        [[nodiscard]] bool isImported() const override;

        void determineFlow() override;
        bool validateFlow(ValidationLogger& validation_logger) const override;

        void createNativeBacking(CompileContext& context) override;
        void build(CompileContext& context) override;

        llvm::DIScope*                                      getDebugScope(CompileContext& context) const override;
        lang::LocalScope*                                   getInsideScope() override;
        [[nodiscard]] std::vector<lang::BasicBlock*> const& getBasicBlocks() const override;

      protected:
        [[nodiscard]] std::pair<llvm::FunctionType*, llvm::Function*> getNativeRepresentation() const override;

      private:
        llvm::FunctionType* native_type_ {nullptr};
        llvm::Function*     native_function_ {nullptr};
    };
}

#endif
