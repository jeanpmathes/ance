#include "Variable.h"

#include <utility>

ance::Variable::Variable(ance::Scope* containing_scope, std::string identifier, ance::Type* type, bool is_final)
    : identifier_(std::move(identifier)),
      is_defined_(true),
      scope_(containing_scope),
      type_(type),
      is_final_(is_final)
{
}

ance::Variable::Variable(std::string identifier)
    : identifier_(std::move(identifier)), is_defined_(false), scope_(nullptr), type_(nullptr), is_final_(true)
{
}

void ance::Variable::define(ance::Scope* containing_scope, ance::Type* type, bool is_final)
{
    assert(!is_defined_);

    scope_    = containing_scope;
    type_     = type;
    is_final_ = is_final;

    is_defined_ = true;
}

bool ance::Variable::isDefined()
{
    return is_defined_;
}

std::string ance::Variable::identifier() const
{
    assert(is_defined_);
    return identifier_;
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