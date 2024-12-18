#include "Function.h"

#include <utility>

#include "lang/AccessModifier.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/ImportedFunction.h"
#include "lang/construct/InitializerFunction.h"
#include "lang/construct/LocalVariable.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/construct/RuntimeFunction.h"
#include "validation/ValidationLogger.h"

lang::Function::Function(Identifier function_name) : name_(function_name) {}

lang::Identifier const& lang::Function::name() const
{
    return name_;
}

std::string lang::Function::getLinkageName() const
{
    return isMangled() ? signature().getMangledName() : std::string(name().text());
}

bool lang::Function::isDefined() const
{
    return definition_.hasValue();
}

bool lang::Function::isRuntime() const
{
    assert(isDefined());
    return definition_.value()->isRuntime();
}

lang::CMP lang::Function::cmp() const
{
    assert(isDefined());
    return definition_.value()->cmp();
}

bool lang::Function::preserveUnitReturn() const
{
    assert(isDefined());
    return definition_.value()->preserveUnitReturn();
}

void lang::Function::defineAsImported(Scope&                                      containing_scope,
                                      lang::AccessModifier                        access,
                                      lang::ResolvingHandle<lang::Type>           return_type,
                                      lang::Location                              return_type_location,
                                      std::vector<Shared<lang::Parameter>> const& parameters,
                                      lang::Location                              location)
{
    definition_ = makeOwned<lang::ImportedFunction>(*this,
                                                    containing_scope,
                                                    access,
                                                    return_type,
                                                    return_type_location,
                                                    parameters,
                                                    location);

    (**definition_).setup();
}

void lang::Function::defineAsCustom(lang::AccessModifier                        access,
                                    lang::CMP                                   cmp,
                                    lang::ResolvingHandle<lang::Type>           return_type,
                                    lang::Location                              return_type_location,
                                    std::vector<Shared<lang::Parameter>> const& parameters,
                                    Statement&                                  block,
                                    Scope&                                      containing_scope,
                                    lang::Location                              declaration_location,
                                    lang::Location                              definition_location)
{
    definition_ = makeOwned<lang::CustomFunction>(*this,
                                                  access,
                                                  cmp,
                                                  return_type,
                                                  return_type_location,
                                                  parameters,
                                                  block,
                                                  containing_scope,
                                                  declaration_location,
                                                  definition_location);

    (**definition_).setup();
}

lang::PredefinedFunction& lang::Function::defineAsPredefined(lang::ResolvingHandle<lang::Type>           return_type,
                                                             bool                                        is_constructor,
                                                             std::vector<Shared<lang::Parameter>> const& parameters,
                                                             lang::AccessModifier access_modifier,
                                                             bool                 is_imported,
                                                             lang::Scope&         containing_scope,
                                                             lang::Location       location)
{
    auto definition = makeOwned<lang::PredefinedFunction>(*this,
                                                          containing_scope,
                                                          access_modifier,
                                                          is_imported,
                                                          return_type,
                                                          is_constructor,
                                                          parameters,
                                                          location);

    lang::PredefinedFunction& predefined_function = *definition;

    definition_ = std::move(definition);
    (**definition_).setup();

    return predefined_function;
}

lang::InitializerFunction& lang::Function::defineAsInit(Statement&                        code,
                                                        lang::CMP                         cmp,
                                                        lang::ResolvingHandle<lang::Type> type,
                                                        lang::Scope&                      containing_scope)
{
    auto definition = makeOwned<lang::InitializerFunction>(*this, code, cmp, type, containing_scope);

    lang::InitializerFunction& initializer_function = *definition;

    definition_ = std::move(definition);
    (**definition_).setup();

    return initializer_function;
}

void lang::Function::defineAsRuntime(lang::ResolvingHandle<lang::Type>    return_type,
                                     std::vector<Shared<lang::Parameter>> parameters,
                                     Execution&                           exec)
{
    definition_ = makeOwned<lang::RuntimeFunction>(*this, return_type, parameters, exec);
    (**definition_).setup();
}

void lang::Function::define(Owned<lang::FunctionDefinition> definition)
{
    definition_ = std::move(definition);
    (**definition_).setup();
}

lang::AccessModifier lang::Function::access() const
{
    assert(isDefined());
    return definition_.value()->access();
}

lang::ResolvingHandle<lang::Type> lang::Function::returnType()
{
    assert(isDefined());
    return definition_.value()->returnType();
}

lang::Type const& lang::Function::returnType() const
{
    assert(isDefined());
    return definition_.value()->returnType();
}

lang::Signature const& lang::Function::signature() const
{
    assert(isDefined());
    return definition_.value()->signature();
}

Statement const* lang::Function::code() const
{
    assert(isDefined());
    return definition_.value()->code();
}

Shared<lang::Parameter> lang::Function::parameter(size_t index)
{
    assert(isDefined());
    return definition_.value()->parameter(index);
}

lang::Parameter const& lang::Function::parameter(size_t index) const
{
    assert(isDefined());
    return definition_.value()->parameter(index);
}

size_t lang::Function::parameterCount() const
{
    assert(isDefined());
    return definition_.value()->parameterCount();
}

std::vector<Shared<lang::Parameter>> const& lang::Function::parameters() const
{
    assert(isDefined());
    return definition_.value()->parameters();
}

lang::Location lang::Function::location() const
{
    assert(isDefined());
    return definition_.value()->location();
}

Optional<lang::Location> lang::Function::getDefinitionLocation() const
{
    assert(isDefined());
    return definition_.value()->getDefinitionLocation();
}

bool lang::Function::isMangled() const
{
    assert(isDefined());
    return definition_.value()->isMangled();
}

bool lang::Function::isImported() const
{
    assert(isDefined());
    return definition_.value()->isImported();
}

void lang::Function::determineFlow()
{
    definition_.value()->determineFlow();
}

void lang::Function::validateFlow(ValidationLogger& validation_logger) const
{
    definition_.value()->validateFlow(validation_logger);
}

void lang::Function::registerDeclaration(Execution& exec) const
{
    definition_.value()->registerDeclaration(exec);
}

bool lang::Function::validateCall(std::vector<std::reference_wrapper<Expression const>> const& arguments,
                                  lang::Location                                               location,
                                  ValidationLogger&                                            validation_logger) const
{
    return definition_.value()->validateCall(arguments, location, validation_logger);
}

Shared<lang::Value> lang::Function::execCall(std::vector<Shared<lang::Value>> const& arguments, Execution& exec) const
{
    return definition_.value()->execCall(arguments, exec);
}

lang::Scope& lang::Function::scope()
{
    return definition_.value()->scope();
}

lang::Scope const& lang::Function::scope() const
{
    return definition_.value()->scope();
}

bool lang::Function::isPartOfFunction() const
{
    return true;
}

lang::BasicBlock const* lang::Function::getEntryBlock() const
{
    return definition_.value()->getEntryBlock();
}

std::vector<lang::BasicBlock*> const& lang::Function::getBasicBlocks() const
{
    return definition_.value()->getBasicBlocks();
}

void lang::Function::resolveFollowingOrder()
{
    definition_.value()->resolveFollowingOrder();
}

void lang::Function::postResolve()
{
    definition_.value()->postResolve();

    Scope::postResolve();
}

void lang::Function::registerEntityDeclarationsFollowingOrder(Execution& exec) const
{
    definition_.value()->registerDeclarationsFollowingOrder(exec);
}

lang::ResolvingHandle<lang::Entity> lang::Function::getUndefinedClone(lang::Context&) const
{
    return lang::makeHandled<lang::Function>(name());
}
