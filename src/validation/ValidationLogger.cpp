#include "ValidationLogger.h"

#include <iostream>

#include "validation/ANSI.h"
#include "validation/SourceFile.h"
#include "validation/Strings.h"

ValidationLogger::ValidationLogger() = default;

size_t ValidationLogger::warningCount() const
{
    return warning_count_;
}

size_t ValidationLogger::errorCount() const
{
    return error_count_;
}

void ValidationLogger::logWarning(std::string const& message, lang::Location location)
{
    warning_count_++;
    log(LogLevel::WARNING, message, location);
}

void ValidationLogger::logError(std::string const& message, lang::Location location)
{
    error_count_++;
    log(LogLevel::ERROR, message, location);
}

void ValidationLogger::log(ValidationLogger::LogLevel level, std::string const& message, lang::Location location)
{
    entries_.emplace_back(level, message, location);
}

void ValidationLogger::emitMessages(std::vector<std::reference_wrapper<SourceFile>> const& source_files,
                                    std::ostream&                                          stream,
                                    std::string const&                                     step_name)
{
    stream << "ance: validation: (" << step_name << ") " << warningCount() << " warnings, " << errorCount() << " errors" << std::endl;

    for (auto& entry : entries_)
    {
        size_t start = 0;

        stream << "ance: ";

        switch (entry.level_)
        {
            case LogLevel::ERROR:
                stream << ansi::ColorRed << "error" << ansi::ColorReset << ": ";
                break;
            case LogLevel::WARNING:
                stream << ansi::ColorYellow << "warning" << ansi::ColorReset << ": ";
                break;
        }

        if (entry.location_.isGlobal())
        {
            stream << entry.message_ << std::endl;
            stream << std::endl;
            continue;
        }

        SourceFile const& source_file = source_files[entry.location_.file()].get();

        stream << source_file.getRelativePath().generic_string() << " ";
        stream << entry.location_ << " " << entry.message_ << std::endl;
        stream << std::endl;

        std::string_view const line_view = trim(source_file.getLine(entry.location_.line()), start);
        stream << '\t' << line_view << std::endl;

        if (entry.location_.isSingleLine())
        {
            size_t const length_to_mark = entry.location_.column() - start;
            size_t const length_of_mark = entry.location_.columnEnd() - entry.location_.column() + 1;

            std::string_view const text_to_mark   = line_view.substr(0, length_to_mark);
            std::string_view const text_with_mark = line_view.substr(length_to_mark, length_of_mark);

            size_t const marker_start  = estimateWidth(text_to_mark);
            size_t const marker_length = estimateWidth(text_with_mark);

            stream << '\t' << std::string(marker_start - 1, ' ') << std::string(marker_length, '~') << std::endl;
            stream << std::endl;
        }
    }
}

void ValidationLogger::clear()
{
    entries_.clear();

    warning_count_ = 0;
    error_count_   = 0;
}
