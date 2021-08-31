#include "FunctionCall.h"

#include <utility>

#include "ance/construct/Function.h"
#include "ance/construct/value/Value.h"
#include "ance/scope/GlobalScope.h"
#include "compiler/CompileContext.h"

namespace ance
{
    class Function;
}

FunctionCall::FunctionCall(std::string identifier, std::vector<Expression*> arguments, ance::Location location)
    : DelayableExpression(location)
    , identifier_(std::move(identifier))
    , arguments_(std::move(arguments))
{}

void FunctionCall::setScope(ance::Scope* scope)
{
    scope_ = scope;

    for (auto* arg : arguments_) { arg->setContainingScope(scope); }
}

ance::Type* FunctionCall::type()
{
    return scope_->getGlobalScope()->getFunction(identifier_)->returnType();
}

void FunctionCall::validate(ValidationLogger& validation_logger)
{
    std::vector<ance::Value*> arg_values;
    for (auto* arg : arguments_)
    {
        arg->validate(validation_logger);
        arg_values.push_back(arg->getValue());
    }

    ance::Function* fn = scope_->getGlobalScope()->getFunction(identifier_);

    fn->validateCall(arg_values, validation_logger);
}

void FunctionCall::doBuild(CompileContext* context)
{
    ance::Function* fn = context->application()->globalScope()->getFunction(identifier_);

    std::vector<ance::Value*> arg_values;

    for (auto* arg : arguments_) { arg_values.push_back(arg->getValue()); }

    ance::Value* return_value = fn->buildCall(arg_values, context);

    if (return_value != nullptr)// Not every function returns a value.
    {
        setValue(return_value);
    }
}

FunctionCall::~FunctionCall() = default;