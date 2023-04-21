#ifndef ANCE_SRC_VALIDATION_VALIDATIONLOGGER_H_
#define ANCE_SRC_VALIDATION_VALIDATIONLOGGER_H_

#include <string>
#include <vector>

#include "lang/utility/Location.h"

class SourceFile;

/**
 * A logger-like handler for validation messages.
 */
class ValidationLogger
{
  public:
    ValidationLogger();

  private:
    enum class LogLevel
    {
        WARNING,
        ERROR
    };

    struct LogEntry {
        LogLevel       level_;
        std::string    message_;
        lang::Location location_;

        LogEntry(LogLevel level, std::string message, lang::Location location)
            : level_(level)
            , message_(std::move(message))
            , location_(location)
        {}
    };

  public:
    /**
     * Log a warning.
     * @param message A message describing the warning.
     * @param location The source location of the code triggering this warning.
     */
    void logWarning(std::string const& message, lang::Location location);

    /**
     * Log an error.
     * @param message A message describing the error.
     * @param location The source location of the code triggering this error.
     */
    void logError(std::string const& message, lang::Location location);

  private:
    void log(LogLevel level, std::string const& message, lang::Location location);

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
     * @param source_files The source file containing the code that was validated with this logger.
     * @param stream The stream to emit the messages to.
     * @param step_name The name of the validation step.
     */
    void emitMessages(std::vector<std::reference_wrapper<SourceFile>> const& source_files,
                      std::ostream&                                          stream,
                      std::string const&                                     step_name);

    /**
     * Clear all logged messages and counters.
     */
    void clear();

  private:
    std::vector<LogEntry> entries_;

    size_t warning_count_ {0};
    size_t error_count_ {0};
};

#endif
