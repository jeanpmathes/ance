#include "ArrayDefinition.h"

#include "lang/ApplicationVisitor.h"
#include "lang/type/ArrayType.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

ArrayDefinition::ArrayDefinition(Optional<lang::ResolvingHandle<lang::Type>> type,
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

Optional<lang::ResolvingHandle<lang::Type>> const& ArrayDefinition::elementType() const
{
    return declared_type_;
}

std::vector<std::reference_wrapper<Expression const>> ArrayDefinition::values() const
{
    std::vector<std::reference_wrapper<Expression const>> values;

    values.reserve(elements_.size());
    for (auto const& element : elements_) { values.emplace_back(*element); }

    return values;
}

void ArrayDefinition::walkDefinitions()
{
    Expression::walkDefinitions();

    if (declared_type_.hasValue()) scope()->addType(declared_type_.value());
}

void ArrayDefinition::defineType(lang::ResolvingHandle<lang::Type>& type)
{
    if (declared_type_.hasValue())
    {
        type.reroute(lang::ArrayType::get(declared_type_.value(), elements_.size()));
        return;
    }

    auto types        = Expression::getTypes(elements_);
    auto common_types = lang::Type::getCommonType(types);

    if (common_types.size() == 1)
    {
        type.reroute(lang::ArrayType::get(common_types.front(), elements_.size()));
        return;
    }
}

bool ArrayDefinition::validate(ValidationLogger& validation_logger) const
{
    bool valid = true;

    for (auto& element : elements_) { valid &= element->validate(validation_logger); }

    if (!valid) return false;

    if (elements_.empty())
    {
        validation_logger.logError("Array definition has no elements", location());
        return false;
    }

    if (declared_type_.hasValue())
    {
        lang::Type const& type = declared_type_.value();

        if (lang::validation::isTypeUndefined(type, type_location_, validation_logger)) return false;

        assert(this->type().getElementType() == type);
    }
    else
    {
        std::vector<std::reference_wrapper<lang::Type const>> const types = Expression::getTypes(elements_);

        auto common_types = lang::Type::getCommonType(types);

        if (common_types.empty() || common_types.size() > 1)
        {
            validation_logger.logError("Array definition has no common type", location());
            return false;
        }

        assert(type().getElementType() == common_types.front());
    }

    for (auto& element : elements_)
    {
        valid &=
            lang::Type::checkMismatch(type().getElementType(), element->type(), element->location(), validation_logger);
    }

    return valid;
}

Expression::Expansion ArrayDefinition::expandWith(Expressions subexpressions) const
{
    Optional<lang::ResolvingHandle<lang::Type>> type;
    if (declared_type_.hasValue()) type = declared_type_.value()->createUndefinedClone();

    return {Statements(),
            makeOwned<ArrayDefinition>(type, type_location_, std::move(subexpressions), location()),
            Statements()};
}

void ArrayDefinition::doBuild(CompileContext& context)
{
    std::vector<Shared<lang::Value>> elements;

    for (auto& element : elements_)
    {
        elements.push_back(lang::Type::makeMatching(type()->getElementType(), element->getValue(), context));
    }

    auto array_type = type()->isArrayType();
    assert(array_type);

    auto value = array_type->createValue(std::move(elements), context);
    setValue(value);
}

ArrayDefinition::~ArrayDefinition() = default;
