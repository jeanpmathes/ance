#include "BooleanConstant.h"

#include <llvm/IR/Constant.h>

#include "ance/type/IntegerType.h"

ance::BooleanConstant::BooleanConstant(bool boolean, Application& app)
    : type_(ance::IntegerType::get(app, 1, true)), boolean_(boolean)
{
}

ance::Type* ance::BooleanConstant::type()
{
    return type_;
}

llvm::Constant* ance::BooleanConstant::buildContent(llvm::Module* m)
{
    return boolean_ ? llvm::ConstantInt::getTrue(type_->getNativeType(m->getContext()))
                    : llvm::ConstantInt::getFalse(type_->getNativeType(m->getContext()));
}

ance::BooleanConstant* ance::BooleanConstant::createFalse(Application& app)
{
    return new BooleanConstant(false, app);
}

ance::BooleanConstant* ance::BooleanConstant::createTrue(Application& app)
{
    return new BooleanConstant(true, app);
}
