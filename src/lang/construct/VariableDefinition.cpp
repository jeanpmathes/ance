#include "VariableDefinition.h"

#include "lang/type/ReferenceType.h"
#include "compiler/CompileContext.h"

lang::VariableDefinition::VariableDefinition(const std::string&                name,
                                             lang::ResolvingHandle<lang::Type> type,
                                             lang::Location                    type_location,
                                             Scope&                            containing_scope,
                                             bool                              is_final,
                                             lang::Location                    location)
    : name_(name)
    , type_(type)
    , type_location_(type_location)
    , scope_(containing_scope)
    , is_final_(is_final)
    , location_(location)
{}

const std::string& lang::VariableDefinition::name() const
{
    return name_;
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

void lang::VariableDefinition::setValue(std::shared_ptr<lang::Value> value, CompileContext* context)
{
    if (type()->isReferenceType())
    {
        std::shared_ptr<lang::Value> reference = getValue(context);

        value = lang::Type::makeMatching(type()->getElementType(), value, context);

        reference->buildContentValue(context);
        value->buildContentValue(context);

        context->ir()->CreateStore(value->getContentValue(), reference->getContentValue());
    }
    else
    {
        storeValue(value, context);
    }
}
