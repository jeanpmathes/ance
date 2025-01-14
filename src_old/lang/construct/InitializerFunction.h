#ifndef ANCE_SRC_LANG_CONSTRUCT_INITIALIZERFUNCTION_H_
#define ANCE_SRC_LANG_CONSTRUCT_INITIALIZERFUNCTION_H_

#include "StatementFunction.h"

#include <list>
#include <optional>
#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "lang/AccessModifier.h"
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
     * A function that initializes a (global) variable.
     */
    class InitializerFunction : public lang::StatementFunction
    {
      public:
        InitializerFunction(Function&                         function,
                            Statement&                        initializer,
                            lang::CMP                         cmp,
                            lang::ResolvingHandle<lang::Type> return_type,
                            Scope&                            containing_scope);

        [[nodiscard]] bool isMangled() const override;

      protected:
        Optional<lang::Location> getDefinitionLocation() const override;
        bool                     preserveUnitReturn() const override;

      public:
        /**
         * Create a code block that initializes a global variable.
         * @param variable The variable to initialize.
         * @param assigner The assigner to use.
         * @param cmp The compile-time evaluation mode of the variable.
         * @param initializer The initializer expression, providing the value to assign.
         * @return The initializer block.
         */
        static Owned<Statement> makeInitializerBlock(lang::ResolvingHandle<lang::Variable> variable,
                                                     lang::Assigner                        assigner,
                                                     lang::CMP                             cmp,
                                                     Owned<Expression>                     initializer);
    };
}

#endif
