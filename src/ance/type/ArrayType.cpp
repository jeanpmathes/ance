#include "ArrayType.h"

#include "ance/construct/value/Value.h"
#include "ance/construct/value/WrappedNativeValue.h"
#include "ance/scope/GlobalScope.h"
#include "ance/type/ReferenceType.h"
#include "ance/type/SizeType.h"
#include "ance/utility/Values.h"
#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

ance::ArrayType::ArrayType(ance::ResolvingHandle<ance::Type> element_type, const uint64_t size)
    : TypeDefinition("[" + element_type->getName() + "; " + std::to_string(size) + "]")
    , size_(size)
    , element_type_(element_type)
    , element_reference_(ance::ReferenceType::get(element_type))
{}

ance::ResolvingHandle<ance::Type> ance::ArrayType::getElementType() const
{
    return element_type_;
}

ance::ResolvingHandle<ance::Type> ance::ArrayType::getActualType()
{
    ance::ResolvingHandle<ance::Type> actual_element_type = element_type_->getActualType();
    if (actual_element_type == element_type_) { return self(); }
    else
    {
        return ance::ArrayType::get(actual_element_type, size_);
    }
}

llvm::Constant* ance::ArrayType::getDefaultContent(llvm::LLVMContext& c)
{
    std::vector<llvm::Constant*> content(size_, element_type_->getDefaultContent(c));
    return llvm::ConstantArray::get(getContentType(c), content);
}

llvm::ArrayType* ance::ArrayType::getContentType(llvm::LLVMContext& c)
{
    if (!type_) { type_ = llvm::ArrayType::get(element_type_->getContentType(c), size_); }

    return type_;
}

bool ance::ArrayType::validate(ValidationLogger& validation_logger, ance::Location location)
{
    if (!element_type_->isDefined())
    {
        validation_logger.logError("Cannot declare array of undefined type '" + element_type_->getAnnotatedName() + "'",
                                   location);
        return false;
    }

    if (element_type_->isReferenceType())
    {
        validation_logger.logError("Cannot declare arrays of reference types", location);
        return false;
    }

    return true;
}

bool ance::ArrayType::isSubscriptDefined()
{
    return true;
}

ance::ResolvingHandle<ance::Type> ance::ArrayType::getSubscriptReturnType()
{
    return element_reference_;
}

bool ance::ArrayType::validateSubscript(ance::Location,
                                        ance::ResolvingHandle<ance::Type> index_type,
                                        ance::Location                    index_location,
                                        ValidationLogger&                 validation_logger)
{
    return ance::Type::checkMismatch(ance::SizeType::getSize(), index_type, index_location, validation_logger);
}

std::shared_ptr<ance::Value> ance::ArrayType::buildSubscript(std::shared_ptr<Value> indexed,
                                                             std::shared_ptr<Value> index,
                                                             CompileContext*        context)
{
    index = ance::Type::makeMatching(ance::SizeType::getSize(), index, context);

    llvm::Value* element_ptr  = buildGetElementPointer(indexed, index, context);
    llvm::Value* native_value = ance::Values::contentToNative(element_reference_, element_ptr, context);

    return std::make_shared<ance::WrappedNativeValue>(getSubscriptReturnType(), native_value);
}

llvm::Value* ance::ArrayType::buildGetElementPointer(const std::shared_ptr<ance::Value>& indexed,
                                                     const std::shared_ptr<ance::Value>& index,
                                                     CompileContext*                     context) const
{
    indexed->buildNativeValue(context);
    index->buildContentValue(context);

    llvm::Value* zero         = llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context->llvmContext()), 0);
    llvm::Value* native_index = index->getContentValue();
    llvm::Value* indices[]    = {zero, native_index};

    llvm::Value* array_ptr =
        indexed->getNativeValue();// This is a pointer as the internal storage of arrays is using pointers.

    // Check if index is smaller than size.
    llvm::Value* native_size =
        llvm::ConstantInt::get(ance::SizeType::getSize()->getContentType(*context->llvmContext()), size_);
    llvm::Value* in_bounds = context->ir()->CreateICmpULT(native_index, native_size);

    in_bounds->setName("..inbounds");

    // todo: use in_bounds bool to throw exception

    llvm::Value* element_ptr = context->ir()->CreateGEP(array_ptr, indices);
    return element_ptr;
}

std::string ance::ArrayType::createMangledName()
{
    return std::string("(") + element_type_->getMangledName() + ")x(" + std::to_string(size_) + std::string(")");
}

llvm::DIType* ance::ArrayType::createDebugType(CompileContext* context)
{
    const llvm::DataLayout& dl         = context->module()->getDataLayout();
    llvm::Type*             array_type = getContentType(*context->llvmContext());

    uint64_t      size            = dl.getTypeSizeInBits(array_type) / 8;
    uint32_t      alignment       = dl.getABITypeAlignment(array_type);
    llvm::DIType* element_di_type = element_type_->getDebugType(context);

    llvm::SmallVector<llvm::Metadata*, 1> subscripts;
    subscripts.push_back(context->di()->getOrCreateSubrange(0, (int64_t) size_));

    return context->di()->createArrayType(size,
                                          alignment,
                                          element_di_type,
                                          context->di()->getOrCreateArray(subscripts));
}

ance::TypeRegistry<uint64_t>& ance::ArrayType::getArrayTypes()
{
    static ance::TypeRegistry<uint64_t> array_types;
    return array_types;
}

ance::TypeDefinitionRegistry* ance::ArrayType::getRegistry()
{
    return &getArrayTypes();
}

ance::ResolvingHandle<ance::Type> ance::ArrayType::get(ance::ResolvingHandle<ance::Type> element_type, uint64_t size)
{
    std::vector<ance::ResolvingHandle<ance::Type>> used_types;
    used_types.push_back(element_type);

    std::optional<ance::ResolvingHandle<ance::Type>> defined_type = getArrayTypes().get(used_types, size);

    if (defined_type.has_value()) { return defined_type.value(); }
    else
    {
        auto*                             array_type = new ance::ArrayType(element_type, size);
        ance::ResolvingHandle<ance::Type> type =
            ance::makeHandled<ance::Type>(std::unique_ptr<ance::ArrayType>(array_type));
        getArrayTypes().add(std::move(used_types), size, type);

        return type;
    }
}
