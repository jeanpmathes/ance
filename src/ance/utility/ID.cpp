#include "ID.h"

namespace
{
    std::string encodeBase62(uint32_t value) {
        static constexpr char charset[] = R"(0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz)";
        std::string encoded;
        do {
            encoded.insert(encoded.begin(), charset[value % 62]);
            value /= 62;
        } while (value > 0);
        return encoded;
    }

    std::string insertDashes(const std::string& input) {
        std::string result;
        for (std::size_t i = 0; i < input.size(); i++) {
            if (i > 0 && i % 3 == 0) result += '-';
            result += input[i];
        }
        return result;
    }
}

std::string ance::utility::id(uint32_t const integer)
{
    std::string const base62 = encodeBase62(integer);
    std::string const grouped = insertDashes(base62);
    return "id-" + grouped;
}
