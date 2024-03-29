#ifndef ANCE_SRC_VALIDATION_STRINGS_H_
#define ANCE_SRC_VALIDATION_STRINGS_H_

#include <string>

/**
 * Trim a string view (removing spaces and tabs) and return the trimmed string view.
 * @param str The string view to trim.
 * @param start The index of the new string start in the old string is assigned to this.
 * @return The trimmed string view.
 */
std::string_view trim(std::string_view str, size_t& start);

/**
 * Estimate the printed width of a string view.
 * @param str The string view to estimate the width of.
 * @return The width, in number of occupied columns.
 */
size_t estimateWidth(std::string_view const& str);

#endif
