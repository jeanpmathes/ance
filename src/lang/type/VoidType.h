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
        [[nodiscard]] StateCount getStateCount() const override;

        llvm::Constant* getDefaultContent(llvm::Module& m) override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) override;

        [[nodiscard]] bool isVoidType() const override;

        void buildDefaultInitializer(llvm::Value* ptr, llvm::Value* count, CompileContext* context) override;
        void buildCopyInitializer(llvm::Value* ptr, llvm::Value* original, CompileContext* context) override;
        void buildFinalizer(llvm::Value* ptr, llvm::Value* count, CompileContext* context) override;
        void buildNativeDeclaration(CompileContext* context) override;
        void buildNativeDefinition(CompileContext* context) override;

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
