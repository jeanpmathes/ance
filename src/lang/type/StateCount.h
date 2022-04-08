#ifndef ANCE_SRC_LANG_TYPE_STATECOUNT_H_
#define ANCE_SRC_LANG_TYPE_STATECOUNT_H_

#include <variant>

enum class SpecialCount
{
    /**
     * For types where states are not exact, and therefore hard to count.
     * One example are floating-point types.
     */
    UNCOUNTABLE,

    /**
     * For types where the exact state count is platform-dependent.
     */
    PLATFORM_DEPENDENT,

    /**
     * For types that represent something abstract.
     * One example are pointers.
     */
    ABSTRACT
};

using StateCount = std::variant<SpecialCount, size_t>;

#endif//ANCE_SRC_LANG_TYPE_STATECOUNT_H_
