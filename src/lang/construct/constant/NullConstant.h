#ifndef ANCE_SRC_LANG_CONSTRUCT_CONSTANT_NULLCONSTANT_H_
#define ANCE_SRC_LANG_CONSTRUCT_CONSTANT_NULLCONSTANT_H_

#include "LiteralConstant.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class Application;

namespace lang
{
    /**
     * The constant null (pointer).
     */
    class NullConstant : public LiteralConstant
    {
      public:
        explicit NullConstant(lang::Context& new_context);

        [[nodiscard]] std::string toString() const override;

        Shared<lang::Constant> embed(CompileContext& context) const override;

        bool equals(lang::Constant const* other) const override;

        Shared<lang::LiteralConstant> clone(lang::Context& new_context) const override;

        /**
         * Create a null constant.
         * @return The new null constant.
         */
        static Shared<lang::NullConstant> create(lang::Context& new_context);
    };
}

#endif
