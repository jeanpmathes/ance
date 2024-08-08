#include "GlobalVariable.h"

#include <utility>

#include "lang/AccessModifier.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Constant.h"
#include "lang/expression/LiteralExpression.h"
#include "lang/scope/GlobalScope.h"
#include "validation/ValidationLogger.h"

lang::GlobalVariable::GlobalVariable(lang::ResolvingHandle<lang::Variable> self,
                                     lang::ResolvingHandle<lang::Type>     type,
                                     lang::Location                        type_location,
                                     Scope&                                containing_scope,
                                     lang::AccessModifier                  access,
                                     bool                                  is_import,
                                     GlobalInitializer                     init,
                                     Assigner                              assigner,
                                     bool                                  is_cmp,
                                     lang::Location                        location)
    : VariableDefinition(self, type, type_location, containing_scope, assigner.isFinal(), location)
    , access_(access)
    , is_import_(is_import)
    , is_cmp_(is_cmp)
    , init_(std::move(init))
    , assigner_(assigner)
{
    if (init_.hasValue())
    {
        if (auto* constant_init = std::get_if<std::reference_wrapper<CompileTimeExpression>>(&init_.value()))
        {
            constant_init->get().setContainingScope(containing_scope);
        }
    }
}

lang::AccessModifier lang::GlobalVariable::access() const
{
    return access_;
}

bool lang::GlobalVariable::isCMP() const
{
    return is_cmp_;
}

lang::Assigner lang::GlobalVariable::assigner() const
{
    return assigner_;
}

void lang::GlobalVariable::registerDeclaration(Execution& exec) const
{
    exec.registerGlobalVariable(*this, is_import_, init_);
}

void lang::GlobalVariable::performInitialization(Execution& exec) const
{
    if (init_.hasValue())
    {
        if (auto* function_init = std::get_if<std::reference_wrapper<lang::Function>>(&init_.value()))
        {
            function_init->get().execCall({}, exec);
        }
    }
}

void lang::GlobalVariable::performFinalization(Execution& exec) const
{
    type().performFinalizer(exec.computeAddressOfVariable(self()), exec);
}

Shared<lang::Value> lang::GlobalVariable::getValuePointer(Execution& exec) const
{
    return exec.computeAddressOfVariable(self());
}
