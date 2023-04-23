#include "FunctionDescription.h"

#include "lang/ApplicationVisitor.h"
#include "lang/utility/Storage.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

lang::FunctionDescription::FunctionDescription(lang::AccessModifier                 access,
                                               lang::Identifier                     name,
                                               lang::ResolvingHandle<lang::Type>    return_type,
                                               lang::Location                       return_type_location,
                                               std::vector<Shared<lang::Parameter>> parameters,
                                               Optional<Owned<Statement>>           code,
                                               lang::Location                       declaration_location,
                                               lang::Location                       definition_location,
                                               bool                                 is_imported)
    : is_imported_(is_imported)
    , access_(access)
    , name_(name)
    , return_type_(return_type)
    , return_type_location_(return_type_location)
    , parameters_(std::move(parameters))
    , code_(std::move(code))
    , declaration_location_(declaration_location)
    , definition_location_(definition_location)
{}

lang::FunctionDescription::FunctionDescription()
    : is_imported_(true)
    , access_(lang::AccessModifier::PUBLIC_ACCESS)
    , name_(lang::Identifier::empty())
    , return_type_(lang::Type::getUndefined())
    , return_type_location_(lang::Location::global())
    , parameters_()
    , code_(std::nullopt)
    , declaration_location_(lang::Location::global())
    , definition_location_(lang::Location::global())
{}

lang::Identifier const& lang::FunctionDescription::name() const
{
    return name_;
}

bool lang::FunctionDescription::isOverloadAllowed() const
{
    return true;
}

lang::AccessModifier lang::FunctionDescription::access() const
{
    return access_;
}

bool lang::FunctionDescription::isImported() const
{
    return is_imported_;
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
    else
    {
        function->defineAsImported(scope(),
                                   access_,
                                   return_type_,
                                   return_type_location_,
                                   parameters_,
                                   declaration_location_);
    }

    function_ = &*function;

    scope().getGlobalScope()->addFunction(std::move(function));
}

lang::Function const* lang::FunctionDescription::function() const
{
    return function_;
}

Statement const* lang::FunctionDescription::code() const
{
    return getPtr(code_);
}

void lang::FunctionDescription::validate(ValidationLogger& validation_logger) const
{
    if (lang::validation::isTypeUndefined(return_type_, return_type_location_, validation_logger)) return;

    return_type_->validate(validation_logger, return_type_location_);

    if (access_ == lang::AccessModifier::PUBLIC_ACCESS)
    {
        lang::validation::isTypeExportable(return_type_, return_type_location_, validation_logger);
    }

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

        if (access_ == lang::AccessModifier::PUBLIC_ACCESS)
        {
            lang::validation::isTypeExportable(parameter->type(), parameter->typeLocation(), validation_logger);
        }

        parameter->type().validate(validation_logger, parameter->typeLocation());

        if (parameter->type().isVoidType())
        {
            validation_logger.logError("Parameter cannot have 'void' type", parameter->location());
        }
    }

    if (code_.hasValue()) { (**code_).validate(validation_logger); }
    else if (access_ != lang::AccessModifier::EXTERN_ACCESS && !is_imported_)
    {
        validation_logger.logError("Functions without a body must be declared as 'extern'", declaration_location_);
    }
}

lang::Description::Descriptions lang::FunctionDescription::expand(lang::Context& new_context) const
{
    Optional<Owned<Statement>> code;

    if (code_.hasValue())
    {
        Statements expanded_statements = (**code_).expand(new_context);
        assert(expanded_statements.size() == 1);

        code = std::move(expanded_statements.front());
    }

    std::vector<Shared<lang::Parameter>> expanded_parameters;

    for (auto& parameter : parameters_) { expanded_parameters.emplace_back(parameter->expand(new_context)); }

    auto expanded = makeOwned<lang::FunctionDescription>(access_,
                                                         name_,
                                                         return_type_->createUndefinedClone(new_context),
                                                         return_type_location_,
                                                         expanded_parameters,
                                                         std::move(code),
                                                         declaration_location_,
                                                         definition_location_,
                                                         is_imported_);

    Descriptions descriptions;
    descriptions.emplace_back(std::move(expanded));

    return descriptions;
}

void lang::FunctionDescription::sync(Storage& storage)
{
    storage.sync(name_);
    storage.sync(return_type_);

    std::vector<Shared<lang::Parameter>> parameters = parameters_;
    parameters_.clear();

    uint64_t size = parameters.size();
    storage.sync(size);

    for (uint64_t i = 0; i < size; ++i)
    {
        if (storage.isReading())
        {
            parameters_.emplace_back(makeShared<lang::Parameter>(lang::Type::getUndefined(),
                                                                 lang::Location::global(),
                                                                 lang::Identifier::empty(),
                                                                 lang::Location::global()));
        }

        if (storage.isWriting()) { parameters_.emplace_back(parameters[i]); }

        storage.sync(*parameters_.back());
    }
}
