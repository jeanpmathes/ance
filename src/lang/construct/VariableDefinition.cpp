#include "VariableDefinition.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/Variable.h"
#include "lang/scope/Scope.h"
#include "lang/type/ReferenceType.h"

lang::VariableDefinition::VariableDefinition(lang::ResolvingHandle<lang::Variable> self,
                                             lang::ResolvingHandle<lang::Type>     type,
                                             lang::Location                        type_location,
                                             Scope&                                containing_scope,
                                             bool                                  is_final,
                                             lang::Location                        location)
    : self_(self)
    , type_location_(type_location)
    , scope_(containing_scope)
    , is_final_(is_final)
    , location_(location)
{
    self_->type().reroute(type);
}

lang::Identifier const& lang::VariableDefinition::name() const
{
    return self_->name();
}

lang::Scope& lang::VariableDefinition::scope()
{
    return scope_;
}

lang::Scope const& lang::VariableDefinition::scope() const
{
    return scope_;
}

lang::ResolvingHandle<lang::Type> lang::VariableDefinition::type()
{
    return self_->type();
}

lang::Type const& lang::VariableDefinition::type() const
{
    return self_->type();
}

lang::Location lang::VariableDefinition::location() const
{
    return location_;
}

bool lang::VariableDefinition::isFinal() const
{
    return is_final_;
}

lang::ResolvingHandle<lang::Variable> lang::VariableDefinition::self()
{
    return self_;
}

lang::Variable const& lang::VariableDefinition::self() const
{
    return self_;
}
