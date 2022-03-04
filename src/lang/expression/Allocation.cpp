#include "Allocation.h"

#include "lang/scope/Scope.h"
#include "lang/type/PointerType.h"
#include "lang/type/SizeType.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

Allocation::Allocation(Runtime::Allocator                allocation,
                       lang::ResolvingHandle<lang::Type> type,
                       std::unique_ptr<Expression>       count,
                       lang::Location                    location,
                       lang::Location                    allocated_type_location)
    : Expression(location)
    , allocation_(allocation)
    , allocated_type_(type)
    , allocated_type_location_(allocated_type_location)
    , count_(std::move(count))
    , return_type_(lang::PointerType::get(type))
{
    if (count_) addChild(*count_);
}

void Allocation::setScope(lang::Scope* scope)
{
    scope->addType(allocated_type_);

    if (count_) count_->setContainingScope(scope);
}

lang::ResolvingHandle<lang::Type> Allocation::type()
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
            lang::Type::checkMismatch(lang::SizeType::getSize(), count_->type(), count_->location(), validation_logger);
    }

    return is_valid;
}

void Allocation::doBuild(CompileContext* context)
{
    std::shared_ptr<lang::Value> count = {};

    if (count_) { count = lang::Type::makeMatching(lang::SizeType::getSize(), count_->getValue(), context); }

    std::shared_ptr<lang::Value> ptr = context->runtime()->allocate(allocation_, allocated_type_, count, context);
    setValue(ptr);
}

Allocation::~Allocation() = default;