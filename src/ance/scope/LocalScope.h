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

        [[nodiscard]] ance::Scope* scope() const override;

        [[nodiscard]] ance::Location location() const override;

        void validate(ValidationLogger& validation_logger) override;

        bool accept(ance::ApplicationVisitor& visitor) override;

        ance::Variable* getVariable(std::string identifier) override;

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
        ance::LocalVariable* defineAutoVariable(const std::string& identifier,
                                                ance::Type*        type,
                                                Assigner           assigner,
                                                ance::Value*       value,
                                                ance::Location     location);

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
        ance::LocalVariable* defineParameterVariable(const std::string& identifier,
                                                     ance::Type*        type,
                                                     Assigner           assigner,
                                                     ance::Value*       value,
                                                     unsigned           parameter_no,
                                                     ance::Location     location);

      private:
        ance::LocalVariable* defineLocalVariable(const std::string& identifier,
                                                 ance::Type*        type,
                                                 Assigner           assigner,
                                                 ance::Value*       value,
                                                 unsigned           parameter_no,
                                                 ance::Location     location);

      private:
        ance::Scope* parent_;

        std::map<std::string, ance::LocalVariable*> local_variables_;
    };
}
#endif
