#ifndef ANCE_SRC_LANG_SCOPE_LOCALSCOPE_H_
#define ANCE_SRC_LANG_SCOPE_LOCALSCOPE_H_

#include "Scope.h"

#include <optional>

#include "lang/Assigner.h"
#include "lang/construct/FunctionGroup.h"
#include "lang/construct/Variable.h"
#include "lang/type/Type.h"
#include "lang/utility/Location.h"
#include "lang/utility/OwningHandle.h"
#include "lang/Assigner.h"
#include "lang/Element.h"

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
        llvm::DIScope*     getDebugScope(CompileContext* context) override;

        [[nodiscard]] lang::Scope* scope() const;

        /**
         * Define a local variable that is not a parameter.
         * @param identifier The identifier.
         * @param type The type.
         * @param type_location The location of the type.
         * @param assigner The assigner to use for initial assignment.
         * @param value The initial value.
         * @param location The source location.
         * @return The defined variable or nothing if defining is not possible.
         */
        std::optional<lang::ResolvingHandle<lang::Variable>> defineAutoVariable(
            const std::string&                  identifier,
            lang::ResolvingHandle<lang::Type>   type,
            lang::Location                      type_location,
            lang::Assigner                      assigner,
            const std::shared_ptr<lang::Value>& value,
            lang::Location                      location);

        /**
         * Define a local variable that is a parameter.
         * @param identifier The identifier.
         * @param type The type.
         * @param type_location The source location of the type.
         * @param value The initial value.
         * @param parameter_no The number of the parameter. Counting starts with one.
         * @param location The source location.
         * @return The defined variable or nothing if defining is not possible.
         */
        std::optional<lang::ResolvingHandle<lang::Variable>> defineParameterVariable(
            const std::string&                  identifier,
            lang::ResolvingHandle<lang::Type>   type,
            lang::Location                      type_location,
            const std::shared_ptr<lang::Value>& value,
            unsigned                            parameter_no,
            lang::Location                      location);

        void registerUsage(lang::ResolvingHandle<lang::Variable> variable) override;
        void registerUsage(lang::ResolvingHandle<lang::FunctionGroup> function_group) override;
        void registerUsage(lang::ResolvingHandle<lang::Type> type) override;

        void registerDefinition(lang::ResolvingHandle<lang::Type> type) override;

        void resolve() override;

      protected:
        bool resolveDefinition(lang::ResolvingHandle<lang::Variable> variable) override;
        bool resolveDefinition(lang::ResolvingHandle<lang::FunctionGroup> function_group) override;
        bool resolveDefinition(lang::ResolvingHandle<lang::Type> type) override;

      public:
        void validate(ValidationLogger& validation_logger) override;

        /**
         * Build all variable declarations.
         * @param context The current compile context.
         */
        void buildDeclarations(CompileContext* context);

      private:
        std::optional<lang::ResolvingHandle<lang::Variable>> defineLocalVariable(
            const std::string&                  identifier,
            lang::ResolvingHandle<lang::Type>   type,
            lang::Location                      type_location,
            lang::Assigner                      assigner,
            const std::shared_ptr<lang::Value>& value,
            unsigned                            parameter_no,
            lang::Location                      location);

      private:
        lang::Scope* parent_;

        std::map<std::string, lang::OwningHandle<lang::Variable>> undefined_variables_;
        std::map<std::string, lang::OwningHandle<lang::Variable>> defined_local_variables_;

        std::map<std::string, lang::OwningHandle<lang::FunctionGroup>> undefined_function_groups_;

        std::map<std::string, lang::OwningHandle<lang::Type>> undefined_types_;
    };
}
#endif