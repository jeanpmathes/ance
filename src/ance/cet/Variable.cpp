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
        if (is_final_ && isDefined())
        {
            return value_.value();
        }

        return LReference::make(Address(*this), type_, type_context_);
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

    utility::Shared<Variable> Variable::createConstant(core::Identifier const& name, utility::Shared<bbt::Value> value, bbt::TypeContext& type_context)
    {
        utility::Shared<Variable> constant = utility::makeShared<Variable>(name, value->type(), true, core::Location::global(), type_context);
        constant->write(std::move(value), {});
        return constant;
    }
}
