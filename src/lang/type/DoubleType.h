#ifndef ANCE_SRC_ANCE_TYPE_DOUBLETYPE_H_
#define ANCE_SRC_ANCE_TYPE_DOUBLETYPE_H_

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
      private:
        DoubleType();

      public:
        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) override;

      private:
        inline static Type* instance_ = nullptr;

        [[nodiscard]] size_t getPrecision() const override;

      public:
        /**
         * Get the double type instance.
         * @return The double type instance.
         */
        static lang::ResolvingHandle<lang::Type> get();
    };
}
#endif