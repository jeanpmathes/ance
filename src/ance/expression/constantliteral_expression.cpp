#include "constantliteral_expression.h"

#include "Constant.h"
#include "Scope.h"

constantliteral_expression::constantliteral_expression(ance::Constant* constant) : constant_(constant)
{

}

ance::Type* constantliteral_expression::get_type()
{
    return constant_->get_type();
}

ance::Constant* constantliteral_expression::get_constant_value()
{
    return constant_;
}
