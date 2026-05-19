#ifndef ANCE_AST_PARSER_H
#define ANCE_AST_PARSER_H

#include <filesystem>

#include "ance/core/Reporter.h"
#include "ance/utility/Owners.h"

namespace ance::core
{
    class Context;
}

namespace ance::ast
{
    struct File;
    struct Declaration;
    struct Statement;
}

/// The abstract syntax tree (AST) namespace.
namespace ance::ast
{
    /// \brief Parses files into ASTs.
    ///
    /// This class consumes a source file or code and produces an abstract syntax tree (AST).
    class Parser
    {
      public:
        Parser(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context);
        ~Parser();

        /// Reads and parses a passed unordered scope file into an AST.
        /// \param file The path to the file, relative to the source tree base directory.
        /// \return The parsed AST.
        utility::Optional<utility::Owned<File>> parseUnorderedFile(std::filesystem::path const& file);

        /// Reads and parses a passed ordered scope file into an AST.
        /// \param file The path to the file, relative to the source tree base directory.
        /// \return The parsed AST.
        utility::Optional<utility::Owned<Statement>> parseOrderedFile(std::filesystem::path const& file);

        /// Parses a piece of core code containing a single declaration into an AST.
        /// \param code The code to parse.
        /// \param id An identifier of the declaration.
        /// \return The parsed AST.
        utility::Optional<utility::Owned<Declaration>> parseDeclaration(std::string const& code, std::string const& id);

      private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
