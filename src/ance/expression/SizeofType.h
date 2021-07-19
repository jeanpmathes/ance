#ifndef ANCE_SRC_ANCE_EXPRESSION_SIZEOFTYPE_H_
#define ANCE_SRC_ANCE_EXPRESSION_SIZEOFTYPE_H_

#include "BackingExpression.h"

#include "ance/construct/value/ExpressionBackedValue.h"

class Application;

class SizeofType : public BackingExpression
{
  public:
    explicit SizeofType(ance::Type* type);

    ance::Type* type() override;

    ance::Value* getValue() override;

    llvm::Value* buildNativeValue(CompileContext* context) override;

  private:
    ance::Value* return_value_ {new ance::ExpressionBackedValue(this)};
    ance::Type*  type_;
};

#endif