#ifndef ANCE_SRC_LANG_UTILITY_OWNERS_H_
#define ANCE_SRC_LANG_UTILITY_OWNERS_H_

#include <memory>

#include "lang/utility/Optional.h"

template<typename T>
class Owned;

template<typename T, class... Args>
Owned<T> makeOwned(Args&&... args);

/**
 * Owns a value. Prefer this over std::unique_ptr.
 * @tparam T The type of the value.
 */
template<typename T>
class Owned
{
  public:
    explicit Owned(T& value);
    Owned(Owned<T>&& value) noexcept;

    template<typename OtherT>
        requires MoveConvertible<T*, OtherT*>
    explicit(false) Owned(Owned<OtherT>&& value) noexcept;// NOLINT(google-explicit-constructor)

    template<typename OtherT>
        requires CopyConvertible<T*, OtherT*>
    explicit(false) Owned(Owned<OtherT>& value) noexcept;// NOLINT(google-explicit-constructor)

    Owned<T>& operator=(Owned<T>&& value) noexcept;

    template<typename OtherT>
        requires MoveConvertible<T*, OtherT*>
    Owned<T>& operator=(Owned<OtherT>&& value) noexcept;

    template<typename OtherT>
        requires CopyConvertible<T*, OtherT*>
    Owned<T>& operator=(Owned<OtherT>& value) noexcept;

    static T* release(Owned<T>&& value);

  private:
    explicit Owned(std::unique_ptr<T>&& value);

  public:
    T*       get();
    T const* get() const;

    T& operator*();
    T* operator->();

    T const& operator*() const;
    T const* operator->() const;

    template<typename OtherT>
    friend class Owned;

    template<typename TargetT, class... Args>
    friend Owned<TargetT> makeOwned(Args&&... args);

  private:
    std::unique_ptr<T> value_;
};

template<typename T, class... Args>
Owned<T> makeOwned(Args&&... args)
{
    return Owned<T>(std::make_unique<T>(std::forward<Args>(args)...));
}

template<typename T>
Optional<Owned<T>> wrap(T* value)
{
    if (value) return Optional<Owned<T>>(Owned<T>(*value));
    return std::nullopt;
}

template<typename T>
T* getPtr(Optional<Owned<T>>& value)
{
    if (value.hasValue()) return value->get();
    return nullptr;
}

template<typename T>
T const* getPtr(Optional<Owned<T>> const& value)
{
    if (value.hasValue()) return value->get();
    return nullptr;
}

template<typename T>
T* unwrap(Owned<T>&& value)
{
    return Owned<T>::release(std::move(value));
}

template<typename T>
class Shared;

template<typename T, class... Args>
Shared<T> makeShared(Args&&... args);

/**
 * Shares a value. Prefer this over std::shared_ptr.
 * @tparam T The type of the value.
 */
template<typename T>
class Shared
{
  public:
    explicit Shared(T& value);
    Shared(Shared<T>&& value) noexcept;
    Shared(Shared<T>& value) noexcept;

    template<typename OtherT>
        requires MoveConvertible<T*, OtherT*>
    explicit(false) Shared(Shared<OtherT>&& value) noexcept;// NOLINT(google-explicit-constructor)

    template<typename OtherT>
        requires CopyConvertible<T*, OtherT*>
    explicit(false) Shared(Shared<OtherT>& value) noexcept;// NOLINT(google-explicit-constructor)

    Shared<T>& operator=(Shared<T> value) noexcept;

    template<typename OtherT>
        requires MoveConvertible<T*, OtherT*>
    Shared<T>& operator=(Shared<OtherT>&& value) noexcept;

    template<typename OtherT>
        requires CopyConvertible<T*, OtherT*>
    Shared<T>& operator=(Shared<OtherT>& value) noexcept;

    bool operator==(Shared<T> const& other) const noexcept;
    bool operator!=(Shared<T> const& other) const noexcept;

  private:
    explicit Shared(std::shared_ptr<T>&& value);

  public:
    T*       get();
    T const* get() const;

    T& operator*();
    T* operator->();

    T const& operator*() const;
    T const* operator->() const;

    template<typename OtherT>
    friend class Shared;

    template<typename TargetT, class... Args>
    friend Shared<TargetT> makeShared(Args&&... args);

    template<typename OtherT>
    Shared<OtherT> cast();

  private:
    std::shared_ptr<T> value_;
};

template<typename T, class... Args>
Shared<T> makeShared(Args&&... args)
{
    return Shared<T>(std::make_shared<T>(std::forward<Args>(args)...));
}

/**
 * A passed reference to a value. A use-case is when a class passes itself to an owned value.
 * @tparam T The type of the value.
 */
template<typename T>
class Passed
{
  public:
    explicit Passed(T& value);
    Passed(Passed<T>&& value) noexcept;
    Passed(Passed<T>& value) noexcept;

    template<typename OtherT>
        requires std::is_base_of_v<T, OtherT>
    explicit(false) Passed(Passed<OtherT>&& value) noexcept;// NOLINT(google-explicit-constructor)

    template<typename OtherT>
        requires std::is_base_of_v<T, OtherT>
    explicit(false) Passed(Passed<OtherT>& value) noexcept;// NOLINT(google-explicit-constructor)

    Passed<T>& operator=(Passed<T> value) noexcept;

    T*       get();
    T const* get() const;

    T& operator*();
    T* operator->();

    T const& operator*() const;
    T const* operator->() const;

    template<typename OtherT>
    friend class Passed;

  private:
    T& reference_;
};

template<typename T>
Passed<T> pass(T& value)
{
    return Passed<T>(value);
}

#include "Owners.tpp"

#endif
