#ifndef ANCE_SRC_LANG_CONSTRUCT_CUSTOMFUNCTION_H_
#define ANCE_SRC_LANG_CONSTRUCT_CUSTOMFUNCTION_H_

#include "StatementFunction.h"

#include <list>
#include <optional>
#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "lang/AccessModifier.h"
#include "lang/Element.h"
#include "lang/construct/CodeBlock.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    class LocalScope;
    class Function;
    class Variable;
}

class Statement;
class Execution;

namespace lang
{
    /**
     * A function that is defined in code.
     */
    class CustomFunction : public lang::StatementFunction
    {
      public:
        CustomFunction(Function&                            function,
                       lang::AccessModifier                 access,
                       bool                                 is_cmp,
                       lang::ResolvingHandle<lang::Type>    return_type,
                       lang::Location                       return_type_location,
                       std::vector<Shared<lang::Parameter>> parameters,
                       Statement&                           code,
                       Scope&                               containing_scope,
                       lang::Location                       declaration_location,
                       lang::Location                       definition_location);

        [[nodiscard]] bool isMangled() const override;

      protected:
        Optional<lang::Location> getDefinitionLocation() const override;
        bool                     preserveUnitReturn() const override;

      public:
        bool validateFlow(ValidationLogger& validation_logger) const override;

      protected:
        using FunctionDefinition::execCall;

      private:
        void validateReturn(ValidationLogger& validation_logger) const;
        void validateUnreachable(ValidationLogger& validation_logger) const;

      private:
        lang::Location definition_location_;
    };
}

#endif
