#ifndef ANCE_BUILD_COMPILER_H
#define ANCE_BUILD_COMPILER_H

#include "ance/core/Reporter.h"
#include "ance/utility/Owners.h"

namespace ance::cet
{
    struct Unit;
}

namespace ance::build
{
    /**
     * Compiles CETs into binaries.
     */
    class Compiler
    {
      public:
        explicit Compiler(core::Reporter& reporter);
        ~Compiler();

        /**
         * Compile a CET unit.
         * @param unit The unit to compile.
         */
        void compile(cet::Unit const& unit);

      private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
