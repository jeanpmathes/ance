#include "Variable.h"

#include <cassert>

#include "ance/cet/Address.h"
#include "ance/cet/ValueExtensions.h"

namespace ance::cet
{
    Variable::Variable(core::Identifier const&    identifier,
                       utility::Shared<bbt::Type> type,
                       bool                       is_final,
                       core::Location const&      location,
                       bbt::TypeContext&          type_context)
        : identifier_(identifier)
        , type_(std::move(type))
        , is_final_(is_final)
        , location_(location)
        , type_context_(type_context)
    {}

    core::Identifier const& Variable::name() const
    {
        return identifier_;
    }

    utility::Shared<bbt::Type> Variable::type()
    {
        return type_;
    }

    bbt::Type const& Variable::type() const
    {
        return *type_;
    }

    bool Variable::isFinal() const
    {
        return is_final_;
    }

    core::Location const& Variable::location() const
    {
        return location_;
    }

    utility::Shared<bbt::Value> Variable::access()
    {
        core::VariabilityModifier variability = core::VariabilityModifier::VARIABLE;

        if (is_final_ && isDefined())
        {
            variability = core::VariabilityModifier::INVARIABLE;
        }

        return Reference::make(Address(*this), type_, variability, type_context_);
    }

    utility::Shared<bbt::Value> Variable::read(std::vector<size_t> const& indices)
    {
        assert(isDefined());

        auto result = load(value_.value(), indices, type_context_);
        assert(result.hasValue());

        return result.value();
    }

    void Variable::write(utility::Shared<bbt::Value> value, std::vector<size_t> const& indices)
    {
        assert(!is_final_ || !isDefined());

        if (indices.empty())
        {
            assert(value->type() == type_);
            value_ = std::move(value);
            return;
        }

        assert(isDefined());

        auto result = store(value_.value(), indices, std::move(value), type_context_);
        assert(result.hasValue());

        value_ = result.value();
    }

    utility::Shared<bbt::Value> Variable::read()
    {
        return read({});
    }

    void Variable::write(utility::Shared<bbt::Value> value)
    {
        write(std::move(value), {});
    }

    bool Variable::isDefined() const
    {
        return value_.hasValue();
    }
}
