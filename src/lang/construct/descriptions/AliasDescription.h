#ifndef ANCE_SRC_LANG_CONSTRUCT_DESCRIPTIONS_ALIASDESCRIPTION_H_
#define ANCE_SRC_LANG_CONSTRUCT_DESCRIPTIONS_ALIASDESCRIPTION_H_

#include "Description.h"

#include "lang/AccessModifier.h"
#include "lang/utility/Identifier.h"
#include "lang/utility/Location.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    class Type;
    class Parameter;
}

namespace lang
{
    /**
     * Describes a type alias.
     */
    class AliasDescription
        : public virtual Description
        , public Element<AliasDescription, ANCE_CONSTRUCTS>
    {
      public:
        AliasDescription(lang::AccessModifier              access,
                         Identifier                        name,
                         lang::ResolvingHandle<lang::Type> actual,
                         lang::Location                    definition_location,
                         lang::Location                    actual_type_location);

        ~AliasDescription() override = default;

        [[nodiscard]] Identifier const& name() const override;
        [[nodiscard]] bool              isOverloadAllowed() const override;

        void validate(ValidationLogger& validation_logger) const override;

        [[nodiscard]] Descriptions expand() const override;

      protected:
        void performInitialization() override;

      private:
        lang::AccessModifier              access_;
        Identifier                        name_;
        lang::ResolvingHandle<lang::Type> actual_;
        lang::Location                    definition_location_;
        lang::Location                    actual_type_location_;

        Optional<lang::ResolvingHandle<lang::Type>> self_ = {};
    };
}

#endif
