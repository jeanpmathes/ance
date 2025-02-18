#ifndef ANCE_CET_RUNNER_H
#define ANCE_CET_RUNNER_H

#include "ance/utility/Owners.h"

namespace ance::cet
{
    /**
     * Runs code in basic-block form (BBT) at compile-time, producing CETs.
     */
    class Runner
    {
    public:
        Runner();
        ~Runner();

        // todo: do all the intermediate steps for the minimal grammar
        // todo: the CET is for now nearly identical to the BBT in nodes, but the runner should output an empty CET unit as highest node
        // todo: when arrived at the compiler, add empty visitor there
        // todo: in the runner, simply print the identifiers to console
        // todo: then add the function registration to resolver and an intrinsic class instead of std::function
        // todo: then add an extended grammar with all statements and expressions

        // todo: has a method Owned<cet::Node> run(Owned<bbt::Statement> const& statement);

    private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
