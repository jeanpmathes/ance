#include "ArrayDefinition.h"

#include "lang/ApplicationVisitor.h"
#include "lang/type/ArrayType.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

ArrayDefinition::ArrayDefinition(std::optional<lang::ResolvingHandle<lang::Type>> type,
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

const std::optional<lang::ResolvingHandle<lang::Type>>& ArrayDefinition::elementType() const
{
    return type_;
}

std::vector<std::reference_wrapper<Expression>> ArrayDefinition::values() const
{
    std::vector<std::reference_wrapper<Expression>> values;

    values.reserve(elements_.size());
    for (const auto& element : elements_) { values.emplace_back(*element); }

    return values;
}

void ArrayDefinition::walkDefinitions()
{
    Expression::walkDefinitions();

    if (type_.has_value()) scope()->addType(type_.value());
}

std::optional<lang::ResolvingHandle<lang::Type>> ArrayDefinition::tryGetType() const
{
    if (type_.has_value()) return lang::ArrayType::get(type_.value(), elements_.size());

    auto types = Expression::tryGetTypes(elements_);
    if (not types.has_value()) return std::nullopt;

    auto common_types = lang::Type::getCommonType(types.value());

    if (common_types.size() == 1) { return lang::ArrayType::get(common_types.front(), elements_.size()); }
    else { return std::nullopt; }
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

    if (type_.has_value())
    {
        lang::ResolvingHandle<lang::Type> type = type_.value();

        if (lang::validation::isTypeUndefined(type, type_location_, validation_logger)) return false;

        assert(this->type()->getElementType() == type_.value());
    }
    else
    {
        std::vector<lang::ResolvingHandle<lang::Type>> types = Expression::getTypes(elements_);

        auto common_types = lang::Type::getCommonType(types);

        if (common_types.empty() || common_types.size() > 1)
        {
            validation_logger.logError("Array definition has no common type", location());
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

Expression::Expansion ArrayDefinition::expandWith(Expressions subexpressions) const
{
    std::optional<lang::ResolvingHandle<lang::Type>> type;
    if (type_.has_value()) type = type_.value()->toUndefined();

    return {Statements(),
            std::make_unique<ArrayDefinition>(type, type_location_, std::move(subexpressions), location()),
            Statements()};
}

void ArrayDefinition::doBuild(CompileContext& context)
{
    std::vector<std::shared_ptr<lang::Value>> elements;

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
