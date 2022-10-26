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
        GlobalVariable(lang::ResolvingHandle<lang::Variable>            self,
                       std::optional<lang::ResolvingHandle<lang::Type>> type,
                       lang::Location                                   type_location,
                       GlobalScope&                                     containing_scope,
                       lang::AccessModifier                             access,
                       std::unique_ptr<Expression>                      init,
                       bool                                             is_final,
                       bool                                             is_constant,
                       lang::Location                                   location);

        [[nodiscard]] lang::AccessModifier access() const;
        [[nodiscard]] bool                 isConstant() const;
        [[nodiscard]] lang::Assigner       assigner() const;
        [[nodiscard]] Expression*          init() const;

        void validate(ValidationLogger& validation_logger) const override;

        void expand() override;
        void determineFlow() override;
        void validateFlow(ValidationLogger& validation_logger) const override;
        void resolve() override;
        void postResolve() override;
        void createNativeBacking(CompileContext& context) override;
        void build(CompileContext& context) override;

        [[nodiscard]] std::set<lang::ResolvingHandle<lang::Function>> getFunctionDependencies() const override;
        [[nodiscard]] std::set<lang::ResolvingHandle<lang::Variable>> getVariableDependencies() const override;

        /**
         * Get all variable dependencies of a variable by traversing the function dependencies.
         * @param variable The variable to get the dependencies for.
         * @return The dependencies.
         */
        static std::set<lang::ResolvingHandle<lang::Variable>> getAllVariableDependencies(
            lang::ResolvingHandle<lang::Variable> variable);

        /**
         * Determine the initialization order for global variables. If no order is possible, the validation logger will be used.
         * @param variables The variables to determine the order for.
         * @param validation_logger The validation logger to log errors to.
         * @return The order, or an empty vector if no order is possible.
         */
        static std::vector<lang::ResolvingHandle<lang::Variable>> determineOrder(
            std::vector<lang::ResolvingHandle<lang::Variable>> variables,
            ValidationLogger&                                  validation_logger);

        void buildDeclaration(CompileContext& context) override;
        void buildDefinition(CompileContext& context) override;
        void buildFinalization(CompileContext& context) override;

        std::shared_ptr<lang::Value> getValue(CompileContext& context) override;

      protected:
        void storeValue(std::shared_ptr<lang::Value> value, CompileContext& context) override;

      private:
        void rerouteIfNeeded();

        std::optional<lang::ResolvingHandle<lang::Type>>  type_opt_;
        lang::AccessModifier                              access_;
        bool                                              is_constant_;
        ConstantExpression*                               constant_init_;
        Expression*                                       init_;
        std::unique_ptr<Expression>                       init_owner_;
        std::optional<lang::OwningHandle<lang::Function>> init_function_;

        llvm::GlobalVariable* native_variable_ {nullptr};
        bool                  finalized_ {false};
    };
}

#endif

