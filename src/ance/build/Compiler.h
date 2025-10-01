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
    /// Compiles CETs into binaries.
    class Compiler
    {
      public:
        Compiler(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context);
        ~Compiler();

        /// Compile a CET unit.
        /// \param unit The unit to compile.
        bool compile(cet::Unit const& unit);

      private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
