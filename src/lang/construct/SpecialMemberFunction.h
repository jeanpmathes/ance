#ifndef ANCE_SRC_LANG_CONSTRUCT_SPECIALMEMBERFUNCTION_H_
#define ANCE_SRC_LANG_CONSTRUCT_SPECIALMEMBERFUNCTION_H_

#include "FunctionDefinition.h"

#include "lang/Element.h"

namespace lang
{
    class Function;
}

namespace lang
{
    /**
     * Represents a special member function, such as a constructor or destructor.
     */
    class SpecialMemberFunction : public lang::FunctionDefinition
    {
      public:
        enum class Kind
        {
            DEFAULT_CONSTRUCTOR,
            COPY_CONSTRUCTOR,
            DEFAULT_DESTRUCTOR
        };

        SpecialMemberFunction(Function&                            function,
                              lang::ResolvingHandle<lang::Type> type,
                              std::vector<Shared<lang::Parameter>> parameters);

        void setup() override;

        static lang::ResolvingHandle<lang::Function> create(lang::ResolvingHandle<lang::Type>  type, Kind kind,
                                                            std::vector<Shared<lang::Parameter>> parameters);

        [[nodiscard]] bool isMangled() const override;
        [[nodiscard]] bool isRuntime() const override;
        [[nodiscard]] bool isImported() const override;

        [[nodiscard]] AccessModifier access() const override;

      protected:
        Optional<lang::Location> getDefinitionLocation() const override;
        bool                     preserveUnitReturn() const override;

      public:
        void determineFlow() override;
        bool validateFlow(ValidationLogger& validation_logger) const override;

        [[nodiscard]] std::vector<lang::BasicBlock*> const& getBasicBlocks() const override;

      private:
        lang::Type const& type_;
    };
}

#endif
