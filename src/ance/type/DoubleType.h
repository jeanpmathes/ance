#ifndef ANCE_SRC_ANCE_TYPE_DOUBLETYPE_H_
#define ANCE_SRC_ANCE_TYPE_DOUBLETYPE_H_

#include "FloatingPointType.h"

#include "ance/type/Type.h"
#include "ance/utility/ResolvingHandle.h"

namespace ance
{
    /**
     * Represents the double precision floating point type.
     */
    class DoubleType : public FloatingPointType
    {
      private:
        DoubleType();

      public:
        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;

        llvm::Type* getContentType(llvm::LLVMContext& c) override;

      private:
        inline static Type* instance_ = nullptr;

      public:
        /**
         * Get the double type instance.
         * @return The double type instance.
         */
        static ance::ResolvingHandle<ance::Type> get();
    };
}
#endif