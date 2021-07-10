#include "Allocation.h"

#include "PointerType.h"
#include "CompileContext.h"

Allocation::Allocation(Runtime::Allocator allocation, ance::Type* type, Expression* count, Application& app)
	: allocation_(allocation),
	  allocated_type_(type),
	  count_(count),
	  return_type_(ance::PointerType::get(app, type))
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

void Allocation::buildValue(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileContext* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	ance::Value* count = count_ ? count_->getValue() : nullptr;
	ance::Value* ptr = state->runtime_->allocate(allocation_, allocated_type_, count, c, m, state, ir, di);
	setValue(ptr);
}

Allocation::~Allocation() = default;
