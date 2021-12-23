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
    assert(function().has_value());
    return function().value()->returnType();
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

    std::optional<ance::ResolvingHandle<ance::Function>> potential_function = function();
    if (!potential_function.has_value())
    {
        validation_logger.logError("Cannot resolve '" + function_group_->name() + "' function overload", location());
        return false;
    }

    ance::ResolvingHandle<ance::Function> actual_function = potential_function.value();
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

    std::shared_ptr<ance::Value> return_value = function().value()->buildCall(arg_values, context);

    if (return_value != nullptr)// Not every function returns a value.
    {
        setValue(return_value);
    }
}

std::optional<ance::ResolvingHandle<ance::Function>> FunctionCall::function()
{
    if (!overload_resolved_)
    {
        std::vector<ance::ResolvingHandle<ance::Type>> arg_types;
        arg_types.reserve(arguments_.size());
        for (auto& arg : arguments_) { arg_types.push_back(arg->type()); }

        function_          = function_group_->resolveOverload(arg_types);
        overload_resolved_ = true;
    }

    return function_;
}

FunctionCall::~FunctionCall() = default;