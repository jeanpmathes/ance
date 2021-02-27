#include "Function.h"

#include <utility>

#include "AccessModifier.h"
#include "LocalScope.h"

ance::Function::Function(access_modifier access, std::string fn_name, ance::Type* return_type, ance::Scope* scope, unsigned int l, unsigned int c) :
	access_(access), name(std::move(fn_name)), line(l), column(c), local_scope_(new ance::LocalScope(scope)), return_type(return_type),
	llvmType(nullptr), llvmFunction(nullptr)
{
}

std::string ance::Function::get_name() const
{
	return name;
}

ance::Type* ance::Function::get_return_type() const
{
	return return_type;
}

ance::LocalScope* ance::Function::get_scope() const
{
	return local_scope_;
}

void  ance::Function::push_statement(Statement* statement)
{
	statements.push_back(statement);
}

void ance::Function::build_name(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	llvmType = llvm::FunctionType::get(return_type->get_native_type(c), false);
	llvmFunction = llvm::Function::Create(llvmType, convert(access_), name, m);

	llvm::SmallVector<llvm::Metadata*, 1> tys;
	tys.push_back(state->ui32);
	llvm::DISubroutineType* debug_type = di->createSubroutineType(di->getOrCreateTypeArray(tys));
	llvm::DISubprogram* debug = di->createFunction(state->unit, name, name, state->code_file, line, debug_type, 0, llvm::DINode::DIFlags::FlagZero, llvm::DISubprogram::toSPFlags(true, true, false, 0U, name == "main"));
	llvmFunction->setSubprogram(debug);
}

void ance::Function::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	llvm::BasicBlock* block = llvm::BasicBlock::Create(c, "entry", llvmFunction);

	ir.SetInsertPoint(block);

	for (auto* statement : statements)
	{
		ir.SetCurrentDebugLocation(llvm::DILocation::get(c, statement->getLine(), statement->getColumn(), llvmFunction->getSubprogram()));

		statement->build(c, m, state, ir, di);
	}

	ir.SetCurrentDebugLocation(nullptr);
}

llvm::CallInst* ance::Function::build_call(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) const
{
	return ir.CreateCall(llvmType, llvmFunction);
}