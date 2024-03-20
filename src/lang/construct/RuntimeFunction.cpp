#include "RuntimeFunction.h"

#include "compiler/CompileContext.h"
#include "compiler/Unit.h"
#include "lang/ApplicationVisitor.h"

lang::RuntimeFunction::RuntimeFunction(lang::Function&                      function,
                                       lang::ResolvingHandle<lang::Type>    return_type,
                                       std::vector<Shared<lang::Parameter>> parameters,
                                       CompileContext&                      context)
    : lang::FunctionDefinition(function,
                               context.unit().globalScope(),
                               return_type,
                               lang::Location::global(),
                               std::move(parameters),
                               lang::Location::global())
{}

void lang::RuntimeFunction::setup()
{
    scope().registerUsage(returnType());

    for (auto& parameter : this->parameters()) { scope().registerUsage(parameter->type()); }
}

bool lang::RuntimeFunction::isMangled() const
{
    return false;
}

bool lang::RuntimeFunction::isRuntime() const
{
    return true;
}

bool lang::RuntimeFunction::isImported() const
{
    return true;
}

Optional<lang::Location> lang::RuntimeFunction::getDefinitionLocation() const
{
    return std::nullopt;
}

bool lang::RuntimeFunction::preserveUnitReturn() const
{
    return false;
}

void lang::RuntimeFunction::determineFlow() {}

bool lang::RuntimeFunction::validateFlow(ValidationLogger&) const
{
    return true;
}

std::vector<lang::BasicBlock*> const& lang::RuntimeFunction::getBasicBlocks() const
{
    static std::vector<lang::BasicBlock*> const empty;
    return empty;
}
