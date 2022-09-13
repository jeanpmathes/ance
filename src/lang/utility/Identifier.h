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
        /**
         * Create an identifier and intern the string.
         * @param string The text of the identifier.
         * @return The identifier.
         */
        static Identifier from(const std::string& string, lang::Location location = lang::Location::global());

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
        bool operator()(const lang::Identifier& lhs, const lang::Identifier& rhs) const
        {
            return lhs.text() < rhs.text();
        }
    };
}

std::ostream& operator<<(std::ostream& os, const lang::Identifier& identifier);

std::string operator+(const std::string& str, const lang::Identifier& identifier);
std::string operator+(const lang::Identifier& identifier, const std::string& str);

std::string operator+(const char* str, const lang::Identifier& identifier);
std::string operator+(const lang::Identifier& identifier, const char* str);

#endif

