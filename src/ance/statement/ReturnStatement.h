#pragma once

#include "Statement.h"
#include "Expression.h"

class ReturnStatement :
	public Statement
{
	public:
		ReturnStatement(Expression* return_value, unsigned int l, unsigned int c);

		void setContainingFunction(ance::DefinedFunction* function) override;

		void build(CompileContext* context) override;

	private:
		Expression* return_value_;
};
