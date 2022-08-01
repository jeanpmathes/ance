#include "FunctionCall.h"

#include <utility>

#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "lang/scope/GlobalScope.h"
#include "validation/ValidationLogger.h"

FunctionCall::FunctionCall(std::optional<lang::ResolvingHandle<lang::FunctionGroup>> function_group,
                           lang::ResolvingHandle<lang::Type>                         type_function_group,
                           std::vector<std::unique_ptr<Expression>>                  arguments,
                           lang::Location                                            location)
    : Expression(location)
    , function_group_(std::move(function_group))
    , type_function_group_(std::move(type_function_group))
    , arguments_(std::move(arguments))
{
    for (auto& argument : arguments_) { addSubexpression(*argument); }
}

const lang::Callable& FunctionCall::callable() const
{
    if (!used_callable_)
    {
        if (function_group_.has_value() && function_group_.value()->isDefined())
        {
            used_callable_ = &*function_group_.value();
        }
        else { used_callable_ = &*type_function_group_; }
    }

    return *used_callable_;
}

std::vector<std::reference_wrapper<Expression>> FunctionCall::arguments() const
{
    std::vector<std::reference_wrapper<Expression>> arguments;

    arguments.reserve(arguments_.size());
    for (auto& argument : arguments_) { arguments.emplace_back(*argument); }

    return arguments;
}

void FunctionCall::walkDefinitions()
{
    Expression::walkDefinitions();

    if (function_group_.has_value()) scope()->registerUsage(function_group_.value());
    if (!type_function_group_->isDefined()) scope()->registerUsage(type_function_group_);
}

lang::ResolvingHandle<lang::Type> FunctionCall::type() const
{
    assert(!function().empty());
    return function().front()->returnType();
}

bool FunctionCall::validate(ValidationLogger& validation_logger) const
{
    std::vector<std::pair<std::shared_ptr<lang::Value>, lang::Location>> arguments;

    bool valid = true;

    for (auto& arg : arguments_)
    {
        valid &= arg->validate(validation_logger);
        arguments.emplace_back(arg->getValue(), arg->location());
    }

    if (!valid) return false;

    if (!callable().isDefined())
    {
        validation_logger.logError("Name '" + callable().name() + "' not defined in the current context", location());
        return false;
    }

    bool is_resolving_valid = callable().validateResolution(argumentTypes(), location(), validation_logger);
    if (!is_resolving_valid) return false;

    std::vector<lang::ResolvingHandle<lang::Function>> potential_functions = function();
    if (potential_functions.empty())
    {
        validation_logger.logError("Cannot resolve '" + callable().name() + "' function overload", location());
        return false;
    }

    if (potential_functions.size() > 1)
    {
        validation_logger.logError("Ambiguous function call to '" + callable().name() + "'", location());
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

Expression::Expansion FunctionCall::expandWith(Expressions subexpressions) const
{
    std::optional<lang::ResolvingHandle<lang::FunctionGroup>> fng;

    return {Statements(),
            std::make_unique<FunctionCall>(function_group_ ? function_group_.value()->toUndefined() : fng,
                                           type_function_group_->toUndefined(),
                                           std::move(subexpressions),
                                           location()),
            Statements()};
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

std::vector<lang::ResolvingHandle<lang::Function>> FunctionCall::function() const
{
    if (!overload_resolved_)
    {
        function_          = callable().resolveOverload(argumentTypes());
        overload_resolved_ = true;
    }

    return function_;
}

std::vector<lang::ResolvingHandle<lang::Type>> FunctionCall::argumentTypes() const
{
    std::vector<lang::ResolvingHandle<lang::Type>> arg_types;
    arg_types.reserve(arguments_.size());
    for (auto& arg : arguments_) { arg_types.push_back(arg->type()); }

    return arg_types;
}

FunctionCall::~FunctionCall() = default;