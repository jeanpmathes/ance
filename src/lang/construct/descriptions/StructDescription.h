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
        StructDescription(lang::Accessibility              accessibility,
                          Identifier                       name,
                          std::vector<Owned<lang::Member>> members,
                          lang::Location                   definition_location);

        explicit StructDescription(bool from_public_import);

        ~StructDescription() override = default;

        [[nodiscard]] Identifier const&                                       name() const override;
        [[nodiscard]] std::vector<std::reference_wrapper<lang::Member const>> members() const;
        [[nodiscard]] bool                                                    isOverloadAllowed() const override;
        [[nodiscard]] bool                                                    isCMP() const override;

        [[nodiscard]] lang::Type const& type() const;

        [[nodiscard]] std::vector<std::reference_wrapper<Entity const>> getProvidedEntities() const override;
        [[nodiscard]] std::vector<Dependency>                           getDeclarationDependencies() const override;
        [[nodiscard]] std::vector<Dependency>                           getDefinitionDependencies() const override;

        void resolveDeclaration() override;
        void resolveDefinition() override;
        void postResolve() override;

        void validate(ValidationLogger& validation_logger) const override;

        [[nodiscard]] Descriptions expand(lang::Context& new_context) const override;

      protected:
        void performInitialization() override;
        void sync(Storage& storage) override;

      private:
        Identifier                       name_;
        std::vector<Owned<lang::Member>> members_;
        lang::Location                   definition_location_;

        lang::ResolvingHandle<lang::Type> self_;
        Optional<Owned<Scope>>            struct_scope_ = {};
    };
}

#endif
