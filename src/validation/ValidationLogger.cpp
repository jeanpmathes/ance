#include "ValidationLogger.h"

#include <iostream>

#include "validation/SourceFile.h"
#include "validation/Strings.h"
#include "validation/ANSI.h"

ValidationLogger::ValidationLogger() = default;

size_t ValidationLogger::warningCount() const
{
    return warning_count_;
}

size_t ValidationLogger::errorCount() const
{
    return error_count_;
}

void ValidationLogger::logWarning(const std::string& message, lang::Location location)
{
    warning_count_++;
    log(LogLevel::WARNING, message, location);
}

void ValidationLogger::logError(const std::string& message, lang::Location location)
{
    error_count_++;
    log(LogLevel::ERROR, message, location);
}

void ValidationLogger::log(ValidationLogger::LogLevel level, const std::string& message, lang::Location location)
{
    entries_.emplace_back(level, message, location);
}

void ValidationLogger::emitMessages(const std::vector<std::reference_wrapper<SourceFile>>& source_files)
{
    std::cout << "ance-c: validation: " << warningCount() << " warnings, " << errorCount() << " errors" << std::endl;

    for (auto& entry : entries_)
    {
        size_t start = 0;

        std::cout << "ance-c: ";

        switch (entry.level_)
        {
            case LogLevel::ERROR:
                std::cout << ansi::ColorRed << "error" << ansi::ColorReset << ": ";
                break;
            case LogLevel::WARNING:
                std::cout << ansi::ColorYellow << "warning" << ansi::ColorReset << ": ";
                break;
        }

        if (entry.location_.isGlobal())
        {
            std::cout << entry.message_ << std::endl;
            std::cout << std::endl;
            continue;
        }

        SourceFile& source_file = source_files[entry.location_.file()].get();

        std::cout << source_file.getRelativePath().generic_string() << " ";
        std::cout << entry.location_ << " " << entry.message_ << std::endl;
        std::cout << std::endl;

        std::cout << '\t' << trim(source_file.getLine(entry.location_.line()), start) << std::endl;

        if (entry.location_.isSingleLine())
        {
            size_t marker_start  = entry.location_.column() - start;
            size_t marker_length = entry.location_.columnEnd() - entry.location_.column() + 1;

            std::cout << '\t' << std::string(marker_start - 1, ' ') << std::string(marker_length, '~') << std::endl;
            std::cout << std::endl;
        }
    }

    entries_.clear();
}

