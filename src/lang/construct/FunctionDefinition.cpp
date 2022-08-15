#include "FunctionDefinition.h"

#include <utility>

#include "compiler/CompileContext.h"
#include "lang/construct/Function.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/utility/Values.h"
#include "validation/ValidationLogger.h"

lang::FunctionDefinition::FunctionDefinition(Function&                                     function,
                                             Scope&                                        containing_scope,
                                             lang::ResolvingHandle<lang::Type>             type,
                                             lang::Location                                return_type_location,
                                             std::vector<std::shared_ptr<lang::Parameter>> parameters,
                                             lang::Location                                location)
    : function_(function)
    , containing_scope_(containing_scope)
    , return_type_(type)
    , return_type_location_(return_type_location)
    , parameters_(std::move(parameters))
    , location_(location)
    , signature_(lang::Signature::fromParameters(name(), parameters_))
{}

const lang::Identifier& lang::FunctionDefinition::name() const
{
    return function_.name();
}

lang::Scope& lang::FunctionDefinition::scope() const
{
    return containing_scope_;
}

lang::Function& lang::FunctionDefinition::function() const
{
    return function_;
}

lang::ResolvingHandle<lang::Type> lang::FunctionDefinition::returnType() const
{
    return return_type_;
}

const lang::Signature& lang::FunctionDefinition::signature() const
{
    return signature_;
}

lang::Location lang::FunctionDefinition::returnTypeLocation() const
{
    return return_type_location_;
}

lang::ResolvingHandle<lang::Type> lang::FunctionDefinition::parameterType(size_t index) const
{
    return parameters_[index]->type();
}

size_t lang::FunctionDefinition::parameterCount() const
{
    return parameters_.size();
}

lang::Location lang::FunctionDefinition::location() const
{
    return location_;
}

void lang::FunctionDefinition::postResolve() {}

bool lang::FunctionDefinition::validateCall(
    const std::vector<std::pair<std::shared_ptr<lang::Value>, lang::Location>>& arguments,
    lang::Location                                                              location,
    ValidationLogger&                                                           validation_logger)
{
    if (arguments.size() != parameters_.size())
    {
        validation_logger.logError("Passed arguments do not match function signature '" + signature_.toString() + "'",
                                   location);
        return false;
    }

    bool valid = true;

    for (const auto& [param, arg] : llvm::zip(parameters_, arguments))
    {
        auto [arg_value, arg_location] = arg;
        valid &= lang::Type::checkMismatch(param->type(), arg_value->type(), arg_location, validation_logger);
    }

    doCallValidation(arguments, location, validation_logger);

    return valid;
}

bool lang::FunctionDefinition::doCallValidation(
    const std::vector<std::pair<std::shared_ptr<lang::Value>, lang::Location>>&,
    lang::Location,
    ValidationLogger&) const
{
    return false;
}

std::shared_ptr<lang::Value> lang::FunctionDefinition::buildCall(
    const std::vector<std::shared_ptr<lang::Value>>& arguments,
    CompileContext&                                  context) const
{
    auto [native_type, native_function] = getNativeRepresentation();

    llvm::Value* content_value = buildCall(arguments, native_type, native_function, context);

    if (returnType()->isVoidType()) { return nullptr; }

    llvm::Value* native_value = lang::Values::contentToNative(returnType(), content_value, context);
    return std::make_shared<lang::WrappedNativeValue>(returnType(), native_value);
}

std::string lang::FunctionDefinition::parameterSource() const
{
    std::string source   = "(";
    bool        is_first = true;

    for (auto& parameter : parameters_)
    {
        if (!is_first) source += ", ";
        source += parameter->name() + ": " + parameter->type()->name();

        is_first = false;
    }

    return source + ")";
}

const std::vector<std::shared_ptr<lang::Parameter>>& lang::FunctionDefinition::parameters() const
{
    return parameters_;
}

std::pair<llvm::FunctionType*, llvm::Function*> lang::FunctionDefinition::createNativeFunction(
    llvm::GlobalValue::LinkageTypes linkage,
    llvm::LLVMContext&              c,
    llvm::Module*                   m)
{
    const std::string& native_name = isMangled() ? signature_.getMangledName() : std::string(function_.name().text());

    std::vector<llvm::Type*> param_types;
    param_types.reserve(parameters_.size());

    for (auto& param : parameters_) { param_types.push_back(param->type()->getContentType(c)); }

    llvm::FunctionType* native_type     = llvm::FunctionType::get(returnType()->getContentType(c), param_types, false);
    llvm::Function*     native_function = llvm::Function::Create(native_type, linkage, native_name, m);

    return {native_type, native_function};
}

llvm::CallInst* lang::FunctionDefinition::buildCall(const std::vector<std::shared_ptr<lang::Value>>& arguments,
                                                    llvm::FunctionType*                              native_type,
                                                    llvm::Function*                                  native_function,
                                                    CompileContext&                                  context) const
{
    std::vector<llvm::Value*> args;
    args.reserve(arguments.size());

    for (const auto& [param, arg] : llvm::zip(parameters_, arguments))
    {
        std::shared_ptr<lang::Value> matched_arg = lang::Type::makeMatching(param->type(), arg, context);

        matched_arg->buildContentValue(context);
        args.push_back(matched_arg->getContentValue());
    }

    auto* content_value = context.ir()->CreateCall(native_type, native_function, args);
    if (!native_type->getReturnType()->isVoidTy()) content_value->setName(name() + ".call");
    return content_value;
}

lang::GlobalScope* lang::FunctionDefinition::getGlobalScope()
{
    return containing_scope_.getGlobalScope();
}