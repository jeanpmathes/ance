#ifndef ANCE_SRC_LANG_CONSTRUCT_DESCRIPTIONS_STRUCTDESCRIPTION_H_
#define ANCE_SRC_LANG_CONSTRUCT_DESCRIPTIONS_STRUCTDESCRIPTION_H_

#include "Description.h"

#include "lang/AccessModifier.h"
#include "lang/construct/Member.h"
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
     * Describes a struct.
     */
    class StructDescription
        : public virtual Description
        , public Element<StructDescription, ANCE_CONSTRUCTS>
    {
      public:
        StructDescription(lang::AccessModifier             access,
                          Identifier                       name,
                          std::vector<Owned<lang::Member>> members,
                          lang::Location                   definition_location);

        ~StructDescription() override = default;

        [[nodiscard]] Identifier const&                                       name() const override;
        [[nodiscard]] lang::AccessModifier                                    access() const;
        [[nodiscard]] std::vector<std::reference_wrapper<const lang::Member>> members() const;
        [[nodiscard]] bool                                                    isOverloadAllowed() const override;

        void validate(ValidationLogger& validation_logger) const override;

        [[nodiscard]] Descriptions expand(lang::Context& new_context) const override;

      protected:
        void performInitialization() override;

      private:
        lang::AccessModifier             access_;
        Identifier                       name_;
        std::vector<Owned<lang::Member>> members_;
        lang::Location                   definition_location_;

        Optional<lang::ResolvingHandle<lang::Type>> self_ = {};
    };
}

#endif
