#include "Expression.h"

#include "ance/type/ReferenceType.h"

Expression::Expression(ance::Location location) : location_(location) {}

ance::Location Expression::location() const
{
    return location_;
}

void Expression::setContainingScope(ance::Scope*) {}

bool Expression::isNamed()
{
    return ance::ReferenceType::isReferenceType(type());
}
