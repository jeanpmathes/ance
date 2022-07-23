#include "TypeClone.h"

#include "lang/scope/Scope.h"
#include "lang/type/Type.h"
#include "lang/type/VoidType.h"
#include "validation/ValidationLogger.h"

lang::TypeClone::TypeClone(lang::Identifier                  name,
                           lang::ResolvingHandle<lang::Type> original,
                           lang::Location                    definition_location,
                           lang::Location                    original_type_location)
    : lang::TypeDefinition(name, definition_location)
    , original_(original)
    , original_type_location_(original_type_location)
{}

StateCount lang::TypeClone::getStateCount() const
{
    return original_->getStateCount();
}

bool lang::TypeClone::isIntegerType() const
{
    return original_->isIntegerType();
}

bool lang::TypeClone::isIntegerType(uint64_t bit_size, bool is_signed) const
{
    return original_->isIntegerType(bit_size, is_signed);
}

bool lang::TypeClone::isBooleanType() const
{
    return original_->isBooleanType();
}

bool lang::TypeClone::isFloatingPointType() const
{
    return original_->isFloatingPointType();
}

bool lang::TypeClone::isFloatingPointType(size_t precision) const
{
    return original_->isFloatingPointType(precision);
}

bool lang::TypeClone::isSizeType() const
{
    return original_->isSizeType();
}

bool lang::TypeClone::isDiffType() const
{
    return original_->isDiffType();
}

bool lang::TypeClone::isVoidType() const
{
    return original_->isVoidType();
}

bool lang::TypeClone::isPointerType() const
{
    return original_->isPointerType();
}

bool lang::TypeClone::isReferenceType() const
{
    return original_->isReferenceType();
}

lang::ResolvingHandle<lang::Type> lang::TypeClone::getElementType() const
{
    return original_->getElementType();
}

lang::ResolvingHandle<lang::Type> lang::TypeClone::getOriginalType() const
{
    return original_;
}

void lang::TypeClone::onScope()
{
    scope()->addType(original_);
}

llvm::Constant* lang::TypeClone::getDefaultContent(llvm::Module& m)
{
    return original_->getDefaultContent(m);
}

llvm::Type* lang::TypeClone::getContentType(llvm::LLVMContext& c)
{
    return original_->getContentType(c);
}

bool lang::TypeClone::validateDefinition(ValidationLogger& validation_logger) const
{
    if (is_valid_) return is_valid_.value();

    bool valid = true;

    if (!original_->isDefined())
    {
        validation_logger.logError("Cannot clone undefined type " + original_->getAnnotatedName(),
                                   original_type_location_);
        valid = false;
    }

    if (original_->getDefinition() == this)
    {
        validation_logger.logError("Cannot clone self", original_type_location_);
        valid = false;
    }

    if (original_ == lang::VoidType::get())// Prevent infinite recursion.
    {
        validation_logger.logError("Cannot create clone of 'void' type", getDefinitionLocation());
        valid = false;
    }

    valid = valid && checkDependencies(validation_logger);

    if (valid)// These checks depend on the definition being roughly valid.
    {
        if (original_
                ->isReferenceType())// Could currently cause problems, as conversion requires actual reference type.
        {
            validation_logger.logError("Cannot clone reference type " + original_->getAnnotatedName(),
                                       original_type_location_);
            valid = false;
        }

        valid &= original_->validate(validation_logger, original_type_location_);
    }

    is_valid_ = valid;
    return is_valid_.value();
}

bool lang::TypeClone::validate(ValidationLogger& validation_logger, lang::Location) const
{
    return validateDefinition(validation_logger);
}

bool lang::TypeClone::isSubscriptDefined()
{
    return original_->isSubscriptDefined();
}

lang::ResolvingHandle<lang::Type> lang::TypeClone::getSubscriptReturnType()
{
    return original_->getSubscriptReturnType();
}

bool lang::TypeClone::validateSubscript(lang::Location                    indexed_location,
                                        lang::ResolvingHandle<lang::Type> index_type,
                                        lang::Location                    index_location,
                                        ValidationLogger&                 validation_logger) const
{
    return original_->validateSubscript(indexed_location, index_type, index_location, validation_logger);
}

std::shared_ptr<lang::Value> lang::TypeClone::buildSubscript(std::shared_ptr<Value> indexed,
                                                             std::shared_ptr<Value> index,
                                                             CompileContext*        context)
{
    return original_->buildSubscript(indexed, index, context);
}

bool lang::TypeClone::hasMember(const lang::Identifier& name)
{
    return original_->hasMember(name);
}

lang::ResolvingHandle<lang::Type> lang::TypeClone::getMemberType(const lang::Identifier& name)
{
    return original_->getMemberType(name);
}

bool lang::TypeClone::validateMemberAccess(const lang::Identifier& name, ValidationLogger& validation_logger) const
{
    return original_->validateMemberAccess(name, validation_logger);
}

std::shared_ptr<lang::Value> lang::TypeClone::buildMemberAccess(std::shared_ptr<Value>  value,
                                                                const lang::Identifier& name,
                                                                CompileContext*         context)
{
    return original_->buildMemberAccess(value, name, context);
}

bool lang::TypeClone::definesIndirection()
{
    return original_->definesIndirection();
}

lang::ResolvingHandle<lang::Type> lang::TypeClone::getIndirectionType()
{
    return original_->getIndirectionType();
}

bool lang::TypeClone::validateIndirection(lang::Location location, ValidationLogger& validation_logger) const
{
    return original_->validateIndirection(location, validation_logger);
}

std::shared_ptr<lang::Value> lang::TypeClone::buildIndirection(std::shared_ptr<Value> value, CompileContext* context)
{
    return original_->buildIndirection(value, context);
}

void lang::TypeClone::buildDefaultInitializer(llvm::Value* ptr, llvm::Value* count, CompileContext* context)
{
    original_->buildDefaultInitializer(ptr, count, context);
}

void lang::TypeClone::buildCopyInitializer(llvm::Value* ptr, llvm::Value* original, CompileContext* context)
{
    original_->buildCopyInitializer(ptr, original, context);
}

void lang::TypeClone::buildFinalizer(llvm::Value* ptr, llvm::Value* count, CompileContext* context)
{
    original_->buildFinalizer(ptr, count, context);
}

void lang::TypeClone::buildNativeDeclaration(CompileContext*) {}

void lang::TypeClone::buildNativeDefinition(CompileContext*) {}

llvm::DIType* lang::TypeClone::createDebugType(CompileContext* context)
{
    return original_->getDebugType(context);
}

std::vector<lang::TypeDefinition*> lang::TypeClone::getDependencies() const
{
    std::vector<lang::TypeDefinition*> dependencies;
    if (original_->isDefined()) dependencies.push_back(original_->getDefinition());

    return dependencies;
}
std::string lang::TypeClone::createMangledName()
{
    return "clone(" + std::string(name().text()) + ")";
}
