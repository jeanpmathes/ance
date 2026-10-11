#ifndef GENERATOR_UTILITY_STRINGS_H
#define GENERATOR_UTILITY_STRINGS_H

#include <string>

namespace utility
{
    std::string toUpperCase(std::string text);
    std::string toSnakeCase(std::string const& text);
}

#endif
