#ifndef ANCE_SRC_LANG_UTILITY_OWNERS_H_
#define ANCE_SRC_LANG_UTILITY_OWNERS_H_

#include <memory>

#include "lang/utility/Optional.h"

template<typename T>
class Owned;

template<typename T, class... ARGS>
Owned<T> makeOwned(ARGS&&... args);

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

    template<typename U>
        requires std::is_base_of_v<T, U>
    explicit(false) Owned(Owned<U>&& value) noexcept;// NOLINT(google-explicit-constructor)

    Owned<T>& operator=(Owned<T>&& value) noexcept;

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

    template<typename U>
    friend class Owned;

    template<typename U, class... ARGS>
    friend Owned<U> makeOwned(ARGS&&... args);

  private:
    std::unique_ptr<T> value_;
};

template<typename T, class... ARGS>
Owned<T> makeOwned(ARGS&&... args)
{
    return Owned<T>(std::make_unique<T>(std::forward<ARGS>(args)...));
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

template<typename T, class... ARGS>
Shared<T> makeShared(ARGS&&... args);

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

    template<typename U>
        requires std::is_base_of_v<T, U>
    explicit(false) Shared(Shared<U>&& value) noexcept;// NOLINT(google-explicit-constructor)

    template<typename U>
        requires std::is_base_of_v<T, U>
    explicit(false) Shared(Shared<U>& value) noexcept;// NOLINT(google-explicit-constructor)

    Shared<T>& operator=(Shared<T> value) noexcept;

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

    template<typename U>
    friend class Shared;

    template<typename U, class... ARGS>
    friend Shared<U> makeShared(ARGS&&... args);

  private:
    std::shared_ptr<T> value_;
};

template<typename T, class... ARGS>
Shared<T> makeShared(ARGS&&... args)
{
    return Shared<T>(std::make_shared<T>(std::forward<ARGS>(args)...));
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

    template<typename U>
        requires std::is_base_of_v<T, U>
    explicit(false) Passed(Passed<U>&& value) noexcept;// NOLINT(google-explicit-constructor)

    template<typename U>
        requires std::is_base_of_v<T, U>
    explicit(false) Passed(Passed<U>& value) noexcept;// NOLINT(google-explicit-constructor)

    Passed<T>& operator=(Passed<T> value) noexcept;

    T*       get();
    T const* get() const;

    T& operator*();
    T* operator->();

    T const& operator*() const;
    T const* operator->() const;

    template<typename U>
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
