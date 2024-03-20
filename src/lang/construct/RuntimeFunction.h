#ifndef ANCE_SRC_LANG_CONSTRUCT_RUNTIMEFUNCTION_H_
#define ANCE_SRC_LANG_CONSTRUCT_RUNTIMEFUNCTION_H_

#include "FunctionDefinition.h"

#include "lang/Element.h"

namespace lang
{
    class Function;
}

namespace lang
{
    class RuntimeFunction : public lang::FunctionDefinition
    {
      public:
        RuntimeFunction(Function&                            function,
                        lang::ResolvingHandle<lang::Type>    return_type,
                        std::vector<Shared<lang::Parameter>> parameters,
                        CompileContext&                      context);

        void setup() override;

        [[nodiscard]] bool isMangled() const override;
        [[nodiscard]] bool isRuntime() const override;
        [[nodiscard]] bool isImported() const override;

      protected:
        Optional<lang::Location> getDefinitionLocation() const override;
        bool                     preserveUnitReturn() const override;

      public:
        void determineFlow() override;
        bool validateFlow(ValidationLogger& validation_logger) const override;

        [[nodiscard]] std::vector<lang::BasicBlock*> const& getBasicBlocks() const override;
    };
}

#endif
