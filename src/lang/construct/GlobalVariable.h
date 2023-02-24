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
        using Initializer =
            Optional<std::variant<std::reference_wrapper<lang::Function>, std::reference_wrapper<ConstantExpression>>>;

        /**
         * Create a new global variable definition.
         */
        GlobalVariable(lang::ResolvingHandle<lang::Variable> self,
                       lang::ResolvingHandle<lang::Type>     type,
                       lang::Location                        type_location,
                       GlobalScope&                          containing_scope,
                       lang::AccessModifier                  access,
                       Initializer                           init,
                       lang::Scope*                          init_scope,
                       Assigner                              assigner,
                       bool                                  is_constant,
                       lang::Location                        location);

        [[nodiscard]] lang::AccessModifier access() const;
        [[nodiscard]] bool                 isConstant() const;
        [[nodiscard]] lang::Assigner       assigner() const;

        [[nodiscard]] std::vector<lang::ResolvingHandle<lang::Function>> getFunctionDependencies() override;
        [[nodiscard]] std::vector<lang::ResolvingHandle<lang::Variable>> getVariableDependencies() override;

        /**
         * Get all variable dependencies of a variable by traversing the function dependencies.
         * @param variable The variable to get the dependencies for.
         * @return The dependencies.
         */
        static std::vector<lang::ResolvingHandle<lang::Variable>> getAllVariableDependencies(
            lang::ResolvingHandle<lang::Variable> variable);

        /**
         * Determine the initialization order for global variables. If no order is possible, the validation logger will be used.
         * @param variables The variables to determine the order for.
         * @param validation_logger The validation logger to log errors to. Pass null to ignore errors.
         * @return The order, or an empty vector if no order is possible.
         */
        static std::vector<lang::ResolvingHandle<lang::Variable>> determineOrder(
            std::vector<lang::ResolvingHandle<lang::Variable>> variables,
            ValidationLogger*                                  validation_logger);

        void buildDeclaration(CompileContext& context) override;
        void buildDefinition(CompileContext& context) override;
        void buildFinalization(CompileContext& context) override;

        Shared<lang::Value> getValue(CompileContext& context) override;

      protected:
        void storeValue(Shared<lang::Value> value, CompileContext& context) override;

      private:
        lang::AccessModifier access_;
        bool                 is_constant_;
        Initializer          init_;
        lang::Scope*         init_scope_;
        Assigner             assigner_;

        llvm::GlobalVariable* native_variable_ {nullptr};
        bool                  finalized_ {false};
    };
}

#endif
