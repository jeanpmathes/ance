#ifndef ANCE_SRC_LANG_TYPE_SINGLETYPE_H_
#define ANCE_SRC_LANG_TYPE_SINGLETYPE_H_

#include "FloatingPointType.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
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

        /**
         * Get the single type instance.
         * @return The instance.
         */
        static lang::ResolvingHandle<lang::Type> get();

      private:
        [[nodiscard]] size_t getPrecision() const override;
    };
}
#endif