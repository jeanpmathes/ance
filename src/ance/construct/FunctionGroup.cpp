#include "FunctionGroup.h"

#include <utility>

#include "validation/ValidationLogger.h"

ance::FunctionGroup::FunctionGroup(std::string name) : name_(std::move(name)) {}

bool ance::FunctionGroup::isDefined() const
{
    return !functions_.empty();
}

const std::string& ance::FunctionGroup::name() const
{
    return name_;
}

void ance::FunctionGroup::resolve()
{
    for (auto& function : functions_) function->resolve();
}

void ance::FunctionGroup::validate(ValidationLogger& validation_logger)
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

void ance::FunctionGroup::createNativeBacking(CompileContext* compile_context)
{
    for (auto& function : functions_) function->createNativeBacking(compile_context);
}

void ance::FunctionGroup::build(CompileContext* compile_context)
{
    for (auto& function : functions_) function->build(compile_context);
}

void ance::FunctionGroup::addFunction(ance::OwningHandle<ance::Function> function)
{
    assert(function->name() == name_);
    functions_.push_back(std::move(function));
}

bool ance::FunctionGroup::validateResolution(std::vector<ance::ResolvingHandle<ance::Type>> types,
                                             ance::Location                                 location,
                                             ValidationLogger&                              validation_logger)
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

std::optional<ance::ResolvingHandle<ance::Function>> ance::FunctionGroup::resolveOverload(
    const std::vector<ance::ResolvingHandle<ance::Type>>& arguments)
{
    for (auto& function : functions_)
    {
        if (function->signature().isMatching(arguments)) { return function.handle(); }
    }

    return {};
}
