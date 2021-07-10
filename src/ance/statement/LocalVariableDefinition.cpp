#include "LocalVariableDefinition.h"

#include <utility>

#include "Expression.h"
#include "DefinedFunction.h"
#include "LocalScope.h"

LocalVariableDefinition::LocalVariableDefinition(
	std::string identifier,
	ance::Type* type,
	Expression* assigned,
	unsigned l,
	unsigned c
)
	: Statement(l, c), identifier_(std::move(identifier)), type_(type), assigned_(assigned)
{
}

void LocalVariableDefinition::setContainingFunction(ance::DefinedFunction* function)
{
	Statement::setContainingFunction(function);

	variable_ = function->getScope()->defineLocalVariable(identifier_, type_, assigned_);
	assigned_->setScope(function->getScope());
}

void LocalVariableDefinition::build(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileContext* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	variable_->build(c, m, state, ir, di);
}
