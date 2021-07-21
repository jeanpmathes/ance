#ifndef ANCE_SRC_ANCE_CONSTRUCT_GLOBALVARIABLE_H_
#define ANCE_SRC_ANCE_CONSTRUCT_GLOBALVARIABLE_H_

#include "Variable.h"

#include <string>

#include "ance/AccessModifier.h"

namespace llvm
{
    class LLVMContext;

    class Module;

    class GlobalVariable;
}

class ConstantExpression;

namespace ance
{
    class Constant;

    class Type;

    class GlobalVariable : public Variable
    {
      public:
        GlobalVariable(
            ance::Scope*        containing_scope,
            AccessModifier      access,
            std::string         identifier,
            ance::Type*         type,
            ConstantExpression* constant_init,
            bool                is_final,
            bool                is_constant);

        explicit GlobalVariable(std::string identifier);

        void defineGlobal(
            ance::Scope*        containing_scope,
            AccessModifier      access,
            ance::Type*         type,
            ConstantExpression* constant_init,
            bool                is_final,
            bool                is_constant);

        void buildGlobal(llvm::Module* m);

        ance::Value* getValue(CompileContext* context) override;

        void setValue(ance::Value* value, CompileContext* context) override;

      private:
        AccessModifier        access_;
        bool                  is_constant_ {false};
        ConstantExpression*   constant_init_ {nullptr};
        llvm::GlobalVariable* native_variable_ {nullptr};

        ance::Constant* initial_value_ {nullptr};
    };
}

#endif
