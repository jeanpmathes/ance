#include "GlobalVariable.h"

#include <utility>

#include "compiler/CompileContext.h"
#include "lang/AccessModifier.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/constant/Constant.h"
#include "lang/expression/ConstantExpression.h"
#include "lang/scope/GlobalScope.h"
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
    variable_handle_ = context.exec().createGlobalVariable(name(), access(), is_import_, type(), is_constant_, init_, location());
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

    type()->performFinalizer(context.exec().computeAddressOfVariable(variable_handle_.value()), context);

    finalized_ = true;
}

Shared<lang::Value> lang::GlobalVariable::getValuePointer(CompileContext& context)
{
    assert(variable_handle_.hasValue());
    return context.exec().computeAddressOfVariable(variable_handle_.value());
}

void lang::GlobalVariable::storeValue(Shared<lang::Value> value, CompileContext& context)
{
    assert(variable_handle_.hasValue());

    Shared<lang::Value> variable_pointer = context.exec().computeAddressOfVariable(variable_handle_.value());
    Shared<lang::Value> value_pointer = context.exec().computeAddressOf(value);

    type()->performCopyInitializer(variable_pointer, value_pointer, context);
}
