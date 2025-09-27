#ifndef ANCE_CET_RUNNER_H
#define ANCE_CET_RUNNER_H

#include <filesystem>

#include "ance/utility/Owners.h"
#include "ance/core/Reporter.h"
#include "ance/core/Context.h"

namespace ance::sources
{
    class SourceTree;
}

namespace ance::cet
{
    struct Unit;

    class Provider;

    /// Runs code in basic-block form (BBT) at compile-time, producing CETs.
    class Runner
    {
    public:
        Runner(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context);
        ~Runner();

        /// Add a provider to use during resolution.
        /// \param provider The provider to add.
        void add(utility::Owned<Provider> provider);

        /// Run the given ordered file and return the resulting unit.
        /// \param file The path to the file to run.
        /// \param out The output stream to report to.
        /// \return The resulting compile-able unit.
        utility::Optional<utility::Owned<Unit>> runOrderedFile(std::filesystem::path const& file, std::ostream& out);

        /// Run the given unordered file and return the resulting unit.
        /// \param file The path to the file to run.
        /// \param out The output stream to report to.
        /// \return The resulting compile-able unit.
        utility::Optional<utility::Owned<Unit>> runUnorderedFile(std::filesystem::path const& file, std::ostream& out);

    private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
