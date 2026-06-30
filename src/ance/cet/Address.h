#ifndef ANCE_CET_ADDRESS_H
#define ANCE_CET_ADDRESS_H

#include <functional>
#include <span>
#include <vector>

#include "ance/cet/Memory.h"

namespace ance::cet
{
    /// \brief Refers to a location within simulated compile-time memory.
    ///
    /// This address type only simulates addressing behavior and is only usable for BBT-based compile-time evaluation.
    /// Translating it to a machine address would not be trivial.
    class Address
    {
    public:
        explicit Address(Memory& memory, std::vector<size_t> indices = {});

      [[nodiscard]] Memory&                 memory() const;
      [[nodiscard]] std::span<size_t const> indices() const;

      /// Create an address which represents subscript-based access into this address.
      /// Note that this does not perform any validation whether the concerned values and types would support such an access.
        [[nodiscard]] Address subscript(size_t index) const;

        /// Read the value at the addressed location.
        [[nodiscard]] utility::Shared<bbt::Value const> read() const;

        /// Write a value to the addressed location.
        void write(utility::Shared<bbt::Value const> value) const;

        /// Check whether the addressed location is defined, i.e. has a value.
        [[nodiscard]] bool                        isDefined() const;

    private:
        std::reference_wrapper<Memory> memory_;
        std::vector<size_t>            indices_;
    };
}

#endif
