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
      private:
        QuadType();

      public:
        llvm::Constant* getDefaultContent(llvm::Module& m) override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) const override;

        /**
         * Get the quad type instance.
         * @return The instance.
         */
        static lang::ResolvingHandle<lang::Type> get();

      private:
        [[nodiscard]] size_t getPrecision() const override;
    };
}
#endif
