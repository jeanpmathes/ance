#include "Function.h"

ance::Function::Function(std::string fn_name, unsigned int l, unsigned int c) : name(fn_name), line(l), column(c)
{
}

std::string ance::Function::GetName()
{
	return name;
}

void  ance::Function::push_statement(Statement* statement)
{
	statements.push_back(statement);
}

void ance::Function::BuildName(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	llvmType = llvm::FunctionType::get(llvm::Type::getInt32Ty(c), false);
	llvmFunction = llvm::Function::Create(llvmType, llvm::GlobalValue::LinkageTypes::PrivateLinkage, name, m);

	llvm::SmallVector<llvm::Metadata*, 1> tys;
	tys.push_back(state->ui32);
	llvm::DISubroutineType* debug_type = di->createSubroutineType(di->getOrCreateTypeArray(tys));
	llvm::DISubprogram* debug = di->createFunction(state->unit, name, name, state->code_file, line, debug_type, 0, llvm::DINode::DIFlags::FlagZero, llvm::DISubprogram::toSPFlags(true, true, false, 0U, name == "main"));
	llvmFunction->setSubprogram(debug);
}

void ance::Function::Build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	llvm::BasicBlock* block = llvm::BasicBlock::Create(c, "entry", llvmFunction);

	ir.SetInsertPoint(block);

	for (auto statement : statements)
	{
		ir.SetCurrentDebugLocation(llvm::DILocation::get(c, statement->getLine(), statement->getColumn(), llvmFunction->getSubprogram()));

		statement->build(c, m, state, ir, di);
	}

	ir.SetCurrentDebugLocation(nullptr);
}

llvm::CallInst* ance::Function::BuildCall(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	return ir.CreateCall(llvmType, llvmFunction);
}