#ifndef ANCE_SRC_LANG_CONSTRUCT_LOCALVARIABLE_H_
#define ANCE_SRC_LANG_CONSTRUCT_LOCALVARIABLE_H_

#include "VariableDefinition.h"

#include <memory>
#include <string>

#include "lang/Element.h"

namespace lang
{
    class Value;
    class LocalScope;
}

namespace lang
{
    /**
     * A local variable or function parameter definition.
     */
    class LocalVariable
        : public lang::VariableDefinition
        , public lang::Element<LocalVariable, ANCE_CONSTRUCTS>
    {
      public:
        /**
         * Create a new local variable definition.
         */
        LocalVariable(Identifier                        name,
                      lang::ResolvingHandle<lang::Type> type,
                      lang::Location                    type_location,
                      Scope&                            containing_scope,
                      bool                              is_final,
                      std::shared_ptr<lang::Value>      value,
                      unsigned                          parameter_no,
                      lang::Location                    location);

        void validate(ValidationLogger& validation_logger) const override;

        void buildDeclaration(CompileContext* context) override;
        void buildDefinition(CompileContext* context) override;
        void buildFinalization(CompileContext* context) override;

        std::shared_ptr<lang::Value> getValue(CompileContext* context) override;

      protected:
        void storeValue(std::shared_ptr<lang::Value> value, CompileContext* context) override;

      private:
        void store(std::shared_ptr<lang::Value> value, CompileContext* context);

      private:
        std::shared_ptr<lang::Value> initial_value_;
        unsigned                     parameter_no_;

        llvm::Value*           native_value_ {};
        llvm::DILocalVariable* local_debug_variable_ {nullptr};
        bool                   finalized_ {false};
    };
}
#endif