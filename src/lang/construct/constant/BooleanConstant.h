#ifndef ANCE_SRC_LANG_CONSTRUCT_CONSTANT_BOOLEANCONSTANT_H_
#define ANCE_SRC_LANG_CONSTRUCT_CONSTANT_BOOLEANCONSTANT_H_

#include "LiteralConstant.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class Application;

namespace lang
{
    /**
     * A constant for boolean values.
     */
    class BooleanConstant : public LiteralConstant
    {
      private:
        explicit BooleanConstant(bool boolean, lang::Context& context);

      public:
        [[nodiscard]] std::string toString() const override;

        Shared<lang::Constant> embed(CompileContext& context) const override;

        bool equals(lang::Constant const* other) const override;

        [[nodiscard]] Shared<lang::LiteralConstant> clone(lang::Context& new_context) const override;

        /**
         * Create a boolean constant with the false value.
         * @return The new boolean constant.
         */
        static Shared<lang::BooleanConstant> createFalse(lang::Context& context);
        /**
         * Create a boolean constant with the true value.
         * @return The new boolean constant.
         */
        static Shared<lang::BooleanConstant> createTrue(lang::Context& context);

      private:
        bool        boolean_;
        std::string string_;
    };
}

#endif
