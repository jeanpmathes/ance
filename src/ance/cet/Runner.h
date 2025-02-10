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

        // todo: has a method Owned<cet::Node> run(Owned<bbt::Statement> const& statement);

    private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
