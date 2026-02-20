#ifndef ANCE_CET_RUNNER_H
#define ANCE_CET_RUNNER_H

#include <filesystem>

#include "ance/utility/Owners.h"

#include "ance/core/Context.h"
#include "ance/core/Reporter.h"

namespace ance::core
{
    class Identifier;
}

namespace ance::sources
{
    class SourceTree;
}

namespace ance::bbt
{
    class TypeContext;
    class Value;
}

namespace ance::cet
{
    struct Unit;

    class Variable;
}

namespace ance::cet
{
    /// Runs code in basic-block form (BBT) at compile-time, producing CETs.
    class Runner
    {
      public:
        Runner(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context);
        ~Runner();

        /// Add a variable to the runner, making it available for all subsequently run code.
        /// The variable is placed in the core language scope, the core scope.
        /// \param name The name of the variable to declare.
        /// \param value The value of the variable to declare.
        void declareCoreVariable(core::Identifier const& name, utility::Shared<bbt::Value> value);

        /// Run the given code, containing a declaration, and make the declared entities available for all subsequently run code.
        /// The code is run the core language scope, the core scope.
        /// \param code The code to run, containing a single declaration.
        /// \param id An identifier to use for the declaration.
        void declareCore(std::string const& code, std::string const& id);

        /// Run the given project file and return the resulting unit.
        /// \param file The path to the file to run.
        /// \return The resulting compile-able unit.
        utility::Optional<utility::Owned<Unit>> runProjectFile(std::filesystem::path const& file);

        /// Get the used type context of this runner.
        bbt::TypeContext& types();

      private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
