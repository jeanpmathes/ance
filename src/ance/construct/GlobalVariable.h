#ifndef ANCE_SRC_ANCE_CONSTRUCT_GLOBALVARIABLE_H_
#define ANCE_SRC_ANCE_CONSTRUCT_GLOBALVARIABLE_H_

#include "VariableDefinition.h"

#include <string>

#include <llvm/IR/LLVMContext.h>

#include "ance/AccessModifier.h"

namespace ance
{
    class Constant;
    class Type;
    class GlobalScope;
}

class ConstantExpression;

namespace ance
{
    /**
     * A global variable.
     */
    class GlobalVariable : public VariableDefinition
    {
      public:
        /**
         * Create a new global variable definition.
         */
        GlobalVariable(const std::string&  identifier,
                       ance::Type*         type,
                       ance::GlobalScope*  containing_scope,
                       AccessModifier      access,
                       ConstantExpression* constant_init,
                       bool                is_final,
                       bool                is_constant,
                       ance::Location      location);

        void validate(ValidationLogger& validation_logger) override;

        void buildDeclaration(CompileContext* context) override;
        void buildDefinition(CompileContext* context) override;

        std::shared_ptr<ance::Value> getValue(CompileContext* context) override;

      protected:
        void storeValue(std::shared_ptr<ance::Value> value, CompileContext* context) override;

      private:
        AccessModifier      access_;
        bool                is_constant_ {false};
        ConstantExpression* constant_init_ {nullptr};

        llvm::GlobalVariable*           native_variable_ {nullptr};
        std::shared_ptr<ance::Constant> initial_value_ {nullptr};
    };
}

#endif
