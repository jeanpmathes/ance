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
      public:
        NullPointerType();
        ~NullPointerType() override = default;

        bool isNullValueType() const override;

        bool                isImplicitlyConvertibleTo(lang::Type const& other) const override;
        bool                validateImplicitConversion(lang::Type const& other,
                                                       lang::Location    location,
                                                       ValidationLogger& validation_logger) const override;
        Shared<lang::Value> buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                    Shared<Value>                     value,
                                                    CompileContext&                   context) override;

      protected:
        llvm::Constant* getDefaultContent(llvm::Module& m) const override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) const override;

        std::string   createMangledName() const override;
        llvm::DIType* createDebugType(CompileContext& context) const override;

        Optional<lang::ResolvingHandle<lang::Type>> getPointeeType() override;
        Type const*                                 getPointeeType() const override;

      public:
        lang::ResolvingHandle<lang::Type> clone(lang::Context& new_context) const override;
    };
}

#endif
