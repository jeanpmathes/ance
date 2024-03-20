#ifndef ANCE_SRC_LANG_CONSTRUCT_PREDEFINEDFUNCTION_H_
#define ANCE_SRC_LANG_CONSTRUCT_PREDEFINEDFUNCTION_H_

#include "FunctionDefinition.h"

#include "lang/Element.h"

namespace lang
{
    class Function;
}

namespace lang
{
    /**
     * A function that is defined by the language itself using native representation, not by source code.
     * Therefore a predefined function does not require some steps like resolving.
     */
    class PredefinedFunction : public lang::FunctionDefinition
    {
      public:
        PredefinedFunction(Function&                            function,
                           Scope&                               containing_scope,
                           lang::AccessModifier                 access_modifier,
                           bool                                 is_imported,
                           lang::ResolvingHandle<lang::Type>    return_type,
                           bool                                 is_constructor,
                           std::vector<Shared<lang::Parameter>> parameters,
                           lang::Location                       location);

        [[nodiscard]] bool           isMangled() const override;
        [[nodiscard]] bool           isImported() const override;
        [[nodiscard]] AccessModifier access() const override;

      protected:
        Optional<lang::Location> getDefinitionLocation() const override;
        bool                     preserveUnitReturn() const override;

      public:
        void determineFlow() override;
        bool validateFlow(ValidationLogger& validation_logger) const override;

        [[nodiscard]] std::vector<lang::BasicBlock*> const& getBasicBlocks() const override;

      public:
        void setCallValidator(std::function<bool(std::vector<std::reference_wrapper<Expression const>> const&,
                                                 lang::Location,
                                                 ValidationLogger&)> validator);
        bool doCallValidation(std::vector<std::reference_wrapper<Expression const>> const& arguments,
                              lang::Location                                               location,
                              ValidationLogger& validation_logger) const override;

      private:
        lang::AccessModifier access_modifier_;
        bool                 is_imported_;
        bool                 is_constructor_;

        std::function<
            bool(std::vector<std::reference_wrapper<Expression const>> const&, lang::Location, ValidationLogger&)>
            call_validator_ {};
    };
}

#endif
