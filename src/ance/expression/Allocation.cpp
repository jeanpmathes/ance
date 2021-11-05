#include "Allocation.h"

#include "ance/type/PointerType.h"
#include "ance/type/SizeType.h"
#include "ance/type/Type.h"
#include "compiler/CompileContext.h"

Allocation::Allocation(Runtime::Allocator          allocation,
                       ance::Type*                 type,
                       std::unique_ptr<Expression> count,
                       ance::Location              location)
    : Expression(location)
    , allocation_(allocation)
    , allocated_type_(type)
    , count_(std::move(count))
    , return_type_(ance::PointerType::get(type))
{}

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
    std::shared_ptr<ance::Value> count = {};

    if (count_) { count = ance::Type::makeMatching(ance::SizeType::getSize(), count_->getValue(), context); }

    std::shared_ptr<ance::Value> ptr = context->runtime()->allocate(allocation_, allocated_type_, count, context);
    setValue(ptr);
}

Allocation::~Allocation() = default;
