#ifndef ANCE_SRC_ANCE_TYPE_HALFTYPE_H_
#define ANCE_SRC_ANCE_TYPE_HALFTYPE_H_

#include "FloatingPointType.h"

namespace ance
{
    /**
     * Represents the half precision floating point type.
     */
    class HalfType : public FloatingPointType
    {
      private:
        HalfType();

      public:
        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;

        llvm::Type* getContentType(llvm::LLVMContext& c) override;

      private:
        inline static Type* instance_ = nullptr;

      public:
        /**
         * Get the half type instance.
         * @return The instance.
         */
        static ance::Type* get();
    };
}
#endif