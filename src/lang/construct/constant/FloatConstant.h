#ifndef ANCE_SRC_LANG_CONSTRUCT_CONSTANT_FLOATCONSTANT_H_
#define ANCE_SRC_LANG_CONSTRUCT_CONSTANT_FLOATCONSTANT_H_

#include "Constant.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    /**
     * A floating point constant of any of the floating point types.
     */
    class FloatConstant : public Constant
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

        lang::ResolvingHandle<lang::Type> type() override;
        [[nodiscard]] lang::Type const&   type() const override;

        llvm::Constant* createContent(llvm::Module& m) override;

        bool equals(lang::Constant const* other) const override;

        Shared<Constant> clone(lang::Context& new_context) const override;

      private:
        std::string                       text_;
        lang::ResolvingHandle<lang::Type> type_;
        llvm::APFloat                     float_;
    };
}

#endif
