#include "Function.h"

#include <utility>

#include "ance/ApplicationVisitor.h"
#include "ance/construct/LocalVariable.h"
#include "ance/scope/LocalScope.h"
#include "ance/type/VoidType.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

ance::Function::Function(std::string                                   function_name,
                         ance::Type*                                   return_type,
                         std::vector<std::shared_ptr<ance::Parameter>> parameters,
                         ance::Location                                location)
    : name_(std::move(function_name))
    , return_type_(return_type)
    , parameters_(std::move(parameters))
    , location_(location)
{}

std::string ance::Function::name() const
{
    return name_;
}

ance::Type* ance::Function::returnType() const
{
    return return_type_;
}

ance::Type* ance::Function::parameterType(size_t index) const
{
    return parameters_[index]->type();
}

size_t ance::Function::parameterCount() const
{
    return parameters_.size();
}

ance::Location ance::Function::location() const
{
    return location_;
}

bool ance::Function::validateCall(const std::vector<std::pair<std::shared_ptr<ance::Value>, ance::Location>>& arguments,
                                  ance::Location                                                              location,
                                  ValidationLogger& validation_logger)
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

std::vector<std::shared_ptr<ance::Parameter>>& ance::Function::parameters()
{
    return parameters_;
}

std::pair<llvm::FunctionType*, llvm::Function*> ance::Function::createNativeFunction(
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

llvm::CallInst* ance::Function::buildCall(const std::vector<std::shared_ptr<ance::Value>>& arguments,
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
