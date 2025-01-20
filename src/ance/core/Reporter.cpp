#include "Reporter.h"

#include <vector>

#include <boost/locale/encoding_utf.hpp>
#include <boost/locale/boundary/index.hpp>
#include <boost/regex/v5/unicode_iterator.hpp>
#include <icu.h>

#include "ance/sources/SourceTree.h"

namespace ansi
{
    inline auto ColorRed    = "\x1B[31m";
    inline auto ColorYellow = "\x1B[33m";

    inline auto ColorReset = "\x1B[0m";
}

namespace text
{
    static std::u32string_view trim(std::u32string_view const str, size_t& start)
    {
        if (str.empty())
            return str;

        size_t begin = str.find_first_not_of(U" \t");
        size_t end   = str.find_last_not_of(U" \t");

        if (begin == std::u32string_view::npos) begin = 0;
        if (end == std::u32string_view::npos) end = str.size() - 1;

        start = begin;

        auto const range = end - begin + 1;
        return str.substr(begin, range);
    }

    static size_t estimateWidth(std::u32string_view const& str)
    {
        size_t width = 0;

        std::string const utf8_str = boost::locale::conv::utf_to_utf<char>(std::u32string(str));

        using SegmentIndex = boost::locale::boundary::segment_index<std::string::const_iterator>;
        SegmentIndex const characters(boost::locale::boundary::character, utf8_str.cbegin(), utf8_str.cend());

        for (auto char_it = characters.begin(); char_it != characters.end(); ++char_it)
        {
            width += 1;

            std::string character = char_it->str();

            boost::u8_to_u32_iterator<std::string::iterator> const code_point_it(character.begin());
            boost::u8_to_u32_iterator<std::string::iterator> const code_point_end(character.end());
            if (code_point_it == code_point_end) continue;

            char32_t const code_point = *code_point_it;

            int const width_type = u_getIntPropertyValue(static_cast<UChar32>(code_point), UCHAR_EAST_ASIAN_WIDTH);
            if ((width_type == U_EA_FULLWIDTH) || (width_type == U_EA_WIDE)) { width += 1; }
        }

        return width;
    }
}

struct ance::core::Reporter::Implementation {
    enum class Level
    {
        WARNING,
        ERROR
    };

    struct Entry {
        Level    level_;
        Location location_;

        std::string message_;

        Entry(Level const level, std::string message, Location const& location)
            : level_(level)
            , location_(location)
            , message_(std::move(message))
        {}
    };

    void report(Level level, std::string const& message, Location location)
    {
        if (level == Level::ERROR) error_count_++;

        if (level == Level::WARNING) warning_count_++;

        entries_.emplace_back(level, message, location);
    }

    void emit(sources::SourceTree& source_tree, std::ostream& out) const
    {
        out << "ance: " << warningCount() << " warnings, " << errorCount() << " errors" << std::endl;

        for (auto& entry : entries_)
        {
            size_t start = 0;

            out << "ance: ";

            switch (entry.level_)
            {
                case Level::ERROR:
                    out << ansi::ColorRed << "error" << ansi::ColorReset << ": ";
                    break;
                case Level::WARNING:
                    out << ansi::ColorYellow << "warning" << ansi::ColorReset << ": ";
                    break;
            }

            if (entry.location_.isGlobal())
            {
                out << entry.message_ << std::endl;
                out << std::endl;
                continue;
            }

            sources::SourceFile const& source_file = source_tree.getFile(entry.location_.file());

            out << source_file.getRelativePath().generic_string() << " ";
            out << entry.location_ << " " << entry.message_ << std::endl;
            out << std::endl;

            std::u32string_view const line_view = text::trim(source_file.getLine(entry.location_.line()), start);
            out << '\t' << boost::locale::conv::utf_to_utf<char>(std::u32string(line_view)) << std::endl;

            if (entry.location_.isSingleLine())
            {
                size_t const length_to_mark = entry.location_.column() - start - 1;
                size_t const length_of_mark = entry.location_.columnEnd() - entry.location_.column() + 1;

                std::u32string_view const text_to_mark = line_view.substr(0, length_to_mark);
                std::u32string_view const text_with_mark = length_to_mark >= line_view.size() ? U"" : line_view.substr(length_to_mark, length_of_mark);

                size_t const missing_to_mark   = length_to_mark - text_to_mark.size();
                size_t const missing_with_mark = length_of_mark - text_with_mark.size();

                size_t const marker_start  = std::max(text::estimateWidth(text_to_mark) + missing_to_mark, 1uz);
                size_t const marker_length = std::max(text::estimateWidth(text_with_mark) + missing_with_mark, 1uz);

                out << '\t' << std::string(marker_start, ' ') << std::string(marker_length, '~') << std::endl;
                out << std::endl;
            }
        }
    }

    [[nodiscard]] size_t errorCount() const { return error_count_; }
    [[nodiscard]] size_t warningCount() const { return warning_count_; }

  private:
    std::vector<Entry> entries_;

    size_t error_count_   = 0;
    size_t warning_count_ = 0;
};

ance::core::Reporter::Reporter() : implementation_(utility::makeOwned<Implementation>()) {}

ance::core::Reporter::~Reporter() = default;

void ance::core::Reporter::warning(std::string const& message, Location const& location)
{
    implementation_->report(Implementation::Level::WARNING, message, location);
}

void ance::core::Reporter::error(std::string const& message, Location const& location)
{
    implementation_->report(Implementation::Level::ERROR, message, location);
}

void ance::core::Reporter::emit(sources::SourceTree& source_tree, std::ostream& out) const
{
    implementation_->emit(source_tree, out);
}

size_t ance::core::Reporter::errorCount() const
{
    return implementation_->errorCount();
}
size_t ance::core::Reporter::warningCount() const
{
    return implementation_->warningCount();
}
