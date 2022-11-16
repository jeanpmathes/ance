#include "ResolvingHandle.h"

#include <cassert>

template<typename T>
lang::ResolvingHandle<T>::ResolvingHandle(std::unique_ptr<T> handled)
    : navigator_(std::shared_ptr<lang::ResolvingHandle<T>::HandleNavigator>(
        new lang::ResolvingHandle<T>::HandleNavigator(std::move(handled))))
{
    if (navigator_->get() == nullptr) return;

    (*this)->setSelf(*this);
}

template<typename T>
T* lang::ResolvingHandle<T>::get() const
{
    return navigator_->get();
}

template<typename T>
std::unique_ptr<T> lang::ResolvingHandle<T>::take()
{
    return navigator_->take();
}

template<typename T>
void lang::ResolvingHandle<T>::reroute(lang::ResolvingHandle<T> target)
{
    assert(getRootNavigator() != target.getRootNavigator());
    navigator_->root()->target(target.getRootNavigator());
}

template<typename T>
T* lang::ResolvingHandle<T>::operator->() noexcept
{
    return get();
}

template<typename T>
T& lang::ResolvingHandle<T>::operator*() noexcept
{
    return *get();
}

template<typename T>
const T* lang::ResolvingHandle<T>::operator->() const noexcept
{
    return get();
}

template<typename T>
const T& lang::ResolvingHandle<T>::operator*() const noexcept
{
    return *get();
}

template<typename T>
std::shared_ptr<typename lang::ResolvingHandle<T>::HandleNavigator> lang::ResolvingHandle<T>::getRootNavigator()
{
    std::shared_ptr<HandleNavigator> nav_root = navigator_->sRoot();
    if (!nav_root) nav_root = navigator_;

    return nav_root;
}

template<typename T>
bool lang::ResolvingHandle<T>::operator==(ResolvingHandle<T> const& other) const
{
    T* target       = get();
    T* other_target = other.get();

    return target->equalsTarget(other_target);
}

template<typename T>
bool lang::ResolvingHandle<T>::operator!=(lang::ResolvingHandle<T> const& other) const
{
    T* target       = get();
    T* other_target = other.get();

    return not target->equalsTarget(other_target);
}

template<typename T>
bool lang::ResolvingHandle<T>::operator<(lang::ResolvingHandle<T> const& other) const
{
    T* target       = get();
    T* other_target = other.get();

    return target < other_target;
}

template<typename T>
lang::ResolvingHandle<T>::HandleNavigator::HandleNavigator(std::shared_ptr<HandleNavigator> next) : next_(next)
{}

template<typename T>
lang::ResolvingHandle<T>::HandleNavigator::HandleNavigator(std::unique_ptr<T> element)
    : owned_element_(std::move(element))
{}

template<typename T>
std::shared_ptr<typename lang::ResolvingHandle<T>::HandleNavigator> lang::ResolvingHandle<T>::HandleNavigator::sRoot()
{
    if (next_)
    {
        std::shared_ptr<HandleNavigator> potential_root = next_->sRoot();

        if (potential_root) { next_ = potential_root; }

        return next_;
    }
    else { return {}; }
}

template<typename T>
typename lang::ResolvingHandle<T>::HandleNavigator* lang::ResolvingHandle<T>::HandleNavigator::root()
{
    return next_ ? next_->root() : this;
}

template<typename T>
T* lang::ResolvingHandle<T>::HandleNavigator::get()
{
    HandleNavigator* root = this->root();
    return root->element_ ? root->element_ : root->owned_element_.get();
}

template<typename T>
std::unique_ptr<T> lang::ResolvingHandle<T>::HandleNavigator::take()
{
    auto root = this->root();
    assert(root->owned_element_);

    std::unique_ptr<T> taken = std::move(root->owned_element_);
    root->element_           = taken.get();

    return taken;
}

template<typename T>
void lang::ResolvingHandle<T>::HandleNavigator::target(std::shared_ptr<lang::ResolvingHandle<T>::HandleNavigator> next)
{
    owned_element_.reset();
    element_ = nullptr;

    next_ = next;
}

template<typename T, class... ARGS>
lang::ResolvingHandle<T> lang::makeHandled(ARGS&&... args)
{
    return ResolvingHandle<T>(std::make_unique<T>(std::forward<ARGS>(args)...));
}

template<typename SELF>
void lang::HandleTarget<SELF>::setSelf(lang::ResolvingHandle<SELF> handle)
{
    assert(!self_);
    self_ = std::make_optional<lang::ResolvingHandle<SELF>>(handle);
}

template<typename SELF>
lang::ResolvingHandle<SELF> lang::HandleTarget<SELF>::self() const
{
    assert(self_);
    return self_.value();
}

template<typename SELF>
bool lang::HandleTarget<SELF>::equalsTarget(SELF* other)
{
    return this == other;
}
