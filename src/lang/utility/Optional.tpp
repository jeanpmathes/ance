#include "Optional.h"

template<Moveable T>
Optional<T>::Optional() = default;

template<Moveable T>
Optional<T>::Optional(std::nullopt_t)
{}

template<Moveable T>
Optional<T>::Optional(T value)
    requires Copyable<T>
    : has_value_(true)
{
    new (storage_.data()) T(std::move(value));
}

template<Moveable T>
Optional<T>::Optional(T&& value)
    requires(!Copyable<T>)
    : has_value_(true)
{
    new (storage_.data()) T(std::move(value));
}

template<Moveable T>
Optional<T>& Optional<T>::operator=(T value)
{
    if (has_value_) std::destroy_at(std::launder(reinterpret_cast<T*>(storage_.data())));

    new (storage_.data()) T(std::move(value));
    has_value_ = true;

    return *this;
}

template<Moveable T>
Optional<T>::Optional(Optional<T>& optional)
    requires Copyable<T>
    : has_value_(optional.has_value_)
{
    if (has_value_) new (storage_.data()) T(*optional);
}

template<Moveable T>
Optional<T>::Optional(Optional<T>&& optional) noexcept : has_value_(optional.has_value_)
{
    if (has_value_) new (storage_.data()) T(std::move(*optional));

    optional.has_value_ = false;
    optional.storage_   = {};
}

template<Moveable T>
Optional<T>& Optional<T>::operator=(Optional<T> optional)
    requires Copyable<T>
{
    if (has_value_) std::destroy_at(std::launder(reinterpret_cast<T*>(storage_.data())));

    has_value_ = optional.has_value_;
    if (has_value_) new (storage_.data()) T(std::move(*optional));

    return *this;
}

template<Moveable T>
Optional<T>& Optional<T>::operator=(Optional<T>&& optional) noexcept
    requires(!Copyable<T>)
{
    if (has_value_) std::destroy_at(std::launder(reinterpret_cast<T*>(storage_.data())));

    has_value_ = optional.has_value_;
    if (has_value_) new (storage_.data()) T(std::move(*optional));

    return *this;
}

template<Moveable T>
Optional<T>::~Optional()
{
    if (has_value_) std::destroy_at(std::launder(reinterpret_cast<T*>(storage_.data())));

    has_value_ = false;
    storage_   = {};
}

template<Moveable T>
bool Optional<T>::hasValue() const
{
    return has_value_;
}

template<Moveable T>
T& Optional<T>::value()
{
    return *std::launder(reinterpret_cast<T*>(storage_.data()));
}

template<Moveable T>
T const& Optional<T>::value() const
{
    return *std::launder(reinterpret_cast<T const*>(storage_.data()));
}

template<Moveable T>
T& Optional<T>::operator*()
{
    return value();
}

template<Moveable T>
T const& Optional<T>::operator*() const
{
    return value();
}

template<Moveable T>
T* Optional<T>::operator->()
{
    return &value();
}

template<Moveable T>
T const* Optional<T>::operator->() const
{
    return &value();
}

template<Moveable T>
T Optional<T>::valueOr(T default_value)
    requires Copyable<T>
{
    return hasValue() ? value() : default_value;
}

template<Moveable T>
T& Optional<T>::valueOr(T& default_value)
{
    return hasValue() ? value() : default_value;
}

template<Moveable T>
T const& Optional<T>::valueOr(T const& default_value) const
{
    return hasValue() ? value() : default_value;
}
