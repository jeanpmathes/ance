#include "Allocation.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/scope/Scope.h"
#include "lang/type/SizeType.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

Allocation::Allocation(Runtime::Allocator                allocation,
                       lang::ResolvingHandle<lang::Type> type,
                       Optional<Owned<Expression>>       count,
                       lang::Location                    location,
                       lang::Location                    allocated_type_location,
                       lang::Context&                    context)
    : Expression(location)
    , allocation_(allocation)
    , allocated_type_(type)
    , allocated_type_location_(allocated_type_location)
    , count_(std::move(count))
    , return_type_(count_.hasValue() ? context.getBufferType(type) : context.getPointerType(type))
{
    if (count_.hasValue()) addSubexpression(*count_.value());
}

Runtime::Allocator Allocation::allocator() const
{
    return allocation_;
}

lang::Type const& Allocation::allocatedType() const
{
    return allocated_type_;
}

Expression const* Allocation::count() const
{
    return getPtr(count_);
}

void Allocation::walkDefinitions()
{
    Expression::walkDefinitions();

    scope()->registerUsageIfUndefined(allocated_type_);
}

void Allocation::defineType(lang::ResolvingHandle<lang::Type> type)
{
    type.reroute(return_type_);
}

bool Allocation::validate(ValidationLogger& validation_logger) const
{
    if (lang::validation::isTypeUndefined(allocated_type_, scope(), allocated_type_location_, validation_logger))
        return false;

    bool is_valid = allocated_type_->validate(validation_logger, location())
                 && return_type_->validate(validation_logger, location());

    if (count_.hasValue())
    {
        count_.value()->validate(validation_logger);

        is_valid &= lang::Type::checkMismatch(scope()->context().getSizeType(),
                                              count_.value()->type(),
                                              count_.value()->location(),
                                              validation_logger);
    }

    is_valid &= scope()->context().validateRuntimeDependency(location(), validation_logger);

    return is_valid;
}

Expression::Expansion Allocation::expandWith(Expressions subexpressions, lang::Context& new_context) const
{
    if (count_.hasValue())
    {
        return {Statements(),
                makeOwned<Allocation>(allocation_,
                                      allocated_type_->getUndefinedTypeClone(new_context),
                                      std::move(subexpressions[0]),
                                      location(),
                                      allocated_type_location_,
                                      new_context),
                Statements()};
    }
    else
    {
        return {Statements(),
                makeOwned<Allocation>(allocation_,
                                      allocated_type_->getUndefinedTypeClone(new_context),
                                      std::nullopt,
                                      location(),
                                      allocated_type_location_,
                                      new_context),
                Statements()};
    }
}

void Allocation::doBuild(CompileContext& context)
{
    Optional<Shared<lang::Value>> count = {};

    if (count_.hasValue())
    {
        count = lang::Type::makeMatching(context.types().getSizeType(), count_.value()->getValue(), context);
    }

    Shared<lang::Value> ptr = context.runtime().allocate(allocation_, allocated_type_, count, context);
    setValue(ptr);
}

Allocation::~Allocation() = default;
