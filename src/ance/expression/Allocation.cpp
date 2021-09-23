#include "Allocation.h"

#include "ance/type/PointerType.h"
#include "ance/type/SizeType.h"
#include "compiler/CompileContext.h"

Allocation::Allocation(Runtime::Allocator allocation,
                       ance::Type*        type,
                       Expression*        count,
                       Application&       app,
                       ance::Location     location)
    : Expression(location)
    , allocation_(allocation)
    , allocated_type_(type)
    , count_(count)
    , return_type_(ance::PointerType::get(app, type))
{
    addChild(*count);
}

void Allocation::setScope(ance::Scope* scope)
{
    if (count_) count_->setContainingScope(scope);
}

ance::Type* Allocation::type()
{
    return return_type_;
}

bool Allocation::validate(ValidationLogger& validation_logger)
{
    if (count_)
    {
        count_->validate(validation_logger);

        return ance::Type::checkMismatch(ance::SizeType::getSize(),
                                         count_->type(),
                                         count_->location(),
                                         validation_logger);
    }

    return true;
}

void Allocation::doBuild(CompileContext* context)
{
    ance::Value* count = count_ ? count_->getValue() : nullptr;
    ance::Value* ptr   = context->runtime()->allocate(allocation_, allocated_type_, count, context);
    setValue(ptr);
}

bool Allocation::accept(ance::ApplicationVisitor& visitor)
{
    return visitor.visitAllocation(*this);
}

Allocation::~Allocation() = default;
