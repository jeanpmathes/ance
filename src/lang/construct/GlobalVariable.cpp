#include "GlobalVariable.h"

#include "compiler/CompileContext.h"
#include "lang/AccessModifier.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/constant/Constant.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/expression/ConstantExpression.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/VoidType.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

namespace llvm
{
    class Constant;
}

lang::GlobalVariable::GlobalVariable(lang::ResolvingHandle<lang::Variable> self,
                                     lang::ResolvingHandle<lang::Type>     type,
                                     lang::Location                        type_location,
                                     GlobalScope&                          containing_scope,
                                     lang::AccessModifier                  access,
                                     std::unique_ptr<Expression>           init,
                                     bool                                  is_final,
                                     bool                                  is_constant,
                                     lang::Location                        location)
    : VariableDefinition(self->name(), type, type_location, containing_scope, is_final, location)
    , access_(access)
    , is_constant_(is_constant)
    , constant_init_(is_constant_ ? dynamic_cast<ConstantExpression*>(init.get()) : nullptr)
    , init_(init.get())
    , init_owner_(std::move(init))
    , init_function_(init_ && not constant_init_
                         ? std::make_unique<lang::Function>(lang::Identifier::from(self->name() + "$init"))
                         : nullptr)
{
    containing_scope.addType(type);

    if (init_)
    {
        if (constant_init_) { constant_init_->setContainingScope(containing_scope); }
        else
        {
            init_function_->defineAsInit(self->toUndefined(), assigner(), std::move(init_owner_), containing_scope);
        }

        addChild(*init_);
    }
}

lang::AccessModifier lang::GlobalVariable::access() const
{
    return access_;
}

bool lang::GlobalVariable::isConstant() const
{
    return is_constant_;
}

lang::Assigner lang::GlobalVariable::assigner() const
{
    if (isFinal()) { return lang::Assigner::FINAL_COPY_ASSIGNMENT; }
    else {
        return lang::Assigner::COPY_ASSIGNMENT;
    }
}

Expression* lang::GlobalVariable::init() const
{
    return init_;
}

void lang::GlobalVariable::validate(ValidationLogger& validation_logger) const
{
    if (lang::validation::isTypeUndefined(type(), typeLocation(), validation_logger)) return;

    if (!type()->validate(validation_logger, typeLocation())) return;

    if (type()->isVoidType())
    {
        validation_logger.logError("Global variable cannot have 'void' type", typeLocation());
        return;
    }

    if (type()->isReferenceType())
    {
        validation_logger.logError("Global variable cannot have reference type", typeLocation());
        return;
    }

    if (!init_ && is_constant_)
    {
        validation_logger.logError("Constants require an explicit constant initializer", location());
        return;
    }

    if (!constant_init_ && is_constant_)
    {
        validation_logger.logError("Initializer for constant variable must be constant", location());
        return;
    }

    if (is_constant_ && !isFinal())
    {
        validation_logger.logError("Assignment to constants must be final", location());
        return;
    }

    if (init_)
    {
        if (init_function_) { init_function_->validate(validation_logger); }

        if (!init_->validate(validation_logger)) return;

        if (constant_init_)
        {
            if (!lang::Type::areSame(type(), constant_init_->type()))
            {
                validation_logger.logError("Constant initializer must be of variable type "
                                               + type()->getAnnotatedName(),
                                           typeLocation());
                return;
            }
        }
        else
        {
            if (!lang::Type::checkMismatch(type(), init_->type(), init_->location(), validation_logger)) return;
        }
    }
}

void lang::GlobalVariable::expand()
{
    if (init_function_)
    {
        clearChildren();
        init_ = nullptr;
        init_owner_.reset();

        init_function_->expand();
    }
}

void lang::GlobalVariable::determineFlow()
{
    if (init_function_) { init_function_->determineFlow(); }
}

void lang::GlobalVariable::validateFlow(ValidationLogger& validation_logger) const
{
    if (init_function_) { init_function_->validateFlow(validation_logger); }
}

void lang::GlobalVariable::resolve()
{
    if (init_function_) { init_function_->resolve(); }
}

void lang::GlobalVariable::postResolve()
{
    if (init_function_) { init_function_->postResolve(); }
}

void lang::GlobalVariable::createNativeBacking(CompileContext& context)
{
    if (init_function_) { init_function_->createNativeBacking(context); }
}

void lang::GlobalVariable::build(CompileContext& context)
{
    if (init_function_) { init_function_->build(context); }
}

void lang::GlobalVariable::buildDeclaration(CompileContext& context)
{
    llvm::Constant* native_initializer;

    if (constant_init_)
    {
        std::shared_ptr<lang::Constant> initial_value = constant_init_->getConstantValue();
        initial_value->buildContentConstant(context.module());
        native_initializer = initial_value->getContentConstant();
    }
    else if (init_function_)
    {
        // Will be initialized at startup.
        native_initializer = llvm::Constant::getNullValue(type()->getContentType(*context.llvmContext()));
    }
    else { native_initializer = type()->getDefaultContent(*context.module()); }

    native_variable_ = new llvm::GlobalVariable(*context.module(),
                                                type()->getContentType(context.module()->getContext()),
                                                is_constant_,
                                                access_.linkage(),
                                                native_initializer,
                                                name().text());

    auto* debug_info = context.di()->createGlobalVariableExpression(context.unit(),
                                                                    name().text(),
                                                                    name().text(),
                                                                    context.sourceFile(),
                                                                    static_cast<unsigned>(location().line()),
                                                                    type()->getDebugType(context),
                                                                    true);

    native_variable_->addDebugInfo(debug_info);
}

void lang::GlobalVariable::buildDefinition(CompileContext& context)
{
    if (constant_init_) return;// Definition done in declaration.

    if (init_function_) { init_function_->buildCall({}, context); }
}

void lang::GlobalVariable::buildFinalization(CompileContext& context)
{
    assert(not finalized_);

    type()->buildFinalizer(native_variable_, context);

    finalized_ = true;
}

std::shared_ptr<lang::Value> lang::GlobalVariable::getValue(CompileContext&)
{
    assert(native_variable_);
    return std::make_shared<lang::WrappedNativeValue>(type(), native_variable_);
}

void lang::GlobalVariable::storeValue(std::shared_ptr<lang::Value> value, CompileContext& context)
{
    assert(native_variable_);

    value = lang::Type::makeMatching(type(), value, context);
    value->buildNativeValue(context);

    type()->buildCopyInitializer(native_variable_, value->getNativeValue(), context);
}
