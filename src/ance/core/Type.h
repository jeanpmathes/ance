#ifndef ANCE_CORE_TYPE_H
#define ANCE_CORE_TYPE_H

#include "ance/core/Identifier.h"

namespace ance::core
{
    /// Represents a type.
    class Type
    {
        /// Creates a new type.
        /// \param identifier The identifier of the type.
        explicit Type(Identifier const& identifier);

      public:
        /// Gets the name of this type.
        [[nodiscard]] Identifier const& name() const;

        /// Get the boolean type, which has two values: true and false.
        static Type const& Bool();

        /// Get the unit type, which has one value: ().
        static Type const& Unit();

        /// Get the size type, which has a platform-dependent size.
        static Type const& Size();

        bool operator==(Type const& other) const;
        bool operator!=(Type const& other) const;

      private:
        Identifier identifier_;
    };
}

std::ostream& operator<<(std::ostream& out, ance::core::Type const& type);

#endif
