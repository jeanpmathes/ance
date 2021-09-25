#include "FunctionCall.h"

#include <utility>

#include "ance/ApplicationVisitor.h"
#include "ance/construct/Function.h"
#include "ance/construct/value/Value.h"
#include "ance/scope/GlobalScope.h"
#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

namespace ance
{
    class Function;
}

FunctionCall::FunctionCall(std::string identifier, std::vector<Expression*> arguments, ance::Location location)
    : Expression(location)
    , identifier_(std::move(identifier))
    , arguments_(std::move(arguments))
{
    for (auto* arg : arguments_) { addChild(*arg); }
}

void FunctionCall::setScope(ance::Scope* scope)
{
    scope_ = scope;

    for (auto* arg : arguments_) { arg->setContainingScope(scope); }
}

ance::Type* FunctionCall::type()
{
    return scope_->getGlobalScope()->getFunction(identifier_)->returnType();
}

bool FunctionCall::validate(ValidationLogger& validation_logger)
{
    std::vector<std::pair<ance::Value*, ance::Location>> arguments;

    bool valid = true;

    for (auto* arg : arguments_)
    {
        valid &= arg->validate(validation_logger);
        arguments.emplace_back(arg->getValue(), arg->location());
    }

    if (!valid) return false;

    ance::Function* fn = scope_->getGlobalScope()->getFunction(identifier_);

    if (!fn)
    {
        validation_logger.logError("Name '" + identifier_ + "' not defined in the current context", location());
        return false;
    }

    return fn->validateCall(arguments, location(), validation_logger);
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

bool FunctionCall::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitFunctionCall(*this);
}

FunctionCall::~FunctionCall() = default;