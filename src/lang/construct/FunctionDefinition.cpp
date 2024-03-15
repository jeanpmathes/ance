#include "FunctionDefinition.h"

#include <utility>

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/construct/constant/UnitConstant.h"
#include "validation/ValidationLogger.h"

lang::FunctionDefinition::FunctionDefinition(Function&                            function,
                                             Scope&                               containing_scope,
                                             lang::ResolvingHandle<lang::Type>    type,
                                             lang::Location                       return_type_location,
                                             std::vector<Shared<lang::Parameter>> parameters,
                                             lang::Location                       location)
    : function_(function)
    , containing_scope_(containing_scope)
    , return_type_(std::move(type))
    , return_type_location_(return_type_location)
    , parameters_(std::move(parameters))
    , location_(location)
    , signature_(lang::Signature::fromParameters(name(), parameters_))
{}

void lang::FunctionDefinition::setup()
{
    // Intentionally empty.
}

lang::Identifier const& lang::FunctionDefinition::name() const
{
    return function_.name();
}

lang::Scope& lang::FunctionDefinition::scope()
{
    return containing_scope_;
}

lang::Scope const& lang::FunctionDefinition::scope() const
{
    return containing_scope_;
}

lang::Function& lang::FunctionDefinition::function()
{
    return function_;
}

lang::Function const& lang::FunctionDefinition::function() const
{
    return function_;
}

lang::AccessModifier lang::FunctionDefinition::access() const
{
    return lang::AccessModifier::PRIVATE_ACCESS;
}

lang::ResolvingHandle<lang::Type> lang::FunctionDefinition::returnType()
{
    return return_type_;
}

lang::Type const& lang::FunctionDefinition::returnType() const
{
    return return_type_;
}

lang::Signature const& lang::FunctionDefinition::signature() const
{
    return signature_;
}

Statement const* lang::FunctionDefinition::code() const
{
    return nullptr;
}

lang::Location lang::FunctionDefinition::returnTypeLocation() const
{
    return return_type_location_;
}

Shared<lang::Parameter> lang::FunctionDefinition::parameter(size_t index)
{
    return parameters_[index];
}

lang::Parameter const& lang::FunctionDefinition::parameter(size_t index) const
{
    return *parameters_[index];
}

size_t lang::FunctionDefinition::parameterCount() const
{
    return parameters_.size();
}

lang::Location lang::FunctionDefinition::location() const
{
    return location_;
}

bool lang::FunctionDefinition::isRuntime() const
{
    return false;
}

bool lang::FunctionDefinition::isImported() const
{
    return false;
}

void lang::FunctionDefinition::resolveFollowingOrder() {}
void lang::FunctionDefinition::postResolve() {}

void lang::FunctionDefinition::buildDeclaration(CompileContext& context) const
{
    context.exec().createFunction(name(),
                                  function_.getLinkageName(),
                                  isRuntime() ? std::nullopt : makeOptional<>(access()),
                                  isImported(),
                                  parameters_,
                                  returnType(),
                                  isRuntime() ? nullptr : &scope(),
                                  preserveUnitReturn(),
                                  location(),
                                  getDefinitionLocation(),
                                  function());
}

bool lang::FunctionDefinition::validateCall(std::vector<std::reference_wrapper<Expression const>> const& arguments,
                                            lang::Location                                                                           location,
    ValidationLogger&                                                                        validation_logger) const
{
    if (arguments.size() != parameters_.size())
    {
        validation_logger.logError("Passed arguments do not match function signature '" + signature_.toString() + "'",
                                   location);
        return false;
    }

    bool valid = true;

    for (auto const [param, arg] : llvm::zip(parameters_, arguments))
    {
        bool const types_defined = param->type().isDefined() && arg.get().type().isDefined();
        valid &= types_defined
              && lang::Type::checkMismatch(param->type(), arg.get().type(), arg.get().location(), validation_logger);
    }

    if (!valid) return false;

    valid &= doCallValidation(arguments, location, validation_logger);

    return valid;
}

bool lang::FunctionDefinition::doCallValidation(std::vector<std::reference_wrapper<Expression const>> const&,
                                                lang::Location,
    ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::FunctionDefinition::buildCall(std::vector<Shared<lang::Value>> arguments,
                                                        CompileContext&                  context) const
{
    return context.exec().performFunctionCall(function(), std::move(arguments));
}

std::vector<Shared<lang::Parameter>> const& lang::FunctionDefinition::parameters() const
{
    return parameters_;
}

std::vector<Shared<lang::Parameter>> lang::FunctionDefinition::parameters()
{
    return parameters_;
}

void lang::FunctionDefinition::buildDeclarationsFollowingOrder(CompileContext&) const {}

lang::BasicBlock const* lang::FunctionDefinition::getEntryBlock() const
{
    return nullptr;
}
