#include "Value.h"

#include "ance/utility/Values.h"

void ance::Value::buildContentValue(CompileContext* context)
{
    buildNativeValue(context);
    content_value_ = ance::Values::nativeToContent(type(), getNativeValue(), context);
}

llvm::Value* ance::Value::getContentValue()
{
    assert(content_value_ && "Content value must be built before accessing it.");
    return content_value_;
}
