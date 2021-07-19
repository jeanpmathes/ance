#ifndef ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_EXPRESSIONBACKEDCONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_EXPRESSIONBACKEDCONSTANT_H_

#include "Constant.h"

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "ance/expression/BackingConstantExpression.h"

class ConstantExpression;

namespace ance
{
    class ExpressionBackedConstant : public Constant
    {
      public:
        explicit ExpressionBackedConstant(BackingConstantExpression* expression);

        ance::Type* type() override;

        llvm::Constant* buildContent(llvm::Module* m) override;

      private:
        BackingConstantExpression* expression_;
    };
}
#endif
