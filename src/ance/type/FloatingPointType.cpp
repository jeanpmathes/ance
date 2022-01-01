#include "FloatingPointType.h"

#include "ance/construct/value/WrappedNativeValue.h"
#include "ance/type/Type.h"
#include "ance/utility/Values.h"
#include "compiler/CompileContext.h"

std::string ance::FloatingPointType::createMangledName()
{
    return getName();
}

llvm::DIType* ance::FloatingPointType::createDebugType(CompileContext* context)
{
    const llvm::DataLayout& dl = context->module()->getDataLayout();

    std::string name         = getName();
    uint64_t    size_in_bits = dl.getTypeSizeInBits(getContentType(*context->llvmContext()));
    auto        encoding     = llvm::dwarf::DW_ATE_float;

    return context->di()->createBasicType(name, size_in_bits, encoding);
}

bool ance::FloatingPointType::isFloatingPointType() const
{
    return true;
}

bool ance::FloatingPointType::isOperatorDefined(BinaryOperator, ance::ResolvingHandle<ance::Type> other)
{
    if (other->isFloatingPointType())
    {
        auto other_type = dynamic_cast<FloatingPointType*>(other->getActualType()->getDefinition());
        return this == other_type;
    }

    return false;
}

ance::ResolvingHandle<ance::Type> ance::FloatingPointType::getOperatorResultType(BinaryOperator,
                                                                                 ance::ResolvingHandle<ance::Type>)
{
    return self();
}

bool ance::FloatingPointType::validateOperator(BinaryOperator,
                                               ance::ResolvingHandle<ance::Type>,
                                               ance::Location,
                                               ance::Location,
                                               ValidationLogger&)
{
    return true;
}

std::shared_ptr<ance::Value> ance::FloatingPointType::buildOperator(BinaryOperator         op,
                                                                    std::shared_ptr<Value> left,
                                                                    std::shared_ptr<Value> right,
                                                                    CompileContext*        context)
{
    left->buildContentValue(context);
    right->buildContentValue(context);

    llvm::Value* left_value  = left->getContentValue();
    llvm::Value* right_value = right->getContentValue();

    llvm::Value* result;

    switch (op)
    {
        case BinaryOperator::ADDITION:
            result = context->ir()->CreateFAdd(left_value, right_value);
            break;
        case BinaryOperator::SUBTRACTION:
            result = context->ir()->CreateFSub(left_value, right_value);
            break;
        case BinaryOperator::MULTIPLICATION:
            result = context->ir()->CreateFMul(left_value, right_value);
            break;
        case BinaryOperator::DIVISION:
            result = context->ir()->CreateFDiv(left_value, right_value);
            break;
        case BinaryOperator::MODULO:
            result = context->ir()->CreateFRem(left_value, right_value);
            break;
    }

    llvm::Value* native_result = ance::Values::contentToNative(self(), result, context);
    return std::make_shared<ance::WrappedNativeValue>(self(), native_result);
}
