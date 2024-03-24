#include "Constant.h"

#include "lang/ApplicationVisitor.h"
#include "lang/type/Type.h"

lang::Constant::Constant(lang::Type const& type) : Value(type) {}

Execution::Handle<false> lang::Constant::getExecutionValue()
{
    throw std::logic_error("Constant is not associated with an execution context");
}

Execution::Handle<true> lang::Constant::getExecutionConstant()
{
    throw std::logic_error("Constant is not associated with an execution context");
}
