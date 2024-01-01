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
                      Optional<Shared<lang::Value>>         value,
                      Optional<unsigned>                    parameter_index,
                      lang::Location                        location);

        static lang::OwningHandle<lang::Variable> makeLocalVariable(Identifier const&                 name,
                                                                    lang::ResolvingHandle<lang::Type> type,
                                                                    lang::Location                    type_location,
                                                                    lang::Assigner                    assigner,
                                                                    Optional<Shared<lang::Value>>     value,
                                                                    lang::Scope&                      containing_scope,
                                                                    lang::Location                    location);

        static lang::OwningHandle<lang::Variable> makeParameterVariable(Identifier const&                 name,
                                                                        lang::ResolvingHandle<lang::Type> type,
                                                                        lang::Location                    type_location,
                                                                        Shared<lang::Value>               value,
                                                                        unsigned       parameter_index,
                                                                        lang::Scope&   containing_scope,
                                                                        lang::Location location);

        void buildDeclaration(CompileContext& context) override;
        void buildInitialization(CompileContext& context) override;
        void buildFinalization(CompileContext& context) override;

        Shared<lang::Value> getValuePointer(CompileContext& context) override;

      protected:
        void storeValue(Shared<lang::Value> value, CompileContext& context) override;

      private:
        Optional<Shared<lang::Value>> initial_value_;
        Optional<unsigned>            parameter_index_;

        Optional<Execution::LocalVariable> local_variable_;
    };
}
#endif
