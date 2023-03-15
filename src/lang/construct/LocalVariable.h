#ifndef ANCE_SRC_LANG_CONSTRUCT_LOCALVARIABLE_H_
#define ANCE_SRC_LANG_CONSTRUCT_LOCALVARIABLE_H_

#include "VariableDefinition.h"

#include <memory>
#include <string>

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
                      unsigned                              parameter_no,
                      lang::Location                        location);

        void buildDeclaration(CompileContext& context) override;
        void buildDefinition(CompileContext& context) override;
        void buildFinalization(CompileContext& context) override;

        Shared<lang::Value> getValue(CompileContext& context) override;

      protected:
        void storeValue(Shared<lang::Value> value, CompileContext& context) override;

      private:
        Optional<Shared<lang::Value>> initial_value_;
        unsigned                      parameter_no_;

        llvm::Value*           native_value_ {};
        llvm::DILocalVariable* local_debug_variable_ {nullptr};
    };
}
#endif
