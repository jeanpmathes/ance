#include "PredefinedFunction.h"

#include "compiler/CompileContext.h"

lang::PredefinedFunction::PredefinedFunction(lang::Function&                               function,
                                             lang::Scope&                                  containing_scope,
                                             lang::ResolvingHandle<lang::Type>             return_type,
                                             std::vector<std::shared_ptr<lang::Parameter>> parameters,
                                             lang::Location                                location)
    : lang::FunctionDefinition(function,
                               containing_scope,
                               return_type,
                               lang::Location(0, 0, 0, 0),
                               std::move(parameters),
                               location)
{}

bool lang::PredefinedFunction::isMangled() const
{
    return true;
}

void lang::PredefinedFunction::validate(ValidationLogger&) const {}

void lang::PredefinedFunction::expand() {}
void lang::PredefinedFunction::determineFlow() {}
bool lang::PredefinedFunction::validateFlow(ValidationLogger&) const
{
    return true;
}

void lang::PredefinedFunction::createNativeBacking(CompileContext* context)
{
    std::tie(native_type_, native_function_) = createNativeFunction(llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                                                                    *context->llvmContext(),
                                                                    context->module());

    for (auto pair : zip(parameters(), native_function_->args())) { std::get<0>(pair)->wrap(&std::get<1>(pair)); }
}

void lang::PredefinedFunction::build(CompileContext*) {}

llvm::DIScope* lang::PredefinedFunction::getDebugScope(CompileContext*)
{
    return native_function_->getSubprogram();
}

lang::LocalScope* lang::PredefinedFunction::getInsideScope()
{
    return nullptr;
}

const std::vector<lang::BasicBlock*>& lang::PredefinedFunction::getBasicBlocks() const
{
    static std::vector<lang::BasicBlock*> empty;
    return empty;
}

std::pair<llvm::FunctionType*, llvm::Function*> lang::PredefinedFunction::getNativeRepresentation() const
{
    return std::make_pair(native_type_, native_function_);
}

void lang::PredefinedFunction::setCallValidator(
    std::function<bool(const std::vector<std::pair<std::shared_ptr<lang::Value>, lang::Location>>&,
                       lang::Location,
                       ValidationLogger&)> validator)
{
    call_validator_ = std::move(validator);
}

bool lang::PredefinedFunction::doCallValidation(
    const std::vector<std::pair<std::shared_ptr<lang::Value>, lang::Location>>& arguments,
    lang::Location                                                              location,
    ValidationLogger&                                                           validation_logger) const
{
    if (call_validator_) { return call_validator_(arguments, location, validation_logger); }
    return true;
}
