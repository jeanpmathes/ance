#include "ResolvingHandle.h"

template<typename T>
ance::ResolvingHandle<T>::ResolvingHandle(std::unique_ptr<T> handled)
    : navigator_(std::shared_ptr<ance::ResolvingHandle<T>::HandleNavigator>(
        new ance::ResolvingHandle<T>::HandleNavigator(std::move(handled))))
{}

template<typename T>
T* ance::ResolvingHandle<T>::get() const
{
    return navigator_->get();
}

template<typename T>
T* ance::ResolvingHandle<T>::operator->() const noexcept
{
    return get();
}

template<typename T>
T& ance::ResolvingHandle<T>::operator*() const noexcept
{
    return *get();
}

template<typename T>
ance::ResolvingHandle<T>::HandleNavigator::HandleNavigator(std::shared_ptr<HandleNavigator> next) : next_(next)
{}

template<typename T>
ance::ResolvingHandle<T>::HandleNavigator::HandleNavigator(std::unique_ptr<T> element)
    : owned_element_(std::move(element))
{}

template<typename T>
typename ance::ResolvingHandle<T>::HandleNavigator* ance::ResolvingHandle<T>::HandleNavigator::root()
{
    return next_ ? next_->root() : this;
}

template<typename T>
T* ance::ResolvingHandle<T>::HandleNavigator::get()
{
    auto root = this->root();
    return root->element_ ? element_ : owned_element_.get();
}

template<typename T, class... ARGS>
ance::ResolvingHandle<T> ance::makeHandled(ARGS&&... args)
{
    return ResolvingHandle<T>(std::make_unique<T>(std::forward<ARGS>(args)...));
}