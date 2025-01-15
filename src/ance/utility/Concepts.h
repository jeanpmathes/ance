#ifndef ANCE_UTILITY_CONCEPTS_H
#define ANCE_UTILITY_CONCEPTS_H

#include <utility>
#include <concepts>

namespace ance::utility
{
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

    template<typename T>
    concept ConstCopyable = requires(T const t, T u) {
        T(t);
        u = t;
    };

    template<typename T, typename OtherT>
    concept MoveConvertible = !std::is_same_v<T, OtherT> and requires(T t, OtherT u) {
        T(std::move(u));
        t = std::move(u);
    };

    template<typename T, typename OtherT>
    concept CopyConvertible = !std::is_same_v<T, OtherT> and requires(T t, OtherT u) {
        T(u);
        t = u;
    };

    template<typename T, typename OtherT>
    concept ConstCopyConvertible = !std::is_same_v<T, OtherT> and requires(T const& t, OtherT u) {
        T(u);
        u = t;
    };
}

#endif
