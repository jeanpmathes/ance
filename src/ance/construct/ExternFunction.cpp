#include "ExternFunction.h"

#include <set>
#include <utility>

#include "ance/construct/value/WrappedNativeValue.h"
#include "ance/scope/Scope.h"
#include "ance/type/ReferenceType.h"
#include "ance/type/VoidType.h"
#include "ance/utility/Values.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

ance::ExternFunction::ExternFunction(ance::Function*                               function,
                                     ance::Scope*                                  containing_scope,
                                     ance::Type*                                   return_type,
                                     std::vector<std::shared_ptr<ance::Parameter>> parameters,
                                     ance::Location                                location)
    : ance::FunctionDefinition(function, containing_scope, return_type, std::move(parameters), location)
{}

void ance::ExternFunction::pushStatement(Statement*) {}
void ance::ExternFunction::addReturn(const std::shared_ptr<ance::Value>&) {}

void ance::ExternFunction::validate(ValidationLogger& validation_logger)
{
    returnType()->validate(validation_logger, location());

    std::set<std::string> names;

    for (const auto& parameter : parameters())
    {
        auto [it, inserted] = names.insert(parameter->name());

        if (!inserted)
        {
            validation_logger.logError("Name '" + parameter->name() + "' already defined in the current context",
                                       parameter->location());
        }

        parameter->type()->validate(validation_logger, parameter->location());

        if (parameter->type() == ance::VoidType::get())
        {
            validation_logger.logError("Parameter cannot have 'void' type", parameter->location());
        }
    }
}

void ance::ExternFunction::createNativeBacking(CompileContext* context)
{
    std::tie(native_type_, native_function_) = createNativeFunction(llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                                                                    *context->llvmContext(),
                                                                    context->module());

    for (auto pair : zip(parameters(), native_function_->args())) { std::get<0>(pair)->wrap(&std::get<1>(pair)); }
}

void ance::ExternFunction::build(CompileContext*) {}

std::shared_ptr<ance::Value> ance::ExternFunction::buildCall(const std::vector<std::shared_ptr<ance::Value>>& arguments,
                                                             CompileContext* context) const
{
    llvm::Value* content_value = buildCall(arguments, native_type_, native_function_, context);

    if (returnType() == ance::VoidType::get()) { return nullptr; }

    llvm::Value* native_value = ance::Values::contentToNative(returnType(), content_value, context);
    return std::make_shared<ance::WrappedNativeValue>(returnType(), native_value);
}

llvm::DIScope* ance::ExternFunction::getDebugScope(CompileContext*)
{
    return native_function_->getSubprogram();
}

ance::Variable* ance::ExternFunction::getVariable(std::string identifier)
{
    return scope()->getVariable(identifier);
}

bool ance::ExternFunction::isTypeRegistered(const std::string& type_name)
{
    return scope()->isTypeRegistered(type_name);
}

ance::Type* ance::ExternFunction::getType(const std::string& type_name)
{
    return scope()->getType(type_name);
}

void ance::ExternFunction::registerType(ance::Type* type)
{
    scope()->registerType(type);
}

ance::LocalScope* ance::ExternFunction::getInsideScope()
{
    return nullptr;
}
