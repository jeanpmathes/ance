#include "ResolvingHandle.h"

#include <cassert>

template<typename T>
lang::ResolvingHandle<T>::ResolvingHandle(Owned<T> handled)
    : navigator_(Shared<lang::HandleNavigator<typename lang::HandleConfig<T>::BaseType>>(
          *(new lang::HandleNavigator<typename lang::HandleConfig<T>::BaseType>(std::move(handled)))))
{}

template<typename T>
lang::ResolvingHandle<T>::ResolvingHandle(
    Shared<lang::HandleNavigator<typename lang::HandleConfig<T>::BaseType>> navigator)
    : navigator_(std::move(navigator))
{}

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
template<typename OtherT>
    requires MoveConvertible<T*, OtherT*>
lang::ResolvingHandle<T>::ResolvingHandle(lang::ResolvingHandle<OtherT>&& value) noexcept
    : navigator_(std::move(value.navigator_))
{}

template<typename T>
template<typename OtherT>
    requires CopyConvertible<T*, OtherT*>
lang::ResolvingHandle<T>::ResolvingHandle(lang::ResolvingHandle<OtherT>& value) noexcept : navigator_(value.navigator_)
{}

template<typename T>
template<typename OtherT>
    requires MoveConvertible<T*, OtherT*>
lang::ResolvingHandle<T>& lang::ResolvingHandle<T>::operator=(lang::ResolvingHandle<OtherT>&& value) noexcept
{
    navigator_ = std::move(value.navigator_);
    return *this;
}

template<typename T>
template<typename OtherT>
    requires CopyConvertible<T*, OtherT*>
lang::ResolvingHandle<T>& lang::ResolvingHandle<T>::operator=(lang::ResolvingHandle<OtherT>& value) noexcept
{
    navigator_ = value.navigator_;
    return *this;
}

template<typename T>
T* lang::ResolvingHandle<T>::get()
{
    auto result_base = navigator_->get();
    auto result      = dynamic_cast<T*>(result_base);

    assert(result != nullptr);

    return result;
}

template<typename T>
T const* lang::ResolvingHandle<T>::get() const
{
    auto result_base = navigator_->get();
    auto result      = dynamic_cast<T const*>(result_base);

    assert(result != nullptr);

    return result;
}

template<typename T>
Owned<T> lang::ResolvingHandle<T>::take()
{
    auto result_base         = navigator_->take();
    auto result_base_pointer = unwrap(std::move(result_base));
    auto result              = dynamic_cast<T*>(result_base_pointer);

    assert(result != nullptr);

    return Owned<T>(*result);
}

template<typename T>
void lang::ResolvingHandle<T>::reroute(lang::ResolvingHandle<T> target)
{
    if (getRootNavigator() != target.getRootNavigator()) { navigator_->navigator()->target(target.getRootNavigator()); }
}

template<typename T>
template<typename OtherT>
bool lang::ResolvingHandle<T>::is() const
{
    auto result_base = navigator_->get();
    auto result      = dynamic_cast<OtherT const*>(result_base);

    return result != nullptr;
}

template<typename T>
template<typename Destination>
Optional<lang::ResolvingHandle<Destination>> lang::ResolvingHandle<T>::as()
{
    if (this->template is<Destination>() == false) return std::nullopt;

    return Optional<lang::ResolvingHandle<Destination>>(lang::ResolvingHandle<Destination>(navigator_));
}

template<typename T>
template<typename Destination>
Destination const* lang::ResolvingHandle<T>::as() const
{
    if (this->template is<Destination>() == false) return nullptr;

    return dynamic_cast<Destination const*>(navigator_->get());
}

template<typename T>
typename lang::HandleConfig<T>::BaseType& lang::ResolvingHandle<T>::base()
{
    return *navigator_->get();
}

template<typename T>
typename lang::HandleConfig<T>::BaseType const& lang::ResolvingHandle<T>::base() const
{
    return *navigator_->get();
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
T const* lang::ResolvingHandle<T>::operator->() const noexcept
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
Shared<lang::HandleNavigator<typename lang::HandleConfig<T>::BaseType>> lang::ResolvingHandle<T>::getRootNavigator()
{
    Optional<Shared<lang::HandleNavigator<typename lang::HandleConfig<T>::BaseType>>> nav_root = navigator_->root();
    if (nav_root.hasValue()) navigator_ = nav_root.value();// Shorten the chain.
    return navigator_;
}

template<typename T>
bool lang::ResolvingHandle<T>::operator==(ResolvingHandle<T> const& other) const
{
    auto const* target       = navigator_->get();
    auto const* other_target = other.navigator_->get();

    return target == other_target;
}

template<typename T>
bool lang::ResolvingHandle<T>::operator!=(lang::ResolvingHandle<T> const& other) const
{
    return not operator==(other);
}

template<typename T>
bool lang::ResolvingHandle<T>::operator<(lang::ResolvingHandle<T> const& other) const
{
    auto const* target       = navigator_->get();
    auto const* other_target = other.navigator_->get();

    return target < other_target;
}

template<typename T>
lang::HandleNavigator<T>::HandleNavigator(Shared<HandleNavigator> next) : next_(next)
{}

template<typename T>
lang::HandleNavigator<T>::HandleNavigator(Owned<T> element)
    : owned_element_(std::move(element))
    , element_(owned_element_.value().get())
{}

template<typename T>
Optional<Shared<typename lang::HandleNavigator<T>>> lang::HandleNavigator<T>::root()
{
    auto root = next_;

    if (root.hasValue())
    {
        auto next_root = root.value()->root();
        if (next_root.hasValue()) root = next_root;
    }

    return root;
}

template<typename T>
typename lang::HandleNavigator<T>* lang::HandleNavigator<T>::navigator()
{
    HandleNavigator* nav = this;

    auto potential_nav = this->root();
    if (potential_nav.hasValue()) nav = potential_nav.value().get();

    return nav;
}

template<typename T>
typename lang::HandleNavigator<T> const* lang::HandleNavigator<T>::root() const
{
    return next_.hasValue() ? next_.value()->root() : this;
}

template<typename T>
T* lang::HandleNavigator<T>::get()
{
    return navigator()->element_;
}

template<typename T>
T const* lang::HandleNavigator<T>::get() const
{
    HandleNavigator const* root = this->root();
    return root->element_;
}

template<typename T>
Owned<T> lang::HandleNavigator<T>::take()
{
    HandleNavigator* root = navigator();
    assert(root->owned_element_.hasValue());

    Owned<T> taken       = std::move(root->owned_element_.value());
    root->owned_element_ = {};

    return taken;
}

template<typename T>
void lang::HandleNavigator<T>::target(Shared<lang::HandleNavigator<T>> next)
{
    owned_element_ = {};
    element_       = nullptr;

    next_ = next;
}

template<typename T>
void lang::ResolvingHandle<T>::invalidate(T const* element)
{
    using BaseType               = typename HandleConfig<T>::BaseType;
    BaseType const* element_base = element;

    auto*           root           = navigator_->navigator();
    BaseType const* actual_element = root->get();

    if (actual_element != element_base) return;

    bool valid = root->owned_element_.hasValue() or root->element_ != nullptr;

    assert(valid);
    assert(!root->owned_element_.hasValue());

    root->element_       = nullptr;
    root->owned_element_ = {};
}

template<typename T>
lang::ResolvingHandle<T> lang::wrapHandled(Owned<T>&& element)
    requires std::derived_from<T, HandleTarget<T>>
{
    auto handle = ResolvingHandle<T>(std::move(element));

    handle->setSelf(handle);

    return handle;
}

template<typename T, class... Args>
lang::ResolvingHandle<T> lang::makeHandled(Args&&... args)
    requires std::derived_from<T, HandleTarget<T>>
{
    return wrapHandled<T>(makeOwned<T>(std::forward<Args>(args)...));
}

template<typename Self>
void lang::HandleTarget<Self>::setSelf(lang::ResolvingHandle<Self> handle)
{
    assert(not self_.hasValue());
    self_ = makeOptional<lang::ResolvingHandle<Self>>(handle);
}

template<typename Self>
lang::ResolvingHandle<Self> lang::HandleTarget<Self>::self()
{
    assert(self_.hasValue());
    return self_.value();
}

template<typename Self>
Self const& lang::HandleTarget<Self>::self() const
{
    assert(self_.hasValue());
    return self_.value();
}
