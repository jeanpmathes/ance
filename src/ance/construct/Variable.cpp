#include "Variable.h"

#include <utility>

#include "ance/construct/value/Value.h"
#include "ance/type/Type.h"

ance::Variable::Variable(ance::Scope* containing_scope, std::string identifier, ance::Type* type, bool is_final)
    : identifier_(std::move(identifier))
    , is_defined_(true)
    , scope_(containing_scope)
    , type_(type)
    , is_final_(is_final)
{}

ance::Variable::Variable(std::string identifier)
    : identifier_(std::move(identifier))
    , is_defined_(false)
    , scope_(nullptr)
    , type_(nullptr)
    , is_final_(true)
{}

void ance::Variable::define(ance::Scope* containing_scope, ance::Type* type, bool is_final)
{
    assert(!is_defined_);

    scope_    = containing_scope;
    type_     = type;
    is_final_ = is_final;

    is_defined_ = true;
}

bool ance::Variable::isDefined() const
{
    return is_defined_;
}

std::string ance::Variable::identifier() const
{
    return identifier_;
}

ance::Scope* ance::Variable::scope() const
{
    assert(is_defined_);
    return scope_;
}

ance::Type* ance::Variable::type() const
{
    assert(is_defined_);
    return type_;
}

bool ance::Variable::isFinal() const
{
    assert(is_defined_);
    return is_final_;
}

void ance::Variable::validateSetValue(ance::Value*      value,
                                      ValidationLogger& validation_logger,
                                      ance::Location    location) const
{
    if (!isDefined())
    {
        validation_logger.logError("Name '" + identifier() + "' is not defined in the current context", location);
        return;// The following variable methods require that the variable is defined.
    }

    if (isFinal())
    {
        validation_logger.logError("Cannot assign to final variable '" + identifier() + "'", location);
        return;// Type mismatch is not relevant if assignment is not allowed no matter what.
    }

    ance::Type::checkMismatch(type(), value->type(), location, validation_logger);
}