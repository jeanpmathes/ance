#include "Reporter.h"

#include <vector>

#include <boost/locale/boundary/index.hpp>
#include <boost/locale/encoding_utf.hpp>
#include <boost/regex/v5/unicode_iterator.hpp>

#include <icu.h>

#include "ance/sources/SourceTree.h"

namespace ansi
{
    inline auto ColorRed    = "\x1B[31m";
    inline auto ColorYellow = "\x1B[33m";
    inline auto ColorBlue   = "\x1B[34m";

    inline auto ColorReset = "\x1B[0m";
}

namespace text
{
    static std::u32string_view trim(std::u32string_view const str, size_t& start)
    {
        if (str.empty()) return str;

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
        if (str.empty()) return 0;

        size_t width = 0;

        std::string const utf8_str = boost::locale::conv::utf_to_utf<char>(std::u32string(str));

        using SegmentIndex = boost::locale::boundary::segment_index<std::string::const_iterator>;
        SegmentIndex const characters(boost::locale::boundary::character, utf8_str.cbegin(), utf8_str.cend());

        for (auto char_it = characters.begin(); char_it != characters.end(); ++char_it)
        {
            width += 1;

            std::string character = char_it->str();

            boost::u8_to_u32_iterator const code_point_it(character.begin());
            boost::u8_to_u32_iterator const code_point_end(character.end());
            if (code_point_it == code_point_end) continue;

            char32_t const code_point = *code_point_it;

            int const width_type = u_getIntPropertyValue(static_cast<UChar32>(code_point), UCHAR_EAST_ASIAN_WIDTH);
            if ((width_type == U_EA_FULLWIDTH) || (width_type == U_EA_WIDE))
            {
                width += 1;
            }
        }

        return width;
    }
}

struct ance::core::Reporter::Implementation
{
    enum class Level
    {
        INFO,
        WARNING,
        ERROR
    };

    struct Entry
    {
        Level    level_;
        Location location_;

        std::string message_;

        Entry(Level const level, std::string message, Location const& location) : level_(level), location_(location), message_(std::move(message)) {}
    };

    Implementation(sources::SourceTree& source_tree, std::ostream& out) : source_tree_(source_tree), out_(out) {}

    void report(Level level, std::string const& message, Location location)
    {
        if (level == Level::ERROR) error_count_++;
        if (level == Level::WARNING) warning_count_++;

        size_t start = 0;

            out_ << "ance: ";

            switch (level)
            {
                case Level::ERROR:
                    out_ << ansi::ColorRed << "error" << ansi::ColorReset << ": ";
                    break;
                case Level::WARNING:
                    out_ << ansi::ColorYellow << "warning" << ansi::ColorReset << ": ";
                    break;
                case Level::INFO:
                    out_ << ansi::ColorBlue << "info" << ansi::ColorReset << ": ";
                    break;
            }

            if (location.isGlobal())
            {
                out_ << message << std::endl;
                return;
            }

            sources::SourceFile const& source_file = source_tree_.getFile(location.fileIndex());

            out_ << source_file.getRelativePath().generic_string() << " ";
            out_ << location << " " << message << std::endl;

            if (location.isFile()) return;

            out_ << std::endl;

            std::u32string_view const line_view = text::trim(source_file.getLine(location.line()), start);
            out_ << '\t' << boost::locale::conv::utf_to_utf<char>(std::u32string(line_view)) << std::endl;

            if (location.isSingleLine())
            {
                size_t const length_to_mark = location.column() - start - 1;
                size_t const length_of_mark = location.columnEnd() - location.column() + 1;

                std::u32string_view const text_to_mark   = line_view.substr(0, length_to_mark);
                std::u32string_view const text_with_mark = length_to_mark >= line_view.size() ? U"" : line_view.substr(length_to_mark, length_of_mark);

                size_t const missing_to_mark   = length_to_mark - text_to_mark.size();
                size_t const missing_with_mark = length_of_mark - text_with_mark.size();

                size_t const marker_start  = std::max(text::estimateWidth(text_to_mark) + missing_to_mark, 0uz);
                size_t const marker_length = std::max(text::estimateWidth(text_with_mark) + missing_with_mark, 1uz);

                out_ << '\t' << std::string(marker_start, ' ') << std::string(marker_length, '~') << std::endl;
                out_ << std::endl;
            }
    }

    void clear()
    {
        error_count_   = 0;
        warning_count_ = 0;
    }

    void report()
    {
        bool const warnings_as_errors = false;// todo: allow setting

        if (errorCount() > 0 || (warnings_as_errors && warningCount() > 0))
        {
            out_ << "ance: " << errorCount() << " errors, " << warningCount() << " warnings" << std::endl;
            out_ << "ance: Failed";

            if (errorCount() == 0) out_ << " (by warning)";
        }
        else
        {
            out_ << "ance: " << warningCount() << " warnings" << std::endl;
            out_ << "ance: Success";
        }

        clear();
    }

    [[nodiscard]] bool isFailed() const
    {
        bool const warnings_as_errors = false;// todo: allow setting

        return errorCount() > 0 || (warnings_as_errors && warningCount() > 0);
    }

    [[nodiscard]] size_t errorCount() const
    {
        return error_count_;
    }

    [[nodiscard]] size_t warningCount() const
    {
        return warning_count_;
    }

  private:
    size_t error_count_   = 0;
    size_t warning_count_ = 0;

    sources::SourceTree& source_tree_;
    std::ostream&        out_;
};

ance::core::Reporter::Reporter(sources::SourceTree& source_tree, std::ostream& out) : implementation_(utility::makeOwned<Implementation>(source_tree, out)) {}

ance::core::Reporter::~Reporter() = default;

void ance::core::Reporter::info(std::string const& message, Location const& location)
{
    implementation_->report(Implementation::Level::INFO, message, location);
}

void ance::core::Reporter::warning(std::string const& message, Location const& location)
{
    implementation_->report(Implementation::Level::WARNING, message, location);
}

void ance::core::Reporter::error(std::string const& message, Location const& location)
{
    implementation_->report(Implementation::Level::ERROR, message, location);
}

void ance::core::Reporter::clear()
{
    implementation_->clear();
}

void ance::core::Reporter::report()
{
    implementation_->report();
}

bool ance::core::Reporter::isFailed() const
{
    return implementation_->isFailed();
}

size_t ance::core::Reporter::errorCount() const
{
    return implementation_->errorCount();
}

size_t ance::core::Reporter::warningCount() const
{
    return implementation_->warningCount();
}

void ance::core::Reporter::print(std::ostream& out, std::string const& message)
{
    out << "ance: " << message << std::endl;
}

void ance::core::Reporter::print(std::ostream& out, std::string const& prefix, std::string const& message)
{
    out << "ance: " << prefix << ": " << message << std::endl;
}
