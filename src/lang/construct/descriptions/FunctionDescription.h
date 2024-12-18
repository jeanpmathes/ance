#ifndef ANCE_SRC_LANG_CONSTRUCT_DESCRIPTIONS_FUNCTIONDESCRIPTION_H_
#define ANCE_SRC_LANG_CONSTRUCT_DESCRIPTIONS_FUNCTIONDESCRIPTION_H_

#include "Description.h"

#include "lang/AccessModifier.h"
#include "lang/CMP.h"
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
     * A function description.
     */
    class FunctionDescription
        : public virtual Description
        , public Element<FunctionDescription, ANCE_CONSTRUCTS>
    {
      public:
        /**
         * Create a new function description.
         * @param accessibility The access modifier.
         * @param cmp The compile-time execution mode.
         * @param name The name.
         * @param return_type The return type.
         * @param return_type_location The location of the return type.
         * @param parameters The parameters.
         * @param code The code.
         * @param declaration_location The location of the declaration.
         * @param definition_location The location of the definition. Use the declaration location if there is no definition.
         */
        FunctionDescription(lang::Accessibility                  accessibility,
                            lang::CMP                            cmp,
                            lang::Identifier                     name,
                            lang::ResolvingHandle<lang::Type>    return_type,
                            lang::Location                       return_type_location,
                            std::vector<Shared<lang::Parameter>> parameters,
                            Optional<Owned<Statement>>           code,
                            lang::Location                       declaration_location,
                            lang::Location                       definition_location);

        /**
         * The import constructor.
         */
        explicit FunctionDescription(bool from_public_import);

        ~FunctionDescription() override = default;

        [[nodiscard]] Identifier const& name() const override;
        [[nodiscard]] bool              isOverloadAllowed() const override;
        [[nodiscard]] lang::CMP         cmp() const override;

        [[nodiscard]] lang::Function const* function() const;
        [[nodiscard]] Statement const*      code() const;

        [[nodiscard]] std::vector<std::reference_wrapper<Entity const>> getProvidedEntities() const override;
        [[nodiscard]] std::vector<Dependency>                           getDeclarationDependencies() const override;
        [[nodiscard]] std::vector<Dependency>                           getDefinitionDependencies() const override;

        void resolveDeclaration() override;
        void resolveDefinition() override;
        void postResolve() override;

        void validate(ValidationLogger& validation_logger) const override;

        [[nodiscard]] Descriptions expand(lang::Context& new_context) const override;

      protected:
        void setUp() override;
        void sync(Storage& storage) override;

      private:
        lang::CMP                            cmp_;
        lang::Identifier                     name_;
        lang::ResolvingHandle<lang::Type>    return_type_;
        lang::Location                       return_type_location_;
        std::vector<Shared<lang::Parameter>> parameters_;
        Optional<Owned<Statement>>           code_;
        lang::Location                       declaration_location_;
        lang::Location                       definition_location_;

        Optional<lang::ResolvingHandle<lang::Function>> function_;
    };
}

#endif
