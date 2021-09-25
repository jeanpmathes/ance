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
      public:
        std::string getName() override;

        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;

        llvm::Type* getContentType(llvm::LLVMContext& c) override;

      private:
        inline static FloatingPointType* instance_ = nullptr;

      public:
        /**
         * Get the quad type instance.
         * @return The instance.
         */
        static ance::FloatingPointType* get();
    };
}
#endif