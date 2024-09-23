#include "Callable.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "validation/ValidationLogger.h"

bool lang::Callable::isCMP() const
{
    return false;
}

std::string lang::Callable::getAnnotatedName(bool) const
{
    return std::string(name().text());
}

void lang::Callable::addFunction(lang::OwningHandle<lang::Function> function)
{
    functions_.push_back(std::move(function));
    function_handles_.push_back(functions_.back().handle());
}

bool lang::Callable::validateResolution(std::vector<std::reference_wrapper<lang::Type const>> const& types,
                                        lang::Location                                               location,
                                        ValidationLogger& validation_logger) const
{
    size_t const argument_count = types.size();

    for (auto& function : getFunctionSource().functions_)
    {
        if (function->signature().getParameterCount() == argument_count) return true;
    }

    validation_logger.logError("No overload of " + getAnnotatedName(true) + " takes " + std::to_string(argument_count)
                                   + " argument(s)",
                               location);

    return false;
}

std::vector<lang::ResolvingHandle<lang::Function>> lang::Callable::resolveOverload(
    std::vector<std::reference_wrapper<lang::Type const>> const& arguments)
{
    std::vector<lang::ResolvingHandle<lang::Function>> same_signatures;
    std::vector<lang::ResolvingHandle<lang::Function>> matching_signatures;

    if (getFunctionSource().functions_.size() == 1)
    {
        std::vector<lang::ResolvingHandle<lang::Function>> result;
        result.push_back(getFunctionSource().functions_.front().handle());
        return result;
    }

    for (auto& function : getFunctionSource().functions_)
    {
        if (function->signature().isSame(arguments)) same_signatures.push_back(function.handle());
        else if (enableImplicitConversionOnCall() && function->signature().isMatching(arguments))
            matching_signatures.emplace_back(function.handle());
    }

    if (same_signatures.empty()) return matching_signatures;
    else return same_signatures;
}

std::vector<std::reference_wrapper<lang::Function const>> lang::Callable::resolveOverload(
    std::vector<std::reference_wrapper<lang::Type const>> const& arguments) const
{
    std::vector<std::reference_wrapper<lang::Function const>> same_signatures;
    std::vector<std::reference_wrapper<lang::Function const>> matching_signatures;

    if (getFunctionSource().functions_.size() == 1)
    {
        std::vector<std::reference_wrapper<lang::Function const>> result;
        result.emplace_back(*getFunctionSource().functions_.front());
        return result;
    }

    for (auto& function : getFunctionSource().functions_)
    {
        if (function->signature().isSame(arguments)) same_signatures.emplace_back(*function);
        else if (enableImplicitConversionOnCall() && function->signature().isMatching(arguments))
            matching_signatures.emplace_back(*function);
    }

    if (same_signatures.empty()) return matching_signatures;
    else return same_signatures;
}

std::vector<lang::ResolvingHandle<lang::Function>>& lang::Callable::functions()
{
    return getFunctionSource().function_handles_;
}

std::vector<lang::ResolvingHandle<lang::Function>> const& lang::Callable::functions() const
{
    return getFunctionSource().function_handles_;
}

bool lang::Callable::enableImplicitConversionOnCall() const
{
    return true;
}

lang::Callable& lang::Callable::getFunctionSource()
{
    return *this;
}

lang::Callable const& lang::Callable::getFunctionSource() const
{
    return *this;
}
