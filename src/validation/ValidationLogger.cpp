#include "ValidationLogger.h"

#include <iostream>

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

void ValidationLogger::logWarning(const std::string& message, ance::Location location)
{
    warning_count_++;
    log(LogLevel::WARNING, message, location);
}

void ValidationLogger::logError(const std::string& message, ance::Location location)
{
    error_count_++;
    log(LogLevel::ERROR, message, location);
}

void ValidationLogger::log(ValidationLogger::LogLevel level, const std::string& message, ance::Location location)
{
    entries_.emplace_back(level, message, location);
}

void ValidationLogger::emitMessages(const SourceFile& source_file)
{
    std::cout << "ance-c: validation: " << warningCount() << " warnings, " << errorCount() << " errors" << std::endl;

    for (auto& entry : entries_)
    {
        unsigned int start = 0;

        std::cout << "ance-c: ";

        switch (entry.level)
        {
            case LogLevel::ERROR:
                std::cout << "error: ";
                break;
            case LogLevel::WARNING:
                std::cout << "warning: ";
                break;
            default:
                assert(false && "Add a case for every log level.");
        }

        std::cout << entry.location << " " << entry.message << std::endl;

        if (entry.location.isGlobal()) continue;

        std::cout << '\t' << trim(source_file.getLine(entry.location.line()), start) << std::endl;

        if (entry.location.isSingleLine())
        {
            unsigned int marker_start  = entry.location.column() - start;
            unsigned int marker_length = entry.location.columnEnd() - entry.location.column() + 1;

            std::cout << '\t' << std::string(marker_start - 1, ' ') << std::string(marker_length, '~') << std::endl;
        }
    }
}
