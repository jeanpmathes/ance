#ifndef ANCE_SRC_LANG_CONSTRUCT_CUSTOMFUNCTION_H_
#define ANCE_SRC_LANG_CONSTRUCT_CUSTOMFUNCTION_H_

#include "FunctionDefinition.h"

#include <list>
#include <optional>
#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "lang/AccessModifier.h"
#include "lang/utility/ResolvingHandle.h"
#include "lang/AccessModifier.h"
#include "lang/Element.h"
#include "lang/construct/CodeBlock.h"

namespace lang
{
    class LocalScope;
    class Function;
    class Variable;
}

class Statement;
class CompileContext;

namespace lang
{
    /**
     * A function that is defined in code.
     */
    class CustomFunction
        : public lang::FunctionDefinition
        , public lang::Element<CustomFunction, ANCE_CONSTRUCTS>
    {
      public:
        CustomFunction(Function&                                     function,
                       lang::AccessModifier                          access,
                       lang::ResolvingHandle<lang::Type>             return_type,
                       lang::Location                                return_type_location,
                       std::vector<std::shared_ptr<lang::Parameter>> parameters,
                       std::unique_ptr<Statement>                    code,
                       Scope&                                        containing_scope,
                       lang::Location                                declaration_location,
                       lang::Location                                definition_location);

        [[nodiscard]] bool isMangled() const override;

        [[nodiscard]] lang::AccessModifier access() const;
        [[nodiscard]] Statement&           code() const;

        void postResolve() override;
        void validate(ValidationLogger& validation_logger) const override;
        void expand() override;
        void determineFlow() override;
        bool validateFlow(ValidationLogger& validation_logger) const override;

        void createNativeBacking(CompileContext& context) override;
        void build(CompileContext& context) override;

        /**
         * Get the debug subprogram.
         * @return The debug subprogram.
         */
        llvm::DISubprogram* debugSubprogram();

        llvm::DIScope*    getDebugScope(CompileContext& context) override;
        lang::LocalScope* getInsideScope() override;

        [[nodiscard]] const std::vector<lang::BasicBlock*>& getBasicBlocks() const override;

      protected:
        using FunctionDefinition::buildCall;

        [[nodiscard]] std::pair<llvm::FunctionType*, llvm::Function*> getNativeRepresentation() const override;

      private:
        void setupCode();
        void validateReturn(ValidationLogger& validation_logger) const;
        void validateUnreachable(ValidationLogger& validation_logger) const;

      private:
        std::unique_ptr<Statement> code_;
        lang::LocalScope*          inside_scope_ {nullptr};

        lang::AccessModifier access_;
        lang::Location       definition_location_;

        std::vector<std::optional<lang::ResolvingHandle<lang::Variable>>> arguments_ {};

        std::unique_ptr<lang::BasicBlock>              initial_block_;
        std::vector<std::unique_ptr<lang::BasicBlock>> blocks_ {};
        std::vector<lang::BasicBlock*>                 used_blocks_ {};

        llvm::FunctionType* native_type_ {nullptr};
        llvm::Function*     native_function_ {nullptr};
    };
}

#endif

