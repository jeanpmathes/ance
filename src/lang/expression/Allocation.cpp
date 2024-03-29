#include "Allocation.h"

#include "lang/ApplicationVisitor.h"
#include "lang/scope/Scope.h"
#include "lang/type/SizeType.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

Allocation::Allocation(Runtime::Allocator                allocation,
                       lang::ResolvingHandle<lang::Type> type,
                       Optional<Owned<Expression>>       count,
                       lang::Location                    location,
                       lang::Location                    allocated_type_location)
    : Expression(location)
    , allocation_(allocation)
    , allocated_type_(type)
    , allocated_type_location_(allocated_type_location)
    , count_(std::move(count))
{
    if (count_.hasValue()) addSubexpression(*count_.value());
}

Runtime::Allocator Allocation::allocator() const
{
    return allocation_;
}

lang::Entity const& Allocation::allocatedType() const
{
    return *allocated_type_;
}

Expression const* Allocation::count() const
{
    return getPtr(count_);
}

void Allocation::walkDefinitions()
{
    Expression::walkDefinitions();

    scope().registerUsage(allocated_type_);
}

void Allocation::defineType(lang::ResolvingHandle<lang::Type> type)
{
    if (!isInitialized()) return;

    if (allocated_type_.is<lang::Type>())
    {
        auto allocated_type = allocated_type_.as<lang::Type>().value();
        type.reroute(count_.hasValue() ? scope().context().getBufferType(allocated_type)
                                       : scope().context().getPointerType(allocated_type));
    }
}

bool Allocation::validate(ValidationLogger& validation_logger) const
{
    if (lang::Type::checkMismatch<lang::Type>(allocated_type_, "type", allocated_type_location_, validation_logger))
        return false;

    bool is_valid = allocated_type_.as<lang::Type>()->validate(validation_logger, location())
                 && type().validate(validation_logger, location());

    if (count_.hasValue())
    {
        count_.value()->validate(validation_logger);

        is_valid &= lang::Type::checkMismatch(scope().context().getSizeType(),
                                              count_.value()->type(),
                                              count_.value()->location(),
                                              validation_logger);
    }

    is_valid &= scope().context().validateRuntimeDependency(location(), validation_logger);

    return is_valid;
}

Expression::Expansion Allocation::expandWith(Expressions subexpressions, lang::Context& new_context) const
{
    if (count_.hasValue())
    {
        return {Statements(),
                makeOwned<Allocation>(allocation_,
                                      allocated_type_->getUndefinedClone<lang::Type>(new_context),
                                      std::move(subexpressions[0]),
                                      location(),
                                      allocated_type_location_),
                Statements()};
    }
    else
    {
        return {Statements(),
                makeOwned<Allocation>(allocation_,
                                      allocated_type_->getUndefinedClone<lang::Type>(new_context),
                                      std::nullopt,
                                      location(),
                                      allocated_type_location_),
                Statements()};
    }
}

Allocation::~Allocation() = default;
