#ifndef ANCE_SRC_LANG_SCOPE_STRUCTSCOPE_H_
#define ANCE_SRC_LANG_SCOPE_STRUCTSCOPE_H_

#include "UnorderedScope.h"

namespace lang
{
    /**
     * The scope in which struct contents like their members are defined.
     */
    class StructScope
        : public UnorderedScope
        , public lang::Element<StructScope, ANCE_CONSTRUCTS>
    {
      public:
        StructScope(Scope& parent, lang::ResolvingHandle<lang::Type> self);

        [[nodiscard]] bool isPartOfFunction() const override;
        Execution::Scoped  getDebugScope(CompileContext& context) const override;

      private:
        lang::Scope*                      parent_;
        lang::ResolvingHandle<lang::Type> self_;
    };
}

#endif
