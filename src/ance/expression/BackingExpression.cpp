#include "BackingExpression.h"

BackingExpression::BackingExpression(ance::Location location) : BuildableExpression(location) {}

void BackingExpression::doBuild(CompileContext* context)
{
    assert(!native_value_ && "Expressions must be built only once.");
    native_value_ = buildNativeValue(context);
}

llvm::Value* BackingExpression::getNativeValue()
{
    assert(native_value_ && "Expressions must be built before accessing value.");
    return native_value_;
}
