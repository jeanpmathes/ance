#ifndef ANCE_SRC_LANG_CONSTRUCT_GLOBALVARIABLE_H_
#define ANCE_SRC_LANG_CONSTRUCT_GLOBALVARIABLE_H_

#include "VariableDefinition.h"

#include <string>

#include <llvm/IR/LLVMContext.h>

#include "lang/AccessModifier.h"
#include "lang/Element.h"
#include "lang/Assigner.h"

namespace lang
{
    class Constant;
    class Type;
    class GlobalScope;
}

class ConstantExpression;

namespace lang
{
    /**
     * A global variable.
     */
    class GlobalVariable
        : public VariableDefinition
        , public lang::Element<GlobalVariable, ANCE_CONSTRUCTS>
    {
      public:
        /**
         * Create a new global variable definition.
         */
        GlobalVariable(const std::string&                  identifier,
                       lang::ResolvingHandle<lang::Type>   type,
                       lang::Location                      type_location,
                       lang::GlobalScope*                  containing_scope,
                       lang::AccessModifier                access,
                       std::unique_ptr<ConstantExpression> constant_init,
                       bool                                is_final,
                       bool                                is_constant,
                       lang::Location                      location);

        [[nodiscard]] lang::AccessModifier access() const;
        [[nodiscard]] bool                 isConstant() const;
        [[nodiscard]] lang::Assigner       assigner() const;
        [[nodiscard]] lang::Constant&      init() const;

        void validate(ValidationLogger& validation_logger) override;

        void buildDeclaration(CompileContext* context) override;
        void buildDefinition(CompileContext* context) override;

        std::shared_ptr<lang::Value> getValue(CompileContext* context) override;

      protected:
        void storeValue(std::shared_ptr<lang::Value> value, CompileContext* context) override;

      private:
        lang::AccessModifier                access_;
        bool                                is_constant_;
        std::unique_ptr<ConstantExpression> constant_init_;

        llvm::GlobalVariable*           native_variable_ {nullptr};
        std::shared_ptr<lang::Constant> initial_value_ {nullptr};
    };
}

#endif
