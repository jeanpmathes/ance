#ifndef ANCE_SRC_LANG_CONSTRUCT_CONSTANT_WRAPPEDCONSTANT_H_
#define ANCE_SRC_LANG_CONSTRUCT_CONSTANT_WRAPPEDCONSTANT_H_

#include "Constant.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class Application;

namespace lang
{
    /**
     * A wrapped llvm constant.
     */
    class WrappedConstant : public Constant
    {
      public:
        WrappedConstant(lang::ResolvingHandle<lang::Type> type, llvm::Constant* constant);

        [[nodiscard]] std::string toString() const override;

        lang::ResolvingHandle<lang::Type> type() override;
        [[nodiscard]] lang::Type const&   type() const override;

        Shared<lang::Constant> createContent(CompileContext& context) override;
        llvm::Constant*        getWrappedConstant() const override;

        bool equals(lang::Constant const* other) const override;

        Shared<lang::Constant> clone(lang::Context& new_context) const override;

      private:
        lang::ResolvingHandle<lang::Type> type_;
        llvm::Constant*                   constant_;
    };
}

#endif
