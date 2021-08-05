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
        LocalVariable(ance::LocalScope* containing_scope,
                      std::string       identifier,
                      ance::Type*       type,
                      ance::Value*      value,
                      bool              is_final,
                      unsigned parameter_no,
                      ance::Location location);

        void build(CompileContext* context);

        ance::Value* getValue(CompileContext* context) override;
        void         setValue(ance::Value* value, CompileContext* context) override;

      private:
        void store(Value* value, CompileContext* context);

      private:
        ance::Value*      initial_value_;
        ance::LocalScope* containing_scope_;

        unsigned parameter_no_;
        ance::Location location_;

        llvm::Value* native_value_ {nullptr};
        llvm::DILocalVariable* local_debug_variable_{nullptr};
    };
}
#endif