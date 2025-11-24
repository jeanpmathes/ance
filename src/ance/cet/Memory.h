#ifndef ANCE_CET_MEMORY_H
#define ANCE_CET_MEMORY_H

#include <vector>

#include "ance/utility/Owners.h"

namespace ance::core
{
    class Type;
}

namespace ance::bbt
{
    class Value;
}

namespace ance::cet
{
    /// Represents an addressable memory location.
    class Memory
    {
    public:
        virtual ~Memory() = default;

        /// Access the memory. This will generally return a reference to it.
        [[nodiscard]] virtual utility::Shared<bbt::Value> access() = 0;

        /// Read a value from the addressed memory location.
        /// \param indices Indices describing the target position inside the memory.
        [[nodiscard]] virtual utility::Shared<bbt::Value> read(std::vector<size_t> const& indices) = 0;

        /// Write a value to the addressed memory location.
        /// \param value The value to write.
        /// \param indices Indices describing the target position inside the memory.
        virtual void write(utility::Shared<bbt::Value> value, std::vector<size_t> const& indices) = 0;

        /// Check whether the memory currently stores a value.
        [[nodiscard]] virtual bool isDefined() const = 0;
    };
}

#endif
