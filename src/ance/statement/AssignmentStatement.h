#pragma once

#include "Statement.h"

class Assignable;

class Expression;

class AssignmentStatement : public Statement
{
	public:
		AssignmentStatement(
			Assignable* assignable,
			Expression* assigned,
			unsigned int l,
			unsigned int c
		);

		void setContainingFunction(ance::DefinedFunction* function) override;

		void build(CompileContext* context) override;

	private:
		Assignable* assignable_;
		Expression* assigned_;
};
