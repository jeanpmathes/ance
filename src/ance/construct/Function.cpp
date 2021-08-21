#include "Function.h"

#include <utility>

ance::Function::Function(std::string function_name, ance::Type* return_type, ance::Location location)
    : name_(std::move(function_name))
    , return_type_(return_type)
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

ance::Location ance::Function::location() const
{
    return location_;
}

std::pair<llvm::FunctionType*, llvm::Function*> ance::Function::createNativeFunction(
    const std::vector<ance::Parameter*>& parameters,
    llvm::GlobalValue::LinkageTypes      linkage,
    llvm::LLVMContext&                   c,
    llvm::Module*                        m)
{
    std::vector<llvm::Type*> param_types;
    param_types.reserve(parameters.size());

    for (auto* param : parameters) { param_types.push_back(param->type()->getContentType(c)); }

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
