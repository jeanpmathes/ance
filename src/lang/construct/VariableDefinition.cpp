#include "VariableDefinition.h"

#include "compiler/CompileContext.h"
#include "lang/construct/Variable.h"
#include "lang/type/ReferenceType.h"

lang::VariableDefinition::VariableDefinition(lang::ResolvingHandle<lang::Variable> self,
                                             lang::ResolvingHandle<lang::Type>     type,
                                             lang::Location                        type_location,
                                             Scope&                                containing_scope,
                                             bool                                  is_final,
                                             lang::Location                        location)
    : self_(self)
    , type_(type)
    , type_location_(type_location)
    , scope_(containing_scope)
    , is_final_(is_final)
    , location_(location)
{}

lang::Identifier const& lang::VariableDefinition::name() const
{
    return self_->name();
}

lang::Scope* lang::VariableDefinition::scope() const
{
    return &scope_;
}
lang::ResolvingHandle<lang::Type> lang::VariableDefinition::type() const
{
    return type_;
}

lang::Location lang::VariableDefinition::location() const
{
    return location_;
}

lang::Location lang::VariableDefinition::typeLocation() const
{
    return type_location_;
}

bool lang::VariableDefinition::isFinal() const
{
    return is_final_;
}

void lang::VariableDefinition::expand() {}
void lang::VariableDefinition::determineFlow() {}
void lang::VariableDefinition::validateFlow(ValidationLogger&) const {}
void lang::VariableDefinition::resolve() {}
void lang::VariableDefinition::postResolve() {}
void lang::VariableDefinition::createNativeBacking(CompileContext&) {}
void lang::VariableDefinition::build(CompileContext&) {}

std::set<lang::ResolvingHandle<lang::Variable>> lang::VariableDefinition::getVariableDependencies() const
{
    return {};
}

std::set<lang::ResolvingHandle<lang::Function>> lang::VariableDefinition::getFunctionDependencies() const
{
    return {};
}

void lang::VariableDefinition::setValue(std::shared_ptr<lang::Value> value, CompileContext& context)
{
    if (type()->isReferenceType())
    {
        std::shared_ptr<lang::Value> reference = getValue(context);

        lang::ResolvingHandle<lang::Type> target_type = type()->getElementType();
        value                                         = lang::Type::makeMatching(target_type, value, context);

        reference->buildContentValue(context);
        value->buildNativeValue(context);

        target_type->buildCopyInitializer(reference->getContentValue(), value->getNativeValue(), context);
    }
    else { storeValue(value, context); }
}

lang::ResolvingHandle<lang::Variable> lang::VariableDefinition::self() const
{
    return self_;
}
