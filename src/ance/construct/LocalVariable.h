#ifndef ANCE_SRC_ANCE_CONSTRUCT_LOCALVARIABLE_H_
#define ANCE_SRC_ANCE_CONSTRUCT_LOCALVARIABLE_H_

#include "VariableDefinition.h"

#include <memory>
#include <string>

namespace ance
{
    class Value;
    class LocalScope;
}

namespace ance
{
    /**
     * A local variable or function parameter definition.
     */
    class LocalVariable : public ance::VariableDefinition
    {
      public:
        /**
         * Create a new local variable definition.
         */
        LocalVariable(const std::string&           identifier,
                      ance::Type*                  type,
                      ance::LocalScope*            containing_scope,
                      bool                         is_final,
                      std::shared_ptr<ance::Value> value,
                      unsigned                     parameter_no,
                      ance::Location               location);

        void validate(ValidationLogger& validation_logger) override;

        void buildDeclaration(CompileContext* context) override;
        void buildDefinition(CompileContext* context) override;

        std::shared_ptr<ance::Value> getValue(CompileContext* context) override;

      protected:
        void storeValue(std::shared_ptr<ance::Value> value, CompileContext* context) override;

      private:
        void store(std::shared_ptr<ance::Value> value, CompileContext* context);

      private:
        std::shared_ptr<ance::Value> initial_value_;
        unsigned       parameter_no_;

        llvm::Value*           native_value_ {};
        llvm::DILocalVariable* local_debug_variable_ {nullptr};
    };
}
#endif