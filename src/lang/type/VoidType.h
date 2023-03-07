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
      public:
        VoidType();

        [[nodiscard]] StateCount getStateCount() const override;

        llvm::Constant* getDefaultContent(llvm::Module& m) const override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) const override;

        [[nodiscard]] bool isVoidType() const override;

        void buildDefaultInitializer(llvm::Value* ptr, llvm::Value* count, CompileContext& context) override;
        void buildCopyInitializer(llvm::Value* ptr, llvm::Value* original, CompileContext& context) override;
        void buildFinalizer(llvm::Value* ptr, llvm::Value* count, CompileContext& context) override;

        void createConstructors() override;
        void buildNativeDeclaration(CompileContext& context) override;
        void buildNativeDefinition(CompileContext& context) override;

      protected:
        std::string   createMangledName() const override;
        llvm::DIType* createDebugType(CompileContext& context) const override;

      public:
        lang::ResolvingHandle<lang::Type> clone(lang::Context& new_context) const override;
    };
}
#endif
