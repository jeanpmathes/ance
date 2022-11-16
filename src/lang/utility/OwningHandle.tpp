
#include "OwningHandle.h"

template<typename T>
lang::OwningHandle<T>::OwningHandle(std::unique_ptr<T> owner, ResolvingHandle<T> handle)
    : owner_(std::move(owner))
    , handle_(handle)
{}

template<typename T>
lang::OwningHandle<T>::OwningHandle() : handle_(std::unique_ptr<T>(nullptr))
{}

template<typename T>
lang::OwningHandle<T> lang::OwningHandle<T>::takeOwnership(ResolvingHandle<T> handle)
{
    return lang::OwningHandle<T>(handle.take(), handle);
}

template<typename T>
lang::ResolvingHandle<T> lang::OwningHandle<T>::handle() const
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
const T& lang::OwningHandle<T>::operator*() const noexcept
{
    return *owner_;
}
