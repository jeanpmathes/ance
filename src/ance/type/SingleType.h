#ifndef ANCE_SRC_ANCE_TYPE_SINGLETYPE_H_
#define ANCE_SRC_ANCE_TYPE_SINGLETYPE_H_

#include "FloatingPointType.h"

namespace ance
{
    /**
     * Represents the single precision floating point type.
     */
    class SingleType : public FloatingPointType
    {
      private:
        SingleType();

      public:
        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;

        llvm::Type* getContentType(llvm::LLVMContext& c) override;

      private:
        inline static Type* instance_ = nullptr;

      public:
        /**
         * Get the single type instance.
         * @return The instance.
         */
        static ance::Type* get();
    };
}
#endif