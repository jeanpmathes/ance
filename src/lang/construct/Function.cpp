#include "Function.h"

#include <utility>

#include "compiler/CompileContext.h"
#include "lang/AccessModifier.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/ImportedFunction.h"
#include "lang/construct/LocalVariable.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/scope/LocalScope.h"
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
                                                  return_type,
                                                  return_type_location,
                                                  parameters,
                                                  block,
                                                  containing_scope,
                                                  declaration_location,
                                                  definition_location);

    (**definition_).setup();
}

lang::PredefinedFunction& lang::Function::defineAsPredefined(lang::ResolvingHandle<lang::Type> return_type,
                                                             bool                              preserve_unit_return,
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
                                                          preserve_unit_return,
                                                          parameters,
                                                          location);

    lang::PredefinedFunction& predefined_function = *definition;

    definition_ = std::move(definition);
    (**definition_).setup();

    return predefined_function;
}

lang::InitializerFunction& lang::Function::defineAsInit(Statement& code, lang::Scope& containing_scope)
{
    auto definition = makeOwned<lang::InitializerFunction>(*this, code, containing_scope);

    lang::InitializerFunction& initializer_function = *definition;

    definition_ = std::move(definition);
    (**definition_).setup();

    return initializer_function;
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

lang::ResolvingHandle<lang::Type> lang::Function::parameterType(size_t index)
{
    assert(isDefined());
    return definition_.value()->parameterType(index);
}

lang::Type const& lang::Function::parameterType(size_t index) const
{
    assert(isDefined());
    return definition_.value()->parameterType(index);
}

lang::Identifier const& lang::Function::parameterName(size_t index) const
{
    assert(isDefined());
    return definition_.value()->parameterName(index);
}

size_t lang::Function::parameterCount() const
{
    assert(isDefined());
    return definition_.value()->parameterCount();
}

lang::Location lang::Function::location() const
{
    assert(isDefined());
    return definition_.value()->location();
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

void lang::Function::createNativeBacking(CompileContext& context)
{
    definition_.value()->createNativeBacking(context);
}

void lang::Function::build(CompileContext& context)
{
    definition_.value()->build(context);
}

bool lang::Function::validateCall(
    std::vector<std::pair<std::reference_wrapper<lang::Value const>, lang::Location>> const& arguments,
    lang::Location                                                                           location,
    ValidationLogger&                                                                        validation_logger) const
{
    return definition_.value()->validateCall(arguments, location, validation_logger);
}

Shared<lang::Value> lang::Function::buildCall(std::vector<Shared<lang::Value>> const& arguments,
                                              CompileContext&                         context)
{
    return definition_.value()->buildCall(arguments, context);
}

lang::Scope* lang::Function::scope()
{
    return &definition_.value()->scope();
}

lang::Scope const* lang::Function::scope() const
{
    return &definition_.value()->scope();
}

llvm::DIScope* lang::Function::getDebugScope(CompileContext& context) const
{
    return definition_.value()->getDebugScope(context);
}

bool lang::Function::isPartOfFunction() const
{
    return true;
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

void lang::Function::buildDeclarationsFollowingOrder(CompileContext& context)
{
    definition_.value()->buildDeclarationsFollowingOrder(context);
}

void lang::Function::setImportExportAttributes(llvm::Function*      function,
                                               lang::AccessModifier access_modifier,
                                               bool                 is_imported,
                                               CompileContext&)
{
    if (access_modifier.linkage() != llvm::GlobalValue::LinkageTypes::ExternalLinkage) return;

    if (is_imported) { function->setDLLStorageClass(llvm::GlobalValue::DLLStorageClassTypes::DLLImportStorageClass); }
    else { function->setDLLStorageClass(llvm::GlobalValue::DLLStorageClassTypes::DLLExportStorageClass); }
}

lang::ResolvingHandle<lang::Entity> lang::Function::getUndefinedClone(lang::Context&) const
{
    return lang::makeHandled<lang::Function>(name());
}
