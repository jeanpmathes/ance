#include "Callable.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "validation/ValidationLogger.h"

void lang::Callable::addFunction(lang::OwningHandle<lang::Function> function)
{
    onAddFunction(*function);

    functions_.push_back(std::move(function));
    function_handles_.push_back(functions_.back().handle());
}

bool lang::Callable::validateResolution(std::vector<lang::ResolvingHandle<lang::Type>> const& types,
                                        lang::Location                                        location,
                                        ValidationLogger&                                     validation_logger) const
{
    size_t argument_count = types.size();

    for (auto& function : functions_)
    {
        if (function->signature().getParameterCount() == argument_count) return true;
    }

    validation_logger.logError("No overload of '" + name() + "' takes " + std::to_string(argument_count) + " arguments",
                               location);

    return false;
}

std::vector<lang::ResolvingHandle<lang::Function>> lang::Callable::resolveOverload(
    std::vector<lang::ResolvingHandle<lang::Type>> const& arguments) const
{
    std::vector<lang::ResolvingHandle<lang::Function>> same_signatures;
    std::vector<lang::ResolvingHandle<lang::Function>> matching_signatures;

    for (auto& function : functions_)
    {
        if (function->signature().isSame(arguments)) same_signatures.push_back(function.handle());
        else if (enableImplicitConversionOnCall() && function->signature().isMatching(arguments))
            matching_signatures.push_back(function.handle());
    }

    if (same_signatures.empty()) return matching_signatures;
    else return same_signatures;
}

void lang::Callable::onAddFunction(lang::Function&) {}

std::vector<lang::ResolvingHandle<lang::Function>>& lang::Callable::functions()
{
    return function_handles_;
}

std::vector<lang::ResolvingHandle<lang::Function>> const& lang::Callable::functions() const
{
    return function_handles_;
}

bool lang::Callable::enableImplicitConversionOnCall() const
{
    return true;
}
