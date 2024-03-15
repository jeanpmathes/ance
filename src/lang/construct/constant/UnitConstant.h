#ifndef ANCE_SRC_LANG_CONSTRUCT_CONSTANT_UNITCONSTANT_H_
#define ANCE_SRC_LANG_CONSTRUCT_CONSTANT_UNITCONSTANT_H_

#include "LiteralConstant.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class Application;

namespace lang
{
    /**
     * The constant unit value.
     */
    class UnitConstant : public LiteralConstant
    {
      public:
        explicit UnitConstant(lang::Context& context);

        [[nodiscard]] std::string toString() const override;

        Shared<lang::Constant> embed(CompileContext& context) const override;

        bool equals(lang::Constant const* other) const override;

        Shared<lang::LiteralConstant> clone(lang::Context& new_context) const override;
    };
}

#endif
