#include "IntegerConstant.h"

#include <utility>

#include "IntegerType.h"

ance::IntegerConstant::IntegerConstant(llvm::APInt integer, bool is_signed, ance::Scope* scope)
    : type_(ance::IntegerType::get(scope, integer.getBitWidth(), is_signed)),
      integer_(std::move(integer)), constant_(nullptr)
{
}

ance::Type* ance::IntegerConstant::get_type()
{
    return type_;
}

llvm::Constant* ance::IntegerConstant::get_constant(llvm::LLVMContext& c)
{
    if (!constant_)
    {
        constant_ = llvm::ConstantInt::get(type_->get_native_type(c), integer_);
    }

    return constant_;
}
