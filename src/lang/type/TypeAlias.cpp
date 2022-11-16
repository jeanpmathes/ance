#include "TypeAlias.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/scope/Scope.h"
#include "lang/type/Type.h"
#include "lang/type/VoidType.h"
#include "lang/utility/Identifier.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

lang::TypeAlias::TypeAlias(lang::Identifier                  name,
                           lang::ResolvingHandle<lang::Type> actual,
                           lang::Location                    definition_location,
                           lang::Location                    actual_type_location)
    : lang::TypeDefinition(name, definition_location)
    , actual_(actual)
    , actual_type_location_(actual_type_location)
{}

StateCount lang::TypeAlias::getStateCount() const
{
    return actual_->getStateCount();
}

lang::FixedWidthIntegerType const* lang::TypeAlias::isFixedWidthIntegerType() const
{
    return actual_->isFixedWidthIntegerType();
}

bool lang::TypeAlias::isSigned() const
{
    return actual_->isSigned();
}

bool lang::TypeAlias::isFixedWidthIntegerType(uint64_t bit_size, bool is_signed) const
{
    return actual_->isFixedWidthIntegerType(bit_size, is_signed);
}

bool lang::TypeAlias::isBooleanType() const
{
    return actual_->isBooleanType();
}

lang::IntegerType const* lang::TypeAlias::isIntegerType() const
{
    return actual_->isIntegerType();
}

lang::FloatingPointType const* lang::TypeAlias::isFloatingPointType() const
{
    return actual_->isFloatingPointType();
}

bool lang::TypeAlias::isFloatingPointType(size_t precision) const
{
    return actual_->isFloatingPointType(precision);
}

bool lang::TypeAlias::isSizeType() const
{
    return actual_->isSizeType();
}

bool lang::TypeAlias::isDiffType() const
{
    return actual_->isDiffType();
}

bool lang::TypeAlias::isVoidType() const
{
    return actual_->isVoidType();
}

bool lang::TypeAlias::isPointerType() const
{
    return actual_->isPointerType();
}

bool lang::TypeAlias::isReferenceType() const
{
    return actual_->isReferenceType();
}

lang::ResolvingHandle<lang::Type> lang::TypeAlias::getElementType() const
{
    return actual_->getElementType();
}

bool lang::TypeAlias::isUnsignedIntegerPointerType() const
{
    return actual_->isUnsignedIntegerPointerType();
}

bool lang::TypeAlias::isNullValueType() const
{
    return actual_->isNullValueType();
}

bool lang::TypeAlias::isAddressType() const
{
    return actual_->isAddressType();
}

bool lang::TypeAlias::isBufferType() const
{
    return actual_->isBufferType();
}

bool lang::TypeAlias::isOpaquePointerType() const
{
    return actual_->isOpaquePointerType();
}

bool lang::TypeAlias::isStructType() const
{
    return actual_->isStructType();
}

lang::VectorizableType const* lang::TypeAlias::isVectorizable() const
{
    return actual_->isVectorizable();
}

lang::VectorizableType* lang::TypeAlias::isVectorizable()
{
    return actual_->isVectorizable();
}

lang::VectorType const* lang::TypeAlias::isVectorType() const
{
    return actual_->isVectorType();
}

lang::VectorType* lang::TypeAlias::isVectorType()
{
    return actual_->isVectorType();
}

lang::ArrayType const* lang::TypeAlias::isArrayType() const
{
    return actual_->isArrayType();
}

lang::ArrayType* lang::TypeAlias::isArrayType()
{
    return actual_->isArrayType();
}

lang::ResolvingHandle<lang::Type> lang::TypeAlias::getActualType() const
{
    if (!actually_actual_.has_value())
    {
        lang::ResolvingHandle<lang::Type> current = actual_;

        while (current != current->getActualType()) { current = current->getActualType(); }

        actually_actual_.emplace(current);
    }

    return actually_actual_.value();
}

void lang::TypeAlias::onScope()
{
    scope()->addType(actual_);
}

llvm::Constant* lang::TypeAlias::getDefaultContent(llvm::Module& m)
{
    return actual_->getDefaultContent(m);
}

llvm::Type* lang::TypeAlias::getContentType(llvm::LLVMContext& c) const
{
    return actual_->getContentType(c);
}

bool lang::TypeAlias::validateDefinition(ValidationLogger& validation_logger) const
{
    if (is_valid_) return is_valid_.value();

    bool valid = true;

    if (actual_->getDefinition() == this)
    {
        validation_logger.logError("Cannot alias self", actual_type_location_);
        valid = false;
    }

    if (lang::validation::isTypeUndefined(actual_, actual_type_location_, validation_logger)) { valid = false; }

    if (actual_ == lang::VoidType::get())// Prevent infinite recursion.
    {
        validation_logger.logError("Cannot create alias for 'void' type", getDefinitionLocation());
        valid = false;
    }

    valid = valid && checkDependencies(validation_logger);

    is_valid_ = valid && actual_->validate(validation_logger, actual_type_location_);
    return is_valid_.value();
}

bool lang::TypeAlias::validate(ValidationLogger& validation_logger, lang::Location) const
{
    return validateDefinition(validation_logger);
}

bool lang::TypeAlias::isSubscriptDefined()
{
    return actual_->isSubscriptDefined();
}

lang::ResolvingHandle<lang::Type> lang::TypeAlias::getSubscriptReturnType()
{
    return actual_->getSubscriptReturnType();
}

bool lang::TypeAlias::validateSubscript(lang::Location                    indexed_location,
                                        lang::ResolvingHandle<lang::Type> index_type,
                                        lang::Location                    index_location,
                                        ValidationLogger&                 validation_logger) const
{
    return actual_->validateSubscript(indexed_location, index_type, index_location, validation_logger);
}

std::shared_ptr<lang::Value> lang::TypeAlias::buildSubscript(std::shared_ptr<Value> indexed,
                                                             std::shared_ptr<Value> index,
                                                             CompileContext&        context)
{
    return actual_->buildSubscript(indexed, index, context);
}

bool lang::TypeAlias::isImplicitlyConvertibleTo(lang::ResolvingHandle<lang::Type> other)
{
    return actual_->isImplicitlyConvertibleTo(other);
}

bool lang::TypeAlias::validateImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                 lang::Location                    location,
                                                 ValidationLogger&                 validation_logger) const
{
    return actual_->validateImplicitConversion(other, location, validation_logger);
}

std::shared_ptr<lang::Value> lang::TypeAlias::buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                                      std::shared_ptr<Value>            value,
                                                                      CompileContext&                   context)
{
    return actual_->buildImplicitConversion(other, value, context);
}

bool lang::TypeAlias::isOperatorDefined(lang::BinaryOperator op, lang::ResolvingHandle<lang::Type> other)
{
    return actual_->isOperatorDefined(op, other);
}

lang::ResolvingHandle<lang::Type> lang::TypeAlias::getOperatorResultType(lang::BinaryOperator              op,
                                                                         lang::ResolvingHandle<lang::Type> other)
{
    return actual_->getOperatorResultType(op, other);
}

bool lang::TypeAlias::validateOperator(lang::BinaryOperator              op,
                                       lang::ResolvingHandle<lang::Type> other,
                                       lang::Location                    left_location,
                                       lang::Location                    right_location,
                                       ValidationLogger&                 validation_logger) const
{
    return actual_->validateOperator(op, other, left_location, right_location, validation_logger);
}

std::shared_ptr<lang::Value> lang::TypeAlias::buildOperator(lang::BinaryOperator   op,
                                                            std::shared_ptr<Value> left,
                                                            std::shared_ptr<Value> right,
                                                            CompileContext&        context)
{
    return actual_->buildOperator(op, left, right, context);
}

bool lang::TypeAlias::hasMember(lang::Identifier const& name)
{
    return actual_->hasMember(name);
}

lang::ResolvingHandle<lang::Type> lang::TypeAlias::getMemberType(lang::Identifier const& name)
{
    return actual_->getMemberType(name);
}

bool lang::TypeAlias::validateMemberAccess(lang::Identifier const& name, ValidationLogger& validation_logger) const
{
    return actual_->validateMemberAccess(name, validation_logger);
}

std::shared_ptr<lang::Value> lang::TypeAlias::buildMemberAccess(std::shared_ptr<Value>  value,
                                                                lang::Identifier const& name,
                                                                CompileContext&         context)
{
    return actual_->buildMemberAccess(value, name, context);
}

bool lang::TypeAlias::definesIndirection()
{
    return actual_->definesIndirection();
}

lang::ResolvingHandle<lang::Type> lang::TypeAlias::getIndirectionType()
{
    return actual_->getIndirectionType();
}

bool lang::TypeAlias::validateIndirection(lang::Location location, ValidationLogger& validation_logger) const
{
    return actual_->validateIndirection(location, validation_logger);
}

std::shared_ptr<lang::Value> lang::TypeAlias::buildIndirection(std::shared_ptr<Value> value, CompileContext& context)
{
    return actual_->buildIndirection(value, context);
}

void lang::TypeAlias::buildDefaultInitializer(llvm::Value* ptr, llvm::Value* count, CompileContext& context)
{
    actual_->buildDefaultInitializer(ptr, count, context);
}

void lang::TypeAlias::buildCopyInitializer(llvm::Value* ptr, llvm::Value* count, CompileContext& context)
{
    actual_->buildCopyInitializer(ptr, count, context);
}

void lang::TypeAlias::buildFinalizer(llvm::Value* ptr, llvm::Value* count, CompileContext& context)
{
    actual_->buildFinalizer(ptr, count, context);
}

void lang::TypeAlias::createConstructors()
{
    if (hasCyclicDependency()) return;
    if (isVoidType() || isReferenceType()) return;

    TypeDefinition::createConstructors();
}

void lang::TypeAlias::buildNativeDeclaration(CompileContext& context)
{
    defineConstructors(context);
}

void lang::TypeAlias::buildNativeDefinition(CompileContext& context)
{
    buildConstructors(context);
}

std::string lang::TypeAlias::createMangledName() const
{
    return getActualType()->getMangledName();
}

llvm::DIType* lang::TypeAlias::createDebugType(CompileContext& context)
{
    return context.di()->createTypedef(actual_->getDebugType(context),
                                       name().text(),
                                       context.getSourceFile(getDefinitionLocation()),
                                       static_cast<unsigned>(getDefinitionLocation().line()),
                                       scope()->getDebugScope(context));
}

std::vector<lang::TypeDefinition*> lang::TypeAlias::getDependencies() const
{
    std::vector<lang::TypeDefinition*> dependencies;
    if (actual_->isDefined()) dependencies.push_back(actual_->getDefinition());

    return dependencies;
}
