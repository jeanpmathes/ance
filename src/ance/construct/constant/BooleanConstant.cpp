#include "BooleanConstant.h"

#include "ance/type/IntegerType.h"

ance::BooleanConstant::BooleanConstant(bool boolean) : type_(ance::IntegerType::get(1, true)), boolean_(boolean) {}

ance::Type* ance::BooleanConstant::type()
{
    return type_;
}

llvm::Constant* ance::BooleanConstant::buildContent(llvm::Module* m)
{
    return boolean_ ? llvm::ConstantInt::getTrue(type_->getContentType(m->getContext()))
                    : llvm::ConstantInt::getFalse(type_->getContentType(m->getContext()));
}

ance::BooleanConstant* ance::BooleanConstant::createFalse()
{
    return new BooleanConstant(false);
}

ance::BooleanConstant* ance::BooleanConstant::createTrue()
{
    return new BooleanConstant(true);
}
