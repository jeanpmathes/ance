#ifndef ANCE_UTILITY_CONTAINERS_H
#define ANCE_UTILITY_CONTAINERS_H

#include <vector>

namespace ance::utility
{
    /**
     * A list of elements.
     * @tparam T The type of the elements.
     */
    template<typename T>
    using List = std::vector<T>;
}

#endif
