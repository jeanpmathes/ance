#include "VariableDefinition.h"

#include "ance/type/ReferenceType.h"
#include "compiler/CompileContext.h"

ance::VariableDefinition::VariableDefinition(const std::string&                identifier,
                                             ance::ResolvingHandle<ance::Type> type,
                                             ance::Scope*                      containing_scope,
                                             bool                              is_final,
                                             ance::Location                    location)
    : identifier_(identifier)
    , type_(type)
    , scope_(containing_scope)
    , is_final_(is_final)
    , location_(location)
{}

const std::string& ance::VariableDefinition::identifier() const
{
    return identifier_;
}

ance::Scope* ance::VariableDefinition::scope() const
{
    return scope_;
}
ance::ResolvingHandle<ance::Type> ance::VariableDefinition::type() const
{
    return type_;
}

ance::Location ance::VariableDefinition::location() const
{
    return location_;
}

bool ance::VariableDefinition::isFinal() const
{
    return is_final_;
}

void ance::VariableDefinition::setValue(const std::shared_ptr<ance::Value>& value, CompileContext* context)
{
    if (ance::ReferenceType::isReferenceType(type()))
    {
        std::shared_ptr<ance::Value> reference = getValue(context);

        reference->buildContentValue(context);
        value->buildContentValue(context);

        context->ir()->CreateStore(value->getContentValue(), reference->getContentValue());
    }
    else
    {
        storeValue(value, context);
    }
}
