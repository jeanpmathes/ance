#ifndef ANCE_SRC_LANG_TYPE_STATECOUNT_H_
#define ANCE_SRC_LANG_TYPE_STATECOUNT_H_

#include <variant>

#include "lang/utility/Optional.h"

enum class SpecialCount
{
    /**
     * For types where the exact state count is platform-dependent, but countable.
     */
    PLATFORM_DEPENDENT,

    /**
     * For types where states are not exact, and therefore hard to count.
     * One example are floating-point types.
     */
    UNCOUNTABLE,

    /**
     * For types that represent something abstract, which means counting does not make sense.
     * One example are pointers.
     */
    ABSTRACT
};

class StateCount
{
  public:
    StateCount(size_t count);      // NOLINT(google-explicit-constructor)
    StateCount(SpecialCount count);// NOLINT(google-explicit-constructor)

    constexpr StateCount() = default;

    [[nodiscard]] Optional<size_t>       count() const;
    [[nodiscard]] Optional<SpecialCount> special() const;

    [[nodiscard]] bool isUnit() const;

    /**
     * Whether this state count is countable. Matching of these is simple.
     * Note that uncountable types that are not abstract are still matchable.
     */
    [[nodiscard]] bool isCountable() const;

    /**
     * Whether this state count is abstract. Matching of these is not possible.
     */
    [[nodiscard]] bool isAbstract() const;

    StateCount operator+(StateCount const& other) const;
    StateCount operator*(StateCount const& other) const;

    static StateCount unit();

  private:
    std::variant<SpecialCount, size_t> count_;
};

#endif
