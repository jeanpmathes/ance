#ifndef ANCE_SRC_LANG_TYPE_VOIDTYPE_H_
#define ANCE_SRC_LANG_TYPE_VOIDTYPE_H_

#include "TypeDefinition.h"

namespace lang
{
    /**
     * Represents the void type. The void type is a special type representing no type or no value.
     */
    class VoidType : public lang::TypeDefinition
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
        static lang::ResolvingHandle<lang::Type> get();
    };
}
#endif
