#include "Function.h"

#include <utility>

ance::Function::Function(std::string                   function_name,
                         ance::Type*                   return_type,
                         std::vector<ance::Parameter*> parameters,
                         ance::Location                location)
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

void ance::Function::validateCall(const std::vector<ance::Value*>& arguments, ValidationLogger&)
{
    assert(arguments.size() == parameters_.size());

    for (auto pair : llvm::zip(parameters_, arguments))
    {
        assert(std::get<0>(pair)->type() == std::get<1>(pair)->type() && "Input parameter types must match.");
    }
}

std::vector<ance::Parameter*>& ance::Function::parameters()
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

    for (auto* param : parameters_) { param_types.push_back(param->type()->getContentType(c)); }

    llvm::FunctionType* native_type     = llvm::FunctionType::get(returnType()->getContentType(c), param_types, false);
    llvm::Function*     native_function = llvm::Function::Create(native_type, linkage, name(), m);

    return {native_type, native_function};
}

llvm::CallInst* ance::Function::buildCall(const std::vector<ance::Value*>& arguments,
                                          llvm::FunctionType*              native_type,
                                          llvm::Function*                  native_function,
                                          CompileContext*                  context) const
{
    std::vector<llvm::Value*> args;
    args.reserve(arguments.size());

    for (auto* arg : arguments)
    {
        arg->buildContentValue(context);
        args.push_back(arg->getContentValue());
    }

    auto* content_value = context->ir()->CreateCall(native_type, native_function, args);
    if (!native_type->getReturnType()->isVoidTy()) content_value->setName(native_function->getName() + ".ret");
    return content_value;
}

