#ifndef ANCE_AST_PARSING_H
#define ANCE_AST_PARSING_H

#include <filesystem>

#include "ance/core/Reporter.h"
#include "ance/sources/SourceTree.h"
#include "ance/utility/Owners.h"

namespace ance::ast
{
    struct Statement;

    /**
     * Parses files into ASTs.
     */
    class Parsing
    {
      public:
        Parsing(sources::SourceTree& source_tree, core::Reporter& reporter);
        ~Parsing();

        /**
         * Reads and parses a passed file into an AST.
         * @param index The index of the file in the source tree.
         * @return The parsed AST.
         */
        utility::Owned<Statement> parse(size_t index);

      private:
        sources::SourceTree& source_tree_;
        core::Reporter&      reporter_;

        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
