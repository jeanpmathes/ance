#ifndef ANCE_CET_RUNNER_H
#define ANCE_CET_RUNNER_H

#include "ance/utility/Owners.h"
#include "ance/core/Reporter.h"

namespace ance::bbt
{
    struct Flow;
}

namespace ance::cet
{
    struct Unit;

    class Provider;

    /// Runs code in basic-block form (BBT) at compile-time, producing CETs.
    class Runner
    {
    public:
        explicit Runner(core::Reporter& reporter);
        ~Runner();

        /// Add a provider to use during resolution.
        /// \param provider The provider to add.
        void add(utility::Owned<Provider> provider);

        /// Run the given tree in basic-block form.
        /// \param flow The flow tree to run.
        /// \return The resulting compile-able unit.
        utility::Owned<Unit> run(bbt::Flow const& flow);

    private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
