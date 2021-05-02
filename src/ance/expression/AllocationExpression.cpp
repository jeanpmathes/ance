#include "AllocationExpression.h"

#include "ExpressionBackedValue.h"
#include "PointerType.h"
#include "CompileState.h"

AllocationExpression::AllocationExpression(Runtime::Allocator allocation, ance::Type* type, Application& app)
	: allocation_(allocation),
	  allocated_type_(type),
	  return_type_(ance::PointerType::get(app, type)),
	  value_(new ance::ExpressionBackedValue(this))
{

}

ance::Type* AllocationExpression::getType()
{
	return return_type_;
}

ance::Value* AllocationExpression::getValue()
{
	return value_;
}

llvm::Value* AllocationExpression::build(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	return state->runtime_->allocate(allocation_, allocated_type_, c, m, state, ir, di);
}

AllocationExpression::~AllocationExpression() = default;
