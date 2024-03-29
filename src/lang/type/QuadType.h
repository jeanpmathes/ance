#ifndef ANCE_SRC_LANG_TYPE_QUADTYPE_H_
#define ANCE_SRC_LANG_TYPE_QUADTYPE_H_

#include "FloatingPointType.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    /**
     * Represents the quadruple precision floating point type.
     */
    class QuadType : public FloatingPointType
    {
      public:
        QuadType();

        lang::ResolvingHandle<lang::Type> clone(lang::Context& new_context) const override;

      private:
        [[nodiscard]] size_t getPrecision() const override;
    };
}
#endif
