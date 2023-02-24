#include "ExternFunction.h"

#include <set>
#include <utility>

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/scope/Scope.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

lang::ExternFunction::ExternFunction(Function&                            function,
                                     Scope&                               containing_scope,
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
{
    containing_scope.addType(return_type);

    for (auto& parameter : this->parameters()) { containing_scope.addType(parameter->type()); }
}

bool lang::ExternFunction::isMangled() const
{
    return false;
}

bool lang::ExternFunction::isImported() const
{
    return true;
}

void lang::ExternFunction::determineFlow() {}

bool lang::ExternFunction::validateFlow(ValidationLogger&) const
{
    return true;
}

void lang::ExternFunction::createNativeBacking(CompileContext& context)
{
    std::tie(native_type_, native_function_) = createNativeFunction(llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                                                                    context.llvmContext(),
                                                                    context.llvmModule());

    auto params = parameters();

    for (unsigned int i = 0; i < params.size(); ++i) { params[i]->wrap(native_function_->getArg(i)); }
}

void lang::ExternFunction::build(CompileContext&) {}

llvm::DIScope* lang::ExternFunction::getDebugScope(CompileContext&) const
{
    return native_function_->getSubprogram();
}

lang::LocalScope* lang::ExternFunction::getInsideScope()
{
    return nullptr;
}

std::vector<lang::BasicBlock*> const& lang::ExternFunction::getBasicBlocks() const
{
    static std::vector<lang::BasicBlock*> const empty;
    return empty;
}

std::pair<llvm::FunctionType*, llvm::Function*> lang::ExternFunction::getNativeRepresentation() const
{
    return std::make_pair(native_type_, native_function_);
}
