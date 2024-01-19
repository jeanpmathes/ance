#ifndef ANCE_SRC_LANG_CONSTRUCT_CONSTANT_UNITCONSTANT_H_
#define ANCE_SRC_LANG_CONSTRUCT_CONSTANT_UNITCONSTANT_H_

#include "Constant.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class Application;

namespace lang
{
    /**
     * The constant unit value.
     */
    class UnitConstant : public Constant
    {
      public:
        explicit UnitConstant(lang::Context& new_context);

        [[nodiscard]] std::string toString() const override;

        lang::ResolvingHandle<lang::Type> type() override;
        [[nodiscard]] lang::Type const&   type() const override;

        Shared<lang::Constant> createContent(CompileContext& context) override;

        bool equals(lang::Constant const* other) const override;

        Shared<lang::Constant> clone(lang::Context& new_context) const override;

        /**
         * Create a new unit constant.
         * @return The new unit constant.
         */
        static Shared<lang::UnitConstant> create(lang::Context& new_context);

      private:
        lang::ResolvingHandle<lang::Type> type_;
    };
}

#endif
