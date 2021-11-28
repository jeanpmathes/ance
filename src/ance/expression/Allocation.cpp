#include "Allocation.h"

#include "ance/scope/Scope.h"
#include "ance/type/PointerType.h"
#include "ance/type/SizeType.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

Allocation::Allocation(Runtime::Allocator                allocation,
                       ance::ResolvingHandle<ance::Type> type,
                       std::unique_ptr<Expression>       count,
                       ance::Location                    location,
                       ance::Location                    allocated_type_location)
    : Expression(location)
    , allocation_(allocation)
    , allocated_type_(type)
    , allocated_type_location_(allocated_type_location)
    , count_(std::move(count))
    , return_type_(ance::PointerType::get(type))
{}

void Allocation::setScope(ance::Scope* scope)
{
    scope->addType(allocated_type_);

    if (count_) count_->setContainingScope(scope);
}

ance::ResolvingHandle<ance::Type> Allocation::type()
{
    return return_type_;
}

bool Allocation::validate(ValidationLogger& validation_logger)
{
    if (!allocated_type_->isDefined())
    {
        validation_logger.logError("Cannot allocate undefined type", allocated_type_location_);
        return false;
    }

    bool is_valid = return_type_->validate(validation_logger, location());

    if (count_)
    {
        count_->validate(validation_logger);

        is_valid &=
            ance::Type::checkMismatch(ance::SizeType::getSize(), count_->type(), count_->location(), validation_logger);
    }

    return is_valid;
}

void Allocation::doBuild(CompileContext* context)
{
    std::shared_ptr<ance::Value> count = {};

    if (count_) { count = ance::Type::makeMatching(ance::SizeType::getSize(), count_->getValue(), context); }

    std::shared_ptr<ance::Value> ptr = context->runtime()->allocate(allocation_, allocated_type_, count, context);
    setValue(ptr);
}

Allocation::~Allocation() = default;
