#include "LocalVariable.h"

#include "LocalScope.h"
#include "Value.h"

ance::LocalVariable::LocalVariable(ance::LocalScope* containing_scope, std::string identifier, ance::Type* type, ance::Value* value) : Variable(containing_scope, identifier, type, false), value_(value), native_value_(nullptr)
{
}

void ance::LocalVariable::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	assert(value_);
	assert(type() ==value_->getType());

	native_value_ = value_->getValue(c, m, state, ir, di);
	native_value_->setName(identifier());
}

llvm::Value* ance::LocalVariable::getValue(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	return native_value_;
}

void ance::LocalVariable::setValue(llvm::Value* value, llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	native_value_ = value;
	native_value_->setName(identifier());
}