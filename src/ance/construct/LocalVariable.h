#ifndef ANCE_SRC_ANCE_CONSTRUCT_LOCALVARIABLE_H_
#define ANCE_SRC_ANCE_CONSTRUCT_LOCALVARIABLE_H_

#include "Variable.h"

namespace ance
{
    class Value;
    class LocalScope;
}

namespace ance
{
    /**
     * A local variable or function parameter.
     */
    class LocalVariable : public ance::Variable
    {
      public:
        /**
         * Create a new local variable.
         * @param containing_scope The containing scope.
         * @param identifier The identifier of the variable.
         * @param type The type.
         * @param value The initial value.
         * @param is_final Whether the variable is final.
         * @param parameter_no The parameter number. Use zero if this is not a parameter.
         * @param location The source location.
         */
        LocalVariable(ance::LocalScope*            containing_scope,
                      std::string                  identifier,
                      ance::Type*                  type,
                      std::shared_ptr<ance::Value> value,
                      bool                         is_final,
                      unsigned                     parameter_no,
                      ance::Location               location);

        [[nodiscard]] ance::Location location() const override;

        void validate(ValidationLogger& validation_logger) override;

        /**
         * Build the local variable declaration which prepares the storage.
         * @param context The current compile context.
         */
        void buildDeclaration(CompileContext* context);

        /**
         * Build the local variable definition which initializes the storage.
         * @param context The current compile context.
         */
        void buildDefinition(CompileContext* context);

        std::shared_ptr<ance::Value> getValue(CompileContext* context) override;

        bool accept(ance::ApplicationVisitor& visitor) override;

      protected:
        void storeValue(std::shared_ptr<ance::Value> value, CompileContext* context) override;

      private:
        void store(std::shared_ptr<ance::Value> value, CompileContext* context);

      private:
        std::shared_ptr<ance::Value> initial_value_;
        ance::LocalScope*            containing_scope_;

        unsigned       parameter_no_;
        ance::Location location_;

        llvm::Value*           native_value_ {};
        llvm::DILocalVariable* local_debug_variable_ {nullptr};
    };
}
#endif