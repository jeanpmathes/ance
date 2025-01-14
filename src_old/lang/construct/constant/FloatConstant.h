#ifndef ANCE_SRC_LANG_CONSTRUCT_CONSTANT_FLOATCONSTANT_H_
#define ANCE_SRC_LANG_CONSTRUCT_CONSTANT_FLOATCONSTANT_H_

#include "LiteralConstant.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    /**
     * A floating point constant of any of the floating point types.
     */
    class FloatConstant : public LiteralConstant
    {
      public:
        /**
         * Create a new floating point constant.
         * @param number The number to use as value.
         * @param semantics The semantics of the constant.
         * @param type The type of float to use.
         */
        FloatConstant(std::string const&                number,
                      llvm::fltSemantics const&         semantics,
                      lang::ResolvingHandle<lang::Type> type);

        [[nodiscard]] std::string toString() const override;

        Shared<lang::Constant> embed(Execution& exec) const override;

        bool equals(lang::Constant const* other) const override;

        Shared<lang::LiteralConstant> clone(lang::Context& new_context) const override;

      private:
        std::string   text_;
        llvm::APFloat float_;
    };
}

#endif
