#ifndef ANCE_SRC_LANG_TYPE_DOUBLETYPE_H_
#define ANCE_SRC_LANG_TYPE_DOUBLETYPE_H_

#include "FloatingPointType.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    /**
     * Represents the double precision floating point type.
     */
    class DoubleType : public FloatingPointType
    {
      public:
        DoubleType();

        llvm::Constant* getDefaultContent(llvm::Module& m) const override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) const override;

      private:
        [[nodiscard]] size_t getPrecision() const override;

      public:
        lang::ResolvingHandle<lang::Type> clone(lang::Context& new_context) const override;
    };
}
#endif
