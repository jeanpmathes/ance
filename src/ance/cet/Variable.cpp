#include "Variable.h"

#include <cassert>

#include "ance/cet/Address.h"
#include "ance/cet/ValueExtensions.h"

namespace ance::cet
{
    Variable::Variable(core::Identifier const& identifier, utility::Shared<bbt::Type> type, bool is_final, core::Location const& location)
    : identifier_(identifier)
    , type_(std::move(type))
    , is_final_(is_final)
    , location_(location)
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
        if (is_final_ && isDefined())
        {
            return value_.value();
        }

        return LReference::make(Address(*this));
    }

    utility::Shared<bbt::Value> Variable::read(std::vector<size_t> const& indices)
    {
        assert(isDefined());
        assert(indices.empty());

        return value_.value();
    }

    void Variable::write(utility::Shared<bbt::Value> value, std::vector<size_t> const& indices)
    {
        assert(!is_final_ || !isDefined());
        assert(value->type() == type_);
        assert(indices.empty());

        value_ = std::move(value);
    }

    bool Variable::isDefined() const
    {
        return value_.hasValue();
    }
}
