#ifndef ANCE_CORE_IDENTIFIER_H
#define ANCE_CORE_IDENTIFIER_H

#include <ostream>
#include <string>
#include <string_view>

#include "Location.h"

class Storage;

namespace ance::core
{
    /// Represents a name, written it code. The text is interned.
    /// Every identifier has a code location attached, the location is however ignored for maps and sets.
    class Identifier
    {
        Identifier(std::string_view string, Location const& location);

      public:
        Identifier(Identifier const& other) = default;
        Identifier(Identifier&& other)      = default;

        Identifier& operator=(Identifier const& other) = default;
        Identifier& operator=(Identifier&& other)      = default;

        /// Create an identifier and intern the string.
        /// \param string The text of the identifier.
        /// \param location The location of the identifier.
        /// \return The identifier.
        static Identifier make(std::string const& string, Location location = Location::global());

        /// Create an empty identifier.
        /// \return The empty identifier.
        static Identifier empty();

        [[nodiscard]] std::string_view text() const;
        [[nodiscard]] Location         location() const;
        [[nodiscard]] bool             isEmpty() const;

        std::weak_ordering operator<=>(Identifier const& other) const;

      private:
        std::string_view string_;
        Location         location_;
    };
}

std::ostream& operator<<(std::ostream& os, ance::core::Identifier const& identifier);

std::string operator+(std::string const& str, ance::core::Identifier const& identifier);
std::string operator+(ance::core::Identifier const& identifier, std::string const& str);

std::string operator+(char const* str, ance::core::Identifier const& identifier);
std::string operator+(ance::core::Identifier const& identifier, char const* str);

#endif
