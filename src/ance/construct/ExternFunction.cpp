#include "ExternFunction.h"

#include <utility>

#include "VoidType.h"
#include "Values.h"
#include "WrappedNativeValue.h"

ance::ExternFunction::ExternFunction(
	std::string function_name,
	ance::Type* return_type,
	std::vector<ance::Parameter*> parameters,
	unsigned int line,
	unsigned int column
)
	: ance::Function(std::move(function_name), return_type, line, column), parameters_(std::move(parameters))
{

}

void ance::ExternFunction::buildName(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState*,
	llvm::IRBuilder<>&,
	llvm::DIBuilder*
)
{
	std::tie(native_type_, native_function_) =
		createNativeFunction(parameters_, llvm::GlobalValue::LinkageTypes::ExternalLinkage, c, m);

	for (auto pair : zip(parameters_, native_function_->args()))
	{
		std::get<0>(pair)->wrap(&std::get<1>(pair));
	}
}

void ance::ExternFunction::build(
	llvm::LLVMContext&,
	llvm::Module*,
	CompileState*,
	llvm::IRBuilder<>&,
	llvm::DIBuilder*
)
{

}

ance::Value* ance::ExternFunction::buildCall(
	const std::vector<ance::Value*>& arguments,
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
) const
{
	assert(arguments.size() == native_type_->getNumParams());

	for (auto pair : llvm::zip(parameters_, arguments))
	{
		assert(std::get<0>(pair)->getType() == std::get<1>(pair)->getType() && "Input parameter types must match.");
	}

	llvm::Value* content_value = buildCall(arguments, native_type_, native_function_, c, m, state, ir, di);

	if (getReturnType() == ance::VoidType::get())
	{
		return nullptr;
	}

	llvm::Value* native_value = ance::Values::contentToNative(getReturnType(), content_value, c, m, state, ir, di);
	return new ance::WrappedNativeValue(getReturnType(), native_value);
}
