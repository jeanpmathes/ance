#ifndef ANCE_SRC_LANG_CONSTRUCT_GLOBALVARIABLE_H_
#define ANCE_SRC_LANG_CONSTRUCT_GLOBALVARIABLE_H_

#include "VariableDefinition.h"

#include <string>

#include <llvm/IR/LLVMContext.h>

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
        using Initializer =
            Optional<std::variant<std::reference_wrapper<lang::Function>, std::reference_wrapper<ConstantExpression>>>;

        /**
         * Create a new global variable definition.
         */
        GlobalVariable(lang::ResolvingHandle<lang::Variable> self,
                       lang::ResolvingHandle<lang::Type>     type,
                       lang::Location                        type_location,
                       Scope&                                containing_scope,
                       lang::AccessModifier                  access,
                       bool                                  is_import,
                       Initializer                           init,
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

        Shared<lang::Value> getValue(CompileContext& context) override;

      protected:
        void storeValue(Shared<lang::Value> value, CompileContext& context) override;

      private:
        lang::AccessModifier access_;
        bool                 is_import_;
        bool                 is_constant_;
        Initializer          init_;
        lang::Scope*         init_scope_;
        Assigner             assigner_;

        llvm::GlobalVariable* native_variable_ {nullptr};
        bool                  finalized_ {false};
    };
}

#endif
