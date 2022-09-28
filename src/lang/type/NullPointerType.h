#ifndef ANCE_SRC_LANG_TYPE_NULLPOINTERTYPE_H_
#define ANCE_SRC_LANG_TYPE_NULLPOINTERTYPE_H_

#include "AddressType.h"

namespace lang
{
    /**
     * The type of the null pointer literal. Can be implicitly converted to any address type.
     */
    class NullPointerType : public lang::AddressType
    {
      private:
        NullPointerType();

      public:
        ~NullPointerType() override = default;

        bool                         isImplicitlyConvertibleTo(lang::ResolvingHandle<lang::Type> other) override;
        bool                         validateImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                                lang::Location                    location,
                                                                ValidationLogger&                 validation_logger) const override;
        std::shared_ptr<lang::Value> buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                             std::shared_ptr<Value>            value,
                                                             CompileContext&                   context) override;

      protected:
        llvm::Constant* getDefaultContent(llvm::Module& m) override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) const override;

        std::string   createMangledName() const override;
        llvm::DIType* createDebugType(CompileContext& context) override;

      public:
        static lang::ResolvingHandle<lang::Type> get();
    };
}

#endif
