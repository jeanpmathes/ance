#include "Function.h"

#include <utility>
#include <llvm/ADT/SmallVector.h> // critical, missing include will cause linking error

#include "Value.h"
#include "AccessModifier.h"
#include "LocalScope.h"
#include "VoidType.h"

ance::Function::Function(AccessModifier access, std::string fn_name, ance::Type* return_type, std::vector<ance::Parameter*> parameters, ance::Scope* scope, unsigned int l, unsigned int c) :
    access_(access), name_(std::move(fn_name)), parameters_(parameters), line_(l), column_(c), local_scope_(new ance::LocalScope(scope)), return_type_(return_type),
    native_type_(nullptr), native_function_(nullptr), has_return_(false), return_value_(nullptr)
{
	for (auto* parameter : parameters_)
	{
		ance::LocalVariable* arg = local_scope_->defineLocalVariable(parameter->name(), parameter->type(),
                                                                     parameter->getValue());
		arguments_.push_back(arg);
	}
}

std::string ance::Function::getName() const
{
	return name_;
}

ance::Type* ance::Function::getReturnType() const
{
	return return_type_;
}

ance::LocalScope* ance::Function::getScope() const
{
	return local_scope_;
}

void  ance::Function::pushStatement(Statement* statement)
{
	statements_.push_back(statement);
}

void ance::Function::buildName(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	std::vector<llvm::Type*> param_types;

	for (auto* param : parameters_)
	{
		param_types.push_back(param->type()->getNativeType(c));
	}

	native_type_ = llvm::FunctionType::get(return_type_->getNativeType(c), param_types, false);
	native_function_ = llvm::Function::Create(native_type_, Convert(access_), name_, m);

	for (auto pair : zip(parameters_, native_function_->args()))
	{
		std::get<0>(pair)->wrap(&std::get<1>(pair));
	}

	llvm::SmallVector<llvm::Metadata*, 1> tys;
	tys.push_back(state->ui_32_);
	llvm::DISubroutineType* debug_type = di->createSubroutineType(di->getOrCreateTypeArray(tys));
	llvm::DISubprogram* debug = di->createFunction(state->unit_, name_, name_, state->code_file_, line_, debug_type, 0, llvm::DINode::DIFlags::FlagZero, llvm::DISubprogram::toSPFlags(true, true, false, 0U, name_ == "main"));
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

		if (has_return_)
		{
			if (return_value_)
			{
				ir.CreateRet(return_value_->getValue(c, m, state, ir, di));
			}
			else
			{
				ir.CreateRetVoid();
			}

			break;
		}
	}

	if (!has_return_)
	{
		if (return_type_ == ance::VoidType::get())
		{
			ir.CreateRetVoid();
		}
		else
		{
			assert(true); // return required
		}
	}

	ir.SetCurrentDebugLocation(nullptr);
}

void ance::Function::addReturn(ance::Value* value)
{
	if (value)
	{
		assert(value->getType() == return_type_);
		return_value_ = value;
        has_return_ = true;
	}
	else
	{
		assert(return_type_ == ance::VoidType::get());
		return_value_ = nullptr;
        has_return_ = true;
	}
}

llvm::CallInst* ance::Function::buildCall(const std::vector<ance::Value*>& arguments, llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) const
{
	assert(arguments.size() == native_type_->getNumParams());

	for (auto pair : llvm::zip(parameters_, arguments))
	{
		assert(std::get<0>(pair)->type() ==std::get<1>(pair)->getType());
	}

	std::vector<llvm::Value*> args;

	for (auto* arg : arguments)
	{
		args.push_back(arg->getValue(c, m, state, ir, di));
	}

	return ir.CreateCall(native_type_, native_function_, args);
}