#include "ResolvingHandle.h"

#include <cassert>

template<typename T>
lang::ResolvingHandle<T>::ResolvingHandle(Owned<T> handled)
    : navigator_(Shared<lang::ResolvingHandle<T>::HandleNavigator>(
        *(new lang::ResolvingHandle<T>::HandleNavigator(std::move(handled)))))
{
    if (navigator_->get() == nullptr) return;

    (*this)->setSelf(*this);
}

template<typename T>
lang::ResolvingHandle<T>::ResolvingHandle(lang::ResolvingHandle<T>&& value) noexcept
    : navigator_(std::move(value.navigator_))
{}

template<typename T>
lang::ResolvingHandle<T>::ResolvingHandle(lang::ResolvingHandle<T>& value) noexcept : navigator_(value.navigator_)
{}

template<typename T>
lang::ResolvingHandle<T>& lang::ResolvingHandle<T>::operator=(lang::ResolvingHandle<T> value) noexcept
{
    std::swap(navigator_, value.navigator_);
    return *this;
}

template<typename T>
T* lang::ResolvingHandle<T>::get()
{
    return navigator_->get();
}

template<typename T>
T const* lang::ResolvingHandle<T>::get() const
{
    return navigator_->get();
}

template<typename T>
Owned<T> lang::ResolvingHandle<T>::take()
{
    return navigator_->take();
}

template<typename T>
void lang::ResolvingHandle<T>::reroute(lang::ResolvingHandle<T> target)
{
    if (getRootNavigator() != target.getRootNavigator()) { navigator_->root()->target(target.getRootNavigator()); }
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
T const& lang::ResolvingHandle<T>::operator*() const noexcept
{
    return *get();
}

template<typename T>
lang::ResolvingHandle<T>::operator T&() noexcept
{
    return *get();
}

template<typename T>
lang::ResolvingHandle<T>::operator T const&() const noexcept
{
    return *get();
}

template<typename T>
Shared<typename lang::ResolvingHandle<T>::HandleNavigator> lang::ResolvingHandle<T>::getRootNavigator()
{
    Optional<Shared<HandleNavigator>> nav_root = navigator_->sRoot();
    if (!nav_root.hasValue()) nav_root = navigator_;

    return nav_root.value();
}

template<typename T>
bool lang::ResolvingHandle<T>::operator==(ResolvingHandle<T> const& other) const
{
    T const* target       = get();
    T const* other_target = other.get();

    return target->equalsTarget(other_target);
}

template<typename T>
bool lang::ResolvingHandle<T>::operator!=(lang::ResolvingHandle<T> const& other) const
{
    T const* target       = get();
    T const* other_target = other.get();

    return not target->equalsTarget(other_target);
}

template<typename T>
bool lang::ResolvingHandle<T>::operator<(lang::ResolvingHandle<T> const& other) const
{
    T const* target       = get();
    T const* other_target = other.get();

    return target < other_target;
}

template<typename T>
lang::ResolvingHandle<T>::HandleNavigator::HandleNavigator(Shared<HandleNavigator> next) : next_(next)
{}

template<typename T>
lang::ResolvingHandle<T>::HandleNavigator::HandleNavigator(Owned<T> element) : owned_element_(std::move(element))
{}

template<typename T>
Optional<Shared<typename lang::ResolvingHandle<T>::HandleNavigator>> lang::ResolvingHandle<T>::HandleNavigator::sRoot()
{
    if (next_.hasValue())
    {
        Optional<Shared<HandleNavigator>> potential_root = next_.value()->sRoot();

        if (potential_root.hasValue()) { next_ = potential_root; }

        return next_;
    }
    else { return {}; }
}

template<typename T>
typename lang::ResolvingHandle<T>::HandleNavigator* lang::ResolvingHandle<T>::HandleNavigator::root()
{
    return next_.hasValue() ? next_.value()->root() : this;
}

template<typename T>
typename lang::ResolvingHandle<T>::HandleNavigator const* lang::ResolvingHandle<T>::HandleNavigator::root() const
{
    return next_.hasValue() ? next_.value()->root() : this;
}

template<typename T>
T* lang::ResolvingHandle<T>::HandleNavigator::get()
{
    HandleNavigator* root = this->root();
    return root->element_ ? root->element_ : root->owned_element_->get();
}

template<typename T>
T const* lang::ResolvingHandle<T>::HandleNavigator::get() const
{
    HandleNavigator const* root = this->root();
    return root->element_ ? root->element_ : root->owned_element_->get();
}

template<typename T>
Owned<T> lang::ResolvingHandle<T>::HandleNavigator::take()
{
    auto root = this->root();
    assert(root->owned_element_.hasValue());

    Owned<T> taken = std::move(root->owned_element_.value());

    root->owned_element_ = {};
    root->element_       = taken.get();

    return taken;
}

template<typename T>
void lang::ResolvingHandle<T>::HandleNavigator::target(Shared<lang::ResolvingHandle<T>::HandleNavigator> next)
{
    owned_element_ = {};
    element_       = nullptr;

    next_ = next;
}

template<typename T>
void lang::ResolvingHandle<T>::invalidate(T const* element)
{
    assert(valid());

    HandleNavigator* root = navigator_->root();

    assert(!root->owned_element_.hasValue());

    T const* actual_element = root->get();

    if (actual_element != element) return;

    root->element_       = nullptr;
    root->owned_element_ = {};
}

template<typename T>
bool lang::ResolvingHandle<T>::valid() const
{
    HandleNavigator const* root = navigator_->root();
    return root->owned_element_.hasValue() or root->element_ != nullptr;
}

template<typename T, class... ARGS>
lang::ResolvingHandle<T> lang::makeHandled(ARGS&&... args)
{
    return ResolvingHandle<T>(makeOwned<T>(std::forward<ARGS>(args)...));
}

template<typename SELF>
void lang::HandleTarget<SELF>::setSelf(lang::ResolvingHandle<SELF> handle)
{
    assert(not self_.hasValue());
    self_ = makeOptional<lang::ResolvingHandle<SELF>>(handle);
}

template<typename SELF>
lang::ResolvingHandle<SELF> lang::HandleTarget<SELF>::self()
{
    assert(self_.hasValue());
    return self_.value();
}

template<typename SELF>
SELF const& lang::HandleTarget<SELF>::self() const
{
    assert(self_.hasValue());
    return self_.value();
}

template<typename SELF>
bool lang::HandleTarget<SELF>::equalsTarget(SELF const* other) const
{
    return this == other;
}
