#include "FunctionCall.h"

#include <utility>

#include "ance/scope/GlobalScope.h"
#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

FunctionCall::FunctionCall(ance::ResolvingHandle<ance::Function>    function,
                           std::vector<std::unique_ptr<Expression>> arguments,
                           ance::Location                           location)
    : Expression(location)
    , function_(std::move(function))
    , arguments_(std::move(arguments))
{}

void FunctionCall::setScope(ance::Scope* scope)
{
    scope->registerUsage(function_);

    for (auto& arg : arguments_) { arg->setContainingScope(scope); }
}

ance::Type* FunctionCall::type()
{
    return function_->returnType();
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

    if (!function_->isDefined())
    {
        validation_logger.logError("Name '" + function_->name() + "' not defined in the current context", location());
        return false;
    }

    return function_->validateCall(arguments, location(), validation_logger);
}

void FunctionCall::doBuild(CompileContext* context)
{
    std::vector<std::shared_ptr<ance::Value>> arg_values;

    for (auto& arg : arguments_) { arg_values.push_back(arg->getValue()); }

    std::shared_ptr<ance::Value> return_value = function_->buildCall(arg_values, context);

    if (return_value != nullptr)// Not every function returns a value.
    {
        setValue(return_value);
    }
}

FunctionCall::~FunctionCall() = default;