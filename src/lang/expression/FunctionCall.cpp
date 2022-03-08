#include "FunctionCall.h"

#include <utility>

#include "lang/scope/GlobalScope.h"
#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

FunctionCall::FunctionCall(lang::ResolvingHandle<lang::FunctionGroup> function_group,
                           std::vector<std::unique_ptr<Expression>>   arguments,
                           lang::Location                             location)
    : Expression(location)
    , function_group_(std::move(function_group))
    , arguments_(std::move(arguments))
{
    for (auto& argument : arguments_) { addChild(*argument); }
}

lang::ResolvingHandle<lang::FunctionGroup> FunctionCall::group() const
{
    return function_group_;
}

std::vector<std::reference_wrapper<Expression>> FunctionCall::arguments() const
{
    std::vector<std::reference_wrapper<Expression>> arguments;

    arguments.reserve(arguments_.size());
    for (auto& argument : arguments_) { arguments.emplace_back(*argument); }

    return arguments;
}

void FunctionCall::setScope(lang::Scope* scope)
{
    scope->registerUsage(function_group_);

    for (auto& arg : arguments_) { arg->setContainingScope(scope); }
}

lang::ResolvingHandle<lang::Type> FunctionCall::type()
{
    assert(!function().empty());
    return function().front()->returnType();
}

bool FunctionCall::validate(ValidationLogger& validation_logger)
{
    std::vector<std::pair<std::shared_ptr<lang::Value>, lang::Location>> arguments;

    bool valid = true;

    for (auto& arg : arguments_)
    {
        valid &= arg->validate(validation_logger);
        arguments.emplace_back(arg->getValue(), arg->location());
    }

    if (!valid) return false;

    if (!function_group_->isDefined())
    {
        validation_logger.logError("Name '" + function_group_->name() + "' not defined in the current context",
                                   location());
        return false;
    }

    bool is_resolving_valid = function_group_->validateResolution(argumentTypes(), location(), validation_logger);
    if (!is_resolving_valid) return false;

    std::vector<lang::ResolvingHandle<lang::Function>> potential_functions = function();
    if (potential_functions.empty())
    {
        validation_logger.logError("Cannot resolve '" + function_group_->name() + "' function overload", location());
        return false;
    }

    if (potential_functions.size() > 1)
    {
        validation_logger.logError("Ambiguous function call to '" + function_group_->name() + "'", location());
        return false;
    }

    lang::ResolvingHandle<lang::Function> actual_function = potential_functions.front();
    if (!actual_function->isDefined())
    {
        validation_logger.logError("Function '" + actual_function->name() + "' is not defined", location());
        return false;
    }

    return actual_function->validateCall(arguments, location(), validation_logger);
}

void FunctionCall::doBuild(CompileContext* context)
{
    std::vector<std::shared_ptr<lang::Value>> arg_values;

    for (auto& arg : arguments_) { arg_values.push_back(arg->getValue()); }

    std::shared_ptr<lang::Value> return_value = function().front()->buildCall(arg_values, context);

    if (return_value != nullptr)// Not every function returns a value.
    {
        setValue(return_value);
    }
}

std::vector<lang::ResolvingHandle<lang::Function>> FunctionCall::function()
{
    if (!overload_resolved_)
    {
        function_          = function_group_->resolveOverload(argumentTypes());
        overload_resolved_ = true;
    }

    return function_;
}

std::vector<lang::ResolvingHandle<lang::Type>> FunctionCall::argumentTypes()
{
    std::vector<lang::ResolvingHandle<lang::Type>> arg_types;
    arg_types.reserve(arguments_.size());
    for (auto& arg : arguments_) { arg_types.push_back(arg->type()); }

    return arg_types;
}

FunctionCall::~FunctionCall() = default;