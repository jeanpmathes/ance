#include "FunctionDefinition.h"

#include <utility>

#include "ance/construct/Function.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

ance::FunctionDefinition::FunctionDefinition(ance::Function*                               function,
                                             ance::Scope*                                  containing_scope,
                                             ance::ResolvingHandle<ance::Type>             type,
                                             ance::Location                                return_type_location,
                                             std::vector<std::shared_ptr<ance::Parameter>> parameters,
                                             ance::Location                                location)
    : function_(function)
    , containing_scope_(containing_scope)
    , return_type_(type)
    , return_type_location_(return_type_location)
    , parameters_(std::move(parameters))
    , location_(location)
{}

const std::string& ance::FunctionDefinition::name() const
{
    return function_->name();
}

ance::Scope* ance::FunctionDefinition::scope() const
{
    return containing_scope_;
}

ance::Function* ance::FunctionDefinition::function() const
{
    return function_;
}

ance::ResolvingHandle<ance::Type> ance::FunctionDefinition::returnType() const
{
    return return_type_;
}

ance::Location ance::FunctionDefinition::returnTypeLocation() const
{
    return return_type_location_;
}

ance::ResolvingHandle<ance::Type> ance::FunctionDefinition::parameterType(size_t index) const
{
    return parameters_[index]->type();
}

size_t ance::FunctionDefinition::parameterCount() const
{
    return parameters_.size();
}

ance::Location ance::FunctionDefinition::location() const
{
    return location_;
}

bool ance::FunctionDefinition::validateCall(
    const std::vector<std::pair<std::shared_ptr<ance::Value>, ance::Location>>& arguments,
    ance::Location                                                              location,
    ValidationLogger&                                                           validation_logger)
{
    if (arguments.size() != parameters_.size())
    {
        validation_logger.logError("No overload of '" + name() + "' takes " + std::to_string(arguments.size())
                                       + " arguments",
                                   location);
        return false;
    }

    bool valid = true;

    for (const auto& [param, arg] : llvm::zip(parameters_, arguments))
    {
        auto [arg_value, arg_location] = arg;
        valid &= ance::Type::checkMismatch(param->type(), arg_value->type(), arg_location, validation_logger);
    }

    return valid;
}

std::vector<std::shared_ptr<ance::Parameter>>& ance::FunctionDefinition::parameters()
{
    return parameters_;
}

std::pair<llvm::FunctionType*, llvm::Function*> ance::FunctionDefinition::createNativeFunction(
    llvm::GlobalValue::LinkageTypes linkage,
    llvm::LLVMContext&              c,
    llvm::Module*                   m)
{
    std::vector<llvm::Type*> param_types;
    param_types.reserve(parameters_.size());

    for (auto& param : parameters_) { param_types.push_back(param->type()->getContentType(c)); }

    llvm::FunctionType* native_type     = llvm::FunctionType::get(returnType()->getContentType(c), param_types, false);
    llvm::Function*     native_function = llvm::Function::Create(native_type, linkage, name(), m);

    return {native_type, native_function};
}

llvm::CallInst* ance::FunctionDefinition::buildCall(const std::vector<std::shared_ptr<ance::Value>>& arguments,
                                                    llvm::FunctionType*                              native_type,
                                                    llvm::Function*                                  native_function,
                                                    CompileContext*                                  context) const
{
    std::vector<llvm::Value*> args;
    args.reserve(arguments.size());

    for (const auto& [param, arg] : llvm::zip(parameters_, arguments))
    {
        std::shared_ptr<ance::Value> matched_arg = ance::Type::makeMatching(param->type(), arg, context);

        matched_arg->buildContentValue(context);
        args.push_back(matched_arg->getContentValue());
    }

    auto* content_value = context->ir()->CreateCall(native_type, native_function, args);
    if (!native_type->getReturnType()->isVoidTy()) content_value->setName(native_function->getName() + ".ret");
    return content_value;
}

ance::GlobalScope* ance::FunctionDefinition::getGlobalScope()
{
    return containing_scope_->getGlobalScope();
}
