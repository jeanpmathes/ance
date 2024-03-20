#include "PredefinedFunction.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"

lang::PredefinedFunction::PredefinedFunction(lang::Function&                      function,
                                             lang::Scope&                         containing_scope,
                                             lang::AccessModifier                 access_modifier,
                                             bool                                 is_imported,
                                             lang::ResolvingHandle<lang::Type>    return_type,
                                             bool                                 is_constructor,
                                             std::vector<Shared<lang::Parameter>> parameters,
                                             lang::Location                       location)
    : lang::FunctionDefinition(function,
                               containing_scope,
                               return_type,
                               lang::Location::global(),
                               std::move(parameters),
                               location)
    , access_modifier_(access_modifier)
    , is_imported_(is_imported)
    , is_constructor_(is_constructor)
{}

bool lang::PredefinedFunction::isMangled() const
{
    return true;
}

bool lang::PredefinedFunction::isImported() const
{
    return is_imported_;
}

lang::AccessModifier lang::PredefinedFunction::access() const
{
    return access_modifier_;
}

Optional<lang::Location> lang::PredefinedFunction::getDefinitionLocation() const
{
    return std::nullopt;
}

bool lang::PredefinedFunction::preserveUnitReturn() const
{
    return is_constructor_;
}

void lang::PredefinedFunction::determineFlow() {}

bool lang::PredefinedFunction::validateFlow(ValidationLogger&) const
{
    return true;
}

std::vector<lang::BasicBlock*> const& lang::PredefinedFunction::getBasicBlocks() const
{
    static std::vector<lang::BasicBlock*> const empty;
    return empty;
}

void lang::PredefinedFunction::setCallValidator(
    std::function<bool(std::vector<std::reference_wrapper<Expression const>> const&, lang::Location, ValidationLogger&)>
        validator)
{
    call_validator_ = std::move(validator);
}

bool lang::PredefinedFunction::doCallValidation(std::vector<std::reference_wrapper<Expression const>> const& arguments,
                                                lang::Location                                               location,
                                                ValidationLogger& validation_logger) const
{
    if (call_validator_) { return call_validator_(arguments, location, validation_logger); }
    return true;
}
