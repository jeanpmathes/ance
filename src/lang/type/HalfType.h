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
      private:
        HalfType();

      public:
        llvm::Constant* getDefaultContent(llvm::Module& m) override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) const override;

        /**
         * Get the half type instance.
         * @return The instance.
         */
        static lang::ResolvingHandle<lang::Type> get();

      private:
        [[nodiscard]] size_t getPrecision() const override;
    };
}
#endif
