#include "ReferenceType.h"

#include "ance/construct/value/Value.h"
#include "ance/construct/value/WrappedNativeValue.h"
#include "ance/scope/GlobalScope.h"
#include "ance/type/Type.h"
#include "ance/type/VoidType.h"
#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

ance::ReferenceType::ReferenceType(ance::Type* element_type)
    : TypeDefinition("&" + element_type->getName())
    , element_type_(element_type)
{}

llvm::Constant* ance::ReferenceType::getDefaultContent(llvm::LLVMContext&)
{
    assert(false && "References cannot be default-initialized.");
    return nullptr;
}

llvm::PointerType* ance::ReferenceType::getContentType(llvm::LLVMContext& c)
{
    return llvm::PointerType::get(element_type_->getContentType(c), 0);
}

bool ance::ReferenceType::validate(ValidationLogger& validation_logger, ance::Location location)
{
    if (element_type_ == ance::VoidType::get())
    {
        validation_logger.logError("Cannot declare reference to '" + ance::VoidType::get()->getName() + "'", location);
        return false;
    }

    if (ance::ReferenceType::isReferenceType(element_type_))
    {
        validation_logger.logError("Cannot declare reference to reference", location);
        return false;
    }

    return true;
}

bool ance::ReferenceType::isSubscriptDefined()
{
    return element_type_->isSubscriptDefined();
}

ance::Type* ance::ReferenceType::getSubscriptReturnType()
{
    return element_type_->getSubscriptReturnType();
}

bool ance::ReferenceType::validateSubscript(Type*,
                                            ance::Location    indexed_location,
                                            Type*             index_type,
                                            ance::Location    index_location,
                                            ValidationLogger& validation_logger)
{
    return element_type_->validateSubscript(element_type_,
                                            indexed_location,
                                            index_type,
                                            index_location,
                                            validation_logger);
}

std::shared_ptr<ance::Value> ance::ReferenceType::buildSubscript(std::shared_ptr<Value> indexed,
                                                                 std::shared_ptr<Value> index,
                                                                 CompileContext*        context)
{
    return element_type_->buildSubscript(getReferenced(indexed, context), index, context);
}

llvm::DIType* ance::ReferenceType::createDebugType(CompileContext* context)
{
    const llvm::DataLayout& dl = context->module()->getDataLayout();

    uint64_t size_in_bits = dl.getTypeSizeInBits(getContentType(*context->llvmContext()));

    llvm::DIType* di_type;

    llvm::DIType* element_di_type = element_type_->getDebugType(context);
    di_type = context->di()->createReferenceType(llvm::dwarf::DW_TAG_reference_type, element_di_type, size_in_bits);

    return di_type;
}

std::map<ance::Type*, ance::Type*>& ance::ReferenceType::getReferenceTypes()
{
    static std::map<ance::Type*, ance::Type*> reference_types;
    return reference_types;
}

llvm::Value* ance::ReferenceType::getReferenced(llvm::Value* value, CompileContext* context)
{
    return context->ir()->CreateLoad(value);
}

std::shared_ptr<ance::Value> ance::ReferenceType::getReferenced(const std::shared_ptr<ance::Value>& value,
                                                                CompileContext*                     context)
{
    value->buildNativeValue(context);

    llvm::Value* native_reference = value->getNativeValue();
    llvm::Value* native_referred  = getReferenced(native_reference, context);

    return std::make_shared<ance::WrappedNativeValue>(element_type_, native_referred);
}

ance::Type* ance::ReferenceType::get(ance::Type* element_type)
{
    auto        it   = getReferenceTypes().find(element_type);
    ance::Type* type = nullptr;

    if (it == getReferenceTypes().end())
    {
        auto* reference_type = new ance::ReferenceType(element_type);
        type                 = new ance::Type(std::unique_ptr<ance::ReferenceType>(reference_type));
        getReferenceTypes().insert(std::make_pair(element_type, type));
    }
    else
    {
        type = it->second;
    }

    return type;
}

bool ance::ReferenceType::isReferenceType(ance::Type* type)
{
    auto* ref_type = dynamic_cast<ance::ReferenceType*>(type->getDefinition());
    return ref_type != nullptr;
}

ance::Type* ance::ReferenceType::getReferencedType(ance::Type* type)
{
    auto ref_type = dynamic_cast<ance::ReferenceType*>(type->getDefinition());
    return ref_type ? ref_type->element_type_ : nullptr;
}
