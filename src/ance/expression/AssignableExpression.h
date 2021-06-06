#ifndef ANCE_SRC_ANCE_EXPRESSION_ASSIGNABLEEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_ASSIGNABLEEXPRESSION_H_

#include "Expression.h"

class AssignableExpression : public virtual Expression
{
	public:
		virtual bool canAssignToValue();
};

#endif
