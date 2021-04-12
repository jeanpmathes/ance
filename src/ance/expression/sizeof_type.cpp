#include "sizeof_type.h"

#include "CompileState.h"
#include "ExpressionBackedValue.h"
#include "SizeType.h"

sizeof_type::sizeof_type(ance::Type* type, Application& app) : return_value_(new ance::ExpressionBackedValue(this)), return_type_(ance::SizeType::get(app)), type_(type)
{
}

ance::Type* sizeof_type::get_type()
{
	return return_type_;
}

ance::Value* sizeof_type::get_value()
{
	return  return_value_;
}

llvm::Value* sizeof_type::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	return ance::SizeType::get(*state->application)->build_value(type_->get_size(m));
}