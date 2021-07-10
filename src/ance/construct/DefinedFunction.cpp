#include "DefinedFunction.h"

#include <utility>
#include <llvm/ADT/SmallVector.h> // critical, missing include will cause linking error

#include "Value.h"
#include "Values.h"
#include "AccessModifier.h"
#include "LocalScope.h"
#include "VoidType.h"
#include "WrappedNativeValue.h"

ance::DefinedFunction::DefinedFunction(
	AccessModifier access,
	std::string function_name,
	ance::Type* return_type,
	std::vector<ance::Parameter*> parameters,
	ance::Scope* scope,
	unsigned int line,
	unsigned int column
)
	:
	ance::Function(std::move(function_name), return_type, line, column),
	access_(access),
	parameters_(std::move(parameters)),
	local_scope_(new ance::LocalScope(scope))
{
	for (auto* parameter : parameters_)
	{
		ance::LocalVariable* arg = local_scope_->defineLocalVariable(
			parameter->name(), parameter->getType(),
			parameter
		);
		arguments_.push_back(arg);
	}
}

ance::LocalScope* ance::DefinedFunction::getScope() const
{
	return local_scope_;
}

void ance::DefinedFunction::pushStatement(Statement* statement)
{
	statements_.push_back(statement);
	statement->setContainingFunction(this);
}

void ance::DefinedFunction::buildName(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileContext* state,
	llvm::IRBuilder<>&,
	llvm::DIBuilder* di
)
{
	std::tie(native_type_, native_function_) = createNativeFunction(parameters_, Convert(access_), c, m);

	for (auto pair : zip(parameters_, native_function_->args()))
	{
		std::get<0>(pair)->wrap(&std::get<1>(pair));
	}

	llvm::SmallVector<llvm::Metadata*, 1> tys;
	tys.push_back(state->ui_32_); // todo: use the correct types
	llvm::DISubroutineType* debug_type = di->createSubroutineType(di->getOrCreateTypeArray(tys));
	llvm::DISubprogram* debug = di->createFunction(
		state->unit_,
		getName(),
		getName(),
		state->code_file_,
		getLine(),
		debug_type,
		0,
		llvm::DINode::DIFlags::FlagZero,
		llvm::DISubprogram::toSPFlags(
			true,
			true,
			false,
			0U,
			getName() == "main"
		));
	native_function_->setSubprogram(debug);
}

void ance::DefinedFunction::build(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileContext* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	llvm::BasicBlock* block = llvm::BasicBlock::Create(c, "entry", native_function_);

	ir.SetInsertPoint(block);

	for (auto* arg : arguments_)
	{
		arg->build(c, m, state, ir, di);
	}

	for (auto* statement : statements_)
	{
		ir.SetCurrentDebugLocation(
			llvm::DILocation::get(
				c,
				statement->getLine(),
				statement->getColumn(),
				native_function_->getSubprogram()));

		statement->build(c, m, state, ir, di);

		if (has_return_)
		{
			if (return_value_)
			{
				return_value_->buildContentValue(c, m, state, ir, di);
				ir.CreateRet(return_value_->getContentValue());
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
		if (getReturnType() == ance::VoidType::get())
		{
			ir.CreateRetVoid();
		}
		else
		{
			assert(true && "Functions with return type that is not void require a return statement.");
		}
	}

	ir.SetCurrentDebugLocation(nullptr);
}

void ance::DefinedFunction::addReturn(ance::Value* value)
{
	if (value)
	{
		assert(value->getType() == getReturnType());
		return_value_ = value;
		has_return_ = true;
	}
	else
	{
		assert(getReturnType() == ance::VoidType::get());
		return_value_ = nullptr;
		has_return_ = true;
	}
}

ance::Value* ance::DefinedFunction::buildCall(
	const std::vector<ance::Value*>& arguments,
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileContext* state,
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