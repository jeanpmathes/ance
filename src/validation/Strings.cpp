#include "Strings.h"

std::string_view trim(std::string_view str, size_t& start)
{
    const auto begin = str.find_first_not_of(" \t");
    const auto end   = str.find_last_not_of(" \t");

    start = begin;

    const auto range = end - begin + 1;
    return str.substr(begin, range);
}
