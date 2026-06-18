#include "Value.h"

#include <algorithm>
#include <ranges>
#include <sstream>
#include <utility>

#include "ance/bbt/Type.h"

namespace ance::bbt
{
    Value::Value(utility::Optional<utility::Shared<Type>> type, TypeContext& type_context) : type_(std::move(type)), type_context_(type_context) {}

    utility::Shared<Type> Value::type()
    {
        return type_.valueOr(type_context_.getType());
    }

    Type const& Value::type() const
    {
        return type_.hasValue() ? *type_.value() : *type_context_.getType();
    }

    utility::Optional<utility::Shared<Value>> Value::access(size_t, utility::Shared<Value>*, TypeContext&)
    {
        // By default, access is not supported.

        return std::nullopt;
    }

    Unit::Unit(TypeContext& type_context) : ValueBase(type_context.getUnit(), type_context) {}

    utility::Shared<Unit> Unit::make(TypeContext& type_context)
    {
        return utility::makeShared<Unit>(type_context);
    }

    std::string Unit::toString() const
    {
        return "()";
    }

    bool Unit::equals(Unit const&) const
    {
        return true;
    }

    Bool::Bool(bool const value, TypeContext& type_context) : ValueBase(type_context.getBool(), type_context), value_(value) {}

    utility::Shared<Bool> Bool::make(bool const value, TypeContext& type_context)
    {
        return utility::makeShared<Bool>(value, type_context);
    }

    std::string Bool::toString() const
    {
        return value_ ? "true" : "false";
    }

    bool Bool::value() const
    {
        return value_;
    }

    bool Bool::equals(Bool const& other) const
    {
        return value_ == other.value_;
    }

    Size::Size(size_t const value, TypeContext& type_context) : ValueBase(type_context.getSize(), type_context), value_(value) {}

    utility::Shared<Size> Size::make(size_t value, TypeContext& type_context)
    {
        return utility::makeShared<Size>(value, type_context);
    }

    utility::Shared<Size> Size::make(std::string const& value, TypeContext& type_context)
    {
        // todo: should use llvm::APInt and it should know the actual bit size here already (maybe through type context)
        // todo: should also do the checks that it is only within the guaranteed ranges

        return make(std::stoull(value), type_context);
    }

    std::string Size::toString() const
    {
        return std::to_string(value_);
    }

    size_t Size::value() const
    {
        return value_;
    }

    bool Size::equals(Size const& other) const
    {
        return value_ == other.value_;
    }

    Float::Float(llvm::APFloat value, TypeContext& type_context)
        : ValueBase(type_context.getFloat(core::Precision::get(value.getSemantics())), type_context)
        , value_(std::move(value))
    {}

    utility::Shared<Float> Float::make(llvm::APFloat value, TypeContext& type_context)
    {
        return utility::makeShared<Float>(std::move(value), type_context);
    }

    utility::Shared<Float> Float::make(std::string const& value, core::Precision const precision, TypeContext& type_context)
    {
        return make(llvm::APFloat(precision.getLlvmSemantics(), value), type_context);
    }

    std::string Float::toString() const
    {
        llvm::SmallVector<char, 32> number;
        value_.toString(number);

        std::string const suffix = core::Precision::get(value_.getSemantics()).getSuffix();

        std::string result;
        result.reserve(number.size() + suffix.size());

        result.append(number.begin(), number.end());
        result.append(suffix);

        return result;
    }

    llvm::APFloat Float::value() const
    {
        return value_;
    }

    bool Float::equals(Float const& other) const
    {
        return value_ == other.value_;
    }

    Identifier::Identifier(core::Identifier const& identifier, TypeContext& type_context)
        : ValueBase(type_context.getIdentifier(), type_context)
        , identifier_(identifier)
    {}

    utility::Shared<Identifier> Identifier::make(core::Identifier const& identifier, TypeContext& type_context)
    {
        return utility::makeShared<Identifier>(identifier, type_context);
    }

    std::string Identifier::toString() const
    {
        return "#" + std::string(identifier_.text());
    }

    core::Identifier const& Identifier::value() const
    {
        return identifier_;
    }

    bool Identifier::equals(Identifier const& other) const
    {
        return identifier_.text() == other.identifier_.text();
    }

    Location::Location(core::Location const& location, TypeContext& type_context) : ValueBase(type_context.getLocation(), type_context), location_(location) {}

    utility::Shared<Location> Location::make(core::Location const& location, TypeContext& type_context)
    {
        return utility::makeShared<Location>(location, type_context);
    }

    std::string Location::toString() const
    {
        std::stringstream ss;
        ss << location_;
        return ss.str();
    }

    core::Location const& Location::value() const
    {
        return location_;
    }

    bool Location::equals(Location const& other) const
    {
        return location_ == other.location_;
    }

    String::String(std::string value, TypeContext& type_context) : ValueBase(type_context.getString(), type_context), value_(std::move(value)) {}

    utility::Shared<String> String::make(std::string value, TypeContext& type_context)
    {
        return utility::makeShared<String>(std::move(value), type_context);
    }

    std::string String::toString() const
    {
        return std::format("\"{}\"", value_);
    }

    std::string const& String::value() const
    {
        return value_;
    }

    bool String::equals(String const& other) const
    {
        return value_ == other.value_;
    }

    Array::Array(utility::Shared<Type> array_type, utility::List<utility::Shared<Value>> element_list, TypeContext& type_context)
        : ValueBase(std::move(array_type), type_context)
        , elements_(std::move(element_list))
    {}

    utility::Shared<Array> Array::make(utility::Shared<Type> array_type, utility::List<utility::Shared<Value>> element_list, TypeContext& type_context)
    {
        return utility::makeShared<Array>(std::move(array_type), std::move(element_list), type_context);
    }

    std::string Array::toString() const
    {
        std::string result = "[";

        for (size_t const index : std::views::iota(size_t {0}, elements_.size()))
        {
            if (index > 0) result += ", ";
            result += elements_[index]->toString();
        }

        result += "]";
        return result;
    }

    utility::Optional<utility::Shared<Value>> Array::access(size_t const index, utility::Shared<Value>* replacement, TypeContext& type_context)
    {
        if (index >= elements_.size())
        {
            return std::nullopt;
        }

        if (replacement == nullptr)
        {
            return elements_[index];
        }

        utility::List<utility::Shared<Value>> elements_copy = elements_;

        assert((*replacement)->type() == type()->getConstructingType(0));
        elements_copy[index] = *replacement;

        return make(type(), std::move(elements_copy), type_context);
    }

    std::span<utility::Shared<Value> const> Array::elements() const
    {
        return elements_;
    }

    bool Array::equals(Array const& other) const
    {
        if (type() != other.type()) return false;
        if (elements_.size() != other.elements_.size()) return false;

        return std::ranges::equal(elements_, other.elements_, [](auto const& left, auto const& right) { return left->equals(*right); });
    }

    bool Array::isEmpty() const
    {
        return elements_.empty();
    }

    size_t Array::length() const
    {
        return elements_.size();
    }
}

std::ostream& operator<<(std::ostream& out, ance::bbt::Value const& value)
{
    return out << value.toString();
}
