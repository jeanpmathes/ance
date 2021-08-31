#ifndef ANCE_SRC_VALIDATION_VALIDATIONLOGGER_H_
#define ANCE_SRC_VALIDATION_VALIDATIONLOGGER_H_

class ValidationLogger
{
  public:
    ValidationLogger();

    ValidationLogger(ValidationLogger&& validation_logger)      = delete;
    ValidationLogger(const ValidationLogger& validation_logger) = delete;

  public:
    [[nodiscard]] size_t warningCount() const;
    [[nodiscard]] size_t errorCount() const;

    void emitMessages();

  private:
    size_t warning_count_ {0};
    size_t error_count_ {0};
};

#endif
