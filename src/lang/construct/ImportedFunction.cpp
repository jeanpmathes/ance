#include "ImportedFunction.h"

#include <set>
#include <utility>

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/scope/Scope.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

lang::ImportedFunction::ImportedFunction(Function& function,
                                         Scope&                               containing_scope,
                                         lang::AccessModifier                 access,
                                         lang::ResolvingHandle<lang::Type>    return_type,
                                         lang::Location                       return_type_location,
                                         std::vector<Shared<lang::Parameter>> parameters,
                                         lang::Location                       location)
    : lang::FunctionDefinition(function,
                               containing_scope,
                               return_type,
                               return_type_location,
                               std::move(parameters),
                               location)
    , access_(access)
{}

void lang::ImportedFunction::setup()
{
    scope().registerUsage(returnType());

    for (auto& parameter : this->parameters()) { scope().registerUsage(parameter->type()); }
}

bool lang::ImportedFunction::isMangled() const
{
    return access_ != lang::AccessModifier::EXTERN_ACCESS;
}

bool lang::ImportedFunction::isImported() const
{
    return true;
}

void lang::ImportedFunction::determineFlow() {}

bool lang::ImportedFunction::validateFlow(ValidationLogger&) const
{
    return true;
}

void lang::ImportedFunction::createNativeBacking(CompileContext& context)
{
    std::tie(native_type_, native_function_) = createNativeFunction(llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                                                                    context.llvmContext(),
                                                                    context.llvmModule());

    lang::Function::setImportExportAttributes(native_function_, access_, true, context);

    auto params = parameters();

    for (unsigned int i = 0; i < params.size(); ++i) { params[i]->wrap(native_function_->getArg(i)); }
}

void lang::ImportedFunction::build(CompileContext&) {}

llvm::DIScope* lang::ImportedFunction::getDebugScope(CompileContext&) const
{
    return native_function_->getSubprogram();
}

std::vector<lang::BasicBlock*> const& lang::ImportedFunction::getBasicBlocks() const
{
    static std::vector<lang::BasicBlock*> const empty;
    return empty;
}

std::pair<llvm::FunctionType*, llvm::Function*> lang::ImportedFunction::getNativeRepresentation() const
{
    return std::make_pair(native_type_, native_function_);
}
