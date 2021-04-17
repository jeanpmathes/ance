#ifndef ANCE_SRC_ANCE_EXPRESSION_BUILDABLECONSTANTEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_BUILDABLECONSTANTEXPRESSION_H_

#include "ConstantExpression.h"
#include "BuildableExpression.h"

class BuildableConstantExpression : public ConstantExpression, public BuildableExpression
{
    public:
        virtual llvm::Constant* buildConstant(llvm::LLVMContext& c) = 0;
        ance::Type* getType() override = 0;
        ance::Constant* getConstantValue() override = 0;

        llvm::Value * build(llvm::LLVMContext &c, llvm::Module *m, CompileState *state, llvm::IRBuilder<> &ir, llvm::DIBuilder *di) override;
};

#endif
