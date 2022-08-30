#include "VectorDefinition.h"

#include "lang/type/VectorType.h"
#include "validation/ValidationLogger.h"

VectorDefinition::VectorDefinition(std::optional<lang::ResolvingHandle<lang::Type>> type,
                                   lang::Location                                   type_location,
                                   std::vector<std::unique_ptr<Expression>>         elements,
                                   lang::Location                                   location)
    : Expression(location)
    , type_(std::move(type))
    , type_location_(type_location)
    , elements_(std::move(elements))
{
    for (auto& element : elements_) { addSubexpression(*element); }
}

const std::optional<lang::ResolvingHandle<lang::Type>>& VectorDefinition::elementType() const
{
    return type_;
}

std::vector<std::reference_wrapper<Expression>> VectorDefinition::values() const
{
    std::vector<std::reference_wrapper<Expression>> values;

    values.reserve(elements_.size());
    for (const auto& element : elements_) { values.emplace_back(*element); }

    return values;
}

void VectorDefinition::walkDefinitions()
{
    Expression::walkDefinitions();

    if (type_.has_value()) scope()->addType(type_.value());
}

std::optional<lang::ResolvingHandle<lang::Type>> VectorDefinition::tryGetType() const
{
    if (type_.has_value()) return lang::VectorType::get(type_.value(), elements_.size());

    std::vector<lang::ResolvingHandle<lang::Type>> types;

    for (auto& element : elements_)
    {
        auto type = element->tryGetType();
        if (type.has_value()) { types.push_back(type.value()); }
        else { return std::nullopt; }
    }

    auto common_types = lang::Type::getCommonType(types);

    if (common_types.size() == 1) { return lang::VectorType::get(common_types.front(), elements_.size()); }
    else { return std::nullopt; }
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

    if (type_.has_value())
    {
        lang::ResolvingHandle<lang::Type> type = type_.value();

        if (!type->isDefined())
        {
            validation_logger.logError("Type " + type->getAnnotatedName() + " not defined", type_location_);
            return false;
        }

        assert(this->type()->getElementType() == type_.value());
    }
    else
    {
        std::vector<lang::ResolvingHandle<lang::Type>> types;
        types.reserve(elements_.size());

        for (auto& element : elements_) { types.push_back(element->type()); }

        auto common_types = lang::Type::getCommonType(types);

        if (common_types.empty() || common_types.size() > 1)
        {
            validation_logger.logError("Vector definition has no common type", location());
            return false;
        }

        assert(type()->getElementType() == common_types.front());
    }

    for (auto& element : elements_)
    {
        valid &= lang::Type::checkMismatch(type()->getElementType(),
                                           element->type(),
                                           element->location(),
                                           validation_logger);
    }

    return valid;
}

Expression::Expansion VectorDefinition::expandWith(Expressions subexpressions) const
{
    std::optional<lang::ResolvingHandle<lang::Type>> type;
    if (type_.has_value()) type = type_.value()->toUndefined();

    return {Statements(),
            std::make_unique<VectorDefinition>(type, type_location_, std::move(subexpressions), location()),
            Statements()};
}

void VectorDefinition::doBuild(CompileContext& context)
{
    std::vector<std::shared_ptr<lang::Value>> elements;

    for (auto& element : elements_)
    {
        elements.push_back(lang::Type::makeMatching(type()->getElementType(), element->getValue(), context));
    }

    auto vector_type = dynamic_cast<lang::VectorType*>(type()->getDefinition());

    auto value = vector_type->createValue(std::move(elements), context);
    setValue(value);
}

VectorDefinition::~VectorDefinition() = default;
