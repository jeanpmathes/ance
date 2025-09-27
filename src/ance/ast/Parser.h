#ifndef ANCE_AST_PARSER_H
#define ANCE_AST_PARSER_H

#include <filesystem>

#include "ance/core/Context.h"
#include "ance/core/Reporter.h"
#include "ance/utility/Owners.h"

namespace ance::ast
{
    struct File;
    struct Statement;

    /// Parses files into ASTs.
    class Parser
    {
      public:
        Parser(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context);
        ~Parser();

        /// Reads and parses a passed unordered scope file into an AST.
        /// \param file The path to the file, relative to the source tree base directory.
        /// \param out The output stream to report to.
        /// \return The parsed AST.
        utility::Optional<utility::Owned<File>> parseUnorderedFile(std::filesystem::path const& file, std::ostream& out);

        /// Reads and parses a passed ordered scope file into an AST.
        /// \param file The path to the file, relative to the source tree base directory.
        /// \param out The output stream to report to.
        /// \return The parsed AST.
        utility::Optional<utility::Owned<Statement>> parseOrderedFile(std::filesystem::path const& file, std::ostream& out);

      private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
