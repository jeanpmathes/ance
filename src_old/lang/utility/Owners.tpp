#include "Owners.h"

template<typename T>
Owned<T>::Owned(T& value) : value_(&value)
{}

template<typename T>
Owned<T>::Owned(std::unique_ptr<T>&& value) : value_(std::move(value))
{}

template<typename T>
Owned<T>::Owned(Owned<T>&& value) noexcept : value_(std::move(value.value_))
{}

template<typename T>
template<typename OtherT>
    requires MoveConvertible<T*, OtherT*>
Owned<T>::Owned(Owned<OtherT>&& value) noexcept : value_(std::move(value.value_))
{}

template<typename T>
Owned<T>& Owned<T>::operator=(Owned<T>&& value) noexcept
{
    value_ = std::move(value.value_);
    return *this;
}

template<typename T>
template<typename OtherT>
    requires MoveConvertible<T*, OtherT*>
Owned<T>& Owned<T>::operator=(Owned<OtherT>&& value) noexcept
{
    value_ = std::move(value.value_);
    return *this;
}

template<typename T>
T* Owned<T>::release(Owned<T>&& value)
{
    return value.value_.release();
}

template<typename T>
T* Owned<T>::get()
{
    return value_.get();
}

template<typename T>
T const* Owned<T>::get() const
{
    return value_.get();
}

template<typename T>
T& Owned<T>::operator*()
{
    return *value_;
}
template<typename T>
T* Owned<T>::operator->()
{
    return value_.get();
}

template<typename T>
T const& Owned<T>::operator*() const
{
    return *value_;
}

template<typename T>
T const* Owned<T>::operator->() const
{
    return value_.get();
}

template<typename T>
Shared<T>::Shared(T& value) : value_(&value)
{}

template<typename T>
Shared<T>::Shared(std::shared_ptr<T>&& value) : value_(std::move(value))
{}

template<typename T>
Shared<T>::Shared(Shared<T>&& value) noexcept : value_(std::move(value.value_))
{}

template<typename T>
Shared<T>::Shared(Shared<T>& value) noexcept : value_(value.value_)
{}

template<typename T>
template<typename OtherT>
    requires MoveConvertible<T*, OtherT*>
Shared<T>::Shared(Shared<OtherT>&& value) noexcept : value_(std::move(value.value_))
{}

template<typename T>
template<typename OtherT>
    requires CopyConvertible<T*, OtherT*>
Shared<T>::Shared(Shared<OtherT>& value) noexcept : value_(value.value_)
{}

template<typename T>
Shared<T>& Shared<T>::operator=(Shared<T> value) noexcept
{
    std::swap(value_, value.value_);
    return *this;
}

template<typename T>
template<typename OtherT>
    requires MoveConvertible<T*, OtherT*>
Shared<T>& Shared<T>::operator=(Shared<OtherT>&& value) noexcept
{
    value_ = std::move(value.value_);
    return *this;
}

template<typename T>
template<typename OtherT>
    requires CopyConvertible<T*, OtherT*>
Shared<T>& Shared<T>::operator=(Shared<OtherT>& value) noexcept
{
    value_ = value.value_;
    return *this;
}

template<typename T>
bool Shared<T>::operator==(Shared<T> const& other) const noexcept
{
    return value_ == other.value_;
}

template<typename T>
bool Shared<T>::operator!=(Shared<T> const& other) const noexcept
{
    return value_ != other.value_;
}

template<typename T>
T* Shared<T>::get()
{
    return value_.get();
}

template<typename T>
T const* Shared<T>::get() const
{
    return value_.get();
}

template<typename T>
T& Shared<T>::operator*()
{
    return *value_;
}

template<typename T>
T* Shared<T>::operator->()
{
    return value_.get();
}

template<typename T>
T const& Shared<T>::operator*() const
{
    return *value_;
}

template<typename T>
T const* Shared<T>::operator->() const
{
    return value_.get();
}

template<typename T>
template<typename OtherT>
Shared<OtherT> Shared<T>::cast()
{
    auto casted = std::dynamic_pointer_cast<OtherT>(value_);

    assert(casted);

    return Shared<OtherT>(std::move(casted));
}

template<typename T>
template<typename OtherT>
OtherT const& Shared<T>::cast() const
{
    auto const* casted = dynamic_cast<OtherT const*>(value_.get());

    assert(casted);

    return *casted;
}
