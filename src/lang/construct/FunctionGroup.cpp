#include "FunctionGroup.h"

#include <utility>

#include "compiler/AnceCompiler.h"
#include "lang/ApplicationVisitor.h"
#include "validation/ValidationLogger.h"

lang::FunctionGroup::FunctionGroup(Identifier name) : name_(name) {}

bool lang::FunctionGroup::isDefined() const
{
    return !functions().empty();
}

lang::Identifier const& lang::FunctionGroup::name() const
{
    return name_;
}

void lang::FunctionGroup::setScope(lang::Scope& scope)
{
    assert(scope_ == nullptr);
    scope_ = &scope;
}

lang::Scope* lang::FunctionGroup::scope()
{
    assert(scope_ != nullptr);
    return scope_;
}

lang::Scope const* lang::FunctionGroup::scope() const
{
    assert(scope_ != nullptr);
    return scope_;
}

bool lang::FunctionGroup::requestOverload(std::vector<lang::ResolvingHandle<lang::Type>>)
{
    return false;
}

void lang::FunctionGroup::resolve()
{
    for (auto& function : functions()) function->resolve();
}

void lang::FunctionGroup::postResolve()
{
    for (auto& function : functions()) function->postResolve();
}

void lang::FunctionGroup::validate(ValidationLogger& validation_logger) const
{
    {// Validate that every signature is unique
        for (size_t i = 0; i < functions().size(); ++i)
        {
            for (size_t j = i + 1; j < functions().size(); ++j)
            {
                if (functions()[i]->signature() == functions()[j]->signature())
                {
                    validation_logger.logError("Duplicated function definition with signature '"
                                                   + functions()[i]->signature().toString() + "'",
                                               functions()[j]->location());
                }
            }
        }
    }

    {// Validate that at most one function is not mangled
        size_t non_mangled_count = 0;

        for (auto& function : functions())
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

    {// Validate that no not-mangled function collides with a reserved function.
        for (auto& function : functions())
        {
            if (function->isMangled()) continue;

            if (function->context().isContainingRuntime() && Runtime::isNameReserved(function->name()))
            {
                validation_logger.logError("Function '" + function->name()
                                               + "' collides with a reserved runtime function",
                                           function->location());
            }

            for (auto& builtin : AnceCompiler::BUILTIN_NAMES)
            {
                if (function->name().text() == builtin)
                {
                    validation_logger.logError("Function '" + function->name()
                                                   + "' collides with a reserved builtin function",
                                               function->location());
                }
            }
        }
    }
}

void lang::FunctionGroup::determineFlow()
{
    for (auto& function : functions()) function->determineFlow();
}

void lang::FunctionGroup::validateFlow(ValidationLogger& validation_logger) const
{
    for (auto& function : functions()) function->validateFlow(validation_logger);
}

void lang::FunctionGroup::createNativeBacking(CompileContext& compile_context)
{
    for (auto& function : functions()) function->createNativeBacking(compile_context);
}

void lang::FunctionGroup::build(CompileContext& compile_context)
{
    for (auto& function : functions()) function->build(compile_context);
}

lang::ResolvingHandle<lang::FunctionGroup> lang::FunctionGroup::toUndefined() const
{
    return lang::makeHandled<lang::FunctionGroup>(name());
}
