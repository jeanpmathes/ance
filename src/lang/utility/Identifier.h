#ifndef ANCE_SRC_LANG_UTILITY_IDENTIFIER_H_
#define ANCE_SRC_LANG_UTILITY_IDENTIFIER_H_

#include <ostream>
#include <string>
#include <string_view>

#include "lang/utility/Location.h"

namespace lang
{
    /**
     * Represents a name, written it code. The text is interned.
     * Every identifier has a code location attached, the location is however ignored for maps and sets.
     */
    class Identifier
    {
      private:
        Identifier(std::string_view string, lang::Location location);

      public:
        Identifier(Identifier const& other) = default;
        Identifier(Identifier&& other)      = default;

        Identifier& operator=(Identifier const& other) = default;
        Identifier& operator=(Identifier&& other)      = default;

        /**
         * Create an identifier and intern the string.
         * @param string The text of the identifier.
         * @return The identifier.
         */
        static Identifier like(std::string const& string, lang::Location location = lang::Location::global());

        [[nodiscard]] std::string_view text() const;
        [[nodiscard]] lang::Location   location() const;

      private:
        std::string_view string_;
        lang::Location   location_;
    };
}

namespace std
{
    template<>
    struct less<lang::Identifier> {
        bool operator()(lang::Identifier const& lhs, lang::Identifier const& rhs) const
        {
            return lhs.text() < rhs.text();
        }
    };
}

std::ostream& operator<<(std::ostream& os, lang::Identifier const& identifier);

std::string operator+(std::string const& str, lang::Identifier const& identifier);
std::string operator+(lang::Identifier const& identifier, std::string const& str);

std::string operator+(char const* str, lang::Identifier const& identifier);
std::string operator+(lang::Identifier const& identifier, char const* str);

#endif
