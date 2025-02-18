#ifndef ANCE_UTILITY_OWNERS_TPP
#define ANCE_UTILITY_OWNERS_TPP

#include "Owners.h"

template<typename T>
ance::utility::Owned<T>::Owned(T& value) : value_(&value)
{}

template<typename T>
ance::utility::Owned<T>::Owned(std::unique_ptr<T>&& value) : value_(std::move(value))
{}

template<typename T>
ance::utility::Owned<T>::Owned(Owned<T>&& value) noexcept : value_(std::move(value.value_))
{}

template<typename T>
template<typename OtherT>
    requires ance::utility::MoveConvertible<T*, OtherT*>
ance::utility::Owned<T>::Owned(Owned<OtherT>&& value) noexcept : value_(std::move(value.value_))
{}

template<typename T>
ance::utility::Owned<T>& ance::utility::Owned<T>::operator=(Owned<T>&& value) noexcept
{
    value_ = std::move(value.value_);
    return *this;
}

template<typename T>
template<typename OtherT>
    requires ance::utility::MoveConvertible<T*, OtherT*>
ance::utility::Owned<T>& ance::utility::Owned<T>::operator=(Owned<OtherT>&& value) noexcept
{
    value_ = std::move(value.value_);
    return *this;
}

template<typename T>
T* ance::utility::Owned<T>::release(Owned<T>&& value)
{
    return value.value_.release();
}

template<typename T>
T* ance::utility::Owned<T>::get()
{
    return value_.get();
}

template<typename T>
T const* ance::utility::Owned<T>::get() const
{
    return value_.get();
}

template<typename T>
T& ance::utility::Owned<T>::operator*()
{
    return *value_;
}

template<typename T>
T* ance::utility::Owned<T>::operator->()
{
    return value_.get();
}

template<typename T>
T const& ance::utility::Owned<T>::operator*() const
{
    return *value_;
}

template<typename T>
T const* ance::utility::Owned<T>::operator->() const
{
    return value_.get();
}

template<typename T>
ance::utility::Shared<T>::Shared(T& value) : value_(&value)
{}

template<typename T>
ance::utility::Shared<T>::Shared(std::shared_ptr<T>&& value) : value_(std::move(value))
{}

template<typename T>
ance::utility::Shared<T>::Shared(Shared<T>&& value) noexcept : value_(std::move(value.value_))
{}

template<typename T>
ance::utility::Shared<T>::Shared(Shared<T>& value) noexcept : value_(value.value_)
{}

template<typename T>
template<typename OtherT>
    requires ance::utility::MoveConvertible<T*, OtherT*>
ance::utility::Shared<T>::Shared(Shared<OtherT>&& value) noexcept : value_(std::move(value.value_))
{}

template<typename T>
template<typename OtherT>
    requires ance::utility::CopyConvertible<T*, OtherT*>
ance::utility::Shared<T>::Shared(Shared<OtherT>& value) noexcept : value_(value.value_)
{}

template<typename T>
ance::utility::Shared<T>& ance::utility::Shared<T>::operator=(Shared<T> value) noexcept
{
    std::swap(value_, value.value_);
    return *this;
}

template<typename T>
template<typename OtherT>
    requires ance::utility::MoveConvertible<T*, OtherT*>
ance::utility::Shared<T>& ance::utility::Shared<T>::operator=(Shared<OtherT>&& value) noexcept
{
    value_ = std::move(value.value_);
    return *this;
}

template<typename T>
template<typename OtherT>
    requires ance::utility::CopyConvertible<T*, OtherT*>
ance::utility::Shared<T>& ance::utility::Shared<T>::operator=(Shared<OtherT>& value) noexcept
{
    value_ = value.value_;
    return *this;
}

template<typename T>
bool ance::utility::Shared<T>::operator==(Shared<T> const& other) const noexcept
{
    return value_ == other.value_;
}

template<typename T>
bool ance::utility::Shared<T>::operator!=(Shared<T> const& other) const noexcept
{
    return value_ != other.value_;
}

template<typename T>
T* ance::utility::Shared<T>::get()
{
    return value_.get();
}

template<typename T>
T const* ance::utility::Shared<T>::get() const
{
    return value_.get();
}

template<typename T>
T& ance::utility::Shared<T>::operator*()
{
    return *value_;
}

template<typename T>
T* ance::utility::Shared<T>::operator->()
{
    return value_.get();
}

template<typename T>
T const& ance::utility::Shared<T>::operator*() const
{
    return *value_;
}

template<typename T>
T const* ance::utility::Shared<T>::operator->() const
{
    return value_.get();
}

template<typename T>
template<typename OtherT>
ance::utility::Shared<OtherT> ance::utility::Shared<T>::cast()
{
    auto casted = std::dynamic_pointer_cast<OtherT>(value_);

    assert(casted);

    return Shared<OtherT>(std::move(casted));
}

template<typename T>
template<typename OtherT>
OtherT const& ance::utility::Shared<T>::cast() const
{
    auto const* casted = dynamic_cast<OtherT const*>(value_.get());

    assert(casted);

    return *casted;
}

template<typename T>
template<typename OtherT>
bool ance::utility::Shared<T>::is() const
{
    return dynamic_cast<OtherT const*>(value_.get()) != nullptr;
}

#endif
