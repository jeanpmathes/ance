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
        FloatConstant(std::string number, const llvm::fltSemantics& semantics, lang::ResolvingHandle<lang::Type> type);

        lang::ResolvingHandle<lang::Type> type() override;
        llvm::Constant*                   buildContent(llvm::Module* m) override;

      private:
        lang::ResolvingHandle<lang::Type> type_;
        llvm::APFloat                     float_;
    };
}

#endif
