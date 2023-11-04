
#include "OwningHandle.h"

template<typename T>
lang::OwningHandle<T>::OwningHandle(Owned<T> owner, ResolvingHandle<T> handle)
    : owner_(std::move(owner))
    , handle_(handle)
{}

template<typename T>
template<typename OtherT>
    requires MoveConvertible<T*, OtherT*>
lang::OwningHandle<T>::OwningHandle(lang::OwningHandle<OtherT>&& value) noexcept
    : owner_(std::move(value.owner_))
    , handle_(std::move(value.handle_))
{}

template<typename T>
template<typename OtherT>
    requires MoveConvertible<T*, OtherT*>
lang::OwningHandle<T>& lang::OwningHandle<T>::operator=(lang::OwningHandle<OtherT>&& value) noexcept
{
    owner_  = std::move(value.owner_);
    handle_ = std::move(value.handle_);
    return *this;
}

template<typename T>
lang::OwningHandle<T> lang::OwningHandle<T>::takeOwnership(ResolvingHandle<T> handle)
{
    return lang::OwningHandle<T>(handle.take(), handle);
}

template<typename T>
template<typename Original>
lang::OwningHandle<T> lang::OwningHandle<T>::cast(lang::OwningHandle<Original>&& owning_handle)
{
    auto handle = owning_handle.handle_;

    assert(handle.template is<T>());

    auto old_owning_pointer = unwrap(std::move(owning_handle.owner_));
    auto new_owning_pointer = dynamic_cast<T*>(old_owning_pointer);

    assert(new_owning_pointer != nullptr);

    return lang::OwningHandle<T>(std::move(wrap(new_owning_pointer).value()), handle.template as<T>().value());
}

template<typename T>
lang::ResolvingHandle<T> lang::OwningHandle<T>::handle()
{
    return handle_;
}

template<typename T>
std::reference_wrapper<lang::ResolvingHandle<T> const> lang::OwningHandle<T>::handle() const
{
    return handle_;
}

template<typename T>
T const& lang::OwningHandle<T>::get() const
{
    return handle_;
}

template<typename T>
T* lang::OwningHandle<T>::operator->() noexcept
{
    return owner_.get();
}

template<typename T>
T& lang::OwningHandle<T>::operator*() noexcept
{
    return *owner_;
}

template<typename T>
const T* lang::OwningHandle<T>::operator->() const noexcept
{
    return owner_.get();
}

template<typename T>
T const& lang::OwningHandle<T>::operator*() const noexcept
{
    return *owner_;
}

template<typename T>
lang::OwningHandle<T>::OwningHandle::~OwningHandle()
{
    if (owner_.get()) handle_.invalidate(owner_.get());
}
