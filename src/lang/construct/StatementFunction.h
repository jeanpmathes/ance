#ifndef ANCE_SRC_LANG_CONSTRUCT_STATEMENTFUNCTION_H_
#define ANCE_SRC_LANG_CONSTRUCT_STATEMENTFUNCTION_H_

#include "FunctionDefinition.h"

#include <list>
#include <optional>
#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "lang/AccessModifier.h"
#include "lang/Element.h"
#include "lang/construct/CodeBlock.h"
#include "lang/utility/ResolvingHandle.h"

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
     * Abstract base class for functions that are defined by a statement.
     */
    class StatementFunction
        : public lang::FunctionDefinition
    {
      public:
        StatementFunction(Function&                                     function,
                          lang::AccessModifier                          access,
                          lang::ResolvingHandle<lang::Type>             return_type,
                          lang::Location                                return_type_location,
                          std::vector<std::shared_ptr<lang::Parameter>> parameters,
                          std::unique_ptr<Statement>                    code,
                          Scope&                                        containing_scope,
                          lang::Location                                declaration_location);

        [[nodiscard]] lang::AccessModifier access() const;
        [[nodiscard]] Statement&           code() const;

        void postResolve() override;
        void validate(ValidationLogger& validation_logger) const override;
        void expand() override;
        void determineFlow() override;
        bool validateFlow(ValidationLogger& validation_logger) const override;

        void createNativeBacking(CompileContext& context) override;
        void build(CompileContext& context) override;

        llvm::DIScope*    getDebugScope(CompileContext& context) override;
        lang::LocalScope* getInsideScope() override;

        [[nodiscard]] const std::vector<lang::BasicBlock*>& getBasicBlocks() const override;

      protected:
        using FunctionDefinition::buildCall;

        [[nodiscard]] std::pair<llvm::FunctionType*, llvm::Function*> getNativeRepresentation() const override;

        [[nodiscard]] BasicBlock&                   getInitialBlock() const;
        [[nodiscard]] std::optional<lang::Location> findUnreachableCode() const;

        [[nodiscard]] const std::vector<std::optional<lang::ResolvingHandle<lang::Variable>>>& arguments() const;

      private:
        void setupCode();

      private:
        std::unique_ptr<Statement> code_;
        lang::LocalScope*          inside_scope_ {nullptr};

        lang::AccessModifier access_;

        std::vector<std::optional<lang::ResolvingHandle<lang::Variable>>> arguments_ {};

        std::unique_ptr<lang::BasicBlock>              initial_block_;
        std::vector<std::unique_ptr<lang::BasicBlock>> blocks_ {};
        std::vector<lang::BasicBlock*>                 used_blocks_ {};

        llvm::FunctionType* native_type_ {nullptr};
        llvm::Function*     native_function_ {nullptr};
    };
}

#endif
