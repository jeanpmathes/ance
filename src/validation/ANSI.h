#ifndef ANCE_SRC_VALIDATION_ANSI_H_
#define ANCE_SRC_VALIDATION_ANSI_H_

#include <string>

namespace ansi
{
    inline const char* ColorRed    = "\x1B[31m";
    inline const char* ColorYellow = "\x1B[93m";
    inline const char* ColorGray   = "\x1B[90m";

    inline const char* ColorReset = "\x1B[0m";
}

#endif
