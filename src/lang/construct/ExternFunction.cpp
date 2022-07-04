#include "ExternFunction.h"

#include <set>
#include <utility>

#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/scope/Scope.h"
#include "lang/type/VoidType.h"
#include "lang/utility/Values.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"
#include "lang/statement/Statement.h"

lang::ExternFunction::ExternFunction(Function&                                     function,
                                     Scope&                                        containing_scope,
                                     lang::ResolvingHandle<lang::Type>             return_type,
                                     lang::Location                                return_type_location,
                                     std::vector<std::shared_ptr<lang::Parameter>> parameters,
                                     lang::Location                                location)
    : lang::FunctionDefinition(function,
                               containing_scope,
                               return_type,
                               return_type_location,
                               std::move(parameters),
                               location)
{
    containing_scope.addType(return_type);

    for (const auto& parameter : this->parameters()) { containing_scope.addType(parameter->type()); }
}

bool lang::ExternFunction::isMangled() const
{
    return false;
}

void lang::ExternFunction::validate(ValidationLogger& validation_logger) const
{
    if (!returnType()->isDefined())
    {
        validation_logger.logError("Return type " + returnType()->getAnnotatedName() + " not defined.",
                                   returnTypeLocation());
        return;
    }

    returnType()->validate(validation_logger, returnTypeLocation());

    std::set<lang::Identifier> names;

    for (const auto& parameter : parameters())
    {
        auto [it, inserted] = names.insert(parameter->name());

        if (!inserted)
        {
            validation_logger.logError("Name '" + parameter->name() + "' already defined in the current context",
                                       parameter->name().location());
        }

        if (!parameter->type()->isDefined())
        {
            validation_logger.logError("Parameter type " + parameter->type()->getAnnotatedName() + " not defined.",
                                       parameter->typeLocation());

            return;
        }

        parameter->type()->validate(validation_logger, parameter->typeLocation());

        if (parameter->type()->isVoidType())
        {
            validation_logger.logError("Parameter cannot have 'void' type", parameter->location());
        }
    }
}

void lang::ExternFunction::expand() {}

void lang::ExternFunction::determineFlow() {}

bool lang::ExternFunction::validateFlow(ValidationLogger&) const
{
    return true;
}

void lang::ExternFunction::createNativeBacking(CompileContext* context)
{
    std::tie(native_type_, native_function_) = createNativeFunction(llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                                                                    *context->llvmContext(),
                                                                    context->module());

    for (auto pair : zip(parameters(), native_function_->args())) { std::get<0>(pair)->wrap(&std::get<1>(pair)); }
}

void lang::ExternFunction::build(CompileContext*) {}

std::shared_ptr<lang::Value> lang::ExternFunction::buildCall(const std::vector<std::shared_ptr<lang::Value>>& arguments,
                                                             CompileContext* context) const
{
    llvm::Value* content_value = buildCall(arguments, native_type_, native_function_, context);

    if (returnType()->isVoidType()) { return nullptr; }

    llvm::Value* native_value = lang::Values::contentToNative(returnType(), content_value, context);
    return std::make_shared<lang::WrappedNativeValue>(returnType(), native_value);
}

llvm::DIScope* lang::ExternFunction::getDebugScope(CompileContext*)
{
    return native_function_->getSubprogram();
}

lang::LocalScope* lang::ExternFunction::getInsideScope()
{
    return nullptr;
}

const std::vector<lang::BasicBlock*>& lang::ExternFunction::getBasicBlocks() const
{
    static std::vector<lang::BasicBlock*> empty;
    return empty;
}
