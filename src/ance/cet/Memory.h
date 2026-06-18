#ifndef ANCE_CET_MEMORY_H
#define ANCE_CET_MEMORY_H

#include <span>

#include "ance/utility/Owners.h"

namespace ance::bbt
{
    class TypeContext;
    class Type;
    class Value;
}

namespace ance::cet
{
    /// Represents an addressable memory location.
    class Memory
    {
    public:
        virtual ~Memory() = default;

      /// Access the memory, returning a reference to it.
      [[nodiscard]] virtual utility::Shared<bbt::Value> access() = 0;

        /// Read a value from the addressed memory location.
      /// \param indices Indices describing the target position inside the memory.
      [[nodiscard]] virtual utility::Shared<bbt::Value> read(std::span<size_t const> indices) = 0;

      /// Write a value to the addressed memory location.
      /// \param value The value to write.
      /// \param indices Indices describing the target position inside the memory.
        virtual void write(utility::Shared<bbt::Value> value, std::span<size_t const> indices) = 0;

      /// Check whether the memory currently stores a value.
        [[nodiscard]] virtual bool isDefined() const = 0;

        /// The type of the value stored in the memory location.
        [[nodiscard]] virtual bbt::Type const& type() const = 0;

      protected:
        /// \brief Load a value using a chain of indices.
        /// Read a value directly, or one of its elements or sub-elements as directed by a chain of indices.
        /// \param value The value to load from.
        /// \param indices The chain of indices to use.
        /// \param type_context The current type context.
        /// \returns The loaded value, or \c std::nullopt if any of the access operations failed.
        [[nodiscard]] static utility::Optional<utility::Shared<bbt::Value>> load(utility::Shared<bbt::Value> value,
                                                                                 std::span<size_t const>     indices,
                                                                                   bbt::TypeContext&           type_context);

        /// \brief Store a replacement value within another value, creating a modified value.
        /// Replace a value directly, or one of its elements or sub-elements as directed by a chain of indices.
        /// \param value The value to replace directly or partially.
        /// \param indices The chain of indices to use.
        /// \param replacement The replacing value, it must have the correct type.
        /// \param type_context The current type context.
        /// \returns The replaced value, or \c std::nullopt if any of the access operations failed.
        [[nodiscard]] static utility::Optional<utility::Shared<bbt::Value>> store(utility::Shared<bbt::Value> value,
                                                                                  std::span<size_t const>     indices,
                                                                                    utility::Shared<bbt::Value> replacement,
                                                                                    bbt::TypeContext&           type_context);
    };
}

#endif
