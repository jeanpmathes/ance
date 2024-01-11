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

        llvm::Constant*    getDefaultContent(CompileContext& context) const override;
        llvm::PointerType* getContentType(CompileContext& context) const override;

        bool                              definesIndirection() const override;
        lang::ResolvingHandle<lang::Type> getIndirectionType() override;
        bool validateIndirection(lang::Location location, ValidationLogger& validation_logger) const override;
        Shared<lang::Value> buildIndirection(Shared<lang::Value> value, CompileContext& context) override;

      private:
        lang::ResolvingHandle<lang::Type> value_type_;
    };
}

#endif
