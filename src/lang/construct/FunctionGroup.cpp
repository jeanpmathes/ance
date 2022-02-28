#include "FunctionGroup.h"

#include <utility>

#include "validation/ValidationLogger.h"

lang::FunctionGroup::FunctionGroup(std::string name) : name_(std::move(name)) {}

bool lang::FunctionGroup::isDefined() const
{
    return !functions_.empty();
}

const std::string& lang::FunctionGroup::name() const
{
    return name_;
}

void lang::FunctionGroup::resolve()
{
    for (auto& function : functions_) function->resolve();
}

void lang::FunctionGroup::validate(ValidationLogger& validation_logger)
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
        for (const auto& function : functions_) { function->validate(validation_logger); }
    }
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
    assert(function->name() == name_);

    addChild(*function);
    functions_.push_back(std::move(function));
}

bool lang::FunctionGroup::validateResolution(const std::vector<lang::ResolvingHandle<lang::Type>>& types,
                                             lang::Location                                        location,
                                             ValidationLogger&                                     validation_logger)
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
    const std::vector<lang::ResolvingHandle<lang::Type>>& arguments)
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
