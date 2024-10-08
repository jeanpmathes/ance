#include "Strings.h"

#include <boost/locale/boundary.hpp>
#include <boost/locale/generator.hpp>
#include <boost/regex/v5/unicode_iterator.hpp>
#include <icu.h>

std::string_view trim(std::string_view str, size_t& start)
{
    if (str.empty()) return str;

    size_t begin = str.find_first_not_of(" \t");
    size_t end   = str.find_last_not_of(" \t");

    if (begin == std::string_view::npos) begin = 0;
    if (end == std::string_view::npos) end = str.size() - 1;

    start = begin;

    auto const range = end - begin + 1;
    return str.substr(begin, range);
}

size_t estimateWidth(std::string_view const& str)
{
    size_t width = 0;

    using SegmentIndex = boost::locale::boundary::segment_index<std::string_view::const_iterator>;
    SegmentIndex characters(boost::locale::boundary::character, str.cbegin(), str.cend());

    for (SegmentIndex::const_iterator char_it = characters.begin(); char_it != characters.end(); char_it++)
    {
        width++;

        std::string character = char_it->str();

        boost::u8_to_u32_iterator<std::string::iterator> code_point_it(character.begin());
        boost::u8_to_u32_iterator<std::string::iterator> code_point_end(character.end());
        if (code_point_it == code_point_end) continue;

        char32_t code_point = *code_point_it;

        int width_type = u_getIntPropertyValue(static_cast<UChar32>(code_point), UCHAR_EAST_ASIAN_WIDTH);
        if ((width_type == U_EA_FULLWIDTH) || (width_type == U_EA_WIDE)) { width++; }
    }

    return width;
}
