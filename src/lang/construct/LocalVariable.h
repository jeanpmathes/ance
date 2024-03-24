#ifndef ANCE_SRC_LANG_CONSTRUCT_LOCALVARIABLE_H_
#define ANCE_SRC_LANG_CONSTRUCT_LOCALVARIABLE_H_

#include "VariableDefinition.h"

#include <memory>
#include <string>

#include "compiler/Execution.h"
#include "lang/Assigner.h"
#include "lang/Element.h"

namespace lang
{
    class Value;
    class LocalScope;
}

namespace lang
{
    /**
     * A local variable or function parameter definition.
     */
    class LocalVariable : public lang::VariableDefinition
    {
      public:
        /**
         * Create a new local variable definition.
         */
        LocalVariable(lang::ResolvingHandle<lang::Variable> self,
                      lang::ResolvingHandle<lang::Type>     type,
                      lang::Location                        type_location,
                      Scope&                                containing_scope,
                      bool                                  is_final,
                      lang::LocalInitializer                init,
                      Optional<size_t>                      parameter_index,
                      lang::Location                        location);

        static lang::OwningHandle<lang::Variable> makeLocalVariable(Identifier const&                 name,
                                                                    lang::ResolvingHandle<lang::Type> type,
                                                                    lang::Location                    type_location,
                                                                    lang::Assigner                    assigner,
                                                                    Expression*                       init,
                                                                    lang::Scope&                      containing_scope,
                                                                    lang::Location                    location);

        static lang::OwningHandle<lang::Variable> makeParameterVariable(lang::Parameter& parameter,
                                                                        size_t           parameter_index,
                                                                        lang::Function&  containing_function);

        void buildDeclaration(Execution& exec) const override;
        void buildInitialization(Execution& exec) const override;
        void buildFinalization(Execution& exec) const override;

        Shared<lang::Value> getValuePointer(Execution& exec) const override;

      private:
        lang::LocalInitializer initializer_;
        Optional<size_t>       parameter_index_;
    };
}
#endif
