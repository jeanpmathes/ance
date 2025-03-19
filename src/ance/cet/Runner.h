#ifndef ANCE_CET_RUNNER_H
#define ANCE_CET_RUNNER_H

#include "ance/utility/Owners.h"
#include "ance/core/Reporter.h"

namespace ance::bbt
{
    struct BasicBlock;
}

namespace ance::cet
{
    struct Unit;

    /// Runs code in basic-block form (BBT) at compile-time, producing CETs.
    class Runner
    {
    public:
        explicit Runner(core::Reporter& reporter);
        ~Runner();


        /// Run the given tree in basic-block form.
        /// \param block The basic block to run.
        /// \return The resulting compile-able unit.
        utility::Owned<Unit> run(bbt::BasicBlock const& block); // todo: should maybe become bbt::Unit or bbt::Function to allow control flow

    private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
