#include "CompileTimeStatement.h"

#include "lang/ApplicationVisitor.h"

lang::CMP CompileTimeStatement::rootCMP() const
{
    return lang::CMP::OPTIONAL_CMP;
}
