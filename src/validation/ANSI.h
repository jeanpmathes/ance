#ifndef ANCE_SRC_VALIDATION_ANSI_H_
#define ANCE_SRC_VALIDATION_ANSI_H_

#include <string>

namespace ansi
{
    inline char const* ColorRed    = "\x1B[31m";
    inline char const* ColorYellow = "\x1B[33m";

    inline char const* ColorReset = "\x1B[0m";
}

#endif
