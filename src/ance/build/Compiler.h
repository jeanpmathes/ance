#ifndef ANCE_BUILD_COMPILER_H
#define ANCE_BUILD_COMPILER_H

#include "ance/core/Context.h"
#include "ance/core/Reporter.h"
#include "ance/utility/Owners.h"

namespace ance::cet
{
    struct Unit;
}

namespace ance::build
{
    /// Compiles projects into binaries.
    class Compiler
    {
      public:
        Compiler(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context);
        ~Compiler();

        /// Compile a project.
        /// \param file The path to the project file to compile.
        /// \return Whether the compilation was successful.
        bool compile(std::filesystem::path const& file);

      private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
