
#include "OwningHandle.h"

template<typename T>
ance::OwningHandle<T>::OwningHandle(std::unique_ptr<T> owner, ResolvingHandle<T> handle)
    : owner_(std::move(owner))
    , handle_(handle)
{}

template<typename T>
ance::OwningHandle<T>::OwningHandle() : handle_(std::unique_ptr<T>(nullptr))
{}

template<typename T>
ance::OwningHandle<T> ance::OwningHandle<T>::takeOwnership(ResolvingHandle<T> handle)
{
    return ance::OwningHandle(handle.take(), handle);
}

template<typename T>
ance::ResolvingHandle<T> ance::OwningHandle<T>::handle()
{
    return handle_;
}

template<typename T>
T* ance::OwningHandle<T>::operator->() const noexcept
{
    return owner_.get();
}

template<typename T>
T& ance::OwningHandle<T>::operator*() const noexcept
{
    return *owner_;
}
