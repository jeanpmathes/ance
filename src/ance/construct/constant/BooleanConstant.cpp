#include "BooleanConstant.h"

#include "ance/type/IntegerType.h"
#include "ance/type/Type.h"

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

std::shared_ptr<ance::BooleanConstant> ance::BooleanConstant::createFalse()
{
    return std::shared_ptr<ance::BooleanConstant>(new BooleanConstant(false));
}

std::shared_ptr<ance::BooleanConstant> ance::BooleanConstant::createTrue()
{
    return std::shared_ptr<ance::BooleanConstant>(new BooleanConstant(true));
}
