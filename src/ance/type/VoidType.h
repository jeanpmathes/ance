#ifndef ANCE_SRC_ANCE_TYPE_VOIDTYPE_H_
#define ANCE_SRC_ANCE_TYPE_VOIDTYPE_H_

#include "TypeDefinition.h"

namespace ance
{
    /**
     * Represents the void type. The void type is a special type representing no type or no value.
     */
    class VoidType : public ance::TypeDefinition
    {
      private:
        VoidType();

      public:
        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) override;

        bool isVoidType() const override;

      protected:
        std::string   createMangledName() override;
        llvm::DIType* createDebugType(CompileContext* context) override;

      public:
        /**
         * Get the void type instance.
         * @return The instance.
         */
        static ance::ResolvingHandle<ance::Type> get();
    };
}
#endif
