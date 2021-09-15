#include "ExternFunction.h"

#include <utility>

#include "ance/construct/value/WrappedNativeValue.h"
#include "ance/type/VoidType.h"
#include "ance/utility/Values.h"

ance::ExternFunction::ExternFunction(std::string                   function_name,
                                     ance::Type*                   return_type,
                                     std::vector<ance::Parameter*> parameters,
                                     ance::Location                location)
    : ance::Function(std::move(function_name), return_type, std::move(parameters), location)
{}

void ance::ExternFunction::validate(ValidationLogger&) {}

void ance::ExternFunction::createNativeBacking(CompileContext* context)
{
    std::tie(native_type_, native_function_) = createNativeFunction(llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                                                                    *context->llvmContext(),
                                                                    context->module());

    for (auto pair : zip(parameters(), native_function_->args())) { std::get<0>(pair)->wrap(&std::get<1>(pair)); }
}

void ance::ExternFunction::build(CompileContext*) {}

ance::Value* ance::ExternFunction::buildCall(const std::vector<ance::Value*>& arguments, CompileContext* context) const
{
    llvm::Value* content_value = buildCall(arguments, native_type_, native_function_, context);

    if (returnType() == ance::VoidType::get()) { return nullptr; }

    llvm::Value* native_value = ance::Values::contentToNative(returnType(), content_value, context);
    return new ance::WrappedNativeValue(returnType(), native_value);
}

bool ance::ExternFunction::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitExternFunction(*this);
}
