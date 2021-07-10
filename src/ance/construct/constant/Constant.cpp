#include "Constant.h"

#include "Type.h"
#include "Values.h"

#include "CompileContext.h"

void ance::Constant::buildContentConstant(llvm::Module* m)
{
	assert(!content_constant_ && "A constant may only be built once.");
	content_constant_ = buildContent(m);
}

llvm::Constant* ance::Constant::getContentConstant()
{
	assert(content_constant_ && "Constant has to be built before accessing content constant.");
	return content_constant_;
}

void ance::Constant::buildNativeValue(CompileContext* context)
{
	buildContentConstant(context->module());
	native_value_ = ance::Values::contentToNative(getType(), content_constant_, context);
}

void ance::Constant::buildContentValue(CompileContext* context)
{
	buildContentConstant(context->module());
}

llvm::Value* ance::Constant::getNativeValue()
{
	assert(native_value_ && "Value has to be built before accessing native value.");
	return native_value_;
}

llvm::Value* ance::Constant::getContentValue()
{
	assert(content_constant_ && "Value has to be built before accessing content value.");
	return content_constant_;
}
