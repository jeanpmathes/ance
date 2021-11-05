#ifndef ANCE_SRC_ANCE_TYPE_QUADTYPE_H_
#define ANCE_SRC_ANCE_TYPE_QUADTYPE_H_

#include "FloatingPointType.h"

namespace ance
{
    /**
     * Represents the quadruple precision floating point type.
     */
    class QuadType : public FloatingPointType
    {
      private:
        QuadType();

      public:
        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;

        llvm::Type* getContentType(llvm::LLVMContext& c) override;

      private:
        inline static Type* instance_ = nullptr;

      public:
        /**
         * Get the quad type instance.
         * @return The instance.
         */
        static ance::Type* get();
    };
}
#endif