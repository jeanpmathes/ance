#ifndef ANCE_SRC_LANG_CONSTRUCT_PREDEFINEDFUNCTION_H_
#define ANCE_SRC_LANG_CONSTRUCT_PREDEFINEDFUNCTION_H_

#include "FunctionDefinition.h"

#include "lang/Element.h"

namespace lang
{
    class Function;
}

namespace lang
{
    /**
     * A function that is defined by the language itself using native representation, not by source code.
     * Therefore a predefined does not require some steps like resolving.
     */
    class PredefinedFunction
        : public lang::FunctionDefinition
        , public lang::Element<PredefinedFunction, ANCE_CONSTRUCTS>
    {
      public:
        PredefinedFunction(Function&                                     function,
                           Scope&                                        containing_scope,
                           lang::ResolvingHandle<lang::Type>             return_type,
                           std::vector<std::shared_ptr<lang::Parameter>> parameters,
                           lang::Location                                location);

        [[nodiscard]] bool isMangled() const override;

        void validate(ValidationLogger& validation_logger) const override;
        void expand() override;
        void determineFlow() override;
        bool validateFlow(ValidationLogger& validation_logger) const override;

        void createNativeBacking(CompileContext* context) override;
        void build(CompileContext* context) override;

        llvm::DIScope*                                      getDebugScope(CompileContext* context) override;
        lang::LocalScope*                                   getInsideScope() override;
        [[nodiscard]] const std::vector<lang::BasicBlock*>& getBasicBlocks() const override;

      public:
        [[nodiscard]] std::pair<llvm::FunctionType*, llvm::Function*> getNativeRepresentation() const override;

        void setCallValidator(
            std::function<bool(const std::vector<std::pair<std::shared_ptr<lang::Value>, lang::Location>>&,
                               lang::Location,
                               ValidationLogger&)> validator);
        bool doCallValidation(const std::vector<std::pair<std::shared_ptr<lang::Value>, lang::Location>>& arguments,
                              lang::Location                                                              location,
                              ValidationLogger& validation_logger) const override;

      private:
        llvm::FunctionType* native_type_ {nullptr};
        llvm::Function*     native_function_ {nullptr};

        std::function<bool(const std::vector<std::pair<std::shared_ptr<lang::Value>, lang::Location>>&,
                           lang::Location,
                           ValidationLogger&)>
            call_validator_ {};
    };
}

#endif
