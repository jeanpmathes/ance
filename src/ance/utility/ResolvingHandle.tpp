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
std::unique_ptr<T> ance::ResolvingHandle<T>::take()
{
    return navigator_->take();
}

template<typename T>
void ance::ResolvingHandle<T>::reroute(ance::ResolvingHandle<T> target)
{
    assert(getRootNavigator() != target.getRootNavigator());
    navigator_->root()->target(target.getRootNavigator());
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
std::shared_ptr<typename ance::ResolvingHandle<T>::HandleNavigator> ance::ResolvingHandle<T>::getRootNavigator()
{
    std::shared_ptr<HandleNavigator> nav_root = navigator_->sRoot();
    if (!nav_root) nav_root = navigator_;

    return nav_root;
}

template<typename T>
ance::ResolvingHandle<T>::HandleNavigator::HandleNavigator(std::shared_ptr<HandleNavigator> next) : next_(next)
{}

template<typename T>
ance::ResolvingHandle<T>::HandleNavigator::HandleNavigator(std::unique_ptr<T> element)
    : owned_element_(std::move(element))
{}

template<typename T>
std::shared_ptr<typename ance::ResolvingHandle<T>::HandleNavigator> ance::ResolvingHandle<T>::HandleNavigator::sRoot()
{
    if (next_)
    {
        std::shared_ptr<HandleNavigator> potential_root = next_->sRoot();
        return potential_root ? potential_root : next_;
    }
    else
    {
        return {};
    }
}

template<typename T>
typename ance::ResolvingHandle<T>::HandleNavigator* ance::ResolvingHandle<T>::HandleNavigator::root()
{
    return next_ ? next_->root() : this;
}

template<typename T>
T* ance::ResolvingHandle<T>::HandleNavigator::get()
{
    HandleNavigator* root = this->root();
    return root->element_ ? root->element_ : root->owned_element_.get();
}

template<typename T>
std::unique_ptr<T> ance::ResolvingHandle<T>::HandleNavigator::take()
{
    auto root = this->root();
    assert(root->owned_element_);

    std::unique_ptr<T> taken = std::move(root->owned_element_);
    root->element_           = taken.get();

    return taken;
}

template<typename T>
void ance::ResolvingHandle<T>::HandleNavigator::target(std::shared_ptr<ance::ResolvingHandle<T>::HandleNavigator> next)
{
    owned_element_.reset();
    element_ = nullptr;

    next_ = next;
}

template<typename T, class... ARGS>
ance::ResolvingHandle<T> ance::makeHandled(ARGS&&... args)
{
    return ResolvingHandle<T>(std::make_unique<T>(std::forward<ARGS>(args)...));
}