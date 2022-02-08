#include "FunctionCall.h"

#include <utility>

#include "ance/scope/GlobalScope.h"
#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

FunctionCall::FunctionCall(ance::ResolvingHandle<ance::FunctionGroup> function_group,
                           std::vector<std::unique_ptr<Expression>>   arguments,
                           ance::Location                             location)
    : Expression(location)
    , function_group_(std::move(function_group))
    , arguments_(std::move(arguments))
{}

void FunctionCall::setScope(ance::Scope* scope)
{
    scope->registerUsage(function_group_);

    for (auto& arg : arguments_) { arg->setContainingScope(scope); }
}

ance::ResolvingHandle<ance::Type> FunctionCall::type()
{
    assert(!function().empty());
    return function().front()->returnType();
}

bool FunctionCall::validate(ValidationLogger& validation_logger)
{
    std::vector<std::pair<std::shared_ptr<ance::Value>, ance::Location>> arguments;

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

    std::vector<ance::ResolvingHandle<ance::Function>> potential_functions = function();
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

    ance::ResolvingHandle<ance::Function> actual_function = potential_functions.front();
    if (!actual_function->isDefined())
    {
        validation_logger.logError("Function '" + actual_function->name() + "' is not defined", location());
        return false;
    }

    return actual_function->validateCall(arguments, location(), validation_logger);
}

void FunctionCall::doBuild(CompileContext* context)
{
    std::vector<std::shared_ptr<ance::Value>> arg_values;

    for (auto& arg : arguments_) { arg_values.push_back(arg->getValue()); }

    std::shared_ptr<ance::Value> return_value = function().front()->buildCall(arg_values, context);

    if (return_value != nullptr)// Not every function returns a value.
    {
        setValue(return_value);
    }
}

std::vector<ance::ResolvingHandle<ance::Function>> FunctionCall::function()
{
    if (!overload_resolved_)
    {
        function_          = function_group_->resolveOverload(argumentTypes());
        overload_resolved_ = true;
    }

    return function_;
}

std::vector<ance::ResolvingHandle<ance::Type>> FunctionCall::argumentTypes()
{
    std::vector<ance::ResolvingHandle<ance::Type>> arg_types;
    arg_types.reserve(arguments_.size());
    for (auto& arg : arguments_) { arg_types.push_back(arg->type()); }

    return arg_types;
}

FunctionCall::~FunctionCall() = default;