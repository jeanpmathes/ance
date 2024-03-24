#include "SpecialMemberFunction.h"

#include "compiler/Unit.h"
#include "lang/ApplicationVisitor.h"

lang::SpecialMemberFunction::SpecialMemberFunction(lang::Function&                      function,
                                                   lang::ResolvingHandle<lang::Type>    type,
                                                   std::vector<Shared<lang::Parameter>> parameters)
    : lang::FunctionDefinition(function,
                               type->scope(),
                               type->scope().context().getUnitType(),
                               lang::Location::global(),
                               std::move(parameters),
                               lang::Location::global())
    , type_(*type)
{}

void lang::SpecialMemberFunction::setup()
{
    scope().registerUsage(returnType());

    for (auto& parameter : this->parameters()) { scope().registerUsage(parameter->type()); }
}

lang::ResolvingHandle<lang::Function> lang::SpecialMemberFunction::create(
    lang::ResolvingHandle<lang::Type>    type,
    lang::SpecialMemberFunction::Kind    kind,
    std::vector<Shared<lang::Parameter>> parameters)
{
    std::string prefix;
    switch (kind)
    {

        case Kind::DEFAULT_CONSTRUCTOR:
            prefix = "ctor_default$";
            break;
        case Kind::COPY_CONSTRUCTOR:
            prefix = "ctor_copy$";
            break;
        case Kind::DEFAULT_DESTRUCTOR:
            prefix = "dtor_default$";
            break;
    }

    std::string const name = prefix + type->getMangledName();

    lang::ResolvingHandle<lang::Function> function = makeHandled<lang::Function>(lang::Identifier::like(name));
    function->define(makeOwned<SpecialMemberFunction>(*function, type, std::move(parameters)));

    return function;
}

bool lang::SpecialMemberFunction::isMangled() const
{
    return false;
}

bool lang::SpecialMemberFunction::isRuntime() const
{
    return false;
}

bool lang::SpecialMemberFunction::isImported() const
{
    return type_.isImported();
}

lang::AccessModifier lang::SpecialMemberFunction::access() const
{
    return type_.getAccessibility().modifier();
}

Optional<lang::Location> lang::SpecialMemberFunction::getDefinitionLocation() const
{
    return std::nullopt;
}

bool lang::SpecialMemberFunction::preserveUnitReturn() const
{
    return true;
}

void lang::SpecialMemberFunction::determineFlow() {}

bool lang::SpecialMemberFunction::validateFlow(ValidationLogger&) const
{
    return true;
}

std::vector<lang::BasicBlock*> const& lang::SpecialMemberFunction::getBasicBlocks() const
{
    static std::vector<lang::BasicBlock*> const empty;
    return empty;
}
