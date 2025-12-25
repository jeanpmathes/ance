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
    void defineCoreLanguageFunctions(cet::Runner& runner);// todo: would be cool if these could be defined using the language itself and intrinsic call grammar

    // todo: the same way it would be cool to have functions defined in code, a similar thing for types would be nice too, albeit more difficult
}

#endif
