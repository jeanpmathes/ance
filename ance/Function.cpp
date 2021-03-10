#include "Function.h"

#include <utility>

#include "Value.h"
#include "AccessModifier.h"
#include "LocalScope.h"

ance::Function::Function(access_modifier access, std::string fn_name, ance::Type* return_type, std::vector<ance::Parameter*> parameters, ance::Scope* scope, unsigned int l, unsigned int c) :
	access_(access), name_(std::move(fn_name)), parameters_(parameters), line_(l), column_(c), local_scope_(new ance::LocalScope(scope)), return_type_(return_type),
	native_type_(nullptr), native_function_(nullptr)
{
	for (auto* parameter : parameters_)
	{
		ance::LocalVariable* arg = local_scope_->define_local_variable(parameter->name(), parameter->type(), parameter->get_value());
		arguments_.push_back(arg);
	}
}

std::string ance::Function::get_name() const
{
	return name_;
}

ance::Type* ance::Function::get_return_type() const
{
	return return_type_;
}

ance::LocalScope* ance::Function::get_scope() const
{
	return local_scope_;
}

void  ance::Function::push_statement(Statement* statement)
{
	statements_.push_back(statement);
}

void ance::Function::build_name(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	std::vector<llvm::Type*> param_types;

	for (auto* param : parameters_)
	{
		param_types.push_back(param->type()->get_native_type(c));
	}

	native_type_ = llvm::FunctionType::get(return_type_->get_native_type(c), param_types, false);
	native_function_ = llvm::Function::Create(native_type_, convert(access_), name_, m);

	for (auto pair : zip(parameters_, native_function_->args()))
	{
		std::get<0>(pair)->wrap(&std::get<1>(pair));
	}

	llvm::SmallVector<llvm::Metadata*, 1> tys;
	tys.push_back(state->ui32);
	llvm::DISubroutineType* debug_type = di->createSubroutineType(di->getOrCreateTypeArray(tys));
	llvm::DISubprogram* debug = di->createFunction(state->unit, name_, name_, state->code_file, line_, debug_type, 0, llvm::DINode::DIFlags::FlagZero, llvm::DISubprogram::toSPFlags(true, true, false, 0U, name_ == "main"));
	native_function_->setSubprogram(debug);
}

void ance::Function::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	llvm::BasicBlock* block = llvm::BasicBlock::Create(c, "entry", native_function_);

	ir.SetInsertPoint(block);

	for (auto* arg : arguments_)
	{
		arg->build(c, m, state, ir, di);
	}

	for (auto* statement : statements_)
	{
		ir.SetCurrentDebugLocation(llvm::DILocation::get(c, statement->getLine(), statement->getColumn(), native_function_->getSubprogram()));

		statement->build(c, m, state, ir, di);
	}

	ir.SetCurrentDebugLocation(nullptr);
}

llvm::CallInst* ance::Function::build_call(const std::vector<ance::Value*>& arguments, llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) const
{
	assert(arguments.size() == native_type_->getNumParams());

	for (auto pair : llvm::zip(parameters_, arguments))
	{
		assert(std::get<0>(pair)->type() == std::get<1>(pair)->get_type());
	}

	std::vector<llvm::Value*> args;

	for (auto* arg : arguments)
	{
		args.push_back(arg->get_value(c, m, state, ir, di));
	}

	return ir.CreateCall(native_type_, native_function_, args);
}