#ifndef ANCE_SRC_LANG_UTILITY_OPTIONAL_H_
#define ANCE_SRC_LANG_UTILITY_OPTIONAL_H_

#include <array>
#include <optional>

template<typename T>
concept Moveable = requires(T t, T u) {
                       T(std::move(t));
                       t = std::move(u);
                   };

template<typename T>
concept Copyable = requires(T t, T u) {
                       T(t);
                       t = u;
                   };

/**
 * A custom optional that does not require a non-const copy constructor.
 * @tparam T The type of the optional.
 */
template<Moveable T>
class Optional
{
  public:
    Optional();
    explicit(false) Optional(std::nullopt_t);// NOLINT(google-explicit-constructor)
    explicit(false) Optional(T value)
        requires Copyable<T>;// NOLINT(google-explicit-constructor)
    explicit(false) Optional(T&& value)
        requires(!Copyable<T>);// NOLINT(google-explicit-constructor)
    Optional<T>& operator=(T value);

    Optional(Optional<T>& optional)
        requires Copyable<T>;
    Optional(Optional<T>&& optional) noexcept;

    Optional<T>& operator=(Optional<T> optional)
        requires Copyable<T>;
    Optional<T>& operator=(Optional<T>&& optional) noexcept
        requires(!Copyable<T>);

    ~Optional();

    [[nodiscard]] bool hasValue() const;

    [[nodiscard]] T&       value();
    [[nodiscard]] T const& value() const;

    [[nodiscard]] T&       operator*();
    [[nodiscard]] T const& operator*() const;

    [[nodiscard]] T*       operator->();
    [[nodiscard]] T const* operator->() const;

    [[nodiscard]] T valueOr(T default_value)
        requires Copyable<T>;
    [[nodiscard]] T&       valueOr(T& default_value);
    [[nodiscard]] T const& valueOr(T const& default_value) const;

  private:
    alignas(T) std::array<std::byte, sizeof(T)> storage_ {};
    bool has_value_ {false};
};

template<typename T>
Optional<std::decay_t<T>> makeOptional(T&& value)
{
    return Optional<std::decay_t<T>>(std::forward<T>(value));
}

template<typename T, class... ARGS>
Optional<T> makeOptional(ARGS&&... args)
{
    return Optional<T>(T(std::forward<ARGS>(args)...));
}

#include "Optional.tpp"

#endif
