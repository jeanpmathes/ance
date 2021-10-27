#ifndef ANCE_SRC_ANCE_SCOPE_LOCALSCOPE_H_
#define ANCE_SRC_ANCE_SCOPE_LOCALSCOPE_H_

#include "Scope.h"

#include "ance/Assigner.h"
#include "ance/construct/LocalVariable.h"
#include "ance/utility/Location.h"

class Expression;

namespace ance
{
    /**
     * A local scope with local variables. Can be used by functions and similar constructs.
     */
    class LocalScope : public Scope
    {
      public:
        /**
         * Create a new local scope.
         * @param parent The parent scope containing this scope.
         */
        explicit LocalScope(ance::Scope* parent);

        ance::GlobalScope* getGlobalScope() override;
        llvm::DIScope*     getDebugScope(CompileContext* context) override;

        [[nodiscard]] ance::Scope* scope() const;

        void validate(ValidationLogger& validation_logger) override;

        ance::Variable* getVariable(std::string identifier) override;

        /**
         * Build all variable declarations.
         * @param context The current compile context.
         */
        void buildDeclarations(CompileContext* context);

        bool        isTypeRegistered(const std::string& type_name) override;
        ance::Type* getType(const std::string& type_name) override;
        void        registerType(ance::Type* type) override;

        /**
         * Define a local variable that is not a parameter.
         * @param identifier The identifier.
         * @param type The type.
         * @param assigner The assigner to use for initial assignment.
         * @param value The initial value.
         * @param location The source location.
         * @return The defined variable or null if defining is not possible.
         */
        ance::Variable* defineAutoVariable(const std::string&                  identifier,
                                           ance::Type*                         type,
                                           Assigner                            assigner,
                                           const std::shared_ptr<ance::Value>& value,
                                           ance::Location                      location);

        /**
         * Define a local variable that is a parameter.
         * @param identifier The identifier.
         * @param type The type.
         * @param assigner The assigner to use for initial assignment.
         * @param value The initial value.
         * @param parameter_no The number of the parameter. Counting starts with one.
         * @param location The source location.
         * @return The defined variable or null if defining is not possible.
         */
        ance::Variable* defineParameterVariable(const std::string&                  identifier,
                                                ance::Type*                         type,
                                                Assigner                            assigner,
                                                const std::shared_ptr<ance::Value>& value,
                                                unsigned                            parameter_no,
                                                ance::Location                      location);

      private:
        ance::Variable* defineLocalVariable(const std::string&                  identifier,
                                            ance::Type*                         type,
                                            Assigner                            assigner,
                                            const std::shared_ptr<ance::Value>& value,
                                            unsigned                            parameter_no,
                                            ance::Location                      location);

      private:
        ance::Scope* parent_;

        std::map<std::string, std::unique_ptr<ance::Variable>> local_variables_;
    };
}
#endif
