#include "utility/Strings.h"

#include <algorithm>
#include <cctype>

namespace utility
{
    std::string toUpperCase(std::string text)
    {
        std::ranges::transform(text, text.begin(), [](char const character) {
            return static_cast<char>(std::toupper(static_cast<unsigned char>(character)));
        });

        return text;
    }

    std::string toSnakeCase(std::string const& text)
    {
        std::string result;

        for (std::size_t index = 0; index < text.size(); ++index)
        {
            char const character = text[index];
            if (std::isupper(static_cast<unsigned char>(character)))
            {
                if (index > 0)
                {
                    char const previous = text[index - 1];
                    bool const next_is_lower =
                        index + 1 < text.size()
                        && std::islower(static_cast<unsigned char>(text[index + 1]));

                    if (std::islower(static_cast<unsigned char>(previous))
                        || next_is_lower)
                    {
                        result += '_';
                    }
                }
                result += static_cast<char>(
                    std::tolower(static_cast<unsigned char>(character))
                );
            }
            else
            {
                result += character;
            }
        }

        return result;
    }
}
