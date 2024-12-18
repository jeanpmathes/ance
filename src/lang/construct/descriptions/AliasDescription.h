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
        AliasDescription(lang::Accessibility               accessibility,
                         Identifier                        name,
                         lang::ResolvingHandle<lang::Type> actual,
                         lang::Location                    definition_location,
                         lang::Location                    actual_type_location);

        explicit AliasDescription(bool from_public_import);

        ~AliasDescription() override = default;

        [[nodiscard]] Identifier const& name() const override;
        [[nodiscard]] lang::Type const& actual() const;
        [[nodiscard]] bool              isOverloadAllowed() const override;
        [[nodiscard]] lang::CMP         cmp() const override;

        [[nodiscard]] lang::Type const& type() const;

        [[nodiscard]] std::vector<std::reference_wrapper<Entity const>> getProvidedEntities() const override;
        [[nodiscard]] std::vector<Dependency>                           getDeclarationDependencies() const override;
        [[nodiscard]] std::vector<Dependency>                           getDefinitionDependencies() const override;

        void validate(ValidationLogger& validation_logger) const override;

        [[nodiscard]] Descriptions expand(lang::Context& new_context) const override;

      protected:
        void setUp() override;
        void resolveDeclaration() override;
        void resolveDefinition() override;
        void sync(Storage& storage) override;

      private:
        Identifier                        name_;
        lang::ResolvingHandle<lang::Type> actual_;
        lang::Location                    definition_location_;
        lang::Location                    actual_type_location_;

        lang::ResolvingHandle<lang::Type> self_;
    };
}

#endif
