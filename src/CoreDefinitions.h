#ifndef ANCE_COREDEFINITIONS_H
#define ANCE_COREDEFINITIONS_H

namespace ance::cet
{
    class Runner;
}

namespace ance
{
    /**
     * Define core functions of the language in the given runner.
     */
    void defineCoreLanguage(cet::Runner& runner);// todo: would be cool if these could be defined using the language itself and intrinsic call grammar
}

#endif
