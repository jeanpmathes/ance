#include "PointerType.h"

#include "lang/construct/value/Value.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/ReferenceType.h"
#include "lang/type/SizeType.h"
#include "lang/type/VoidType.h"
#include "lang/utility/Values.h"
#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

lang::PointerType::PointerType(lang::ResolvingHandle<lang::Type> element_type)
    : TypeDefinition("*" + element_type->getName())
    , element_type_(element_type)
    , element_reference_(lang::ReferenceType::get(element_type))
{}

bool lang::PointerType::isPointerType() const
{
    return true;
}

lang::ResolvingHandle<lang::Type> lang::PointerType::getElementType() const
{
    return element_type_;
}

lang::ResolvingHandle<lang::Type> lang::PointerType::getActualType()
{
    lang::ResolvingHandle<lang::Type> actual_element_type = element_type_->getActualType();
    if (actual_element_type == element_type_) { return self(); }
    else {
        return lang::PointerType::get(actual_element_type);
    }
}

llvm::Constant* lang::PointerType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantPointerNull::get(getContentType(c));
}

llvm::PointerType* lang::PointerType::getContentType(llvm::LLVMContext& c)
{
    llvm::Type* native_type;

    if (element_type_->isVoidType()) { native_type = llvm::Type::getInt8PtrTy(c); }
    else {
        native_type = element_type_->getContentType(c);
    }

    return llvm::PointerType::get(native_type, 0);
}

bool lang::PointerType::validate(ValidationLogger& validation_logger, lang::Location location)
{
    if (!element_type_->isDefined())
    {
        validation_logger.logError("Cannot declare pointer to undefined type" + element_type_->getAnnotatedName(),
                                   location);
        return false;
    }

    if (element_type_->isReferenceType())
    {
        validation_logger.logError("Cannot declare pointers to reference types", location);
        return false;
    }

    return true;
}

bool lang::PointerType::isSubscriptDefined()
{
    return true;
}

lang::ResolvingHandle<lang::Type> lang::PointerType::getSubscriptReturnType()
{
    return element_reference_;
}

bool lang::PointerType::validateSubscript(lang::Location,
                                          lang::ResolvingHandle<lang::Type> index_type,
                                          lang::Location                    index_location,
                                          ValidationLogger&                 validation_logger)
{
    return lang::Type::checkMismatch(lang::SizeType::getSize(), index_type, index_location, validation_logger);
}

std::shared_ptr<lang::Value> lang::PointerType::buildSubscript(std::shared_ptr<Value> indexed,
                                                               std::shared_ptr<Value> index,
                                                               CompileContext*        context)
{
    index = lang::Type::makeMatching(lang::SizeType::getSize(), index, context);

    llvm::Value* element_ptr  = buildGetElementPointer(indexed, index, context);
    llvm::Value* native_value = lang::Values::contentToNative(element_reference_, element_ptr, context);

    return std::make_shared<lang::WrappedNativeValue>(getSubscriptReturnType(), native_value);
}

llvm::Value* lang::PointerType::buildGetElementPointer(const std::shared_ptr<lang::Value>& indexed,
                                                       const std::shared_ptr<lang::Value>& index,
                                                       CompileContext*                     context)
{
    indexed->buildContentValue(context);
    index->buildContentValue(context);

    llvm::Value* native_index = index->getContentValue();
    llvm::Value* indices[]    = {native_index};

    llvm::Value* ptr = indexed->getContentValue();//Pointer to content is instead of pointer to pointer is required.

    llvm::Value* element_ptr =
        context->ir()->CreateGEP(element_type_->getContentType(*context->llvmContext()), ptr, indices);
    return element_ptr;
}

std::string lang::PointerType::createMangledName()
{
    return std::string("ptr") + "(" + element_type_->getMangledName() + ")";
}

llvm::DIType* lang::PointerType::createDebugType(CompileContext* context)
{
    const llvm::DataLayout& dl = context->module()->getDataLayout();

    uint64_t size_in_bits = dl.getTypeSizeInBits(getContentType(*context->llvmContext()));

    llvm::DIType* di_type;

    if (element_type_->isVoidType())
    {
        std::string name     = getName();
        auto        encoding = llvm::dwarf::DW_ATE_address;

        di_type = context->di()->createBasicType(name, size_in_bits, encoding);
    }
    else {
        llvm::DIType* element_di_type = element_type_->getDebugType(context);

        di_type = context->di()->createPointerType(element_di_type, size_in_bits);
    }

    return di_type;
}

lang::TypeRegistry<>& lang::PointerType::getPointerTypes()
{
    static TypeRegistry<> pointer_types;
    return pointer_types;
}

lang::TypeDefinitionRegistry* lang::PointerType::getRegistry()
{
    return &getPointerTypes();
}

lang::ResolvingHandle<lang::Type> lang::PointerType::get(lang::ResolvingHandle<lang::Type> element_type)
{
    std::vector<lang::ResolvingHandle<lang::Type>> used_types;
    used_types.push_back(element_type);

    std::optional<lang::ResolvingHandle<lang::Type>> defined_type = getPointerTypes().get(used_types, lang::Empty());

    if (defined_type.has_value()) { return defined_type.value(); }
    else {
        auto*                             pointer_type = new lang::PointerType(element_type);
        lang::ResolvingHandle<lang::Type> type =
            lang::makeHandled<lang::Type>(std::unique_ptr<lang::PointerType>(pointer_type));
        getPointerTypes().add(std::move(used_types), lang::Empty(), type);

        return type;
    }
}
