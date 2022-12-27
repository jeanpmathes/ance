#ifndef ANCE_SRC_LANG_TYPE_OPAQUEPOINTERTYPE_H_
#define ANCE_SRC_LANG_TYPE_OPAQUEPOINTERTYPE_H_

#include "AddressType.h"

namespace lang
{
    /**
     * Represents special pointer types that have no element type and are limited in the operations they can perform.
     */
    class OpaquePointerType : public lang::AddressType
    {
      private:
        OpaquePointerType();

      public:
        ~OpaquePointerType() override = default;

        bool isOpaquePointerType() const override;

      protected:
        llvm::Constant* getDefaultContent(llvm::Module& m) const override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) const override;

        std::string   createMangledName() const override;
        llvm::DIType* createDebugType(CompileContext& context) const override;

        Optional<lang::ResolvingHandle<lang::Type>> getPointeeType() override;
        Type const*                                 getPointeeType() const override;

      public:
        static lang::ResolvingHandle<lang::Type> get();

        ResolvingHandle<lang::Type> clone() const override;
    };
}

#endif
