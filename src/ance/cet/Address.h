#ifndef ANCE_CET_ADDRESS_H
#define ANCE_CET_ADDRESS_H

#include <functional>
#include <vector>

#include "ance/cet/Memory.h"

namespace ance::cet
{
    /// Refers to a location within memory.
    class Address
    {
    public:
        explicit Address(Memory& memory, std::vector<size_t> indices = {});

        [[nodiscard]] Memory&                     memory() const;
        [[nodiscard]] std::vector<size_t> const&  indices() const;
        void                                      append(std::vector<size_t> const& indices);

        /// Read the value at the addressed location.
        [[nodiscard]] utility::Shared<bbt::Value> read() const;

        /// Write a value to the addressed location.
        void                                      write(utility::Shared<bbt::Value> value) const;

        /// Check whether the addressed location is defined, i.e. has a value.
        [[nodiscard]] bool                        isDefined() const;

    private:
        std::reference_wrapper<Memory> memory_;
        std::vector<size_t>            indices_;
    };
}

#endif
