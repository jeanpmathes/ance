#include "Expression.h"

Expression::Expression(ance::Location location) : location_(location) {}

ance::Location Expression::location() const
{
    return location_;
}

void Expression::setContainingScope(ance::Scope*) {}
