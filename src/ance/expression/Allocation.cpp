#include "Allocation.h"

#include "ExpressionBackedValue.h"
#include "PointerType.h"
#include "CompileState.h"

Allocation::Allocation(Runtime::Allocator allocation, ance::Type* type, Application& app)
	: allocation_(allocation),
	  allocated_type_(type),
	  return_type_(ance::PointerType::get(app, type)),
	  value_(new ance::ExpressionBackedValue(this))
{

}

ance::Type* Allocation::getType()
{
	return return_type_;
}

ance::Value* Allocation::getValue()
{
	return value_;
}

llvm::Value* Allocation::build(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	return state->runtime_->allocate(allocation_, allocated_type_, c, m, state, ir, di);
}

Allocation::~Allocation() = default;
