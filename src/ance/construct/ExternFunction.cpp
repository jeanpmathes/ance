#include "ExternFunction.h"

#include <utility>

#include "ance/utility/Values.h"
#include "ance/type/VoidType.h"
#include "ance/construct/value/WrappedNativeValue.h"

ance::ExternFunction::ExternFunction(
    std::string                   function_name,
    ance::Type*                   return_type,
    std::vector<ance::Parameter*> parameters,
    unsigned int                  line,
    unsigned int                  column)
    : ance::Function(std::move(function_name), return_type, line, column), parameters_(std::move(parameters))
{
}

void ance::ExternFunction::buildName(CompileContext* context)
{
    std::tie(native_type_, native_function_) =
        createNativeFunction(
            parameters_,
            llvm::GlobalValue::LinkageTypes::ExternalLinkage,
            *context->llvmContext(),
            context->module());

    for (auto pair : zip(parameters_, native_function_->args()))
    {
        std::get<0>(pair)->wrap(&std::get<1>(pair));
    }
}

void ance::ExternFunction::build(CompileContext*)
{
}

ance::Value* ance::ExternFunction::buildCall(const std::vector<ance::Value*>& arguments, CompileContext* context) const
{
    assert(arguments.size() == native_type_->getNumParams());

    for (auto pair : llvm::zip(parameters_, arguments))
    {
        assert(std::get<0>(pair)->type() == std::get<1>(pair)->type() && "Input parameter types must match.");
    }

    llvm::Value* content_value = buildCall(arguments, native_type_, native_function_, context);

    if (getReturnType() == ance::VoidType::get())
    {
        return nullptr;
    }

    llvm::Value* native_value = ance::Values::contentToNative(getReturnType(), content_value, context);
    return new ance::WrappedNativeValue(getReturnType(), native_value);
}
