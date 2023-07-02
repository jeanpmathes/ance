#ifndef ANCE_SRC_LANG_SCOPE_ORDEREDSCOPE_H_
#define ANCE_SRC_LANG_SCOPE_ORDEREDSCOPE_H_

#include "Scope.h"

#include <set>

#include "lang/Assigner.h"
#include "lang/utility/Identifier.h"

namespace lang
{
    /**
     * A scope in which the order of definitions matters.
     * Redefinitions of names are allowed.
     */
    class OrderedScope : public virtual Scope
    {
      public:
        OrderedScope* asOrderedScope() override;

        [[nodiscard]] bool isNameConflicted(lang::Identifier const& name) const override;

        void addDescription(Owned<lang::Description> description) override;
        void addFunction(lang::OwningHandle<lang::Function> function) override;
        void addVariable(lang::OwningHandle<lang::Variable> variable) override;
        void addType(lang::OwningHandle<lang::Type> type) override;

        /**
         * Prepare the definition of a new variable. This will block resolution above this scope.
         * @param name The name of the variable.
         */
        void prepareDefinition(Identifier name);

        /**
         * Drop a variable. A variable must be defined in this scope to be dropped.
         * @param variable The variable to drop.
         * @return True if the variable was dropped, false otherwise.
         */
        bool drop(lang::ResolvingHandle<lang::Variable> variable);

        /**
         * Check if a variable with the specified name was defined and then dropped.
         * @param variable The variable to check.
         * @return True if the variable was dropped, false otherwise.
         */
        [[nodiscard]] bool wasVariableDropped(lang::Variable const& variable) const;

        void registerUsage(lang::ResolvingHandle<lang::Variable> variable) override;
        void registerUsage(lang::ResolvingHandle<lang::FunctionGroup> function_group) override;
        void registerUsage(lang::ResolvingHandle<lang::Type> type) override;

        void registerDefinition(lang::ResolvingHandle<lang::Type> type) override;

        Optional<OwningHandle<lang::Variable>> connectWithDefinitionAccordingToOrdering(
            lang::OwningHandle<lang::Variable> variable) override;

        void resolve() override;
        void postResolve() override;

        bool resolveDefinition(lang::ResolvingHandle<lang::Variable> variable) override;
        bool resolveDefinition(lang::ResolvingHandle<lang::FunctionGroup> function_group) override;
        bool resolveDefinition(lang::ResolvingHandle<lang::Type> type) override;

        /**
         * Build all variable declarations.
         * @param context The current compile context.
         */
        void buildDeclarations(CompileContext& context);
        void buildFinalization(CompileContext& context) override;

      protected:
        void onSubScope(Scope* sub_scope) override;

      private:
        std::set<lang::Identifier> blockers_ {};

        std::map<lang::Identifier, lang::OwningHandle<lang::Variable>>              undefined_variables_ {};
        std::map<lang::Identifier, lang::OwningHandle<lang::Variable>>              blocked_variables_ {};
        std::map<lang::Identifier, std::vector<lang::OwningHandle<lang::Variable>>> defined_variables_ {};

        std::map<lang::Identifier, lang::ResolvingHandle<lang::Variable>> active_variables_ {};

        std::map<lang::Identifier, lang::OwningHandle<lang::FunctionGroup>>         undefined_function_groups_ {};
        std::map<lang::Identifier, lang::OwningHandle<lang::FunctionGroup>>         blocked_function_groups_ {};
        std::map<lang::Identifier, std::vector<lang::OwningHandle<lang::Function>>> defined_functions_ {};

        std::map<lang::Identifier, lang::OwningHandle<lang::Type>>              undefined_types_ {};
        std::map<lang::Identifier, lang::OwningHandle<lang::Type>>              blocked_types_ {};
        std::map<lang::Identifier, std::vector<lang::OwningHandle<lang::Type>>> defined_types_ {};

        std::map<lang::Identifier, std::vector<Owned<lang::Description>>> descriptions_ {};

        std::vector<lang::Scope*> sub_scopes_;
    };
}

#endif
