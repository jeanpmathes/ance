#ifndef ANCE_SRC_ANCE_TYPE_SINGLETYPE_H_
#define ANCE_SRC_ANCE_TYPE_SINGLETYPE_H_

#include "FloatingPointType.h"

#include "ance/type/Type.h"
#include "ance/utility/ResolvingHandle.h"

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
        llvm::Type*     getContentType(llvm::LLVMContext& c) override;

        [[nodiscard]] bool isFloatingPointType(size_t precision) const override;

        /**
         * Get the single type instance.
         * @return The instance.
         */
        static ance::ResolvingHandle<ance::Type> get();
    };
}
#endif