#ifndef ANCE_SRC_ANCE_EXPRESSION_CONSTANTLITERAL_EXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_CONSTANTLITERAL_EXPRESSION_H_

#include "ConstantExpression.h"

class constantliteral_expression : public ConstantExpression
{
    public:
        constantliteral_expression(ance::Constant* constant);

        ance::Type* get_type() override;
        ance::Constant* get_constant_value() override;

    private:
        ance::Constant* constant_;
};

#endif
