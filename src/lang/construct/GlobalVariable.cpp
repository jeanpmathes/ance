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
                                     lang::Function const*                 init,
                                     Assigner                              assigner,
                                     lang::CMP                             cmp,
                                     lang::Location                        location)
    : VariableDefinition(self, type, type_location, containing_scope, assigner.isFinal(), location)
    , access_(access)
    , is_import_(is_import)
    , cmp_(cmp)
    , init_(init)
    , assigner_(assigner)
{
}

lang::AccessModifier lang::GlobalVariable::access() const
{
    return access_;
}

bool lang::GlobalVariable::isImported() const
{
    return is_import_;
}

lang::Assigner lang::GlobalVariable::assigner() const
{
    return assigner_;
}

lang::Function const* lang::GlobalVariable::initializer() const
{
    return init_;
}

lang::CMP lang::GlobalVariable::cmp() const
{
    return cmp_;
}

void lang::GlobalVariable::registerDeclaration(Execution& exec) const
{
    exec.declareGlobalVariable(*this);
}

void lang::GlobalVariable::registerDefinition(Execution& exec) const
{
    exec.defineGlobalVariable(*this);
}

void lang::GlobalVariable::performInitialization(Execution& exec) const
{
    if (init_ != nullptr && !cmp().isCompileTime()) { init_->execCall({}, exec); }
}

void lang::GlobalVariable::performFinalization(Execution& exec) const
{
    type().performFinalizer(exec.computeAddressOfVariable(self()), exec);
}

Shared<lang::Value> lang::GlobalVariable::getValuePointer(Execution& exec) const
{
    return exec.computeAddressOfVariable(self());
}
