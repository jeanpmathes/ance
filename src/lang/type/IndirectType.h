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

        bool                definesIndirection() const override;
        lang::Type const& getIndirectionType() const override;
        bool validateIndirection(lang::Location location, ValidationLogger& validation_logger) const override;
        Shared<lang::Value> buildIndirection(Shared<lang::Value> value, CompileContext& context) const override;

      private:
        lang::ResolvingHandle<lang::Type> value_type_;
    };
}

#endif
