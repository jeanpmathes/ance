#ifndef ANCE_UTILITY_OPTIONAL_TPP
#define ANCE_UTILITY_OPTIONAL_TPP

#include "Optional.h"

#include <cassert>

template<ance::utility::Moveable T>
ance::utility::Optional<T>::Optional() = default;

template<ance::utility::Moveable T>
ance::utility::Optional<T>::Optional(std::nullopt_t)
{}

template<ance::utility::Moveable T>
ance::utility::Optional<T>::Optional(T const& value)
    requires ConstCopyable<T>
    : has_value_(true)
{
    new (storage_.data()) T(value);
}

template<ance::utility::Moveable T>
ance::utility::Optional<T>::Optional(T value)
    requires(!ConstCopyable<T> and Copyable<T>)
    : has_value_(true)
{
    new (storage_.data()) T(std::move(value));
}

template<ance::utility::Moveable T>
ance::utility::Optional<T>::Optional(T&& value)
    requires(!ConstCopyable<T> and !Copyable<T>)
    : has_value_(true)
{
    new (storage_.data()) T(std::move(value));
}

template<ance::utility::Moveable T>
ance::utility::Optional<T>& ance::utility::Optional<T>::operator=(T value)
{
    if (has_value_) std::destroy_at(std::launder(reinterpret_cast<T*>(storage_.data())));

    new (storage_.data()) T(std::move(value));
    has_value_ = true;

    return *this;
}

template<ance::utility::Moveable T>
ance::utility::Optional<T>::Optional(Optional<T> const& optional)
    requires ConstCopyable<T>
    : has_value_(optional.has_value_)
{
    if (has_value_) new (storage_.data()) T(*optional);
}

template<ance::utility::Moveable T>
ance::utility::Optional<T>::Optional(Optional<T>& optional)
    requires(!ConstCopyable<T> and Copyable<T>)
    : has_value_(optional.has_value_)
{
    if (has_value_) new (storage_.data()) T(*optional);
}

template<ance::utility::Moveable T>
ance::utility::Optional<T>::Optional(Optional<T>&& optional) noexcept : has_value_(optional.has_value_)
{
    if (has_value_) new (storage_.data()) T(std::move(*optional));

    optional.has_value_ = false;
    optional.storage_   = {};
}

template<ance::utility::Moveable T>
template<typename OtherT>
    requires ance::utility::ConstCopyConvertible<T, OtherT>
ance::utility::Optional<T>::Optional(Optional<OtherT> const& optional) : has_value_(optional.has_value_)
{
    if (has_value_) new (storage_.data()) T(*optional);
}

template<ance::utility::Moveable T>
template<typename OtherT>
    requires(!ance::utility::ConstCopyConvertible<T, OtherT> and ance::utility::CopyConvertible<T, OtherT>)
ance::utility::Optional<T>::Optional(Optional<OtherT>& optional) : has_value_(optional.has_value_)
{
    if (has_value_) new (storage_.data()) T(*optional);
}

template<ance::utility::Moveable T>
template<typename OtherT>
    requires ance::utility::MoveConvertible<T, OtherT>
ance::utility::Optional<T>::Optional(Optional<OtherT>&& optional) : has_value_(optional.has_value_)
{
    if (has_value_) new (storage_.data()) T(std::move(*optional));

    optional.has_value_ = false;
    optional.storage_   = {};
}

template<ance::utility::Moveable T>
ance::utility::Optional<T>& ance::utility::Optional<T>::operator=(Optional<T> optional)
    requires Copyable<T>
{
    if (has_value_) std::destroy_at(std::launder(reinterpret_cast<T*>(storage_.data())));

    has_value_ = optional.has_value_;
    if (has_value_) new (storage_.data()) T(std::move(*optional));

    return *this;
}

template<ance::utility::Moveable T>
ance::utility::Optional<T>& ance::utility::Optional<T>::operator=(Optional<T>&& optional) noexcept
    requires(!Copyable<T>)
{
    if (has_value_) std::destroy_at(std::launder(reinterpret_cast<T*>(storage_.data())));

    has_value_ = optional.has_value_;
    if (has_value_) new (storage_.data()) T(std::move(*optional));

    return *this;
}

template<ance::utility::Moveable T>
template<typename OtherT>
    requires ance::utility::MoveConvertible<T, OtherT>
ance::utility::Optional<T>& ance::utility::Optional<T>::operator=(Optional<OtherT>&& optional)
{
    if (has_value_) std::destroy_at(std::launder(reinterpret_cast<T*>(storage_.data())));

    has_value_ = optional.has_value_;
    if (has_value_) new (storage_.data()) T(std::move(*optional));

    return *this;
}

template<ance::utility::Moveable T>
template<typename OtherT>
    requires ance::utility::CopyConvertible<T, OtherT>
ance::utility::Optional<T>& ance::utility::Optional<T>::operator=(Optional<OtherT>& optional)
{
    if (has_value_) std::destroy_at(std::launder(reinterpret_cast<T*>(storage_.data())));

    has_value_ = optional.has_value_;
    if (has_value_) new (storage_.data()) T(*optional);

    return *this;
}

template<ance::utility::Moveable T>
ance::utility::Optional<T>::~Optional<T>()
{
    if (has_value_) std::destroy_at(std::launder(reinterpret_cast<T*>(storage_.data())));

    has_value_ = false;
    storage_   = {};
}

template<ance::utility::Moveable T>
bool ance::utility::Optional<T>::hasValue() const
{
    return has_value_;
}

template<ance::utility::Moveable T>
T& ance::utility::Optional<T>::value()
{
    assert(hasValue());
    return *std::launder(reinterpret_cast<T*>(storage_.data()));
}

template<ance::utility::Moveable T>
T const& ance::utility::Optional<T>::value() const
{
    assert(hasValue());
    return *std::launder(reinterpret_cast<T const*>(storage_.data()));
}

template<ance::utility::Moveable T>
T& ance::utility::Optional<T>::operator*()
{
    return value();
}

template<ance::utility::Moveable T>
T const& ance::utility::Optional<T>::operator*() const
{
    return value();
}

template<ance::utility::Moveable T>
T* ance::utility::Optional<T>::operator->()
{
    return &value();
}

template<ance::utility::Moveable T>
T const* ance::utility::Optional<T>::operator->() const
{
    return &value();
}

template<ance::utility::Moveable T>
T ance::utility::Optional<T>::valueOr(T default_value)
    requires Copyable<T>
{
    return hasValue() ? value() : default_value;
}

template<ance::utility::Moveable T>
T& ance::utility::Optional<T>::valueOr(T& default_value)
    requires(!Copyable<T>)
{
    return hasValue() ? value() : default_value;
}

template<ance::utility::Moveable T>
T const& ance::utility::Optional<T>::valueOr(T const& default_value) const
    requires(!Copyable<T>)
{
    return hasValue() ? value() : default_value;
}

template<ance::utility::Moveable T>
ance::utility::Optional<T>::operator std::optional<T>()
    requires Copyable<T>
{
    return hasValue() ? std::optional<T>(value()) : std::nullopt;
}

#endif
