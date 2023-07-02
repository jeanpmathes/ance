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
     * A local scope with local variables. Can be used by functions and similar constructs.
     */
    class LocalScope
        : public OrderedScope
        , public lang::Element<LocalScope, ANCE_CONSTRUCTS>
    {
      public:
        /**
         * Create a new local scope.
         * @param parent The parent scope containing this scope.
         */
        explicit LocalScope(lang::Scope* parent);

        llvm::DIScope*                         getDebugScope(CompileContext& context) const override;

        [[nodiscard]] bool isPartOfFunction() const override;
    };
}
#endif
