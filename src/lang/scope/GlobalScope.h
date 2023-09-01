#ifndef ANCE_SRC_LANG_SCOPE_GLOBALSCOPE_H_
#define ANCE_SRC_LANG_SCOPE_GLOBALSCOPE_H_

#include "UnorderedScope.h"

#include "lang/AccessModifier.h"
#include "lang/Assigner.h"
#include "lang/Context.h"
#include "lang/Element.h"
#include "lang/construct/CodeBlock.h"
#include "lang/construct/Function.h"
#include "lang/construct/FunctionGroup.h"
#include "lang/construct/Member.h"
#include "lang/construct/Variable.h"
#include "lang/type/Type.h"
#include "lang/utility/Identifier.h"
#include "lang/utility/OwningHandle.h"
#include "lang/utility/TypeRegistry.h"

class ConstantExpression;
class Storage;

namespace lang
{
    class Description;
}

namespace lang
{
    /**
     * The top level scope.
     */
    class GlobalScope
        : public UnorderedScope
        , public lang::Element<GlobalScope, ANCE_CONSTRUCTS>
    {
      public:
        explicit GlobalScope(bool is_containing_runtime);

        Scope*                     scope() override;
        [[nodiscard]] Scope const* scope() const override;

        /**
         * Get the context, in which all basic systems like the typesystem are defined.
         */
        lang::Context& context() override;
        /**
         * Get the context, in which all basic systems like the typesystem are defined.
         */
        [[nodiscard]] lang::Context const& context() const override;

        [[nodiscard]] bool isPartOfFunction() const override;

        lang::GlobalScope*                     getGlobalScope() override;
        [[nodiscard]] lang::GlobalScope const* getGlobalScope() const override;
        llvm::DIScope*                         getDebugScope(CompileContext& context) const override;

        [[nodiscard]] Owned<lang::GlobalScope> expand() const;
        void                                   determineFlow();

        void validateFlow(ValidationLogger& validation_logger) const;

        /**
         * Synchronize all (public) descriptions with the given storage.
         * @param scope The scope to sync.
         * @param storage The storage to sync with.
         */
        static void synchronize(lang::GlobalScope* scope, Storage& storage);

      public:
        /**
         * Check if this global scope has an entry point.
         * The default entry point is a main method returning ui32.
         * @return True if there is an entry point.
         */
        [[nodiscard]] bool hasEntryPoint() const;

        /**
         * Get the entry point. Fails if there is no entry point.
         * @return The entry point.
         */
        lang::ResolvingHandle<lang::Function> getEntryPoint();

        void buildDeclarations(CompileContext& context) override;
        void buildDefinitions(CompileContext& context) override;

      protected:
        void onResolve() override;
        void onPostResolve() override;

      private:
        [[nodiscard]] Optional<lang::ResolvingHandle<lang::Function>> findEntryPoint();

      private:
        Optional<Owned<lang::Context>> context_;
    };
}

#endif
