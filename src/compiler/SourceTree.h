#ifndef ANCE_SRC_COMPILER_SOURCETREE_H_
#define ANCE_SRC_COMPILER_SOURCETREE_H_

#include "grammar/anceLexer.h"
#include "grammar/anceParser.h"
#include <antlr4-runtime.h>

#include "compiler/Application.h"
#include "compiler/SourceVisitor.h"
#include "validation/AnceSyntaxErrorHandler.h"
#include "validation/SourceFile.h"

/**
 * Read and parses all source files.
 */
class SourceTree
{
  public:
    explicit SourceTree(Application& application);

    /**
     * Read in and parse all source files.
     * @return The number of source files.
     */
    size_t parse();

    /**
     * Emit error and other messages.
     * @return The number of fatal errors.
     */
    size_t emitMessages();

    /**
     * Visit all source files with the given visitor.
     * @param visitor The visitor.
     */
    void accept(SourceVisitor& visitor);

    /**
     * Get all source files.
     * @return The source files.
     */
    std::vector<std::reference_wrapper<SourceFile>> getSourceFiles();

  private:
    struct SourceFileReadResult {
        std::unique_ptr<FileContext>               file_context;
        std::unique_ptr<AnceSyntaxErrorHandler>    syntax_error_handler;
        std::unique_ptr<SourceFile>                source_file;
        std::unique_ptr<antlr4::ANTLRInputStream>  input;
        std::unique_ptr<anceLexer>                 lexer;
        std::unique_ptr<antlr4::CommonTokenStream> tokens;
        std::unique_ptr<anceParser>                parser;
        antlr4::tree::ParseTree*                   tree {};
    };

    static SourceFileReadResult readSourceFile(std::filesystem::path const& project_path,
                                               std::filesystem::path const& file_path,
                                               size_t                       file_index);

  private:
    Application&                      application_;
    std::vector<SourceFileReadResult> source_files_;
};

#endif
