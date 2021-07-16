#include "Allocation.h"

#include "CompileContext.h"
#include "PointerType.h"

Allocation::Allocation(Runtime::Allocator allocation, ance::Type* type, Expression* count, Application& app)
    : allocation_(allocation),
      allocated_type_(type),
      count_(count),
      return_type_(ance::PointerType::get(app, type))
{
}

void Allocation::setScope(ance::Scope* scope)
{
    if (count_) count_->setScope(scope);
}

ance::Type* Allocation::type()
{
    return return_type_;
}

void Allocation::buildValue(CompileContext* context)
{
    ance::Value* count = count_ ? count_->getValue() : nullptr;
    ance::Value* ptr   = context->runtime()->allocate(allocation_, allocated_type_, count, context);
    setValue(ptr);
}

Allocation::~Allocation() = default;
