#include "Allocation.h"

#include "ExpressionBackedValue.h"
#include "PointerType.h"
#include "CompileState.h"

Allocation::Allocation(Runtime::Allocator allocation, ance::Type* type, Expression* count, Application& app)
	: allocation_(allocation),
	  allocated_type_(type),
	  count_(count),
	  return_type_(ance::PointerType::get(app, type)),
	  value_(new ance::ExpressionBackedValue(this))
{

}

void Allocation::setScope(ance::Scope* scope)
{
	if (count_) count_->setScope(scope);
}

ance::Type* Allocation::getType()
{
	return return_type_;
}

ance::Value* Allocation::getValue()
{
	return value_;
}

llvm::Value* Allocation::buildNativeValue(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	ance::Value* count = count_ ? count_->getValue() : nullptr;
	return state->runtime_->allocate(allocation_, allocated_type_, count, c, m, state, ir, di);
}

Allocation::~Allocation() = default;
