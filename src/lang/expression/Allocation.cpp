#include "Allocation.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/scope/Scope.h"
#include "lang/type/BufferType.h"
#include "lang/type/PointerType.h"
#include "lang/type/SizeType.h"
#include "validation/Utilities.h"
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
    , return_type_(count_ ? lang::BufferType::get(type) : lang::PointerType::get(type))
{
    if (count_) addSubexpression(*count_);
}

Runtime::Allocator Allocation::allocator() const
{
    return allocation_;
}

lang::ResolvingHandle<lang::Type> Allocation::allocatedType() const
{
    return allocated_type_;
}

Expression* Allocation::count() const
{
    return count_.get();
}

void Allocation::walkDefinitions()
{
    Expression::walkDefinitions();

    scope()->addType(allocated_type_);
}

std::optional<lang::ResolvingHandle<lang::Type>> Allocation::tryGetType() const
{
    return return_type_;
}

bool Allocation::validate(ValidationLogger& validation_logger) const
{
    if (lang::validation::isTypeUndefined(allocated_type_, allocated_type_location_, validation_logger)) return false;

    bool is_valid = allocated_type_->validate(validation_logger, location())
                 && return_type_->validate(validation_logger, location());

    if (count_)
    {
        count_->validate(validation_logger);

        is_valid &=
            lang::Type::checkMismatch(lang::SizeType::getSize(), count_->type(), count_->location(), validation_logger);
    }

    return is_valid;
}

Expression::Expansion Allocation::expandWith(Expressions subexpressions) const
{
    if (count_)
    {
        return {Statements(),
                std::make_unique<Allocation>(allocation_,
                                             allocated_type_->toUndefined(),
                                             std::move(subexpressions[0]),
                                             location(),
                                             allocated_type_location_),
                Statements()};
    }
    else
    {
        return {Statements(),
                std::make_unique<Allocation>(allocation_,
                                             allocated_type_->toUndefined(),
                                             nullptr,
                                             location(),
                                             allocated_type_location_),
                Statements()};
    }
}

void Allocation::doBuild(CompileContext& context)
{
    std::shared_ptr<lang::Value> count = {};

    if (count_) { count = lang::Type::makeMatching(lang::SizeType::getSize(), count_->getValue(), context); }

    std::shared_ptr<lang::Value> ptr = context.runtime()->allocate(allocation_, allocated_type_, count, context);
    setValue(ptr);
}

Allocation::~Allocation() = default;
