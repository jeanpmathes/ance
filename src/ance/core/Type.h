#ifndef ANCE_CORE_TYPE_H
#define ANCE_CORE_TYPE_H

#include "ance/core/Identifier.h"

namespace ance::core
{
    /// Unique identifier for a type, allowing more compact referencing.
    struct TypeID
    {
        uint32_t app;
        uint32_t id;
    };

    /// Represents a type.
    class Type
    {
        /// Creates a new type.
        /// \param identifier The identifier of the type.
        explicit Type(Identifier const& identifier);

        Type(const Type&) = delete;
        Type& operator=(const Type&) = delete;

        Type(Type&&) = delete;
        Type& operator=(Type&&) = delete;

      public:
        /// Gets the name of this type.
        [[nodiscard]] Identifier const& name() const;

        /// Get the boolean type, which has two values: true and false.
        static Type const& Bool();

        /// Get the unit type, which has one value: ().
        static Type const& Unit();

        /// Get the size type, which has a platform-dependent size.
        static Type const& Size();

        /// Get the string type.
        static Type const& String();

        /// Get the entity reference type, which is used to refer to entities.
        static Type const& EntityRef();

        /// Get the identifier type, which is the type of all identifiers.
        static Type const& Ident();

        /// Get the type-type - the type of all types.
        static Type const& Self();

        /// Get the scope type, which refers to scope values.
        static Type const& Scope();

        /// Get the source location type.
        static Type const& Location();

        /// Get a type by its ID.
        [[nodiscard]] static Type const& byID(TypeID const& id) ;

        /// Get the ID of this type.
        [[nodiscard]] TypeID id() const;

        bool operator==(Type const& other) const;
        bool operator!=(Type const& other) const;

      private:
        Identifier identifier_;
        uint32_t index_;
    };
}

std::ostream& operator<<(std::ostream& out, ance::core::Type const& type);

#endif
