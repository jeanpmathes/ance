#include "PredefinedFunction.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"

lang::PredefinedFunction::PredefinedFunction(lang::Function&                      function,
                                             lang::Scope&                         containing_scope,
                                             lang::AccessModifier                 access_modifier,
                                             bool                                 is_imported,
                                             lang::ResolvingHandle<lang::Type>    return_type,
                                             std::vector<Shared<lang::Parameter>> parameters,
                                             lang::Location                       location)
    : lang::FunctionDefinition(function,
                               containing_scope,
                               return_type,
                               lang::Location::global(),
                               std::move(parameters),
                               location)
    , access_modifier_(access_modifier)
    , is_imported_(is_imported)
{}

bool lang::PredefinedFunction::isMangled() const
{
    return true;
}

bool lang::PredefinedFunction::isImported() const
{
    return is_imported_;
}

void lang::PredefinedFunction::determineFlow() {}
bool lang::PredefinedFunction::validateFlow(ValidationLogger&) const
{
    return true;
}

void lang::PredefinedFunction::createNativeBacking(CompileContext& context)
{
    llvm::GlobalValue::LinkageTypes const linkage = access_modifier_.linkage();
    if (is_imported_) { assert(linkage == llvm::GlobalValue::LinkageTypes::ExternalLinkage); }

    std::tie(native_type_, native_function_) =
        createNativeFunction(linkage, context.llvmContext(), context.llvmModule());

    auto params = parameters();

    for (unsigned int i = 0; i < params.size(); ++i) { params[i]->wrap(native_function_->getArg(i)); }
}

void lang::PredefinedFunction::build(CompileContext&) {}

llvm::DIScope* lang::PredefinedFunction::getDebugScope(CompileContext&) const
{
    return native_function_->getSubprogram();
}

lang::LocalScope* lang::PredefinedFunction::getInsideScope()
{
    return nullptr;
}

std::vector<lang::BasicBlock*> const& lang::PredefinedFunction::getBasicBlocks() const
{
    static std::vector<lang::BasicBlock*> const empty;
    return empty;
}

std::pair<llvm::FunctionType*, llvm::Function*> lang::PredefinedFunction::getNativeRepresentation() const
{
    return std::make_pair(native_type_, native_function_);
}

void lang::PredefinedFunction::setCallValidator(
    std::function<bool(std::vector<std::pair<std::reference_wrapper<lang::Value const>, lang::Location>> const&,
                       lang::Location,
                       ValidationLogger&)> validator)
{
    call_validator_ = std::move(validator);
}

bool lang::PredefinedFunction::doCallValidation(
    std::vector<std::pair<std::reference_wrapper<lang::Value const>, lang::Location>> const& arguments,
    lang::Location                                                                           location,
    ValidationLogger&                                                                        validation_logger) const
{
    if (call_validator_) { return call_validator_(arguments, location, validation_logger); }
    return true;
}
