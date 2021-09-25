#ifndef ANCE_SRC_ANCE_TYPE_DOUBLETYPE_H_
#define ANCE_SRC_ANCE_TYPE_DOUBLETYPE_H_

#include "FloatingPointType.h"

namespace ance
{
    /**
     * Represents the double precision floating point type.
     */
    class DoubleType : public FloatingPointType
    {
      public:
        std::string getName() override;

        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;

        llvm::Type* getContentType(llvm::LLVMContext& c) override;

      private:
        inline static FloatingPointType* instance_ = nullptr;

      public:
        /**
         * Get the double type instance.
         * @return The double type instance.
         */
        static ance::FloatingPointType* get();
    };
}
#endif