#include "VectorDefinition.h"

#include "lang/ApplicationVisitor.h"
#include "lang/type/VectorType.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

VectorDefinition::VectorDefinition(Optional<lang::ResolvingHandle<lang::Type>> type,
                                   lang::Location                              type_location,
                                   std::vector<Owned<Expression>>              elements,
                                   lang::Location                              location)
    : Expression(location)
    , declared_type_(std::move(type))
    , type_location_(type_location)
    , elements_(std::move(elements))
{
    for (auto& element : elements_) { addSubexpression(*element); }
}

Optional<std::reference_wrapper<const lang::Type>> VectorDefinition::elementType() const
{
    if (declared_type_.hasValue()) return std::cref(*declared_type_.value().as<lang::Type>());
    return std::nullopt;
}

std::vector<std::reference_wrapper<Expression const>> VectorDefinition::values() const
{
    std::vector<std::reference_wrapper<Expression const>> values;

    values.reserve(elements_.size());
    for (auto const& element : elements_) { values.emplace_back(*element); }

    return values;
}

void VectorDefinition::walkDefinitions()
{
    Expression::walkDefinitions();

    if (declared_type_.hasValue()) scope()->registerUsage(declared_type_.value());
}

void VectorDefinition::defineType(lang::ResolvingHandle<lang::Type> type)
{
    if (scope() == nullptr) return;

    if (declared_type_.hasValue())
    {
        if (!declared_type_.value().is<lang::Type>()) return;

        type.reroute(
            scope()->context().getVectorType(declared_type_.value().as<lang::Type>().value(), elements_.size()));
        return;
    }
    else
    {
        auto types        = Expression::getTypes(elements_);
        auto common_types = lang::Type::getCommonType(types);

        if (common_types.size() == 1)
        {
            type.reroute(scope()->context().getVectorType(common_types.front(), elements_.size()));
        }
    }
}

bool VectorDefinition::validate(ValidationLogger& validation_logger) const
{
    bool valid = true;

    for (auto& element : elements_) { valid &= element->validate(validation_logger); }

    if (!valid) return false;

    if (elements_.empty())
    {
        validation_logger.logError("Vector definition has no elements", location());
        return false;
    }

    if (declared_type_.hasValue())
    {
        if (lang::Type::checkMismatch<lang::Type>(declared_type_.value(), "type", type_location_, validation_logger))
            return false;

        assert(this->type().getElementType() == *declared_type_.value().as<lang::Type>());
    }
    else
    {
        auto const types = Expression::getTypes(elements_);

        auto common_types = lang::Type::getCommonType(types);

        if (common_types.empty() || common_types.size() > 1)
        {
            validation_logger.logError("Vector definition has no common type", location());
            return false;
        }
    }

    for (auto& element : elements_)
    {
        valid &=
            lang::Type::checkMismatch(type().getElementType(), element->type(), element->location(), validation_logger);
    }

    return valid;
}

Expression::Expansion VectorDefinition::expandWith(Expressions subexpressions, lang::Context& new_context) const
{
    Optional<lang::ResolvingHandle<lang::Type>> type;
    if (declared_type_.hasValue()) type = declared_type_.value()->getUndefinedClone<lang::Type>(new_context);

    return {Statements(),
            makeOwned<VectorDefinition>(type, type_location_, std::move(subexpressions), location()),
            Statements()};
}

void VectorDefinition::doBuild(CompileContext& context)
{
    std::vector<Shared<lang::Value>> elements;

    elements.reserve(elements_.size());
    for (auto& element : elements_)
    {
        elements.push_back(lang::Type::makeMatching(type()->getElementType(), element->getValue(), context));
    }

    auto vector_type = type()->isVectorType();
    assert(vector_type);

    auto value = vector_type->createValue(std::move(elements), context);
    setValue(value);
}

VectorDefinition::~VectorDefinition() = default;
