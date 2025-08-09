#ifndef ANCE_SRC_LANG_UTILITY_OPTIONAL_H
#define ANCE_SRC_LANG_UTILITY_OPTIONAL_H

#include <optional>
#include <array>

#include "Concepts.h"

namespace ance::utility
{

    /// A custom optional that does not require a non-const copy constructor.
    /// @tparam T The type of the optional.

    template<Moveable T>
    class Optional
    {
      public:
        Optional();

        explicit(false) Optional(std::nullopt_t);
        explicit(false) Optional(T const& value)
            requires ConstCopyable<T>;
        explicit(false) Optional(T value)
            requires(!ConstCopyable<T> and Copyable<T>);
        explicit(false) Optional(T&& value)
            requires(!ConstCopyable<T> and !Copyable<T>);

        Optional<T>& operator=(T value);

        template<typename OtherT>
        requires ConstCopyConvertible<T, OtherT>
        explicit(false) Optional(OtherT const& value);
        template<typename OtherT>
        requires(!ConstCopyConvertible<T, OtherT> and CopyConvertible<T, OtherT>)
        explicit(false) Optional(OtherT& value);
        template<typename OtherT>
        requires MoveConvertible<T, OtherT>
        explicit(false) Optional(OtherT&& value);

        Optional(Optional<T> const& optional)
            requires ConstCopyable<T>;
        Optional(Optional<T>& optional)
            requires(!ConstCopyable<T> and Copyable<T>);
        Optional(Optional<T>&& optional) noexcept;

        template<typename OtherT>
            requires ConstCopyConvertible<T, OtherT>
        explicit(false) Optional(Optional<OtherT> const& optional);

        template<typename OtherT>
            requires(!ConstCopyConvertible<T, OtherT> and CopyConvertible<T, OtherT>)
        explicit(false) Optional(Optional<OtherT>& optional);

        template<typename OtherT>
            requires MoveConvertible<T, OtherT>
        explicit(false) Optional(Optional<OtherT>&& optional);

        template<typename OtherT>
            requires MoveConvertible<T, OtherT>
        explicit(false) Optional(Optional<OtherT> optional);

        Optional<T>& operator=(Optional<T> optional)
            requires Copyable<T>;
        Optional<T>& operator=(Optional<T>&& optional) noexcept
            requires(!Copyable<T>);
        template<typename OtherT>
            requires MoveConvertible<T, OtherT>
        Optional<T>& operator=(Optional<OtherT>&& optional);
        template<typename OtherT>
            requires CopyConvertible<T, OtherT>
        Optional<T>& operator=(Optional<OtherT>& optional);

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
        [[nodiscard]] T& valueOr(T& default_value)
            requires(!Copyable<T>);
        [[nodiscard]] T const& valueOr(T const& default_value) const
            requires(!Copyable<T>);

        template<Moveable>
        friend class Optional;

        operator std::optional<T>()
            requires Copyable<T>;

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
}

#include "Optional.tpp"

#endif
