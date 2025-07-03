#ifndef ANCE_UTILITY_ID_H
#define ANCE_UTILITY_ID_H

#include <string>

namespace ance::utility
{
    std::string id(uint32_t integer);

    /// Generate a nice ID from a pointer.
    /// The same pointer will always result in the same ID, different pointers give different IDs.
    template<typename T>
    std::string id(const T* ptr) {
        return id(static_cast<uint32_t>(reinterpret_cast<uintptr_t>(ptr) & 0xFFFFFFFF));
    }
}

#endif
