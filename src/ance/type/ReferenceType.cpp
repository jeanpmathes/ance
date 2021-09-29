#include "ReferenceType.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>

#include "ance/construct/value/Value.h"
#include "ance/construct/value/WrappedNativeValue.h"
#include "ance/scope/GlobalScope.h"
#include "ance/type/VoidType.h"
#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

ance::ReferenceType::ReferenceType(ance::Type* element_type) : element_type_(element_type) {}

std::string ance::ReferenceType::getName()
{
    return "&" + element_type_->getName();
}

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

bool ance::ReferenceType::isIndexerDefined(Indexer indexer)
{
    return element_type_->isIndexerDefined(indexer);
}

ance::Type* ance::ReferenceType::getIndexerReturnType()
{
    return element_type_->getIndexerReturnType();
}

bool ance::ReferenceType::validateGetIndexer(ance::Value*      indexed,
                                             ance::Location    indexed_location,
                                             ance::Value*      index,
                                             ance::Location    index_location,
                                             ValidationLogger& validation_logger)
{
    return element_type_->validateGetIndexer(indexed, indexed_location, index, index_location, validation_logger);
}

ance::Value* ance::ReferenceType::buildGetIndexer(ance::Value* indexed, ance::Value* index, CompileContext* context)
{
    return element_type_->buildGetIndexer(indexed, index, context);
}

void ance::ReferenceType::validateSetIndexer(ance::Value*      indexed,
                                             ance::Location    indexed_location,
                                             ance::Value*      index,
                                             ance::Location    index_location,
                                             ance::Value*      value,
                                             ance::Location    value_location,
                                             ValidationLogger& validation_logger)
{
    element_type_->validateSetIndexer(indexed,
                                      indexed_location,
                                      index,
                                      index_location,
                                      value,
                                      value_location,
                                      validation_logger);
}

void ance::ReferenceType::buildSetIndexer(ance::Value*    indexed,
                                          ance::Value*    index,
                                          ance::Value*    value,
                                          CompileContext* context)
{
    element_type_->buildSetIndexer(indexed, index, value, context);
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
llvm::Value* ance::ReferenceType::getReferenced(llvm::Value* value, CompileContext* context)
{
    return context->ir()->CreateLoad(value);
}

ance::Value* ance::ReferenceType::getReferenced(ance::Value* value, CompileContext* context)
{
    assert(value->type() == this);

    value->buildNativeValue(context);

    llvm::Value* native_reference = value->getNativeValue();
    llvm::Value* native_referred  = getReferenced(native_reference, context);

    return new ance::WrappedNativeValue(element_type_, native_referred);
}

ance::Type* ance::ReferenceType::get(Application& app, ance::Type* element_type)
{
    auto*       type      = new ance::ReferenceType(element_type);
    std::string type_name = type->getName();

    if (app.globalScope()->isTypeRegistered(type_name))
    {
        delete type;
        return app.globalScope()->getType(type_name);
    }
    else
    {
        app.globalScope()->registerType(type);
        return type;
    }
}

bool ance::ReferenceType::isReferenceType(ance::Type* type)
{
    ance::Type* ref_type = dynamic_cast<ance::ReferenceType*>(type);
    return ref_type != nullptr;
}

ance::Type* ance::ReferenceType::getReferencedType(ance::Type* type)
{
    auto ref_type = dynamic_cast<ance::ReferenceType*>(type);
    return ref_type ? ref_type->element_type_ : nullptr;
}
