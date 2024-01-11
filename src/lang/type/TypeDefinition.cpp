#include "TypeDefinition.h"

#include <stack>

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/construct/Parameter.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/type/SizeType.h"
#include "lang/type/Type.h"
#include "validation/ValidationLogger.h"

lang::TypeDefinition::TypeDefinition(lang::Identifier name, lang::Location location) : name_(name), location_(location)
{}

bool lang::TypeDefinition::isFullyDefined() const
{
    auto self = const_cast<TypeDefinition*>(this);

    for (auto dependency : self->getDeclarationDependencies())
    {
        if (dependency->getDefinition() == nullptr) return false;
    }

    for (auto dependency : self->getDefinitionDependencies())
    {
        if (dependency->getDefinition() == nullptr) return false;
    }

    return true;
}

lang::Identifier const& lang::TypeDefinition::name() const
{
    return name_;
}

std::string const& lang::TypeDefinition::getMangledName() const
{
    if (mangled_name_.empty()) { mangled_name_ = createMangledName(); }

    return mangled_name_;
}

lang::Location lang::TypeDefinition::getDefinitionLocation() const
{
    return location_;
}

bool lang::TypeDefinition::isCustom() const
{
    return false;// Most types are built-in.
}

bool lang::TypeDefinition::isImported() const
{
    return false;// Only custom types can be imported.
}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::clone(lang::Context&) const
{
    assert(!isCustom() && "TypeDefinition::clone() called on custom type definition.");
    throw std::logic_error("Not implemented");
}

lang::FixedWidthIntegerType const* lang::TypeDefinition::isFixedWidthIntegerType() const
{
    return nullptr;
}

bool lang::TypeDefinition::isFixedWidthIntegerType(uint64_t, bool) const
{
    return false;
}

bool lang::TypeDefinition::isSigned() const
{
    return false;
}

lang::IntegerType const* lang::TypeDefinition::isIntegerType() const
{
    return nullptr;
}

bool lang::TypeDefinition::isBooleanType() const
{
    return false;
}

bool lang::TypeDefinition::isCharType() const
{
    return false;
}

bool lang::TypeDefinition::isUnsignedIntegerPointerType() const
{
    return false;
}

lang::FloatingPointType const* lang::TypeDefinition::isFloatingPointType() const
{
    return nullptr;
}

bool lang::TypeDefinition::isFloatingPointType(size_t) const
{
    return false;
}

bool lang::TypeDefinition::isSizeType() const
{
    return false;
}

bool lang::TypeDefinition::isDiffType() const
{
    return false;
}

bool lang::TypeDefinition::isUnitType() const
{
    return false;
}

bool lang::TypeDefinition::isNullValueType() const
{
    return false;
}

bool lang::TypeDefinition::isPointerType() const
{
    return false;
}

lang::AddressType const* lang::TypeDefinition::isAddressType() const
{
    return nullptr;
}

bool lang::TypeDefinition::isBufferType() const
{
    return false;
}

bool lang::TypeDefinition::isOpaquePointerType() const
{
    return false;
}

bool lang::TypeDefinition::isReferenceType() const
{
    return false;
}

bool lang::TypeDefinition::isStructType() const
{
    return false;
}

lang::VectorizableType const* lang::TypeDefinition::isVectorizable() const
{
    return nullptr;
}

lang::VectorizableType* lang::TypeDefinition::isVectorizable()
{
    return nullptr;
}

lang::VectorType const* lang::TypeDefinition::isVectorType() const
{
    return nullptr;
}

lang::VectorType* lang::TypeDefinition::isVectorType()
{
    return nullptr;
}

lang::ArrayType const* lang::TypeDefinition::isArrayType() const
{
    return nullptr;
}

lang::ArrayType* lang::TypeDefinition::isArrayType()
{
    return nullptr;
}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::getElementType()
{
    return lang::Type::getUndefined();
}

lang::Type const& lang::TypeDefinition::getElementType() const
{
    static lang::ResolvingHandle<lang::Type> undefined = lang::Type::getUndefined();
    return undefined;
}

void lang::TypeDefinition::setType(lang::Type* type)
{
    assert(!type_);
    type_ = type;
}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::getActualType()
{
    return self();
}

lang::Type const& lang::TypeDefinition::getActualType() const
{
    return self();
}

lang::Accessibility const& lang::TypeDefinition::getAccessibility() const
{
    static lang::Accessibility const default_accessibility =
        lang::Accessibility(lang::AccessModifier::PRIVATE_ACCESS, lang::SourceAccessibility::BUILT_IN);

    assert(!isCustom());
    return default_accessibility;
}

void lang::TypeDefinition::setContainingScope(lang::Scope* scope)
{
    containing_scope_ = scope;
}

lang::Scope* lang::TypeDefinition::scope()
{
    assert(containing_scope_);
    return containing_scope_;
}

lang::Scope const* lang::TypeDefinition::scope() const
{
    assert(containing_scope_);
    return containing_scope_;
}

void lang::TypeDefinition::postResolve()
{
    createConstructors();
}

bool lang::TypeDefinition::requestOverload(std::vector<lang::ResolvingHandle<lang::Type>> parameters)
{
    lang::TypeDefinition* definition = getActualType()->getDefinition();
    if (definition != this) return definition->requestOverload(parameters);

    for (auto const& [constructor_parameters, function] : requested_constructors_)
    {
        if (constructor_parameters == parameters) return true;
    }

    if (acceptOverloadRequest(parameters))
    {
        requested_constructors_.emplace_back(parameters, &createConstructor(parameters));
        return true;
    }

    return false;
}

void lang::TypeDefinition::createConstructors()
{
    default_constructor_ = &createConstructor({});
}

llvm::Type* lang::TypeDefinition::getNativeType(CompileContext& context) const
{
    return llvm::PointerType::get(getContentType(context), 0);
}

Execution::Type lang::TypeDefinition::getDebugType(CompileContext& context) const
{
    if (!debug_type_.hasValue()) { debug_type_ = createDebugType(context); }

    return debug_type_.value();
}

llvm::TypeSize lang::TypeDefinition::getContentSize(CompileContext& context) const
{
    return context.exec().llvmSizeOf(self());
}

bool lang::TypeDefinition::isSubscriptDefined() const
{
    return false;
}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::getSubscriptReturnType()
{
    return lang::Type::getUndefined();
}

bool lang::TypeDefinition::isOperatorDefined(lang::BinaryOperator, lang::Type const&) const
{
    return false;
}

bool lang::TypeDefinition::isOperatorDefined(lang::UnaryOperator) const
{
    return false;
}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::getOperatorResultType(lang::BinaryOperator,
                                                                              lang::ResolvingHandle<lang::Type>)
{
    return lang::Type::getUndefined();
}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::getOperatorResultType(lang::UnaryOperator)
{
    return lang::Type::getUndefined();
}

bool lang::TypeDefinition::isImplicitlyConvertibleTo(lang::Type const&) const
{
    return false;
}

bool lang::TypeDefinition::isCastingPossibleTo(lang::Type const&) const
{
    return false;
}

bool lang::TypeDefinition::hasMember(lang::Identifier const&) const
{
    return false;
}

lang::Member& lang::TypeDefinition::getMember(lang::Identifier const& name)
{
    throw std::logic_error("Type does not have member '" + name + "'");
}

bool lang::TypeDefinition::definesIndirection() const
{
    return false;
}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::getIndirectionType()
{
    return lang::Type::getUndefined();
}

bool lang::TypeDefinition::validate(ValidationLogger&, lang::Location) const
{
    return true;
}

bool lang::TypeDefinition::validateSubscript(lang::Location, lang::Type const&, lang::Location, ValidationLogger&) const
{
    return false;
}

bool lang::TypeDefinition::validateOperator(lang::BinaryOperator,
                                            lang::Type const&,
                                            lang::Location,
                                            lang::Location,
                                            ValidationLogger&) const
{
    return false;
}

bool lang::TypeDefinition::validateOperator(lang::UnaryOperator, lang::Location, ValidationLogger&) const
{
    return false;
}

bool lang::TypeDefinition::validateImplicitConversion(lang::Type const&, lang::Location, ValidationLogger&) const
{
    return false;
}

bool lang::TypeDefinition::validateCast(lang::Type const&, lang::Location, ValidationLogger&) const
{
    return false;
}

bool lang::TypeDefinition::validateMemberAccess(lang::Identifier const&, ValidationLogger&) const
{
    return false;
}

bool lang::TypeDefinition::validateIndirection(lang::Location, ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::TypeDefinition::buildSubscript(Shared<lang::Value>, Shared<lang::Value>, CompileContext&)
{
    throw std::logic_error("Subscript not defined");
}

Shared<lang::Value> lang::TypeDefinition::buildOperator(lang::BinaryOperator,
                                                        Shared<lang::Value>,
                                                        Shared<lang::Value>,
                                                        CompileContext&)
{
    throw std::logic_error("Operator not defined");
}

Shared<lang::Value> lang::TypeDefinition::buildOperator(lang::UnaryOperator, Shared<lang::Value>, CompileContext&)
{
    throw std::logic_error("Operator not defined");
}

Shared<lang::Value> lang::TypeDefinition::buildImplicitConversion(lang::ResolvingHandle<lang::Type>,
                                                                  Shared<lang::Value>,
                                                                  CompileContext&)
{
    throw std::logic_error("Implicit conversion not defined");
}

Shared<lang::Value> lang::TypeDefinition::buildCast(lang::ResolvingHandle<lang::Type>,
                                                    Shared<lang::Value>,
                                                    CompileContext&)
{
    throw std::logic_error("Cast not defined");
}

Shared<lang::Value> lang::TypeDefinition::buildMemberAccess(Shared<lang::Value>,
                                                            lang::Identifier const&,
                                                            CompileContext&)
{
    throw std::logic_error("Member access not defined");
}

Shared<lang::Value> lang::TypeDefinition::buildIndirection(Shared<lang::Value>, CompileContext&)
{
    throw std::logic_error("Indirection not defined");
}

void lang::TypeDefinition::performDefaultInitializer(Shared<lang::Value> ptr, CompileContext& context)
{
    performDefaultInitializer(ptr, context.exec().getSizeValue(1), context);
}

void lang::TypeDefinition::performDefaultInitializer(Shared<lang::Value> ptr,
                                                     Shared<lang::Value> count,
                                                     CompileContext&     context)
{
    if (isTriviallyDefaultConstructible())
    {
        Shared<lang::Value> size = context.exec().computeAllocatedSize(self(), count);
        context.exec().performMemoryClear(ptr, size);
    }
    else if (default_initializer_.hasValue())
    {
        std::vector<Shared<lang::Value>> args;
        args.emplace_back(ptr);
        args.emplace_back(count);
        context.exec().performFunctionCall(default_initializer_.value(), args);
    }
}

void lang::TypeDefinition::performCopyInitializer(Shared<lang::Value> destination,
                                                  Shared<lang::Value> source,
                                                  CompileContext& context)
{
    if (isTriviallyCopyConstructible())
    {
        Shared<lang::Value> size = context.exec().computeAllocatedSize(self(), {});
        context.exec().performMemoryCopy(destination, source, size);
    }
    else if (copy_initializer_.hasValue())
    {
        std::vector<Shared<lang::Value>> args;
        args.emplace_back(destination);
        args.emplace_back(source);
        context.exec().performFunctionCall(copy_initializer_.value(), args);
    }
}

void lang::TypeDefinition::performFinalizer(Shared<lang::Value> ptr, CompileContext& context)
{
    performFinalizer(ptr, context.exec().getSizeValue(1), context);
}

void lang::TypeDefinition::performFinalizer(Shared<lang::Value> ptr, Shared<lang::Value> count, CompileContext& context)
{
    if (isTriviallyDestructible() || !default_finalizer_.hasValue()) return;

    std::vector<Shared<lang::Value>> args;
    args.emplace_back(ptr);
    args.emplace_back(count);
    context.exec().performFunctionCall(default_finalizer_.value(), args);
}

void lang::TypeDefinition::buildNativeDeclaration(CompileContext& context)
{
    if (isImported()) assert(getAccessibility().modifier().linkage() == llvm::GlobalValue::ExternalLinkage);

    if (!isTriviallyDefaultConstructible())
    {
        std::string const default_initializer_name = "ctor_default$" + getMangledName();
        default_initializer_parameters_.emplace_back(makeShared<Parameter>(context.ctx().getPointerType(self())));
        default_initializer_parameters_.emplace_back(makeShared<Parameter>(context.ctx().getSizeType()));

        default_initializer_ = context.exec().createFunction(lang::Identifier::like(default_initializer_name),
                                                             default_initializer_name,
                                                             getAccessibility().modifier(),
                                                             isImported(),
                                                             default_initializer_parameters_,
                                                             context.ctx().getUnitType(),
                                                             scope(),
                                                             false,
                                                             lang::Location::global(),
                                                             std::nullopt);
    }

    if (!isTriviallyCopyConstructible())
    {
        std::string const copy_initializer_name = "ctor_copy$" + getMangledName();
        copy_initializer_parameters_.emplace_back(makeShared<Parameter>(context.ctx().getPointerType(self())));
        copy_initializer_parameters_.emplace_back(makeShared<Parameter>(context.ctx().getPointerType(self())));

        copy_initializer_ = context.exec().createFunction(lang::Identifier::like(copy_initializer_name),
                                                          copy_initializer_name,
                                                          getAccessibility().modifier(),
                                                          isImported(),
                                                          copy_initializer_parameters_,
                                                          context.ctx().getUnitType(),
                                                          scope(),
                                                          false,
                                                          lang::Location::global(),
                                                          std::nullopt);
    }

    if (!isTriviallyDestructible())
    {
        std::string const default_finalizer_name = "dtor_default$" + getMangledName();
        default_finalizer_parameters_.emplace_back(makeShared<Parameter>(context.ctx().getPointerType(self())));
        default_finalizer_parameters_.emplace_back(makeShared<Parameter>(context.ctx().getSizeType()));

        default_finalizer_ = context.exec().createFunction(lang::Identifier::like(default_finalizer_name),
                                                           default_finalizer_name,
                                                           getAccessibility().modifier(),
                                                           isImported(),
                                                           default_finalizer_parameters_,
                                                           context.ctx().getUnitType(),
                                                           scope(),
                                                           false,
                                                           lang::Location::global(),
                                                           std::nullopt);
    }

    defineConstructors(context);
}

void lang::TypeDefinition::buildNativeDefinition(CompileContext& context)
{
    if (isImported()) return;

    if (!isTriviallyDefaultConstructible()) defineDefaultInitializer(context);
    if (!isTriviallyCopyConstructible()) defineCopyInitializer(context);
    if (!isTriviallyDestructible()) defineDefaultFinalizer(context);

    buildConstructors(context);
}

void lang::TypeDefinition::defineConstructors(CompileContext& context)
{
    for (auto& [parameters, constructor] : requested_constructors_) { constructor->createNativeBacking(context); }

    if (!default_constructor_) return;

    default_constructor_->createNativeBacking(context);
}

void lang::TypeDefinition::buildConstructors(CompileContext& context)
{
    for (auto& [parameters, constructor] : requested_constructors_)
    {
        buildRequestedOverload(parameters, *constructor, context);
    }

    if (!default_constructor_) return;

    lang::PredefinedFunction const& default_constructor = *default_constructor_;
    auto                            function_handle     = default_constructor.getFunctionHandle(context);

    context.exec().enterFunctionBody(function_handle);

    if (getStateCount().isUnit()) context.exec().performReturn(context.exec().getDefaultValue(self()));
    else
    {
        Shared<lang::Value> ptr = context.exec().performStackAllocation(self());
        performDefaultInitializer(ptr, context);

        Shared<lang::Value> result = context.exec().performLoadFromAddress(ptr);
        context.exec().performReturn(result);
    }
}

bool lang::TypeDefinition::isTriviallyDefaultConstructible() const
{
    return false;
}

bool lang::TypeDefinition::isTriviallyCopyConstructible() const
{
    return false;
}

bool lang::TypeDefinition::isTriviallyDestructible() const
{
    return false;
}

void lang::TypeDefinition::defineDefaultInitializer(CompileContext& context)
{
    Shared<lang::Value> ptr   = default_initializer_parameters_[0];
    Shared<lang::Value> count = default_initializer_parameters_[1];

    context.exec().enterFunctionBody(default_initializer_.value());
    context.exec().performPointerIteration(ptr, count, [&](Shared<lang::Value> element_ptr) {
        performSingleDefaultInitializerDefinition(element_ptr, context);
    });
    context.exec().performReturn({});
}

void lang::TypeDefinition::defineCopyInitializer(CompileContext& context)
{
    Shared<lang::Value> dst_ptr = copy_initializer_parameters_[0];
    Shared<lang::Value> src_ptr = copy_initializer_parameters_[1];

    context.exec().enterFunctionBody(copy_initializer_.value());
    performSingleCopyInitializerDefinition(dst_ptr, src_ptr, context);
    context.exec().performReturn({});
}

void lang::TypeDefinition::defineDefaultFinalizer(CompileContext& context)
{
    Shared<lang::Value> ptr   = default_finalizer_parameters_[0];
    Shared<lang::Value> count = default_finalizer_parameters_[1];

    context.exec().enterFunctionBody(default_finalizer_.value());
    context.exec().performPointerIteration(ptr, count, [&](Shared<lang::Value> element_ptr) {
        buildSingleDefaultFinalizerDefinition(element_ptr, context);
    });
    context.exec().performReturn({});
}

void lang::TypeDefinition::performSingleDefaultInitializerDefinition(Shared<lang::Value> ptr, CompileContext& context)
{
    if (getStateCount().isUnit()) return;

    Shared<lang::Value> initial = context.exec().getDefaultValue(self());
    context.exec().performStoreToAddress(ptr, initial);
}

void lang::TypeDefinition::performSingleCopyInitializerDefinition(Shared<lang::Value> dst_ptr,
                                                                  Shared<lang::Value> src_ptr,
                                                                  CompileContext&     context)
{
    if (getStateCount().isUnit()) return;

    Shared<lang::Value> value = context.exec().performLoadFromAddress(src_ptr);
    context.exec().performStoreToAddress(dst_ptr, value);
}

void lang::TypeDefinition::buildSingleDefaultFinalizerDefinition(Shared<lang::Value>, CompileContext&) {}

std::vector<lang::ResolvingHandle<lang::Type>> lang::TypeDefinition::getDeclarationDependencies()
{
    return {};
}

std::vector<lang::ResolvingHandle<lang::Type>> lang::TypeDefinition::getDefinitionDependencies()
{
    return {};
}

lang::PredefinedFunction& lang::TypeDefinition::createConstructor(
    std::vector<lang::ResolvingHandle<lang::Type>> parameter_types)
{
    lang::OwningHandle<lang::Function> function = lang::OwningHandle<lang::Function>::takeOwnership(
        lang::makeHandled<lang::Function>(lang::Identifier::like(name() + "$constructor")));

    size_t count = 1;

    std::vector<Shared<lang::Parameter>> parameters;
    for (auto& parameter_type : parameter_types)
    {
        std::string const parameter_name = "p" + std::to_string(count++);
        parameters.push_back(makeShared<lang::Parameter>(parameter_type,
                                                         lang::Location::global(),
                                                         lang::Identifier::like(parameter_name),
                                                         lang::Location::global()));
    }

    lang::PredefinedFunction& predefined_function = function->defineAsPredefined(self(),
                                                                                 true,
                                                                                 parameters,
                                                                                 getAccessibility().modifier(),
                                                                                 isImported(),
                                                                                 *scope(),
                                                                                 lang::Location::global());

    predefined_function.setCallValidator(
        [this](std::vector<std::pair<std::reference_wrapper<lang::Value const>, lang::Location>> const& arguments,
               lang::Location                                                                           location,
               ValidationLogger& validation_logger) {
            if (arguments.size() == 1)
            {
                auto const& [argument, argument_location] = arguments[0];

                if (argument.get().type().isImplicitlyConvertibleTo(self()))
                {
                    validation_logger.logWarning("Unnecessary conversion constructor, use implicit conversion",
                                                 location);
                }
            }

            return true;
        });

    self()->addFunction(std::move(function));

    return predefined_function;
}

bool lang::TypeDefinition::acceptOverloadRequest(std::vector<ResolvingHandle<lang::Type>>)
{
    return false;
}

void lang::TypeDefinition::buildRequestedOverload(std::vector<lang::ResolvingHandle<lang::Type>>,
                                                  lang::PredefinedFunction&,
                                                  CompileContext&)
{}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::self() const
{
    assert(type_);
    return type_->self();
}
