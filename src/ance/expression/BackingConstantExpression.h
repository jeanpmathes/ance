#ifndef ANCE_SRC_ANCE_EXPRESSION_BACKINGCONSTANTEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_BACKINGCONSTANTEXPRESSION_H_

#include "ConstantExpression.h"

#include "ance/expression/BackingExpression.h"

class BackingConstantExpression
    : public ConstantExpression
    , public BackingExpression
{
  public:
    void buildConstant(llvm::LLVMContext& c);

    ance::Type* type() override = 0;

    ance::Constant* getConstantValue() override = 0;

    llvm::Constant* getContentConstant();

  protected:
    virtual llvm::Constant* buildContentConstant(llvm::LLVMContext& c) = 0;

    llvm::Value* buildNativeValue(CompileContext* context) final;

  private:
    llvm::Constant* content_constant_ {nullptr};
};

#endif
