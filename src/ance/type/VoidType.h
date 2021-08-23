#ifndef ANCE_SRC_ANCE_TYPE_VOIDTYPE_H_
#define ANCE_SRC_ANCE_TYPE_VOIDTYPE_H_

#include "Type.h"

namespace ance
{
    /**
     * Represents the void type. The void type is a special type representing no type or no value.
     */
    class VoidType : public Type
    {
      public:
        std::string getName() override;

        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;

        llvm::Type* getContentType(llvm::LLVMContext& c) override;

      private:
        VoidType() = default;

      protected:
        llvm::DIType* createDebugType(CompileContext* context) override;

      public:
        /**
         * Get the void type instance.
         * @return The instance.
         */
        static VoidType* get();

      private:
        inline static VoidType* instance_ = nullptr;
    };
}
#endif
