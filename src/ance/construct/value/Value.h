#ifndef ANCE_SRC_ANCE_CONSTRUCT_VALUE_VALUE_H_
#define ANCE_SRC_ANCE_CONSTRUCT_VALUE_VALUE_H_

#include "llvm/IR/DIBuilder.h"
#include "llvm/IR/IRBuilder.h"

class Expression;

class CompileContext;

namespace ance
{
    class Type;

    class Value
    {
      public:
        virtual ance::Type* getType() = 0;

        virtual void buildNativeValue(CompileContext* context) = 0;

        virtual void buildContentValue(CompileContext* context);

        virtual llvm::Value* getNativeValue() = 0;

        virtual llvm::Value* getContentValue();

        virtual ~Value() = default;

      private:
        llvm::Value* content_value_ {nullptr};
    };
}
#endif