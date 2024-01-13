#include "BuildableExpression.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"

void BuildableExpression::build(CompileContext& context)
{
    context.setDebugLocation(location(), scope());
    doBuild(context);
    context.resetDebugLocation();
}
