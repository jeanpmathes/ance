#include "FunctionCall.h"

#include <utility>

#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/scope/GlobalScope.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

FunctionCall::FunctionCall(Optional<lang::ResolvingHandle<lang::FunctionGroup>> function_group,
                           lang::ResolvingHandle<lang::Type>                    type_function_group,
                           std::vector<Owned<Expression>>                       arguments,
                           lang::Location                                       location)
    : Expression(location)
    , function_group_(std::move(function_group))
    , type_function_group_(std::move(type_function_group))
    , arguments_(std::move(arguments))
{
    for (auto& argument : arguments_) { addSubexpression(*argument); }
}

template<typename OUT, typename IN>
struct GetCallable {
    static OUT get(IN self)
    {
        if (!self->used_callable_)
        {
            if (self->function_group_.hasValue() && self->function_group_.value()->isDefined())
            {
                self->used_callable_ = &*self->function_group_.value();
            }
            else { self->used_callable_ = &*self->type_function_group_; }
        }

        return const_cast<OUT>(*self->used_callable_);
    }
};

lang::Callable const& FunctionCall::callable() const
{
    return GetCallable<lang::Callable const&, FunctionCall const*>::get(this);
}

lang::Callable& FunctionCall::getCallable()
{
    return GetCallable<lang::Callable&, FunctionCall*>::get(this);
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

    if (function_group_.hasValue()) scope()->registerUsage(function_group_.value());
    if (!type_function_group_->isDefined()) scope()->registerUsage(type_function_group_);
}

void FunctionCall::postResolve()
{
    Expression::postResolve();

    if (not callable().isDefined()) return;

    std::vector<lang::ResolvingHandle<lang::Type>> argument_types;
    argument_types.reserve(arguments_.size());

    for (auto& argument : arguments_)
    {
        auto argument_type = argument->type();
        if (not argument_type->isDefined()) return;
        argument_types.emplace_back(argument_type);
    }

    getCallable().requestOverload(argument_types);

    if (function().size() == 1 && function().front()->isDefined()) scope()->addDependency(function().front());

    function();// This must be called before validation to ensure that overload resolution is done.
    type();
}

void FunctionCall::defineType(lang::ResolvingHandle<lang::Type> type)
{
    if (!used_callable_) return;

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

    if (!callable().isDefined())
    {
        validation_logger.logError("Name '" + callable().name() + "' is undefined in current context", location());
        return false;
    }

    bool const is_resolving_valid = callable().validateResolution(argumentTypes(), location(), validation_logger);
    if (!is_resolving_valid) return false;

    auto functions = callable().resolveOverload(argumentTypes());

    if (functions.empty())
    {
        validation_logger.logError("Cannot resolve '" + callable().name() + "' function overload", location());
        return false;
    }

    if (functions.size() > 1)
    {
        validation_logger.logError("Ambiguous function call to '" + callable().name() + "'", location());
        return false;
    }

    std::reference_wrapper<lang::Function const> const actual_function = functions.front();

    if (lang::validation::isFunctionUndefined(actual_function, location(), validation_logger)) return false;

    return actual_function.get().validateCall(arguments, location(), validation_logger);
}

Expression::Expansion FunctionCall::expandWith(Expressions subexpressions, lang::Context& new_context) const
{
    Optional<lang::ResolvingHandle<lang::FunctionGroup>> fng;

    return {Statements(),
            makeOwned<FunctionCall>(function_group_.hasValue() ? function_group_.value()->toUndefined() : fng,
                                    type_function_group_->createUndefinedClone(new_context),
                                    std::move(subexpressions),
                                    location()),
            Statements()};
}

void FunctionCall::doBuild(CompileContext& context)
{
    std::vector<Shared<lang::Value>> arg_values;

    for (auto& arg : arguments_) { arg_values.push_back(arg->getValue()); }

    Optional<Shared<lang::Value>> return_value = function().front()->buildCall(arg_values, context);

    if (return_value.hasValue()) { setValue(return_value.value()); }
}

std::vector<lang::ResolvingHandle<lang::Function>> FunctionCall::function()
{
    if (!overload_resolved_)
    {
        function_          = getCallable().resolveOverload(argumentTypes());
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
