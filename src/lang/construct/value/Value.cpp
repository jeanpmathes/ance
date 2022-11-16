#include "Value.h"

#include "lang/utility/Values.h"

void lang::Value::buildContentValue(CompileContext& context)
{
    buildNativeValue(context);
    content_value_ = lang::Values::nativeToContent(type(), getNativeValue(), context);
}

llvm::Value* lang::Value::getContentValue()
{
    assert(content_value_ && "Content value must be built before accessing it.");
    return content_value_;
}
