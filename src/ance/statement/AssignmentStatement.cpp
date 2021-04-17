#include "AssignmentStatement.h"

#include <utility>

#include "Expression.h"
#include "Function.h"
#include "LocalScope.h"
#include "Value.h"

AssignmentStatement::AssignmentStatement(ance::Function* function, unsigned int l, unsigned int c, std::string variable_identifier, Expression* assigned) :
	Statement(function, l, c), variable_identifier_(std::move(variable_identifier)), assigned_(assigned)
{
}

void AssignmentStatement::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
    getContainingFunction()->getScope()->getVariable(variable_identifier_)->setValue(assigned_->getValue()
                                                                                            ->getValue(c,
                                                                                                       m,
                                                                                                       state,
                                                                                                       ir,
                                                                                                       di),
                                                                                     c,
                                                                                     m,
                                                                                     state,
                                                                                     ir,
                                                                                     di);
}

AssignmentStatement::~AssignmentStatement() = default;