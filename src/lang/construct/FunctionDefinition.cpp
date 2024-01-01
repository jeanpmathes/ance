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

lang::Scope& lang::FunctionDefinition::scope() const
{
    return containing_scope_;
}

lang::Function& lang::FunctionDefinition::function() const
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

lang::ResolvingHandle<lang::Type> lang::FunctionDefinition::parameterType(size_t index)
{
    return parameters_[index]->type();
}

lang::Type const& lang::FunctionDefinition::parameterType(size_t index) const
{
    return parameters_[index]->type();
}

lang::Identifier const& lang::FunctionDefinition::parameterName(size_t index) const
{
    return parameters_[index]->name();
}

size_t lang::FunctionDefinition::parameterCount() const
{
    return parameters_.size();
}

lang::Location lang::FunctionDefinition::location() const
{
    return location_;
}

bool lang::FunctionDefinition::isImported() const
{
    return false;
}

void lang::FunctionDefinition::resolveFollowingOrder() {}
void lang::FunctionDefinition::postResolve() {}

void lang::FunctionDefinition::createNativeBacking(CompileContext& context)
{
    function_handle_ = createBackingFunction(access(), isImported(), getDefinitionLocation(), isConstructor(), context);
}

bool lang::FunctionDefinition::validateCall(
    std::vector<std::pair<std::reference_wrapper<lang::Value const>, lang::Location>> const& arguments,
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
        auto const& [arg_value, arg_location] = arg;
        bool const types_defined              = param->type().isDefined() && arg_value.get().type().isDefined();
        valid &= types_defined
              && lang::Type::checkMismatch(param->type(), arg_value.get().type(), arg_location, validation_logger);
    }

    if (!valid) return false;

    valid &= doCallValidation(arguments, location, validation_logger);

    return valid;
}

bool lang::FunctionDefinition::doCallValidation(
    std::vector<std::pair<std::reference_wrapper<lang::Value const>, lang::Location>> const&,
    lang::Location,
    ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::FunctionDefinition::buildCall(std::vector<Shared<lang::Value>> arguments,
                                                        CompileContext&                  context)
{
    return context.exec().performFunctionCall(function_handle_.value(), std::move(arguments));
}

std::vector<Shared<lang::Parameter>> const& lang::FunctionDefinition::parameters() const
{
    return parameters_;
}

std::vector<Shared<lang::Parameter>> lang::FunctionDefinition::parameters()
{
    return parameters_;
}

Execution::Function lang::FunctionDefinition::createBackingFunction(lang::AccessModifier     access,
                                                                    bool                     is_imported,
                                                                    Optional<lang::Location> definition_location,
                                                                    bool                     is_constructor,
                                                                    CompileContext&          context)
{
    return context.exec().createFunction(name(),
                                         function_.getLinkageName(),
                                         access,
                                         is_imported,
                                         parameters_,
                                         returnType(),
                                         &scope(),
                                         is_constructor,
                                         location(),
                                         definition_location);
}

void lang::FunctionDefinition::buildDeclarationsFollowingOrder(CompileContext&) {}

Execution::Scoped lang::FunctionDefinition::getDebugScope() const
{
    return function_handle_.value();
}
