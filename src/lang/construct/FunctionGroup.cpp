#include "FunctionGroup.h"

#include <utility>

#include "validation/ValidationLogger.h"

lang::FunctionGroup::FunctionGroup(Identifier name) : name_(std::move(name)) {}

bool lang::FunctionGroup::isDefined() const
{
    return !functions_.empty();
}

const lang::Identifier& lang::FunctionGroup::name() const
{
    return name_;
}

void lang::FunctionGroup::resolve()
{
    for (auto& function : functions_) function->resolve();
}

void lang::FunctionGroup::validate(ValidationLogger& validation_logger) const
{
    {// Validate that every signature is unique
        for (size_t i = 0; i < functions_.size(); ++i)
        {
            for (size_t j = i + 1; j < functions_.size(); ++j)
            {
                if (functions_[i]->signature() == functions_[j]->signature())
                {
                    validation_logger.logError("Duplicated function definition with signature '"
                                                   + functions_[i]->signature().toString() + "'",
                                               functions_[j]->location());
                }
            }
        }
    }

    {// Validate that at most one function is not mangled
        size_t non_mangled_count = 0;

        for (auto& function : functions_)
        {
            if (!function->isMangled())
            {
                if (non_mangled_count > 0)
                {
                    validation_logger.logError("Multiple non-mangled functions in function group '" + name_ + "'",
                                               function->location());
                }

                non_mangled_count++;
            }
        }
    }

    {// Validate every function
        for (auto& function : functions_) { function->validate(validation_logger); }
    }
}

void lang::FunctionGroup::expand()
{
    for (auto& function : functions_) function->expand();
}

void lang::FunctionGroup::determineFlow()
{
    for (auto& function : functions_) function->determineFlow();
}

void lang::FunctionGroup::validateFlow(ValidationLogger& validation_logger) const
{
    for (auto& function : functions_) function->validateFlow(validation_logger);
}

void lang::FunctionGroup::createNativeBacking(CompileContext* compile_context)
{
    for (auto& function : functions_) function->createNativeBacking(compile_context);
}

void lang::FunctionGroup::build(CompileContext* compile_context)
{
    for (auto& function : functions_) function->build(compile_context);
}

void lang::FunctionGroup::addFunction(lang::OwningHandle<lang::Function> function)
{
    assert(function->name().text() == name_.text());

    addChild(*function);
    functions_.push_back(std::move(function));
}

bool lang::FunctionGroup::validateResolution(const std::vector<lang::ResolvingHandle<lang::Type>>& types,
                                             lang::Location                                        location,
                                             ValidationLogger& validation_logger) const
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

std::vector<lang::ResolvingHandle<lang::Function>> lang::FunctionGroup::resolveOverload(
    const std::vector<lang::ResolvingHandle<lang::Type>>& arguments) const
{
    std::vector<lang::ResolvingHandle<lang::Function>> same_signatures;
    std::vector<lang::ResolvingHandle<lang::Function>> matching_signatures;

    for (auto& function : functions_)
    {
        if (function->signature().isSame(arguments)) same_signatures.push_back(function.handle());
        else if (function->signature().isMatching(arguments)) matching_signatures.push_back(function.handle());
    }

    if (same_signatures.empty()) return matching_signatures;
    else return same_signatures;
}

lang::ResolvingHandle<lang::FunctionGroup> lang::FunctionGroup::toUndefined() const
{
    return lang::makeHandled<lang::FunctionGroup>(name());
}
