#include "BooleanType.h"

#include "compiler/CompileContext.h"
#include "lang/type/Type.h"
#include "lang/construct/value/Value.h"
#include "lang/utility/Values.h"
#include "lang/construct/value/WrappedNativeValue.h"

lang::BooleanType::BooleanType() : TypeDefinition(lang::Identifier::from("bool")) {}

StateCount lang::BooleanType::getStateCount() const
{
    size_t count = 2;
    return count;
}

bool lang::BooleanType::isBooleanType() const
{
    return true;
}

llvm::Constant* lang::BooleanType::getDefaultContent(llvm::Module& m)
{
    return llvm::ConstantInt::get(getContentType(m.getContext()), 0, false);
}

llvm::Type* lang::BooleanType::getContentType(llvm::LLVMContext& c)
{
    if (!native_type_) { native_type_ = llvm::Type::getInt1Ty(c); }

    return native_type_;
}

bool lang::BooleanType::isTriviallyDefaultConstructible() const
{
    return true;
}

bool lang::BooleanType::isTriviallyCopyConstructible() const
{
    return true;
}

bool lang::BooleanType::isTriviallyDestructible() const
{
    return true;
}

std::string lang::BooleanType::createMangledName()
{
    return "b";
}

llvm::DIType* lang::BooleanType::createDebugType(CompileContext* context)
{
    const llvm::DataLayout& dl = context->module()->getDataLayout();

    std::string name         = std::string(this->name().text());
    uint64_t    size_in_bits = dl.getTypeSizeInBits(getContentType(*context->llvmContext()));

    return context->di()->createBasicType(name, size_in_bits, llvm::dwarf::DW_ATE_boolean);
}

lang::ResolvingHandle<lang::Type> lang::BooleanType::get()
{
    static lang::ResolvingHandle<lang::Type> instance =
        lang::makeHandled<lang::Type>(std::unique_ptr<lang::TypeDefinition>(new BooleanType()));
    return instance;
}

bool lang::BooleanType::isOperatorDefined(lang::UnaryOperator op)
{
    return op == lang::UnaryOperator::NOT;
}

lang::ResolvingHandle<lang::Type> lang::BooleanType::getOperatorResultType(lang::UnaryOperator)
{
    return self();
}

bool lang::BooleanType::validateOperator(lang::UnaryOperator, lang::Location, ValidationLogger&) const
{
    return true;
}

std::shared_ptr<lang::Value> lang::BooleanType::buildOperator(lang::UnaryOperator    op,
                                                              std::shared_ptr<Value> value,
                                                              CompileContext*        context)
{
    value->buildContentValue(context);
    llvm::Value* content_value = value->getContentValue();

    llvm::Value* result;

    switch (op)
    {
        case lang::UnaryOperator::NOT:
            result = context->ir()->CreateNot(content_value, content_value->getName() + ".not");
            break;

        default:
            throw std::logic_error("Unsupported unary operator.");
    }

    lang::ResolvingHandle<lang::Type> result_type   = getOperatorResultType(op);
    llvm::Value*                      native_result = lang::Values::contentToNative(result_type, result, context);
    return std::make_shared<lang::WrappedNativeValue>(result_type, native_result);
}
