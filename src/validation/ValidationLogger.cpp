#include "ValidationLogger.h"

#include <iostream>

ValidationLogger::ValidationLogger() = default;

size_t ValidationLogger::warningCount() const
{
    return warning_count_;
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

size_t ValidationLogger::errorCount() const
{
    return error_count_;
}

void ValidationLogger::emitMessages(const SourceFile& source_file)
{
    std::cout << "ance-c: validation: " << warningCount() << " warnings, " << errorCount() << " errors" << std::endl;

    for (auto& entry : entries_)
    {
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
        std::cout << '\t' << trim(source_file.getLine(entry.location.line())) << std::endl;
    }
}

std::string_view ValidationLogger::trim(std::string_view str)
{
    const auto begin = str.find_first_not_of(" \t");
    const auto end   = str.find_last_not_of(" \t");

    const auto range = end - begin + 1;
    return str.substr(begin, range);
}
