#include "ValidationLogger.h"

#include <iostream>

ValidationLogger::ValidationLogger() = default;

size_t ValidationLogger::warningCount() const
{
    return warning_count_;
}

size_t ValidationLogger::errorCount() const
{
    return error_count_;
}

void ValidationLogger::emitMessages()
{
    std::cout << "ance-c: validation: " << warningCount() << " warnings, " << errorCount() << " errors" << std::endl;
}
