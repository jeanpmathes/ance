#include "FunctionDescription.h"

#include "lang/ApplicationVisitor.h"
#include "lang/utility/Storage.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

lang::FunctionDescription::FunctionDescription(lang::Accessibility                  accessibility,
                                               lang::Identifier                     name,
                                               lang::ResolvingHandle<lang::Type>    return_type,
                                               lang::Location                       return_type_location,
                                               std::vector<Shared<lang::Parameter>> parameters,
                                               Optional<Owned<Statement>>           code,
                                               lang::Location                       declaration_location,
                                               lang::Location                       definition_location)
    : Description(accessibility)
    , name_(name)
    , return_type_(return_type)
    , return_type_location_(return_type_location)
    , parameters_(std::move(parameters))
    , code_(std::move(code))
    , declaration_location_(declaration_location)
    , definition_location_(definition_location)
{}

lang::FunctionDescription::FunctionDescription(bool from_public_import)
    : Description(lang::Accessibility::imported(from_public_import))
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

void lang::FunctionDescription::performInitialization()
{
    function_ = lang::makeHandled<lang::Function>(name_);

    if (code_.hasValue())
    {
        function_.value()->defineAsCustom(access().modifier(),
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
        function_.value()->defineAsImported(scope(),
                                            access().modifier(),
                                            return_type_,
                                            return_type_location_,
                                            parameters_,
                                            declaration_location_);
    }
}

lang::Function const* lang::FunctionDescription::function() const
{
    return &*function_.value();
}

Statement const* lang::FunctionDescription::code() const
{
    return getPtr(code_);
}

std::vector<std::reference_wrapper<const lang::Entity>> lang::FunctionDescription::getProvidedEntities() const
{
    return {};// Does not provide any entities as it is part of a function group.
}

std::vector<lang::Description::Dependency> lang::FunctionDescription::getDeclarationDependencies() const
{
    auto* self = const_cast<FunctionDescription*>(this);

    std::vector<Dependency>    dependencies;
    std::set<lang::Identifier> added;

    auto add = [&](lang::ResolvingHandle<lang::Entity> entity) {
        if (auto type = entity.as<lang::Type>(); type.hasValue())
        {
            for (auto& dependency : (**type).extractTypesToResolve())
            {
                if (added.contains(dependency->name())) continue;

                dependencies.emplace_back(dependency);
                added.insert(dependency->name());
            }
        }
        else if (!added.contains(entity->name()))
        {
            dependencies.emplace_back(entity.base());
            added.insert(entity->name());
        }
    };

    add(self->return_type_);

    for (auto parameter : self->parameters_) { add(parameter->type()); }

    return dependencies;
}

std::vector<lang::Description::Dependency> lang::FunctionDescription::getDefinitionDependencies() const
{
    std::vector<Dependency> dependencies;

    for (auto& dependency : function_.value()->getDependenciesOnDeclaration())
    {
        dependencies.emplace_back(dependency, false);
    }

    for (auto& dependency : function_.value()->getDependenciesOnDefinition()) { dependencies.emplace_back(dependency); }

    return dependencies;
}

void lang::FunctionDescription::resolveDeclaration()
{
    scope().addEntity(lang::OwningHandle<lang::Function>::takeOwnership(function_.value()));
}

void lang::FunctionDescription::resolveDefinition()
{
    function_.value()->resolve();
}

void lang::FunctionDescription::postResolve()
{
    function_.value()->postResolve();
}

void lang::FunctionDescription::validate(ValidationLogger& validation_logger) const
{
    return_type_->validate(validation_logger, return_type_location_);

    if (access().modifier() == lang::AccessModifier::PUBLIC_ACCESS)
    {
        lang::validation::isTypeExportable(return_type_, return_type_location_, validation_logger);
    }

    std::set<lang::Identifier> names;

    for (auto const& parameter : parameters_)
    {
        auto [it, inserted] = names.insert(parameter->name());

        if (!inserted)
        {
            validation_logger.logWarning("Name '" + parameter->name() + "' already used for a parameter",
                                         parameter->name().location());
        }

        if (access().modifier() == lang::AccessModifier::PUBLIC_ACCESS)
        {
            lang::validation::isTypeExportable(parameter->type(), parameter->typeLocation(), validation_logger);
        }

        parameter->type().validate(validation_logger, parameter->typeLocation());
    }

    if (code_.hasValue()) { (**code_).validate(validation_logger); }
    else if (access().modifier() != lang::AccessModifier::EXTERN_ACCESS && !isImported())
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
    expanded_parameters.reserve(parameters_.size());
    for (auto& parameter : parameters_) { expanded_parameters.emplace_back(parameter->expand(new_context)); }

    auto expanded = makeOwned<lang::FunctionDescription>(access(),
                                                         name_,
                                                         return_type_->getUndefinedTypeClone(new_context),
                                                         return_type_location_,
                                                         expanded_parameters,
                                                         std::move(code),
                                                         declaration_location_,
                                                         definition_location_);

    Descriptions descriptions;
    descriptions.emplace_back(std::move(expanded));

    return descriptions;
}

void lang::FunctionDescription::buildDeclaration(CompileContext& context)
{
    function_.value()->createNativeBacking(context);
}

void lang::FunctionDescription::buildDefinition(CompileContext& context)
{
    function_.value()->build(context);
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
