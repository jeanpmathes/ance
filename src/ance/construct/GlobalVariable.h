#ifndef ANCE_SRC_ANCE_CONSTRUCT_GLOBALVARIABLE_H_
#define ANCE_SRC_ANCE_CONSTRUCT_GLOBALVARIABLE_H_

#include "Variable.h"

#include <string>

#include <llvm/IR/LLVMContext.h>

#include "ance/AccessModifier.h"

namespace ance
{
    class Constant;
    class Type;
}

class ConstantExpression;

namespace ance
{
    /**
     * A global variable.
     */
    class GlobalVariable : public Variable
    {
      public:
        /**
         * Create a new global variable with complete definition.
         * @param containing_scope The containing scope.
         * @param access The access type.
         * @param identifier The identifier.
         * @param type The type.
         * @param constant_init The constant used for initialization.
         * @param is_final Whether the variable is final.
         * @param is_constant Whether the variable is constant.
         * @param location The source location.
         */
        GlobalVariable(ance::Scope*        containing_scope,
                       AccessModifier      access,
                       std::string         identifier,
                       ance::Type*         type,
                       ConstantExpression* constant_init,
                       bool                is_final,
                       bool                is_constant,
                       ance::Location      location);

        /**
         * Create an undefined global variable.
         * @param identifier The identifier of the variable.
         */
        explicit GlobalVariable(std::string identifier);

        /**
         * Define an undefined global variable.
         * @param containing_scope The containing scope.
         * @param access The access type.
         * @param type The type.
         * @param constant_init The constant used for initialization.
         * @param is_final Whether the variable is final.
         * @param is_constant Whether the variable is constant.
         * @param location The source location.
         */
        void defineGlobal(ance::Scope*        containing_scope,
                          AccessModifier      access,
                          ance::Type*         type,
                          ConstantExpression* constant_init,
                          bool                is_final,
                          bool                is_constant,
                          ance::Location      location);

        [[nodiscard]] ance::Location location() const;

        void validate(ValidationLogger& validation_logger) override;

        /**
         * Create the native content backing the variable.
         * @param context The current compile context.
         */
        void createNativeBacking(CompileContext* context);

        std::shared_ptr<ance::Value> getValue(CompileContext* context) override;

      protected:
        void storeValue(std::shared_ptr<ance::Value> value, CompileContext* context) override;

      private:
        AccessModifier      access_;
        ance::Location      location_;
        bool                is_constant_ {false};
        ConstantExpression* constant_init_ {nullptr};

        llvm::GlobalVariable*           native_variable_ {nullptr};
        std::shared_ptr<ance::Constant> initial_value_ {nullptr};
    };
}

#endif
