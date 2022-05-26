#ifndef ANCE_SRC_LANG_EXPRESSION_BACKINGCONSTANTEXPRESSION_H_
#define ANCE_SRC_LANG_EXPRESSION_BACKINGCONSTANTEXPRESSION_H_

#include "BuildableExpression.h"
#include "ConstantExpression.h"

/**
 * An interface for expressions that can back a constant.
 */
class BackingConstantExpression
    : public ConstantExpression
    , public BuildableExpression
{
  public:
    /**
     * Build the constant.
     * @param c The llvm context.
     */
    void buildConstant(llvm::LLVMContext& c);

    lang::ResolvingHandle<lang::Type> type() override = 0;

    [[nodiscard]] std::shared_ptr<lang::Constant> getConstantValue() const override = 0;

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

    void doBuild(CompileContext* context) override;

  private:
    llvm::Constant* content_constant_ {nullptr};
};

#endif
