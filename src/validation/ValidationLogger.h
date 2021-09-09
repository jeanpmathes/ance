#ifndef ANCE_SRC_VALIDATION_VALIDATIONLOGGER_H_
#define ANCE_SRC_VALIDATION_VALIDATIONLOGGER_H_

#include <string>
#include <vector>

#include "ance/utility/Location.h"
#include "validation/SourceFile.h"

class ValidationLogger
{
  public:
    ValidationLogger();

    ValidationLogger(ValidationLogger&& validation_logger)      = delete;
    ValidationLogger(const ValidationLogger& validation_logger) = delete;

  private:
    enum class LogLevel
    {
        WARNING,
        ERROR
    };

    struct LogEntry {
        LogLevel       level;
        std::string    message;
        ance::Location location;

        LogEntry(LogLevel level, std::string message, ance::Location location)
            : level(level)
            , message(std::move(message))
            , location(location)
        {}
    };

  public:
    /**
     * Log a warning.
     * @param message A message describing the warning.
     * @param location The source location of the code triggering this warning.
     */
    void logWarning(const std::string& message, ance::Location location);

    /**
     * Log an error.
     * @param message A message describing the error.
     * @param location The source location of the code triggering this error.
     */
    void logError(const std::string& message, ance::Location location);

  private:
    void log(LogLevel level, const std::string& message, ance::Location location);

  public:
    /**
     * Get the number of logged warnings.
     * @return The warning count.
     */
    [[nodiscard]] size_t warningCount() const;
    /**
     * Get the number of logged errors.
     * @return The error count.
     */
    [[nodiscard]] size_t errorCount() const;

    /**
     * Emit all logged messages.
     * @param source_file The source file containing the code that was validated with this logger.
     */
    void emitMessages(const SourceFile& source_file);

  private:
    static std::string_view trim(std::string_view str, unsigned int& start);

  private:
    std::vector<LogEntry> entries_;

    size_t warning_count_ {0};
    size_t error_count_ {0};
};

#endif
