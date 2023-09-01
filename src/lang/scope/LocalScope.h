#ifndef ANCE_SRC_LANG_SCOPE_LOCALSCOPE_H_
#define ANCE_SRC_LANG_SCOPE_LOCALSCOPE_H_

#include "OrderedScope.h"

#include "lang/Element.h"
#include "lang/construct/FunctionGroup.h"
#include "lang/construct/Variable.h"
#include "lang/type/Type.h"
#include "lang/utility/Optional.h"
#include "lang/utility/OwningHandle.h"

class Expression;

namespace lang
{
    /**
     * A local scope with local variables. Is used by code blocks.
     */
    class LocalScope
        : public OrderedScope
        , public lang::Element<LocalScope, ANCE_CONSTRUCTS>
    {
      public:
        /**
         * Create a new local scope.
         * @param parent The parent scope containing this scope.
         * @param code_block The code block causing this scope.
         */
        LocalScope(lang::Scope* parent, lang::CodeBlock& code_block);

        void resolveFollowingOrder() override;
        void buildDeclarationsFollowingOrder(CompileContext& context) override;

        llvm::DIScope* getDebugScope(CompileContext& context) const override;

        [[nodiscard]] bool isPartOfFunction() const override;

      private:
        lang::CodeBlock& code_block_;
    };
}
#endif
