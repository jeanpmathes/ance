#include "TypeDefinition.h"

#include <map>
#include <set>
#include <stack>

#include "compiler/CompileContext.h"
#include "lang/construct/Function.h"
#include "lang/construct/Parameter.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/type/SizeType.h"
#include "lang/type/Type.h"
#include "lang/type/VoidType.h"
#include "validation/ValidationLogger.h"

lang::TypeDefinition::TypeDefinition(lang::Identifier name, lang::Location location)
    : name_(std::move(name))
    , location_(location)
{}

const lang::Identifier& lang::TypeDefinition::name() const
{
    return name_;
}

const std::string& lang::TypeDefinition::getMangledName()
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
    return !location_.isGlobal();
}

bool lang::TypeDefinition::isIntegerType() const
{
    return false;
}

bool lang::TypeDefinition::isIntegerType(uint64_t, bool) const
{
    return false;
}

bool lang::TypeDefinition::isBooleanType() const
{
    return false;
}

bool lang::TypeDefinition::isFloatingPointType() const
{
    return false;
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

bool lang::TypeDefinition::isVoidType() const
{
    return false;
}

bool lang::TypeDefinition::isPointerType() const
{
    return false;
}

bool lang::TypeDefinition::isReferenceType() const
{
    return false;
}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::getElementType() const
{
    return lang::VoidType::get();
}

void lang::TypeDefinition::setType(lang::Type* type)
{
    assert(!type_);
    type_ = type;
}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::getActualType() const
{
    return self();
}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::getOriginalType() const
{
    return self();
}

lang::AccessModifier lang::TypeDefinition::getAccessModifier() const
{
    return lang::AccessModifier::PRIVATE_ACCESS;
}

void lang::TypeDefinition::setContainingScope(lang::Scope* scope)
{
    if (containing_scope_) return;
    containing_scope_ = scope;

    onScope();
}

void lang::TypeDefinition::postResolve()
{
    createConstructors();
}

void lang::TypeDefinition::createConstructors()
{
    default_constructor_ = &createConstructor({});
}

void lang::TypeDefinition::onScope() {}

lang::Scope* lang::TypeDefinition::scope()
{
    assert(containing_scope_);
    return containing_scope_;
}

llvm::Type* lang::TypeDefinition::getNativeType(llvm::LLVMContext& c)
{
    return llvm::PointerType::get(getContentType(c), 0);
}

llvm::DIType* lang::TypeDefinition::getDebugType(CompileContext* context)
{
    if (!debug_type_) { debug_type_ = createDebugType(context); }

    return debug_type_;
}

llvm::TypeSize lang::TypeDefinition::getNativeSize(llvm::Module* m)
{
    if (self() == lang::VoidType::get()) return llvm::TypeSize::getNull();

    return m->getDataLayout().getTypeAllocSize(getNativeType(m->getContext()));
}

llvm::TypeSize lang::TypeDefinition::getContentSize(llvm::Module* m)
{
    if (self() == lang::VoidType::get()) return llvm::TypeSize::getNull();

    return m->getDataLayout().getTypeAllocSize(getContentType(m->getContext()));
}

bool lang::TypeDefinition::isSubscriptDefined()
{
    return false;
}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::getSubscriptReturnType()
{
    return lang::VoidType::get();
}

bool lang::TypeDefinition::isOperatorDefined(lang::BinaryOperator, lang::ResolvingHandle<lang::Type>)
{
    return false;
}

bool lang::TypeDefinition::isOperatorDefined(lang::UnaryOperator)
{
    return false;
}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::getOperatorResultType(lang::BinaryOperator,
                                                                              lang::ResolvingHandle<lang::Type>)
{
    return lang::VoidType::get();
}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::getOperatorResultType(lang::UnaryOperator)
{
    return lang::VoidType::get();
}

bool lang::TypeDefinition::isImplicitlyConvertibleTo(lang::ResolvingHandle<lang::Type>)
{
    return false;
}

bool lang::TypeDefinition::hasMember(const lang::Identifier&)
{
    return false;
}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::getMemberType(const lang::Identifier&)
{
    return lang::VoidType::get();
}

bool lang::TypeDefinition::definesIndirection()
{
    return false;
}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::getIndirectionType()
{
    return lang::VoidType::get();
}

bool lang::TypeDefinition::validateDefinition(ValidationLogger&) const
{
    return true;
}

bool lang::TypeDefinition::validate(ValidationLogger&, lang::Location) const
{
    return true;
}

bool lang::TypeDefinition::validateSubscript(lang::Location,
                                             lang::ResolvingHandle<lang::Type>,
                                             lang::Location,
                                             ValidationLogger&) const
{
    return false;
}

bool lang::TypeDefinition::validateOperator(lang::BinaryOperator,
                                            lang::ResolvingHandle<lang::Type>,
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

bool lang::TypeDefinition::validateImplicitConversion(lang::ResolvingHandle<lang::Type>,
                                                      lang::Location,
                                                      ValidationLogger&) const
{
    return false;
}

bool lang::TypeDefinition::validateMemberAccess(const lang::Identifier&, ValidationLogger&) const
{
    return false;
}

bool lang::TypeDefinition::validateIndirection(lang::Location, ValidationLogger&) const
{
    return true;
}

std::shared_ptr<lang::Value> lang::TypeDefinition::buildSubscript(std::shared_ptr<Value>,
                                                                  std::shared_ptr<Value>,
                                                                  CompileContext*)
{
    return nullptr;
}

std::shared_ptr<lang::Value> lang::TypeDefinition::buildOperator(lang::BinaryOperator,
                                                                 std::shared_ptr<Value>,
                                                                 std::shared_ptr<Value>,
                                                                 CompileContext*)
{
    return nullptr;
}

std::shared_ptr<lang::Value> lang::TypeDefinition::buildOperator(lang::UnaryOperator,
                                                                 std::shared_ptr<Value>,
                                                                 CompileContext*)
{
    return nullptr;
}

std::shared_ptr<lang::Value> lang::TypeDefinition::buildImplicitConversion(lang::ResolvingHandle<lang::Type>,
                                                                           std::shared_ptr<Value>,
                                                                           CompileContext*)
{
    return nullptr;
}

std::shared_ptr<lang::Value> lang::TypeDefinition::buildMemberAccess(std::shared_ptr<Value>,
                                                                     const lang::Identifier&,
                                                                     CompileContext*)
{
    return nullptr;
}

std::shared_ptr<lang::Value> lang::TypeDefinition::buildIndirection(std::shared_ptr<Value>, CompileContext*)
{
    return nullptr;
}

void lang::TypeDefinition::buildDefaultInitializer(llvm::Value* ptr, CompileContext* context)
{
    llvm::APInt count_value = llvm::APInt(lang::SizeType::getSizeWidth(), 1);
    llvm::Type* count_type  = lang::SizeType::getSize()->getContentType(*context->llvmContext());

    llvm::Value* count = llvm::ConstantInt::get(count_type, count_value);

    buildDefaultInitializer(ptr, count, context);
}

void lang::TypeDefinition::buildDefaultInitializer(llvm::Value* ptr, llvm::Value* count, CompileContext* context)
{
    if (isTriviallyDefaultConstructible())
    {
        llvm::Value* element_size =
            llvm::ConstantInt::get(lang::SizeType::getSize()->getContentType(*context->llvmContext()),
                                   getContentSize(context->module()).getFixedSize(),
                                   false);

        llvm::Value* size = context->ir()->CreateMul(count, element_size, count->getName() + ".mul");

        context->ir()->CreateMemSet(ptr,
                                    llvm::ConstantInt::get(llvm::Type::getInt8Ty(*context->llvmContext()), 0),
                                    size,
                                    llvm::Align(1));

        return;
    }

    if (!default_initializer_) return;

    context->ir()->CreateCall(default_initializer_, {ptr, count});
}

void lang::TypeDefinition::buildCopyInitializer(llvm::Value* ptr, llvm::Value* original, CompileContext* context)
{
    if (isTriviallyCopyConstructible())
    {
        context->ir()->CreateMemCpy(ptr,
                                    llvm::Align(1),
                                    original,
                                    llvm::Align(1),
                                    getContentSize(context->module()).getFixedSize());
        return;
    }

    if (!copy_initializer_) return;

    context->ir()->CreateCall(copy_initializer_, {ptr, original});
}

void lang::TypeDefinition::buildFinalizer(llvm::Value* ptr, CompileContext* context)
{
    llvm::APInt count_value = llvm::APInt(lang::SizeType::getSizeWidth(), 1);
    llvm::Type* count_type  = lang::SizeType::getSize()->getContentType(*context->llvmContext());

    llvm::Value* count = llvm::ConstantInt::get(count_type, count_value);

    buildFinalizer(ptr, count, context);
}

void lang::TypeDefinition::buildFinalizer(llvm::Value* ptr, llvm::Value* count, CompileContext* context)
{
    if (isTriviallyDestructible() || !default_finalizer_) return;

    context->ir()->CreateCall(default_finalizer_, {ptr, count});
}

void lang::TypeDefinition::buildNativeDeclaration(CompileContext* context)
{
    if (!isTriviallyDefaultConstructible())
    {
        llvm::FunctionType* default_initializer_type =
            llvm::FunctionType::get(llvm::Type::getVoidTy(*context->llvmContext()),
                                    {getNativeType(*context->llvmContext()),
                                     lang::SizeType::getSize()->getContentType(*context->llvmContext())},
                                    false);

        default_initializer_ = llvm::Function::Create(default_initializer_type,
                                                      getAccessModifier().linkage(),
                                                      "ctor_default$" + getMangledName(),
                                                      context->module());
    }

    if (!isTriviallyCopyConstructible())
    {
        llvm::FunctionType* copy_initializer_type =
            llvm::FunctionType::get(llvm::Type::getVoidTy(*context->llvmContext()),
                                    {getNativeType(*context->llvmContext()), getNativeType(*context->llvmContext())},
                                    false);

        copy_initializer_ = llvm::Function::Create(copy_initializer_type,
                                                   getAccessModifier().linkage(),
                                                   "ctor_copy$" + getMangledName(),
                                                   context->module());
    }

    if (!isTriviallyDestructible())
    {
        llvm::FunctionType* default_finalizer_type =
            llvm::FunctionType::get(llvm::Type::getVoidTy(*context->llvmContext()),
                                    {getNativeType(*context->llvmContext()),
                                     lang::SizeType::getSize()->getContentType(*context->llvmContext())},
                                    false);

        default_finalizer_ = llvm::Function::Create(default_finalizer_type,
                                                    getAccessModifier().linkage(),
                                                    "dtor_default$" + getMangledName(),
                                                    context->module());
    }

    defineConstructors(context);
}

void lang::TypeDefinition::buildNativeDefinition(CompileContext* context)
{
    if (!isTriviallyDefaultConstructible()) defineDefaultInitializer(context);
    if (!isTriviallyCopyConstructible()) defineCopyInitializer(context);
    if (!isTriviallyDestructible()) defineDefaultFinalizer(context);

    buildConstructors(context);
}

void lang::TypeDefinition::defineConstructors(CompileContext* context)
{
    if (!default_constructor_) return;

    default_constructor_->createNativeBacking(context);
}

void lang::TypeDefinition::buildConstructors(CompileContext* context)
{
    if (!default_constructor_) return;

    lang::PredefinedFunction& default_constructor = *default_constructor_;
    auto [native_fn_type, native_fn]              = default_constructor.getNativeRepresentation();

    llvm::BasicBlock* block = llvm::BasicBlock::Create(*context->llvmContext(), "block", native_fn);
    context->ir()->SetInsertPoint(block);
    {
        llvm::Value* ptr = context->ir()->CreateAlloca(getContentType(*context->llvmContext()), nullptr, "alloca");
        buildDefaultInitializer(ptr, context);
        llvm::Value* val = context->ir()->CreateLoad(getContentType(*context->llvmContext()), ptr, "load");
        context->ir()->CreateRet(val);
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

void lang::TypeDefinition::defineDefaultInitializer(CompileContext* context)
{
    llvm::Value* ptr   = default_initializer_->getArg(0);
    llvm::Value* count = default_initializer_->getArg(1);

    buildPointerIteration(
        default_initializer_,
        ptr,
        count,
        [&](llvm::Value* element_ptr, CompileContext* context) {
            buildSingleDefaultInitializerDefinition(element_ptr, context);
        },
        context);
}

void lang::TypeDefinition::defineCopyInitializer(CompileContext* context)
{
    llvm::Value* dst_ptr = copy_initializer_->getArg(0);
    llvm::Value* src_ptr = copy_initializer_->getArg(1);

    llvm::BasicBlock* block = llvm::BasicBlock::Create(*context->llvmContext(), "block", copy_initializer_);
    context->ir()->SetInsertPoint(block);
    {
        buildSingleCopyInitializerDefinition(dst_ptr, src_ptr, context);
        context->ir()->CreateRetVoid();
    }
}

void lang::TypeDefinition::defineDefaultFinalizer(CompileContext* context)
{
    llvm::Value* ptr   = default_finalizer_->getArg(0);
    llvm::Value* count = default_finalizer_->getArg(1);

    buildPointerIteration(
        default_finalizer_,
        ptr,
        count,
        [&](llvm::Value* element_ptr, CompileContext* context) {
            buildSingleDefaultFinalizerDefinition(element_ptr, context);
        },
        context);
}

void lang::TypeDefinition::buildSingleDefaultInitializerDefinition(llvm::Value* ptr, CompileContext* context)
{
    llvm::Value* content = getDefaultContent(*context->module());
    context->ir()->CreateStore(content, ptr);
}

void lang::TypeDefinition::buildSingleCopyInitializerDefinition(llvm::Value*    dst_ptr,
                                                                llvm::Value*    src_ptr,
                                                                CompileContext* context)
{
    llvm::Type* content_type = getContentType(*context->llvmContext());

    llvm::Value* src_content = context->ir()->CreateLoad(content_type, src_ptr);
    context->ir()->CreateStore(src_content, dst_ptr);
}

void lang::TypeDefinition::buildSingleDefaultFinalizerDefinition(llvm::Value*, CompileContext*) {}

bool lang::TypeDefinition::checkDependencies(ValidationLogger& validation_logger) const
{
    if (hasCyclicDependency())
    {
        validation_logger.logError("Type " + self()->getAnnotatedName(false) + " has circular dependency",
                                   this->getDefinitionLocation());

        return false;
    }

    return true;
}

bool lang::TypeDefinition::hasCyclicDependency() const
{
    if (cyclic_dependency_.has_value()) { return cyclic_dependency_.value(); }

    const int visited  = 1;
    const int finished = 2;

    std::stack<std::pair<const lang::TypeDefinition*, bool>> to_check;
    std::map<const lang::TypeDefinition*, int>               state;

    to_check.emplace(this, false);

    while (!to_check.empty())
    {
        auto& [current, visited_children] = to_check.top();

        if (visited_children)
        {
            to_check.pop();
            state[current] = finished;
        }
        else {
            to_check.top() = std::make_pair(current, true);

            if (state[current] == visited)
            {
                cyclic_dependency_ = true;
                return true;
            }

            state[current] = visited;

            for (auto& dependency : current->getDependencies())
            {
                if (state[dependency] == finished) continue;
                to_check.emplace(dependency, false);
            }
        }
    }

    cyclic_dependency_ = false;
    return false;
}

std::vector<lang::TypeDefinition*> lang::TypeDefinition::getDependencies() const
{
    return {};
}

lang::PredefinedFunction& lang::TypeDefinition::createConstructor(
    std::vector<lang::ResolvingHandle<lang::Type>> parameter_types)
{
    lang::OwningHandle<lang::Function> function =
        lang::OwningHandle<lang::Function>::takeOwnership(lang::makeHandled<lang::Function>(lang::Identifier(name())));

    size_t count = 1;

    std::vector<std::shared_ptr<lang::Parameter>> parameters;
    for (auto& parameter_type : parameter_types)
    {
        std::string parameter_name = "p" + std::to_string(count++);
        parameters.push_back(std::make_shared<lang::Parameter>(parameter_type,
                                                               lang::Location(0, 0, 0, 0),
                                                               lang::Identifier::from(parameter_name),
                                                               lang::Location(0, 0, 0, 0)));
    }

    lang::PredefinedFunction& predefined_function =
        function->defineAsPredefined(self(), parameters, *scope(), lang::Location(0, 0, 0, 0));

    self()->addFunction(std::move(function));

    return predefined_function;
}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::self() const
{
    assert(type_);
    return type_->self();
}

void lang::TypeDefinition::buildPointerIteration(llvm::Function*                                    function,
                                                 llvm::Value*                                       ptr,
                                                 llvm::Value*                                       count,
                                                 std::function<void(llvm::Value*, CompileContext*)> operation,
                                                 CompileContext*                                    context)
{
    llvm::Type* size_type = SizeType::getSize()->getContentType(*context->llvmContext());

    llvm::BasicBlock* init = llvm::BasicBlock::Create(*context->llvmContext(), "init", function);
    llvm::BasicBlock* body = llvm::BasicBlock::Create(*context->llvmContext(), "body", function);
    llvm::BasicBlock* end  = llvm::BasicBlock::Create(*context->llvmContext(), "end", function);

    context->ir()->SetInsertPoint(init);
    {
        context->ir()->CreateBr(body);
    }

    context->ir()->SetInsertPoint(body);
    {
        llvm::PHINode* current = context->ir()->CreatePHI(size_type, 2, "i");
        current->addIncoming(llvm::ConstantInt::get(size_type, 0), init);

        llvm::Value* element_ptr =
            context->ir()->CreateInBoundsGEP(getContentType(*context->llvmContext()), ptr, current, "element_ptr");
        operation(element_ptr, context);

        llvm::Value* next = context->ir()->CreateAdd(current, llvm::ConstantInt::get(size_type, 1), "next");
        current->addIncoming(next, body);

        llvm::Value* condition = context->ir()->CreateICmpULT(next, count, "condition");
        context->ir()->CreateCondBr(condition, body, end);
    }

    context->ir()->SetInsertPoint(end);
    {
        context->ir()->CreateRetVoid();
    }
}
