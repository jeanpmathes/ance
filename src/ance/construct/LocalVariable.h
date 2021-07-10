#ifndef ANCE_SRC_ANCE_CONSTRUCT_LOCALVARIABLE_H_
#define ANCE_SRC_ANCE_CONSTRUCT_LOCALVARIABLE_H_

#include "Variable.h"

namespace ance
{
    class Value;

    class LocalScope;

    class LocalVariable : public ance::Variable
    {
      public:
        LocalVariable(
            ance::LocalScope* containing_scope,
            std::string       identifier,
            ance::Type*       type,
            ance::Value*      value);

        void build(CompileContext* context);

        ance::Value* getValue(CompileContext* context) override;

        void setValue(ance::Value* value, CompileContext* context) override;

      private:
        ance::Value* initial_value_;
        llvm::Value* native_value_ {nullptr};
    };
}
#endif