#include "CompileTimeStatement.h"

#include "lang/ApplicationVisitor.h"

bool CompileTimeStatement::isRootCMP() const
{
    return true;
}
