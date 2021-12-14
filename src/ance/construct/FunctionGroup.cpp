#include "FunctionGroup.h"

#include <utility>

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
    for (const auto& function : functions_) { function->validate(validation_logger); }
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

std::optional<ance::ResolvingHandle<ance::Function>> ance::FunctionGroup::resolveOverload()
{
    if (functions_.empty()) return {};

    return functions_.front().handle();
}
