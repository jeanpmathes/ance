#ifndef ANCE_SRC_LANG_CONSTRUCT_DESCRIPTIONS_FUNCTIONDESCRIPTION_H_
#define ANCE_SRC_LANG_CONSTRUCT_DESCRIPTIONS_FUNCTIONDESCRIPTION_H_

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
     * A function description.
     */
    class FunctionDescription
        : public virtual Description
        , public Element<FunctionDescription, ANCE_CONSTRUCTS>
    {
      public:
        /**
         * Create a new function description.
         * @param access The access modifier.
         * @param name The name.
         * @param return_type The return type.
         * @param return_type_location The location of the return type.
         * @param parameters The parameters.
         * @param code The code.
         * @param declaration_location The location of the declaration.
         * @param definition_location The location of the definition. Use the declaration location if there is no definition.
         * @param is_imported Whether the function is imported.
         */
        FunctionDescription(lang::AccessModifier                 access,
                            lang::Identifier                     name,
                            lang::ResolvingHandle<lang::Type>    return_type,
                            lang::Location                       return_type_location,
                            std::vector<Shared<lang::Parameter>> parameters,
                            Optional<Owned<Statement>>           code,
                            lang::Location                       declaration_location,
                            lang::Location                       definition_location,
                            bool                                 is_imported = false);

        /**
         * The import constructor.
         */
        FunctionDescription();

        ~FunctionDescription() override = default;

        [[nodiscard]] Identifier const& name() const override;
        [[nodiscard]] bool              isOverloadAllowed() const override;
        [[nodiscard]] AccessModifier    access() const override;
        [[nodiscard]] bool              isImported() const override;

        [[nodiscard]] lang::Function const* function() const;
        [[nodiscard]] Statement const*      code() const;

        void validate(ValidationLogger& validation_logger) const override;

        [[nodiscard]] Descriptions expand(lang::Context& new_context) const override;

      protected:
        void performInitialization() override;
        void sync(Storage& storage) override;

      private:
        bool                                 is_imported_;
        lang::AccessModifier                 access_;
        lang::Identifier                     name_;
        lang::ResolvingHandle<lang::Type>    return_type_;
        lang::Location                       return_type_location_;
        std::vector<Shared<lang::Parameter>> parameters_;
        Optional<Owned<Statement>>           code_;
        lang::Location                       declaration_location_;
        lang::Location                       definition_location_;

        lang::Function* function_ {nullptr};
    };
}

#endif
