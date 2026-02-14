#include "Reporter.h"

#include <utility>
#include <vector>

#include <boost/locale/boundary/index.hpp>
#include <boost/locale/encoding_utf.hpp>
#include <boost/regex/v5/unicode_iterator.hpp>

#include <icu.h>

#include "ance/sources/SourceTree.h"

namespace ansi
{
    inline auto ColorSuccess = "\x1B[32m";
    inline auto ColorError    = "\x1B[31m";
    inline auto ColorWarning = "\x1B[33m";
    inline auto ColorInfo   = "\x1B[34m";
    inline auto ColorTrace   = "\x1B[36m";
    inline auto ColorMeta    = "\x1B[90m";

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
        TRACE,
        INFO,
        WARNING,
        ERROR
    };

    Implementation(Reporter* reporter, sources::SourceTree& source_tree, std::ostream& out, bool trace_enable) : reporter_(reporter), source_tree_(source_tree), out_(out), trace_enabled_(trace_enable) {}

    static char const* colorForLevel(Level level)
    {
        switch (level)
        {
            case Level::ERROR: return ansi::ColorError;
            case Level::WARNING: return ansi::ColorWarning;
            case Level::INFO: return ansi::ColorInfo;
            case Level::TRACE: return ansi::ColorTrace;
        }

        return ansi::ColorReset;
    }

    void report(Level const level, std::string const& message, std::string const& compiler_location, Location const& location)
    {
        if (level == Level::TRACE && !isTraceEnabled()) return;

        if (level == Level::ERROR) error_count_++;
        if (level == Level::WARNING) warning_count_++;

        size_t start = 0;

            out_ << "ance: ";

            switch (level)
            {
                case Level::ERROR:
                    out_ << ansi::ColorError << "error" << ansi::ColorReset << ": ";
                    break;
                case Level::WARNING:
                    out_ << ansi::ColorWarning << "warning" << ansi::ColorReset << ": ";
                    break;
                case Level::INFO:
                    out_ << ansi::ColorInfo << "info" << ansi::ColorReset << ": ";
                    break;
                case Level::TRACE:
                    out_ << ansi::ColorTrace << "trace" << ansi::ColorReset << ": ";
                    break;
            }

            if (!compiler_location.empty())
            {
                out_ << "[" << compiler_location << "] ";
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

                out_ << '\t' << std::string(marker_start, ' ') << colorForLevel(level) << std::string(marker_length, '~') << ansi::ColorReset << std::endl;
            }
            else
            {
                size_t const extra_lines = location.lineEnd() - location.line();
                out_ << '\t' << ansi::ColorMeta << "(+ " << extra_lines << " more line" << (extra_lines > 1 ? "s" : "") << ")" << ansi::ColorReset << std::endl;
            }

            out_ << std::endl;
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
            out_ << "ance: ";

            if (errorCount() > 0)
            {
                out_ << ansi::ColorError << errorCount() << " error" << (errorCount() > 1 ? "s" : "") << ansi::ColorReset;
            }
            else
            {
                out_ << "0 errors";
            }

            out_ << ", ";

            if (warningCount() > 0)
            {
                out_ << ansi::ColorWarning << warningCount() << " warning" << (warningCount() > 1 ? "s" : "") << ansi::ColorReset;
            }
            else
            {
                out_ << "0 warnings";
            }

            out_ << std::endl;

            out_ << "ance: " << ansi::ColorError << "Failed" << ansi::ColorReset;

            if (errorCount() == 0) out_ << " (by warning)";

            out_ << std::endl;
        }
        else
        {
            if (warningCount() > 0)
            {
                out_ << "ance: " << ansi::ColorWarning << warningCount() << " warning" << (warningCount() > 1 ? "s" : "") << ansi::ColorReset << std::endl;
            }

            out_ << "ance: " << ansi::ColorSuccess << "Success" << ansi::ColorReset << std::endl;
        }

        clear();
    }

    MessageBuilder beginReport(Level const level, std::string const& compiler_location, Location const& location)
    {
        return {*reporter_, compiler_location, location, level != Level::TRACE || isTraceEnabled() };
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

    [[nodiscard]] bool isTraceEnabled() const
    {
        return trace_enabled_;
    }

  private:
    size_t error_count_   = 0;
    size_t warning_count_ = 0;

    Reporter*       reporter_;
    sources::SourceTree& source_tree_;
    std::ostream&        out_;
    bool trace_enabled_;
};

ance::core::Reporter::MessageBuilder::MessageBuilder(Reporter& reporter, std::string compiler_location, Location const& location, bool const enabled) : reporter_(&reporter)
    , compiler_location_(std::move(compiler_location))
    , location_(location)
{
    if (enabled)
    {
        stream_ = utility::makeOptional(std::ostringstream());
    }
}

ance::core::Reporter::MessageBuilder::MessageBuilder(MessageBuilder&& other) noexcept : reporter_(other.reporter_)
    , compiler_location_(std::move(other.compiler_location_))
    , location_(other.location_)
    , stream_(std::move(other.stream_))
{
    other.reporter_ = nullptr;
}

ance::core::Reporter::MessageBuilder& ance::core::Reporter::MessageBuilder::operator=(MessageBuilder&& other) noexcept
{
    if (this == &other) return *this;

    reporter_ = other.reporter_;
    compiler_location_ = std::move(other.compiler_location_);
    location_ = other.location_;
    stream_   = std::move(other.stream_);

    other.reporter_ = nullptr;

    return *this;
}

ance::core::Reporter::MessageBuilder::~MessageBuilder()
{
    if (reporter_ != nullptr && stream_.hasValue())
    {
        reporter_->implementation_->report(Implementation::Level::TRACE, stream_.value().str(), compiler_location_, location_);
    }
}

ance::core::Reporter::Reporter(sources::SourceTree& source_tree, std::ostream& out, bool trace_enabled) : implementation_(utility::makeOwned<Implementation>(this, source_tree, out, trace_enabled)) {}

ance::core::Reporter::~Reporter() = default;

void ance::core::Reporter::trace(std::string const& message, std::string const& compiler_location, Location const& location)
{
    implementation_->report(Implementation::Level::TRACE, message, compiler_location, location);
}

void ance::core::Reporter::trace(std::function<std::string()> const& message_builder, std::string const& compiler_location, Location const& location)
{
    if (implementation_->isTraceEnabled())
    {
        implementation_->report(Implementation::Level::TRACE, message_builder(), compiler_location, location);
    }
}

ance::core::Reporter::MessageBuilder ance::core::Reporter::trace(std::string const& compiler_location, Location const& location)
{
    return implementation_->beginReport(Implementation::Level::TRACE, compiler_location, location);
}

void ance::core::Reporter::info(std::string const& message, Location const& location)
{
    implementation_->report(Implementation::Level::INFO, message, "", location);
}

ance::core::Reporter::MessageBuilder ance::core::Reporter::info(Location const& location)
{
    return implementation_->beginReport(Implementation::Level::INFO, "", location);
}

void ance::core::Reporter::warning(std::string const& message, Location const& location)
{
    implementation_->report(Implementation::Level::WARNING, message, "", location);
}

ance::core::Reporter::MessageBuilder ance::core::Reporter::warning(Location const& location)
{
    return implementation_->beginReport(Implementation::Level::WARNING, "", location);
}

void ance::core::Reporter::error(std::string const& message, Location const& location)
{
    implementation_->report(Implementation::Level::ERROR, message, "", location);
}

ance::core::Reporter::MessageBuilder ance::core::Reporter::error(Location const& location)
{
    return implementation_->beginReport(Implementation::Level::ERROR, "", location);
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

bool ance::core::Reporter::isTraceEnabled() const
{
    return implementation_->isTraceEnabled();
}

void ance::core::Reporter::print(std::ostream& out, std::string const& message)
{
    out << "ance: " << message << std::endl;
}

void ance::core::Reporter::print(std::ostream& out, std::string const& prefix, std::string const& message)
{
    out << "ance: " << prefix << ": " << message << std::endl;
}
