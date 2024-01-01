#ifndef ANCE_SRC_LANG_CONSTRUCT_GLOBALVARIABLE_H_
#define ANCE_SRC_LANG_CONSTRUCT_GLOBALVARIABLE_H_

#include "VariableDefinition.h"

#include <string>
#include <variant>

#include <llvm/IR/LLVMContext.h>

#include "compiler/Execution.h"
#include "lang/AccessModifier.h"
#include "lang/Assigner.h"
#include "lang/Element.h"

namespace lang
{
    class Constant;
    class Type;
    class GlobalScope;
    class Variable;
}

class ConstantExpression;

namespace lang
{
    /**
     * A global variable.
     */
    class GlobalVariable
        : public VariableDefinition
    {
      public:
        /**
         * Create a new global variable definition.
         */
        GlobalVariable(lang::ResolvingHandle<lang::Variable> self,
                       lang::ResolvingHandle<lang::Type>     type,
                       lang::Location                        type_location,
                       Scope&                                containing_scope,
                       lang::AccessModifier                  access,
                       bool                                  is_import,
                       lang::Initializer                     init,
                       lang::Scope*                          init_scope,
                       Assigner                              assigner,
                       bool                                  is_constant,
                       lang::Location                        location);

        [[nodiscard]] lang::AccessModifier access() const;
        [[nodiscard]] bool                 isConstant() const;
        [[nodiscard]] lang::Assigner       assigner() const;

        void buildDeclaration(CompileContext& context) override;
        void buildInitialization(CompileContext& context) override;
        void buildFinalization(CompileContext& context) override;

        Shared<lang::Value> getValuePointer(CompileContext& context) override;

      protected:
        void storeValue(Shared<lang::Value> value, CompileContext& context) override;

      private:
        lang::AccessModifier access_;
        bool                 is_import_;
        bool                 is_constant_;
        Initializer          init_;
        lang::Scope*         init_scope_;
        Assigner             assigner_;

        Optional<Execution::GlobalVariable> variable_handle_;
        bool                  finalized_ {false};
    };
}

#endif
