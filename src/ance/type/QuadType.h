#ifndef ANCE_SRC_ANCE_TYPE_QUADTYPE_H_
#define ANCE_SRC_ANCE_TYPE_QUADTYPE_H_

#include "FloatingPointType.h"

#include "ance/type/Type.h"
#include "ance/utility/ResolvingHandle.h"

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
        llvm::Type*     getContentType(llvm::LLVMContext& c) override;

        [[nodiscard]] bool isFloatingPointType(size_t precision) const override;

        /**
         * Get the quad type instance.
         * @return The instance.
         */
        static ance::ResolvingHandle<ance::Type> get();
    };
}
#endif