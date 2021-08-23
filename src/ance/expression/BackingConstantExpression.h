#ifndef ANCE_SRC_ANCE_EXPRESSION_BACKINGCONSTANTEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_BACKINGCONSTANTEXPRESSION_H_

#include "ConstantExpression.h"

#include "ance/expression/BackingExpression.h"

/**
 * An interface for expressions that can back a constant.
 */
class BackingConstantExpression
    : public ConstantExpression
    , public BackingExpression
{
  public:
    /**
     * Build the constant.
     * @param c The llvm context.
     */
    void buildConstant(llvm::LLVMContext& c);

    ance::Type* type() override = 0;

    ance::Constant* getConstantValue() override = 0;

    /**
     * Get the content constant. Must be built before.
     * @return The content constant.
     */
    llvm::Constant* getContentConstant();

  protected:
    /**
     * Build the content constant.
     * @param c The llvm context.
     * @return The content constant.
     */
    virtual llvm::Constant* buildContentConstant(llvm::LLVMContext& c) = 0;

    llvm::Value* buildNativeValue(CompileContext* context) final;

  private:
    llvm::Constant* content_constant_ {nullptr};
};

#endif
