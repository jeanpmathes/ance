#include "ImportedFunction.h"

#include <utility>

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/scope/Scope.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

lang::ImportedFunction::ImportedFunction(Function& function,
                                         Scope&                               containing_scope,
                                         lang::AccessModifier                 access,
                                         lang::ResolvingHandle<lang::Type>    return_type,
                                         lang::Location                       return_type_location,
                                         std::vector<Shared<lang::Parameter>> parameters,
                                         lang::Location                       location)
    : lang::FunctionDefinition(function,
                               containing_scope,
                               return_type,
                               return_type_location,
                               std::move(parameters),
                               location)
    , access_(access)
{}

void lang::ImportedFunction::setup()
{
    scope().registerUsage(returnType());

    for (auto& parameter : this->parameters()) { scope().registerUsage(parameter->type()); }
}

bool lang::ImportedFunction::isMangled() const
{
    return access_ != lang::AccessModifier::EXTERN_ACCESS;
}

bool lang::ImportedFunction::isImported() const
{
    return true;
}

lang::AccessModifier lang::ImportedFunction::access() const
{
    return access_;
}

Optional<lang::Location> lang::ImportedFunction::getDefinitionLocation() const
{
    return std::nullopt;
}

bool lang::ImportedFunction::isConstructor() const
{
    return false;
}

void lang::ImportedFunction::determineFlow() {}

bool lang::ImportedFunction::validateFlow(ValidationLogger&) const
{
    return true;
}

void lang::ImportedFunction::build(CompileContext&) {}

std::vector<lang::BasicBlock*> const& lang::ImportedFunction::getBasicBlocks() const
{
    static std::vector<lang::BasicBlock*> const empty;
    return empty;
}
