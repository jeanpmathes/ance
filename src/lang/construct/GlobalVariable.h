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
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    class Constant;
    class Type;
    class GlobalScope;
    class Variable;
}

class LiteralExpression;

namespace lang
{
    /**
     * A global variable.
     */
    class GlobalVariable : public VariableDefinition
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
                       lang::Function const*                 init,
                       Assigner                              assigner,
                       lang::CMP                             cmp,
                       lang::Location                        location);

        [[nodiscard]] lang::AccessModifier access() const;
        [[nodiscard]] bool                        isImported() const;
        [[nodiscard]] lang::Assigner       assigner() const;
        [[nodiscard]] lang::Function const*       initializer() const;

        [[nodiscard]] lang::CMP cmp() const override;

        void registerDeclaration(Execution& exec) const override;
        void registerDefinition(Execution& exec) const override;

        void performInitialization(Execution& exec) const override;
        void performFinalization(Execution& exec) const override;

        Shared<lang::Value> getValuePointer(Execution& exec) const override;

      private:
        lang::AccessModifier access_;
        bool                 is_import_;
        lang::CMP             cmp_;
        lang::Function const* init_;
        Assigner             assigner_;
    };
}

#endif
