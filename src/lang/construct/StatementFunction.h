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
class Execution;

namespace lang
{
    /**
     * Abstract base class for functions that are defined by a statement.
     */
    class StatementFunction : public lang::FunctionDefinition
    {
      public:
        StatementFunction(Function&                            function,
                          lang::AccessModifier                 access,
                          bool                              is_cmp,
                          lang::ResolvingHandle<lang::Type>    return_type,
                          lang::Location                       return_type_location,

                          std::vector<Shared<lang::Parameter>> parameters,
                          Statement&                           code,
                          Scope&                               containing_scope,
                          lang::Location                       declaration_location);

        void setup() override;

        bool isCMP() const override;

        [[nodiscard]] lang::AccessModifier access() const override;
        [[nodiscard]] Statement const*     code() const override;

        void resolveFollowingOrder() override;
        void postResolve() override;
        void determineFlow() override;
        bool validateFlow(ValidationLogger& validation_logger) const override;

        void registerDeclarationsFollowingOrder(Execution& exec) const override;

        BasicBlock const*                                   getEntryBlock() const override;
        [[nodiscard]] std::vector<lang::BasicBlock*> const& getBasicBlocks() const override;

      protected:
        using FunctionDefinition::execCall;

        [[nodiscard]] BasicBlock const&        getInitialBlock() const;
        [[nodiscard]] Optional<lang::Location> findUnreachableCode() const;

      private:
        Statement&   code_;
        lang::Scope* inside_scope_ {nullptr};

        lang::AccessModifier access_;
        bool                 is_cmp_;

        Owned<lang::BasicBlock>              initial_block_;
        std::vector<Owned<lang::BasicBlock>> blocks_ {};
        std::vector<lang::BasicBlock*>       used_blocks_ {};
    };
}

#endif
