#ifndef ANCE_SRC_LANG_TYPE_HALFTYPE_H_
#define ANCE_SRC_LANG_TYPE_HALFTYPE_H_

#include "FloatingPointType.h"

namespace lang
{
    /**
     * Represents the half precision floating point type.
     */
    class HalfType : public FloatingPointType
    {
      public:
        HalfType();

        llvm::Constant* getDefaultContent(llvm::Module& m) const override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) const override;

        lang::ResolvingHandle<lang::Type> clone(lang::Context& new_context) const override;

      private:
        [[nodiscard]] size_t getPrecision() const override;
    };
}
#endif
