#ifndef ANCE_SRC_LANG_TYPE_INDIRECTTYPE_H_
#define ANCE_SRC_LANG_TYPE_INDIRECTTYPE_H_

#include "TypeDefinition.h"

namespace lang
{
    /**
     * Represents an indirect type. It points to a value.
     */
    class IndirectType : public virtual lang::TypeDefinition
    {
      public:
        /**
         * Create a new indirect type.
         * @param element_type The type of the value.
         */
        explicit IndirectType(lang::ResolvingHandle<lang::Type> element_type);
        ~IndirectType() override = default;

        llvm::Constant*    getDefaultContent(llvm::Module& m) override;
        llvm::PointerType* getContentType(llvm::LLVMContext& c) const override;

        bool                              definesIndirection() override;
        lang::ResolvingHandle<lang::Type> getIndirectionType() override;
        bool validateIndirection(lang::Location location, ValidationLogger& validation_logger) const override;
        std::shared_ptr<lang::Value> buildIndirection(std::shared_ptr<Value> value, CompileContext& context) override;

      private:
        lang::ResolvingHandle<lang::Type> value_type_;
        lang::ResolvingHandle<lang::Type> value_reference_;
    };
}

#endif
