#include "UnsignedIntegerPointerType.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"

lang::UnsignedIntegerPointerType::UnsignedIntegerPointerType() : TypeDefinition(lang::Identifier::from("uiptr")) {}

bool lang::UnsignedIntegerPointerType::isUnsignedIntegerPointerType() const
{
    return true;
}

bool lang::UnsignedIntegerPointerType::acceptOverloadRequest(
    const std::vector<lang::ResolvingHandle<lang::Type>>& parameters)
{
    if (parameters.size() == 1 && parameters[0]->isAddressType()) return true;

    return IntegerType::acceptOverloadRequest(parameters);
}

void lang::UnsignedIntegerPointerType::buildRequestedOverload(
    const std::vector<lang::ResolvingHandle<lang::Type>>& parameters,
    lang::PredefinedFunction&                             function,
    CompileContext&                                       context)
{
    if (parameters.size() == 1) { buildRequestedOverload(parameters[0], self(), function, context); }
}

void lang::UnsignedIntegerPointerType::buildRequestedOverload(lang::ResolvingHandle<lang::Type> parameter_element,
                                                              lang::ResolvingHandle<lang::Type> return_type,
                                                              lang::PredefinedFunction&         function,
                                                              CompileContext&                   context)
{
    llvm::Function* native_function;
    std::tie(std::ignore, native_function) = function.getNativeRepresentation();

    if (parameter_element->isAddressType())
    {
        llvm::BasicBlock* block = llvm::BasicBlock::Create(*context.llvmContext(), "block", native_function);
        context.ir()->SetInsertPoint(block);
        {
            llvm::Value* original = native_function->getArg(0);

            llvm::Value* converted = context.ir()->CreatePtrToInt(original,
                                                                  return_type->getContentType(*context.llvmContext()),
                                                                  original->getName() + ".ptrtoint");

            context.ir()->CreateRet(converted);
        }

        return;
    }

    IntegerType::buildRequestedOverload(parameter_element, return_type, function, context);
}

std::string lang::UnsignedIntegerPointerType::createMangledName() const
{
    return std::string(name().text());
}

void lang::UnsignedIntegerPointerType::init(llvm::LLVMContext&, llvm::DataLayout& data_layout)
{
    assert(size_ == 0);

    size_ = std::max(static_cast<unsigned int>(MINIMUM_BIT_SIZE), data_layout.getPointerSizeInBits());
}

unsigned int lang::UnsignedIntegerPointerType::sizeInBits()
{
    assert(size_ != 0);
    return size_;
}

lang::ResolvingHandle<lang::Type> lang::UnsignedIntegerPointerType::get()
{
    static lang::ResolvingHandle<lang::Type> instance =
        lang::makeHandled<lang::Type>(std::unique_ptr<lang::TypeDefinition>(new UnsignedIntegerPointerType()));
    return instance;
}

std::optional<size_t> lang::UnsignedIntegerPointerType::getBitSize() const
{
    return std::nullopt;
}

size_t lang::UnsignedIntegerPointerType::getNativeBitSize() const
{
    return size_;
}

bool lang::UnsignedIntegerPointerType::isSigned() const
{
    return false;
}

size_t lang::UnsignedIntegerPointerType::getMinimumBitSize() const
{
    return MINIMUM_BIT_SIZE;
}

std::string lang::UnsignedIntegerPointerType::getSuffix() const
{
    return "uiptr";
}
