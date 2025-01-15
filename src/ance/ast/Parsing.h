#ifndef ANCE_AST_PARSING_H
#define ANCE_AST_PARSING_H

#include <filesystem>

#include "ance/utility/Owners.h"

#include "Node.h"

namespace ance::ast
{
    /**
     * Parses files into ASTs.
     */
    class Parsing
    {
        // todo: the parser class should internally use the antlr4 visitor to create the ast
        // todo: that should handle fault tolerance - check what old does but do not fail on errors, instead handle by checking the antlr4 ctx objects and return error nodes
        // todo: cause compiler errors (create a reporter class, should take source file)

        /**
         * Reads and parses a passed file into an AST.
         * @param file_path The file to parse.
         * @return The parsed AST.
         */
        utility::Owned<Statement> parse(std::filesystem::path const& file_path);
    };
}

#endif
