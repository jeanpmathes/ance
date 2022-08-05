#include "ReferenceType.h"

#include "lang/construct/value/Value.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/VoidType.h"
#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

lang::ReferenceType::ReferenceType(lang::ResolvingHandle<lang::Type> element_type)
    : TypeDefinition(lang::Identifier::from("&" + element_type->name()))
    , element_type_(element_type)
{}

StateCount lang::ReferenceType::getStateCount() const
{
    return element_type_->getStateCount();
}

bool lang::ReferenceType::isReferenceType() const
{
    return true;
}

lang::ResolvingHandle<lang::Type> lang::ReferenceType::getElementType() const
{
    return element_type_;
}

lang::ResolvingHandle<lang::Type> lang::ReferenceType::getActualType() const
{
    lang::ResolvingHandle<lang::Type> actual_element_type = element_type_->getActualType();
    if (actual_element_type == element_type_) { return self(); }
    else {
        return lang::ReferenceType::get(actual_element_type);
    }
}

llvm::Constant* lang::ReferenceType::getDefaultContent(llvm::Module&)
{
    assert(false && "References cannot be default-initialized.");
    return nullptr;
}

llvm::PointerType* lang::ReferenceType::getContentType(llvm::LLVMContext& c) const
{
    return llvm::PointerType::get(element_type_->getContentType(c), 0);
}

bool lang::ReferenceType::validate(ValidationLogger& validation_logger, lang::Location location) const
{
    if (!element_type_->isDefined())
    {
        validation_logger.logError("Cannot declare reference to undefined type " + element_type_->getAnnotatedName(),
                                   location);
        return false;
    }

    if (element_type_->isVoidType())
    {
        validation_logger.logError("Cannot declare reference to " + lang::VoidType::get()->getAnnotatedName(),
                                   location);
        return false;
    }

    if (element_type_->isReferenceType())
    {
        validation_logger.logError("Cannot declare reference to reference", location);
        return false;
    }

    return true;
}

bool lang::ReferenceType::isSubscriptDefined()
{
    return element_type_->isSubscriptDefined();
}

lang::ResolvingHandle<lang::Type> lang::ReferenceType::getSubscriptReturnType()
{
    return element_type_->getSubscriptReturnType();
}

bool lang::ReferenceType::validateSubscript(lang::Location                    indexed_location,
                                            lang::ResolvingHandle<lang::Type> index_type,
                                            lang::Location                    index_location,
                                            ValidationLogger&                 validation_logger) const
{
    return element_type_->validateSubscript(indexed_location, index_type, index_location, validation_logger);
}

std::shared_ptr<lang::Value> lang::ReferenceType::buildSubscript(std::shared_ptr<Value> indexed,
                                                                 std::shared_ptr<Value> index,
                                                                 CompileContext*        context)
{
    return element_type_->buildSubscript(getReferenced(indexed, context), index, context);
}

bool lang::ReferenceType::isOperatorDefined(lang::BinaryOperator op, lang::ResolvingHandle<lang::Type> other)
{
    return element_type_->isOperatorDefined(op, other);
}

lang::ResolvingHandle<lang::Type> lang::ReferenceType::getOperatorResultType(lang::BinaryOperator              op,
                                                                             lang::ResolvingHandle<lang::Type> other)
{
    return element_type_->getOperatorResultType(op, other);
}

bool lang::ReferenceType::validateOperator(lang::BinaryOperator              op,
                                           lang::ResolvingHandle<lang::Type> other,
                                           lang::Location                    left_location,
                                           lang::Location                    right_location,
                                           ValidationLogger&                 validation_logger) const
{
    return element_type_->validateOperator(op, other, left_location, right_location, validation_logger);
}

std::shared_ptr<lang::Value> lang::ReferenceType::buildOperator(lang::BinaryOperator   op,
                                                                std::shared_ptr<Value> left,
                                                                std::shared_ptr<Value> right,
                                                                CompileContext*        context)
{
    return element_type_->buildOperator(op, getReferenced(left, context), right, context);
}

bool lang::ReferenceType::isOperatorDefined(lang::UnaryOperator op)
{
    return element_type_->isOperatorDefined(op);
}

lang::ResolvingHandle<lang::Type> lang::ReferenceType::getOperatorResultType(lang::UnaryOperator op)
{
    return element_type_->getOperatorResultType(op);
}

bool lang::ReferenceType::validateOperator(lang::UnaryOperator op,
                                           lang::Location      location,
                                           ValidationLogger&   validation_logger) const
{
    return element_type_->validateOperator(op, location, validation_logger);
}

std::shared_ptr<lang::Value> lang::ReferenceType::buildOperator(lang::UnaryOperator    op,
                                                                std::shared_ptr<Value> value,
                                                                CompileContext*        context)
{
    return element_type_->buildOperator(op, getReferenced(value, context), context);
}

bool lang::ReferenceType::hasMember(const lang::Identifier& name)
{
    return element_type_->hasMember(name);
}

lang::ResolvingHandle<lang::Type> lang::ReferenceType::getMemberType(const lang::Identifier& name)
{
    return element_type_->getMemberType(name);
}

bool lang::ReferenceType::validateMemberAccess(const lang::Identifier& name, ValidationLogger& validation_logger) const
{
    return element_type_->validateMemberAccess(name, validation_logger);
}

std::shared_ptr<lang::Value> lang::ReferenceType::buildMemberAccess(std::shared_ptr<Value>  value,
                                                                    const lang::Identifier& name,
                                                                    CompileContext*         context)
{
    return element_type_->buildMemberAccess(value, name, context);
}

bool lang::ReferenceType::definesIndirection()
{
    return element_type_->definesIndirection();
}

lang::ResolvingHandle<lang::Type> lang::ReferenceType::getIndirectionType()
{
    return element_type_->getIndirectionType();
}

bool lang::ReferenceType::validateIndirection(lang::Location location, ValidationLogger& validation_logger) const
{
    return element_type_->validateIndirection(location, validation_logger);
}

std::shared_ptr<lang::Value> lang::ReferenceType::buildIndirection(std::shared_ptr<Value> value,
                                                                   CompileContext*        context)
{
    return element_type_->buildIndirection(getReferenced(value, context), context);
}

void lang::ReferenceType::buildDefaultInitializer(llvm::Value*, llvm::Value*, CompileContext*)
{
    throw std::logic_error("Reference does not have a default value.");
}

void lang::ReferenceType::buildCopyInitializer(llvm::Value*, llvm::Value*, CompileContext*)
{
    throw std::logic_error("Reference does not have a copy value.");
}

void lang::ReferenceType::buildFinalizer(llvm::Value*, llvm::Value*, CompileContext*)
{
    throw std::logic_error("Reference does not have a finalizer.");
}

void lang::ReferenceType::createConstructors() {}

void lang::ReferenceType::buildNativeDeclaration(CompileContext*) {}

void lang::ReferenceType::buildNativeDefinition(CompileContext*) {}

std::string lang::ReferenceType::createMangledName() const
{
    return std::string("ref") + "(" + element_type_->getMangledName() + ")";
}

llvm::DIType* lang::ReferenceType::createDebugType(CompileContext* context)
{
    const llvm::DataLayout& dl = context->module()->getDataLayout();

    uint64_t size_in_bits = dl.getTypeSizeInBits(getContentType(*context->llvmContext()));

    llvm::DIType* di_type;

    llvm::DIType* element_di_type = element_type_->getDebugType(context);
    di_type = context->di()->createReferenceType(llvm::dwarf::DW_TAG_reference_type, element_di_type, size_in_bits);

    return di_type;
}

lang::TypeRegistry<>& lang::ReferenceType::getReferenceTypes()
{
    static lang::TypeRegistry<> reference_types;
    return reference_types;
}

lang::TypeDefinitionRegistry* lang::ReferenceType::getRegistry()
{
    return &getReferenceTypes();
}

llvm::Value* lang::ReferenceType::getReferenced(llvm::Value* value, CompileContext* context)
{
    return context->ir()->CreateLoad(getContentType(*context->llvmContext()), value, value->getName() + ".load");
}

std::shared_ptr<lang::Value> lang::ReferenceType::getReferenced(const std::shared_ptr<lang::Value>& value,
                                                                CompileContext*                     context)
{
    value->buildNativeValue(context);

    llvm::Value* native_reference = value->getNativeValue();
    llvm::Value* native_referred  = getReferenced(native_reference, context);

    return std::make_shared<lang::WrappedNativeValue>(element_type_, native_referred);
}

lang::ResolvingHandle<lang::Type> lang::ReferenceType::get(lang::ResolvingHandle<lang::Type> element_type)
{
    element_type = element_type->toSeparateUndefined();

    std::vector<lang::ResolvingHandle<lang::Type>> used_types;
    used_types.push_back(element_type);

    std::optional<lang::ResolvingHandle<lang::Type>> defined_type = getReferenceTypes().get(used_types, lang::Empty());

    if (defined_type.has_value()) { return defined_type.value(); }
    else
    {
        auto*                             reference_type = new lang::ReferenceType(element_type);
        lang::ResolvingHandle<lang::Type> type =
            lang::makeHandled<lang::Type>(std::unique_ptr<lang::ReferenceType>(reference_type));
        getReferenceTypes().add(std::move(used_types), lang::Empty(), type);

        return type;
    }
}
