
#include "OwningHandle.h"

template<typename T>
lang::OwningHandle<T>::OwningHandle(Owned<T> owner, ResolvingHandle<T> handle)
    : owner_(std::move(owner))
    , handle_(handle)
{}

template<typename T>
lang::OwningHandle<T> lang::OwningHandle<T>::takeOwnership(ResolvingHandle<T> handle)
{
    return lang::OwningHandle<T>(handle.take(), handle);
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
