#include "ReferenceType.h"

#include "ance/construct/value/Value.h"
#include "ance/construct/value/WrappedNativeValue.h"
#include "ance/scope/GlobalScope.h"
#include "ance/type/Type.h"
#include "ance/type/VoidType.h"
#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

ance::ReferenceType::ReferenceType(ance::ResolvingHandle<ance::Type> element_type)
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
    if (!element_type_->isDefined())
    {
        validation_logger.logError("Cannot declare reference to undefined type '" + element_type_->getName() + "'",
                                   location);
        return false;
    }

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

ance::ResolvingHandle<ance::Type> ance::ReferenceType::getSubscriptReturnType()
{
    return element_type_->getSubscriptReturnType();
}

bool ance::ReferenceType::validateSubscript(ance::Location                    indexed_location,
                                            ance::ResolvingHandle<ance::Type> index_type,
                                            ance::Location                    index_location,
                                            ValidationLogger&                 validation_logger)
{
    return element_type_->validateSubscript(indexed_location, index_type, index_location, validation_logger);
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

ance::TypeRegistry<>& ance::ReferenceType::getReferenceTypes()
{
    static ance::TypeRegistry<> reference_types;
    return reference_types;
}

ance::TypeDefinitionRegistry* ance::ReferenceType::getRegistry()
{
    return &getReferenceTypes();
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

ance::ResolvingHandle<ance::Type> ance::ReferenceType::get(ance::ResolvingHandle<ance::Type> element_type)
{
    std::vector<ance::ResolvingHandle<ance::Type>> used_types;
    used_types.push_back(element_type);

    std::optional<ance::ResolvingHandle<ance::Type>> defined_type = getReferenceTypes().get(used_types, ance::Empty());

    if (defined_type.has_value()) { return defined_type.value(); }
    else
    {
        auto*                             reference_type = new ance::ReferenceType(element_type);
        ance::ResolvingHandle<ance::Type> type =
            ance::makeHandled<ance::Type>(std::unique_ptr<ance::ReferenceType>(reference_type));
        getReferenceTypes().add(std::move(used_types), ance::Empty(), type);

        return type;
    }
}

bool ance::ReferenceType::isReferenceType(ance::ResolvingHandle<ance::Type> type)
{
    auto* ref_type = dynamic_cast<ance::ReferenceType*>(type->getDefinition());
    return ref_type != nullptr;
}

ance::ResolvingHandle<ance::Type> ance::ReferenceType::getReferencedType(ance::ResolvingHandle<ance::Type> type)
{
    auto ref_type = dynamic_cast<ance::ReferenceType*>(type->getDefinition());
    return ref_type ? ref_type->element_type_ : ance::VoidType::get();
}
