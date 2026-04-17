#ifndef ANCE_CET_COREDEFINITIONS_H
#define ANCE_CET_COREDEFINITIONS_H

namespace ance::cet
{
    class Runner;

    /// Define core functions and types of the language.
    /// These are generally compile-time functions - runtime(-only) functions are provided through the standard library.
    void defineLanguageCore(Runner& runner);
}

#endif
