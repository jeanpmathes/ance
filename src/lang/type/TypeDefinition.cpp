#include "TypeDefinition.h"

#include <map>
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
    throw std::logic_error("Not implemented.");
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

llvm::Type* lang::TypeDefinition::getNativeType(llvm::LLVMContext& c) const
{
    return llvm::PointerType::get(getContentType(c), 0);
}

llvm::DIType* lang::TypeDefinition::getDebugType(CompileContext& context) const
{
    if (!debug_type_) { debug_type_ = createDebugType(context); }

    return debug_type_;
}

llvm::TypeSize lang::TypeDefinition::getNativeSize(llvm::Module& m)
{
    return m.getDataLayout().getTypeAllocSize(getNativeType(m.getContext()));
}

llvm::TypeSize lang::TypeDefinition::getContentSize(llvm::Module& m)
{
    return m.getDataLayout().getTypeAllocSize(getContentType(m.getContext()));
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

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::getMemberType(lang::Identifier const&)
{
    return lang::Type::getUndefined();
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

Shared<lang::Value> lang::TypeDefinition::buildSubscript(Shared<Value>, Shared<Value>, CompileContext&)
{
    throw std::logic_error("Subscript not defined");
}

Shared<lang::Value> lang::TypeDefinition::buildOperator(lang::BinaryOperator,
                                                        Shared<Value>,
                                                        Shared<Value>,
                                                        CompileContext&)
{
    throw std::logic_error("Operator not defined");
}

Shared<lang::Value> lang::TypeDefinition::buildOperator(lang::UnaryOperator, Shared<Value>, CompileContext&)
{
    throw std::logic_error("Operator not defined");
}

Shared<lang::Value> lang::TypeDefinition::buildImplicitConversion(lang::ResolvingHandle<lang::Type>,
                                                                  Shared<Value>,
                                                                  CompileContext&)
{
    throw std::logic_error("Implicit conversion not defined");
}

Shared<lang::Value> lang::TypeDefinition::buildCast(lang::ResolvingHandle<lang::Type>, Shared<Value>, CompileContext&)
{
    throw std::logic_error("Cast not defined");
}

Shared<lang::Value> lang::TypeDefinition::buildMemberAccess(Shared<Value>, lang::Identifier const&, CompileContext&)
{
    throw std::logic_error("Member access not defined");
}

Shared<lang::Value> lang::TypeDefinition::buildIndirection(Shared<Value>, CompileContext&)
{
    throw std::logic_error("Indirection not defined");
}

void lang::TypeDefinition::buildDefaultInitializer(llvm::Value* ptr, CompileContext& context)
{
    llvm::APInt const count_value = llvm::APInt(lang::SizeType::getSizeWidth(), 1);
    llvm::Type*       count_type  = context.types().getSizeType()->getContentType(context.llvmContext());

    llvm::Value* count = llvm::ConstantInt::get(count_type, count_value);

    buildDefaultInitializer(ptr, count, context);
}

void lang::TypeDefinition::buildDefaultInitializer(llvm::Value* ptr, llvm::Value* count, CompileContext& context)
{
    if (isTriviallyDefaultConstructible())
    {
        llvm::Value* element_size =
            llvm::ConstantInt::get(context.types().getSizeType()->getContentType(context.llvmContext()),
                                   getContentSize(context.llvmModule()).getFixedSize(),
                                   false);

        llvm::Value* size = context.ir().CreateMul(count, element_size, count->getName() + ".mul");

        context.ir().CreateMemSet(ptr,
                                  llvm::ConstantInt::get(llvm::Type::getInt8Ty(context.llvmContext()), 0),
                                  size,
                                  llvm::Align(1));

        return;
    }

    if (!default_initializer_) return;

    context.ir().CreateCall(default_initializer_, {ptr, count});
}

void lang::TypeDefinition::buildCopyInitializer(llvm::Value* ptr, llvm::Value* original, CompileContext& context)
{
    if (isTriviallyCopyConstructible())
    {
        context.ir().CreateMemCpy(ptr,
                                  llvm::Align(1),
                                  original,
                                  llvm::Align(1),
                                  getContentSize(context.llvmModule()).getFixedSize());
        return;
    }

    if (!copy_initializer_) return;

    context.ir().CreateCall(copy_initializer_, {ptr, original});
}

void lang::TypeDefinition::buildFinalizer(llvm::Value* ptr, CompileContext& context)
{
    llvm::APInt const count_value = llvm::APInt(lang::SizeType::getSizeWidth(), 1);
    llvm::Type*       count_type  = context.types().getSizeType()->getContentType(context.llvmContext());

    llvm::Value* count = llvm::ConstantInt::get(count_type, count_value);

    buildFinalizer(ptr, count, context);
}

void lang::TypeDefinition::buildFinalizer(llvm::Value* ptr, llvm::Value* count, CompileContext& context)
{
    if (isTriviallyDestructible() || !default_finalizer_) return;

    context.ir().CreateCall(default_finalizer_, {ptr, count});
}

void lang::TypeDefinition::buildNativeDeclaration(CompileContext& context)
{
    if (isImported()) assert(getAccessibility().modifier().linkage() == llvm::GlobalValue::ExternalLinkage);

    if (!isTriviallyDefaultConstructible())
    {
        llvm::FunctionType* default_initializer_type =
            llvm::FunctionType::get(llvm::Type::getVoidTy(context.llvmContext()),
                                    {getNativeType(context.llvmContext()),
                                     context.types().getSizeType()->getContentType(context.llvmContext())},
                                    false);

        default_initializer_ = llvm::Function::Create(default_initializer_type,
                                                      getAccessibility().modifier().linkage(),
                                                      "ctor_default$" + getMangledName(),
                                                      context.llvmModule());

        lang::Function::setImportExportAttributes(default_initializer_,
                                                  getAccessibility().modifier(),
                                                  isImported(),
                                                  context);
    }

    if (!isTriviallyCopyConstructible())
    {
        llvm::FunctionType* copy_initializer_type =
            llvm::FunctionType::get(llvm::Type::getVoidTy(context.llvmContext()),
                                    {getNativeType(context.llvmContext()), getNativeType(context.llvmContext())},
                                    false);

        copy_initializer_ = llvm::Function::Create(copy_initializer_type,
                                                   getAccessibility().modifier().linkage(),
                                                   "ctor_copy$" + getMangledName(),
                                                   context.llvmModule());

        lang::Function::setImportExportAttributes(copy_initializer_,
                                                  getAccessibility().modifier(),
                                                  isImported(),
                                                  context);
    }

    if (!isTriviallyDestructible())
    {
        llvm::FunctionType* default_finalizer_type =
            llvm::FunctionType::get(llvm::Type::getVoidTy(context.llvmContext()),
                                    {getNativeType(context.llvmContext()),
                                     scope()->context().getSizeType()->getContentType(context.llvmContext())},
                                    false);

        default_finalizer_ = llvm::Function::Create(default_finalizer_type,
                                                    getAccessibility().modifier().linkage(),
                                                    "dtor_default$" + getMangledName(),
                                                    context.llvmModule());

        lang::Function::setImportExportAttributes(default_finalizer_,
                                                  getAccessibility().modifier(),
                                                  isImported(),
                                                  context);
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
    auto [native_fn_type, native_fn]                    = default_constructor.getNativeRepresentation();

    llvm::BasicBlock* block = llvm::BasicBlock::Create(context.llvmContext(), "block", native_fn);
    context.ir().SetInsertPoint(block);

    if (getStateCount().isUnit())
        context.ir().CreateRet(llvm::Constant::getNullValue(getContentType(context.llvmContext())));
    else
    {
        llvm::Value* ptr = context.ir().CreateAlloca(getContentType(context.llvmContext()), nullptr, "alloca");
        buildDefaultInitializer(ptr, context);
        llvm::Value* val = context.ir().CreateLoad(getContentType(context.llvmContext()), ptr, "load");
        context.ir().CreateRet(val);
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
    llvm::Value* ptr   = default_initializer_->getArg(0);
    llvm::Value* count = default_initializer_->getArg(1);

    buildPointerIteration(
        default_initializer_,
        ptr,
        count,
        [this](llvm::Value* element_ptr, CompileContext& c_context) {
            buildSingleDefaultInitializerDefinition(element_ptr, c_context);
        },
        context);
}

void lang::TypeDefinition::defineCopyInitializer(CompileContext& context)
{
    llvm::Value* dst_ptr = copy_initializer_->getArg(0);
    llvm::Value* src_ptr = copy_initializer_->getArg(1);

    llvm::BasicBlock* block = llvm::BasicBlock::Create(context.llvmContext(), "block", copy_initializer_);
    context.ir().SetInsertPoint(block);
    {
        buildSingleCopyInitializerDefinition(dst_ptr, src_ptr, context);
        context.ir().CreateRetVoid();
    }
}

void lang::TypeDefinition::defineDefaultFinalizer(CompileContext& context)
{
    llvm::Value* ptr   = default_finalizer_->getArg(0);
    llvm::Value* count = default_finalizer_->getArg(1);

    buildPointerIteration(
        default_finalizer_,
        ptr,
        count,
        [this](llvm::Value* element_ptr, CompileContext& c_context) {
            buildSingleDefaultFinalizerDefinition(element_ptr, c_context);
        },
        context);
}

void lang::TypeDefinition::buildSingleDefaultInitializerDefinition(llvm::Value* ptr, CompileContext& context)
{
    if (getStateCount().isUnit()) return;

    llvm::Value* content = getDefaultContent(context.llvmModule());
    context.ir().CreateStore(content, ptr);
}

void lang::TypeDefinition::buildSingleCopyInitializerDefinition(llvm::Value*    dst_ptr,
                                                                llvm::Value*    src_ptr,
                                                                CompileContext& context)
{
    if (getStateCount().isUnit()) return;

    llvm::Type* content_type = getContentType(context.llvmContext());

    llvm::Value* src_content = context.ir().CreateLoad(content_type, src_ptr);
    context.ir().CreateStore(src_content, dst_ptr);
}

void lang::TypeDefinition::buildSingleDefaultFinalizerDefinition(llvm::Value*, CompileContext&) {}

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
                                                                                 true,// Preserve unit return type.
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

void lang::TypeDefinition::buildPointerIteration(llvm::Function*                                    function,
                                                 llvm::Value*                                       ptr,
                                                 llvm::Value*                                       count,
                                                 std::function<void(llvm::Value*, CompileContext&)> operation,
                                                 CompileContext&                                    context) const
{
    llvm::Type* size_type = context.types().getSizeType()->getContentType(context.llvmContext());

    llvm::BasicBlock* init = llvm::BasicBlock::Create(context.llvmContext(), "init", function);
    llvm::BasicBlock* body = llvm::BasicBlock::Create(context.llvmContext(), "body", function);
    llvm::BasicBlock* end  = llvm::BasicBlock::Create(context.llvmContext(), "end", function);

    context.ir().SetInsertPoint(init);
    {
        context.ir().CreateBr(body);
    }

    context.ir().SetInsertPoint(body);
    {
        llvm::PHINode* current_index = context.ir().CreatePHI(size_type, 2, "i");
        current_index->addIncoming(llvm::ConstantInt::get(size_type, 0), init);

        llvm::Value* element_ptr = getStateCount().isUnit()
                                     ? ptr
                                     : context.ir().CreateInBoundsGEP(getContentType(context.llvmContext()),
                                                                      ptr,
                                                                      current_index,
                                                                      "element_ptr");
        operation(element_ptr, context);

        llvm::Value* next_index = context.ir().CreateAdd(current_index, llvm::ConstantInt::get(size_type, 1), "next");
        current_index->addIncoming(next_index, body);

        llvm::Value* condition = context.ir().CreateICmpULT(next_index, count, "condition");
        context.ir().CreateCondBr(condition, body, end);
    }

    context.ir().SetInsertPoint(end);
    {
        context.ir().CreateRetVoid();
    }
}
