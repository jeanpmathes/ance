#include "FunctionCall.h"

#include <utility>

#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/scope/GlobalScope.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

FunctionCall::FunctionCall(lang::ResolvingHandle<lang::Entity> callable,
                           std::vector<Owned<Expression>>      arguments,
                           lang::Location                      location)
    : Expression(location)
    , callable_(callable)
    , arguments_(std::move(arguments))
{
    for (auto& argument : arguments_) { addSubexpression(*argument); }
}

lang::Entity const& FunctionCall::callee() const
{
    return *callable_;
}

lang::Callable const* FunctionCall::getCallable() const
{
    if (!used_callable_.hasValue())
    {
        if (callable_.is<lang::FunctionGroup>()) { used_callable_ = callable_.as<lang::FunctionGroup>(); }
        else if (callable_.is<lang::Type>()) { used_callable_ = callable_.as<lang::Type>(); }
        else { used_callable_ = nullptr; }
    }

    return used_callable_.value();
}

lang::Callable* FunctionCall::getCallable()
{
    return const_cast<lang::Callable*>(static_cast<FunctionCall const*>(this)->getCallable());
}

std::vector<std::reference_wrapper<Expression const>> FunctionCall::arguments() const
{
    std::vector<std::reference_wrapper<Expression const>> arguments;

    arguments.reserve(arguments_.size());
    for (auto& argument : arguments_) { arguments.emplace_back(*argument); }

    return arguments;
}

void FunctionCall::walkDefinitions()
{
    Expression::walkDefinitions();

    scope()->registerUsageIfUndefined(callable_);
}

void FunctionCall::postResolve()
{
    Expression::postResolve();

    if (getCallable() == nullptr || !getCallable()->isDefined()) return;

    std::vector<lang::ResolvingHandle<lang::Type>> argument_types;
    argument_types.reserve(arguments_.size());

    for (auto& argument : arguments_)
    {
        auto argument_type = argument->type();
        if (not argument_type->isDefined()) return;
        argument_types.emplace_back(argument_type);
    }

    getCallable()->requestOverload(argument_types);

    if (function().size() == 1 && function().front()->isDefined()) scope()->addDependency(function().front());

    function();// This must be called before validation to ensure that overload resolution is done.
    type();
}

void FunctionCall::defineType(lang::ResolvingHandle<lang::Type> type)
{
    if (!used_callable_.hasValue()) return;

    for (auto& argument : arguments_)
    {
        if (not argument->type()->isDefined()) return;
    }

    if (function().empty()) return;

    type.reroute(function().front()->returnType());
}

bool FunctionCall::validate(ValidationLogger& validation_logger) const
{
    std::vector<std::pair<std::reference_wrapper<lang::Value const>, lang::Location>> arguments;

    bool valid = true;

    for (auto& arg : arguments_)
    {
        valid &= arg->validate(validation_logger);
        arguments.emplace_back(arg->getValue(), arg->location());
    }

    if (!valid) return false;

    if (lang::validation::isUndefined(callable_, scope(), location(), validation_logger)) return false;
    if (getCallable() == nullptr)
    {
        validation_logger.logError("Provided value " + callable_->getAnnotatedName() + "is not callable", location());
        return false;
    }

    bool const is_resolving_valid = getCallable()->validateResolution(argumentTypes(), location(), validation_logger);
    if (!is_resolving_valid) return false;

    auto functions = getCallable()->resolveOverload(argumentTypes());

    if (functions.empty())
    {
        validation_logger.logError("Cannot resolve " + getCallable()->getAnnotatedName(true) + " function overload",
                                   location());
        return false;
    }

    if (functions.size() > 1)
    {
        validation_logger.logError("Ambiguous function call to " + getCallable()->getAnnotatedName(true), location());
        return false;
    }

    std::reference_wrapper<lang::Function const> const actual_function = functions.front();

    if (lang::validation::isUndefined(actual_function, scope(), location(), validation_logger)) return false;

    return actual_function.get().validateCall(arguments, location(), validation_logger);
}

Expression::Expansion FunctionCall::expandWith(Expressions subexpressions, lang::Context& new_context) const
{
    return {Statements(),
            makeOwned<FunctionCall>(callable_->getUndefinedClone(new_context), std::move(subexpressions), location()),
            Statements()};
}

void FunctionCall::doBuild(CompileContext& context)
{
    std::vector<Shared<lang::Value>> arg_values;

    arg_values.reserve(arguments_.size());
    for (auto& arg : arguments_) { arg_values.push_back(arg->getValue()); }

    Shared<lang::Value> return_value = function().front()->buildCall(arg_values, context);
    setValue(return_value);
}

std::vector<lang::ResolvingHandle<lang::Function>> FunctionCall::function()
{
    if (!overload_resolved_)
    {
        function_ = getCallable() != nullptr ? getCallable()->resolveOverload(argumentTypes()) : decltype(function_)();
        overload_resolved_ = true;
    }

    return function_;
}

std::vector<std::reference_wrapper<lang::Type const>> FunctionCall::argumentTypes() const
{
    std::vector<std::reference_wrapper<lang::Type const>> arg_types;

    arg_types.reserve(arguments_.size());
    for (auto& arg : arguments_) { arg_types.emplace_back(arg->type()); }

    return arg_types;
}

FunctionCall::~FunctionCall() = default;
