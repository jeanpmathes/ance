#include "GlobalVariable.h"

#include <utility>

#include "compiler/CompileContext.h"
#include "lang/AccessModifier.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/constant/Constant.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/expression/ConstantExpression.h"
#include "lang/scope/GlobalScope.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

namespace llvm
{
    class Constant;
}

lang::GlobalVariable::GlobalVariable(lang::ResolvingHandle<lang::Variable> self,
                                     lang::ResolvingHandle<lang::Type>     type,
                                     lang::Location                        type_location,
                                     Scope&                                containing_scope,
                                     lang::AccessModifier                  access,
                                     bool                                  is_import,
                                     Initializer                           init,
                                     lang::Scope*                          init_scope,
                                     Assigner                              assigner,
                                     bool                                  is_constant,
                                     lang::Location                        location)
    : VariableDefinition(self, type, type_location, containing_scope, assigner.isFinal(), location)
    , access_(access)
    , is_import_(is_import)
    , is_constant_(is_constant)
    , init_(std::move(init))
    , init_scope_(init_scope)
    , assigner_(assigner)
{
    if (init_.hasValue())
    {
        if (auto* constant_init = std::get_if<std::reference_wrapper<ConstantExpression>>(&init_.value()))
        {
            constant_init->get().setContainingScope(containing_scope);
        }
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
    return assigner_;
}

void lang::GlobalVariable::buildDeclaration(CompileContext& context)
{
    llvm::Constant* native_initializer = nullptr;

    if (init_.hasValue())
    {
        if (auto* constant_init = std::get_if<std::reference_wrapper<ConstantExpression>>(&init_.value()))
        {
            Shared<lang::Constant> initial_value = constant_init->get().getConstantValue();
            initial_value->buildContentConstant(context.llvmModule());
            native_initializer = initial_value->getContentConstant();
        }
        else
        {
            // Will be initialized at startup.
            assert(std::holds_alternative<std::reference_wrapper<lang::Function>>(init_.value()));
            native_initializer = llvm::Constant::getNullValue(type()->getContentType(context.llvmContext()));
        }
    }
    else if (!is_import_) { native_initializer = type()->getDefaultContent(context.llvmModule()); }

    llvm::Type*       native_type  = type()->getContentType(context.llvmModule().getContext());
    std::string const linkage_name = std::string(name().text());

    native_variable_ = new llvm::GlobalVariable(context.llvmModule(),
                                                native_type,
                                                is_constant_,
                                                access_.linkage(),
                                                native_initializer,
                                                linkage_name,
                                                nullptr,
                                                llvm::GlobalValue::NotThreadLocal,
                                                llvm::None,
                                                is_import_);

    llvm::GlobalValue::DLLStorageClassTypes dll_storage_class = llvm::GlobalValue::DefaultStorageClass;
    if (access_ == AccessModifier::PUBLIC_ACCESS)
    {
        dll_storage_class =
            is_import_ ? llvm::GlobalValue::DLLImportStorageClass : llvm::GlobalValue::DLLExportStorageClass;
    }
    native_variable_->setDLLStorageClass(dll_storage_class);
    native_variable_->setDSOLocal(!is_import_);

    llvm::MaybeAlign const alignment = context.llvmModule().getDataLayout().getABITypeAlign(native_type);
    native_variable_->setAlignment(alignment);

    auto* debug_info = context.di().createGlobalVariableExpression(&context.llvmUnit(),
                                                                   name().text(),
                                                                   name().text(),
                                                                   context.getSourceFile(location()),
                                                                   static_cast<unsigned>(location().line()),
                                                                   type()->getDebugType(context),
                                                                   access_ == AccessModifier::PRIVATE_ACCESS);

    native_variable_->addDebugInfo(debug_info);
}

void lang::GlobalVariable::buildInitialization(CompileContext& context)
{
    if (init_.hasValue())
    {
        if (auto* function_init = std::get_if<std::reference_wrapper<lang::Function>>(&init_.value()))
        {
            function_init->get().buildCall({}, context);
        }
    }
}

void lang::GlobalVariable::buildFinalization(CompileContext& context)
{
    assert(not finalized_);

    type()->buildFinalizer(native_variable_, context);

    finalized_ = true;
}

Shared<lang::Value> lang::GlobalVariable::getValue(CompileContext&)
{
    assert(native_variable_);
    return makeShared<lang::WrappedNativeValue>(type(), native_variable_);
}

void lang::GlobalVariable::storeValue(Shared<lang::Value> value, CompileContext& context)
{
    assert(native_variable_);

    value = lang::Type::makeMatching(type(), value, context);
    value->buildNativeValue(context);

    type()->buildCopyInitializer(native_variable_, value->getNativeValue(), context);
}
