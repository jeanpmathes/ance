#include "assignment_statement.h"

#include "Expression.h"
#include "Value.h"

assignment_statement::assignment_statement(unsigned int l, unsigned int c, std::string variable_identifier, ance::Scope* scope, Expression* assigned) :
	Statement(l, c), variable_identifier_(variable_identifier), scope_(scope), assigned_(assigned)
{
}

void assignment_statement::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	scope_->set_variable(variable_identifier_, assigned_->get_value()->get_value(c, m, state, ir, di), c, m, state, ir, di);
}

assignment_statement::~assignment_statement() = default;