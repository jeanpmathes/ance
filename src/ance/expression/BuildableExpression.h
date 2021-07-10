#ifndef ANCE_SRC_ANCE_EXPRESSION_BUILDABLEEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_BUILDABLEEXPRESSION_H_

#include "Expression.h"

class BuildableExpression : public virtual Expression
{
	public:
		virtual void build(CompileContext* context) = 0;
};

#endif
