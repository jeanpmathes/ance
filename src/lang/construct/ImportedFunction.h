#ifndef ANCE_SRC_LANG_CONSTRUCT_IMPORTEDFUNCTION_H_
#define ANCE_SRC_LANG_CONSTRUCT_IMPORTEDFUNCTION_H_

#include "FunctionDefinition.h"

#include "lang/Element.h"

namespace lang
{
    class Function;
}

namespace lang
{
    /**
     * A function that is just declared, the actual definition is provided externally when linking.
     */
    class ImportedFunction : public lang::FunctionDefinition
    {
      public:
        ImportedFunction(Function&                            function,
                         Scope&                               containing_scope,
                         lang::AccessModifier                 access,
                         lang::ResolvingHandle<lang::Type>    return_type,
                         lang::Location                       return_type_location,
                         std::vector<Shared<lang::Parameter>> parameters,
                         lang::Location                       location);

        void setup() override;

        [[nodiscard]] bool isMangled() const override;
        [[nodiscard]] bool isImported() const override;
        [[nodiscard]] AccessModifier     access() const override;

      protected:
        Optional<lang::Location> getDefinitionLocation() const override;
        bool                     preserveUnitReturn() const override;

      public:
        void determineFlow() override;
        bool validateFlow(ValidationLogger& validation_logger) const override;

        [[nodiscard]] std::vector<lang::BasicBlock*> const& getBasicBlocks() const override;

      private:
        lang::AccessModifier access_;
    };
}

#endif
