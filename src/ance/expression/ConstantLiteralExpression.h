#ifndef ANCE_SRC_ANCE_EXPRESSION_CONSTANTLITERALEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_CONSTANTLITERALEXPRESSION_H_

#include "ConstantExpression.h"

class ConstantLiteralExpression : public ConstantExpression
{
	public:
		explicit ConstantLiteralExpression(ance::Constant* constant);

		ance::Type* getType() override;

		ance::Constant* getConstantValue() override;

	private:
		ance::Constant* constant_;
};

#endif
