#include "LocalReferenceVariableDefinition.h"

#include <utility>

#include "ance/ApplicationVisitor.h"
#include "ance/construct/DefinedFunction.h"
#include "ance/construct/LocalVariable.h"
#include "ance/construct/value/RoughlyCastedValue.h"
#include "ance/expression/Addressof.h"
#include "ance/scope/LocalScope.h"

LocalReferenceVariableDefinition* LocalReferenceVariableDefinition::refer(std::string    identifier,
                                                                          ance::Type*    type,
                                                                          Expression*    value,
                                                                          Application&   app,
                                                                          ance::Location location)
{
    auto* addressof = new Addressof(value, app, location);
    return new LocalReferenceVariableDefinition(std::move(identifier), type, addressof, location);
}

LocalReferenceVariableDefinition* LocalReferenceVariableDefinition::referTo(std::string    identifier,
                                                                            ance::Type*    type,
                                                                            Expression*    address,
                                                                            ance::Location location)
{
    return new LocalReferenceVariableDefinition(std::move(identifier), type, address, location);
}

LocalReferenceVariableDefinition::LocalReferenceVariableDefinition(std::string    identifier,
                                                                   ance::Type*    type,
                                                                   Expression*    address,
                                                                   ance::Location location)
    : Statement(location)
    , identifier_(std::move(identifier))
    , type_(type)
    , address_(address)
{
    addChild(*address);
}

void LocalReferenceVariableDefinition::setFunction(ance::DefinedFunction* function)
{
    variable_ =
        function->getFunctionScope()->defineAutoVariable(identifier_,
                                                         type_,
                                                         Assigner::REFERENCE_BINDING,
                                                         new ance::RoughlyCastedValue(type_, address_->getValue()),
                                                         location());

    address_->setContainingScope(function);
}
void LocalReferenceVariableDefinition::validate(ValidationLogger& validation_logger)
{
    address_->validate(validation_logger);
}

void LocalReferenceVariableDefinition::doBuild(CompileContext* context)
{
    variable_->build(context);
}

bool LocalReferenceVariableDefinition::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitLocalReferenceVariableDefinition(*this);
}
