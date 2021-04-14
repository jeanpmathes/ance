#ifndef ANCE_SRC_ANCE_EXPRESSION_BUILDABLECONSTANTEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_BUILDABLECONSTANTEXPRESSION_H_

#include "ConstantExpression.h"
#include "BuildableExpression.h"

class BuildableConstantExpression : public ConstantExpression, public BuildableExpression
{
    public:
        virtual llvm::Constant* build_constant(llvm::LLVMContext& c) = 0;
        ance::Type* get_type() override = 0;
        ance::Constant* get_constant_value() override = 0;

        llvm::Value * build(llvm::LLVMContext &c, llvm::Module *m, CompileState *state, llvm::IRBuilder<> &ir, llvm::DIBuilder *di) override;
};

#endif
