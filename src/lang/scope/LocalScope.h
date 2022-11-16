#ifndef ANCE_SRC_LANG_SCOPE_LOCALSCOPE_H_
#define ANCE_SRC_LANG_SCOPE_LOCALSCOPE_H_

#include "Scope.h"

#include <optional>
#include <set>

#include "lang/Assigner.h"
#include "lang/Element.h"
#include "lang/construct/FunctionGroup.h"
#include "lang/construct/Variable.h"
#include "lang/type/Type.h"
#include "lang/utility/Location.h"
#include "lang/utility/OwningHandle.h"

class Expression;

namespace lang
{
    /**
     * A local scope with local variables. Can be used by functions and similar constructs.
     */
    class LocalScope
        : public Scope
        , public lang::Element<LocalScope, ANCE_CONSTRUCTS>
    {
      public:
        /**
         * Create a new local scope.
         * @param parent The parent scope containing this scope.
         */
        explicit LocalScope(lang::Scope* parent);

        lang::Scope* scope() override;

        lang::GlobalScope* getGlobalScope() override;
        lang::LocalScope*  asLocalScope() override;
        llvm::DIScope*     getDebugScope(CompileContext& context) override;

        [[nodiscard]] lang::Scope* scope() const;

        /**
         * Prepare the definition of a new variable. This will block resolution above this scope.
         * @param name The name of the variable.
         */
        void prepareDefinition(Identifier name);

        /**
         * Define a local variable. Parameters are not local variables and should be define in function scope.
         * If the name is already defined, the old variable will be dropped.
         * @param name The name.
         * @param type The type.
         * @param type_location The location of the type.
         * @param assigner The assigner to use for initial assignment.
         * @param value The initial value.
         * @param location The source location.
         * @return The defined variable.
         */
        lang::ResolvingHandle<lang::Variable> defineLocalVariable(Identifier                          name,
                                                                  lang::ResolvingHandle<lang::Type>   type,
                                                                  lang::Location                      type_location,
                                                                  lang::Assigner                      assigner,
                                                                  std::shared_ptr<lang::Value> const& value,
                                                                  lang::Location                      location);

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
        bool wasVariableDropped(lang::ResolvingHandle<lang::Variable> variable) const;

        void registerUsage(lang::ResolvingHandle<lang::Variable> variable) override;
        void registerUsage(lang::ResolvingHandle<lang::FunctionGroup> function_group) override;
        void registerUsage(lang::ResolvingHandle<lang::Type> type) override;

        void registerDefinition(lang::ResolvingHandle<lang::Type> type) override;

        void resolve() override;
        void postResolve() override;

      protected:
        bool resolveDefinition(lang::ResolvingHandle<lang::Variable> variable) override;
        bool resolveDefinition(lang::ResolvingHandle<lang::FunctionGroup> function_group) override;
        bool resolveDefinition(lang::ResolvingHandle<lang::Type> type) override;

        bool findExistingLocalDeclaration(lang::ResolvingHandle<lang::Variable> variable);

        void onSubScope(lang::LocalScope* sub_scope) override;

      public:
        void validate(ValidationLogger& validation_logger) const override;

        /**
         * Build all variable declarations.
         * @param context The current compile context.
         */
        void buildDeclarations(CompileContext& context);

        void buildFinalization(CompileContext& context) override;

        /**
         * Build all finalization of to the function.
         * @param context The current compile context.
         */
        void buildReturnFinalization(CompileContext& context);

      private:
        lang::Scope*                   parent_;
        std::vector<lang::LocalScope*> sub_scopes_;

        std::set<lang::Identifier> blockers_ {};

        std::map<lang::Identifier, lang::OwningHandle<lang::Variable>>              undefined_variables_ {};
        std::map<lang::Identifier, lang::OwningHandle<lang::Variable>>              blocked_variables_ {};
        std::map<lang::Identifier, std::vector<lang::OwningHandle<lang::Variable>>> defined_local_variables_ {};

        std::map<lang::Identifier, lang::ResolvingHandle<lang::Variable>> active_variables_ {};

        std::map<lang::Identifier, lang::OwningHandle<lang::FunctionGroup>> undefined_function_groups_ {};
        std::map<lang::Identifier, lang::OwningHandle<lang::FunctionGroup>> blocked_function_groups_ {};

        std::map<lang::Identifier, lang::OwningHandle<lang::Type>> undefined_types_ {};
        std::map<lang::Identifier, lang::OwningHandle<lang::Type>> blocked_types_ {};
    };
}
#endif
