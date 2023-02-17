#include "FunctionDescription.h"

#include "lang/ApplicationVisitor.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

lang::FunctionDescription::FunctionDescription(lang::AccessModifier                 access,
                                               lang::Identifier                     name,
                                               lang::ResolvingHandle<lang::Type>    return_type,
                                               lang::Location                       return_type_location,
                                               std::vector<Shared<lang::Parameter>> parameters,
                                               Optional<Owned<Statement>>           code,
                                               lang::Location                       declaration_location,
                                               lang::Location                       definition_location)
    : access_(access)
    , name_(name)
    , return_type_(return_type)
    , return_type_location_(return_type_location)
    , parameters_(std::move(parameters))
    , code_(std::move(code))
    , declaration_location_(declaration_location)
    , definition_location_(definition_location)
{}

lang::Identifier const& lang::FunctionDescription::name() const
{
    return name_;
}

bool lang::FunctionDescription::isOverloadAllowed() const
{
    return true;
}

void lang::FunctionDescription::performInitialization()
{
    lang::OwningHandle<lang::Function> function =
        lang::OwningHandle<lang::Function>::takeOwnership(lang::makeHandled<lang::Function>(name_));

    if (code_.hasValue())
    {
        function->defineAsCustom(access_,
                                 return_type_,
                                 return_type_location_,
                                 parameters_,
                                 **code_,
                                 scope(),
                                 declaration_location_,
                                 definition_location_);
    }
    else { function->defineAsExtern(scope(), return_type_, return_type_location_, parameters_, declaration_location_); }

    scope().getGlobalScope()->addFunction(std::move(function));
}

void lang::FunctionDescription::validate(ValidationLogger& validation_logger) const
{
    if (lang::validation::isTypeUndefined(return_type_, return_type_location_, validation_logger)) return;

    return_type_->validate(validation_logger, return_type_location_);

    std::set<lang::Identifier> names;

    for (auto const& parameter : parameters_)
    {
        auto [it, inserted] = names.insert(parameter->name());

        if (!inserted)
        {
            validation_logger.logError("Name '" + parameter->name() + "' already defined in the current context",
                                       parameter->name().location());
        }

        if (lang::validation::isTypeUndefined(parameter->type(), parameter->typeLocation(), validation_logger)) return;

        parameter->type().validate(validation_logger, parameter->typeLocation());

        if (parameter->type().isVoidType())
        {
            validation_logger.logError("Parameter cannot have 'void' type", parameter->location());
        }
    }
}

lang::Description::Descriptions lang::FunctionDescription::expand() const
{
    Optional<Owned<Statement>> code;

    if (code_.hasValue())
    {
        Statements expanded_statements = (**code_).expand();
        assert(expanded_statements.size() == 1);

        code = std::move(expanded_statements.front());
    }

    std::vector<Shared<lang::Parameter>> expanded_parameters;

    for (auto& parameter : parameters_) { expanded_parameters.emplace_back(parameter->expand()); }

    auto expanded = makeOwned<lang::FunctionDescription>(access_,
                                                         name_,
                                                         return_type_->createUndefinedClone(),
                                                         return_type_location_,
                                                         expanded_parameters,
                                                         std::move(code),
                                                         declaration_location_,
                                                         definition_location_);

    Descriptions descriptions;
    descriptions.emplace_back(std::move(expanded));

    return descriptions;
}
