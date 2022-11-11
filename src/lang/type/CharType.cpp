#include "CharType.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/construct/value/Value.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/type/BooleanType.h"
#include "lang/type/Type.h"
#include "lang/utility/Values.h"

lang::CharType::CharType() : TypeDefinition(lang::Identifier::from("char")) {}

StateCount lang::CharType::getStateCount() const
{
    size_t state_count = 1ULL << SIZE_IN_BITS;
    return state_count;
}

bool lang::CharType::isCharType() const
{
    return true;
}

llvm::Constant* lang::CharType::getDefaultContent(llvm::Module& m)
{
    return llvm::ConstantInt::get(getContentType(m.getContext()), 0, false);
}

llvm::Type* lang::CharType::getContentType(llvm::LLVMContext& c) const
{
    return llvm::Type::getIntNTy(c, static_cast<unsigned>(SIZE_IN_BITS));
}

bool lang::CharType::acceptOverloadRequest(const std::vector<lang::ResolvingHandle<lang::Type>>& parameters)
{
    if (parameters.size() == 1 && parameters[0]->isFixedWidthIntegerType(SIZE_IN_BITS, false)) return true;

    return false;
}

void lang::CharType::buildRequestedOverload(const std::vector<lang::ResolvingHandle<lang::Type>>& parameters,
                                            lang::PredefinedFunction&                             function,
                                            CompileContext&                                       context)
{
    llvm::Function* native_function;
    std::tie(std::ignore, native_function) = function.getNativeRepresentation();

    if (parameters.size() == 1 && parameters[0]->isFixedWidthIntegerType(SIZE_IN_BITS, false))
    {
        llvm::BasicBlock* block = llvm::BasicBlock::Create(*context.llvmContext(), "block", native_function);
        context.ir()->SetInsertPoint(block);
        {
            llvm::Value* original = native_function->getArg(0);
            context.ir()->CreateRet(original);
        }

        return;
    }
}

bool lang::CharType::isOperatorDefined(lang::BinaryOperator op, lang::ResolvingHandle<lang::Type> other)
{
    if (not op.isEquality()) return false;

    other = lang::Type::getReferencedType(other);
    return other->isCharType();
}

lang::ResolvingHandle<lang::Type> lang::CharType::getOperatorResultType(lang::BinaryOperator op,
                                                                        lang::ResolvingHandle<lang::Type>)
{
    if (op.isEquality()) return lang::BooleanType::get();

    return lang::Type::getUndefined();
}

bool lang::CharType::validateOperator(lang::BinaryOperator,
                                      lang::ResolvingHandle<lang::Type>,
                                      lang::Location,
                                      lang::Location,
                                      ValidationLogger&) const
{
    return true;
}

std::shared_ptr<lang::Value> lang::CharType::buildOperator(lang::BinaryOperator   op,
                                                           std::shared_ptr<Value> left,
                                                           std::shared_ptr<Value> right,
                                                           CompileContext&        context)
{
    right = lang::Type::getValueOrReferencedValue(right, context);

    left->buildContentValue(context);
    right->buildContentValue(context);

    llvm::Value* left_value  = left->getContentValue();
    llvm::Value* right_value = right->getContentValue();

    llvm::Value* result;

    switch (op)
    {
        case lang::BinaryOperator::EQUAL:
            result = context.ir()->CreateICmpEQ(left_value, right_value, left_value->getName() + ".icmp");
            break;
        case lang::BinaryOperator::NOT_EQUAL:
            result = context.ir()->CreateICmpNE(left_value, right_value, left_value->getName() + ".icmp");
            break;

        default:
            return nullptr;
    }

    lang::ResolvingHandle<lang::Type> result_type   = getOperatorResultType(op, right->type());
    llvm::Value*                      native_result = lang::Values::contentToNative(result_type, result, context);

    return std::make_shared<lang::WrappedNativeValue>(result_type, native_result);
}

bool lang::CharType::isTriviallyDefaultConstructible() const
{
    return true;
}

bool lang::CharType::isTriviallyCopyConstructible() const
{
    return true;
}

bool lang::CharType::isTriviallyDestructible() const
{
    return true;
}

std::string lang::CharType::createMangledName() const
{
    return "c";
}

llvm::DIType* lang::CharType::createDebugType(CompileContext& context)
{
    std::string name = std::string(this->name().text());

    return context.di()->createBasicType(name, SIZE_IN_BITS, llvm::dwarf::DW_ATE_UCS);
}

lang::ResolvingHandle<lang::Type> lang::CharType::get()
{
    static lang::ResolvingHandle<lang::Type> instance =
        lang::makeHandled<lang::Type>(std::unique_ptr<lang::TypeDefinition>(new CharType()));
    return instance;
}
