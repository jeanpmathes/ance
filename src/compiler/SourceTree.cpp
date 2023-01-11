#include "SourceTree.h"

#include <future>

#include "compiler/Project.h"
#include "lang/ApplicationVisitor.h"

SourceTree::SourceTree(Unit& unit) : unit_(unit) {}

Unit& SourceTree::unit()
{
    return unit_;
}

size_t SourceTree::parse()
{
    std::filesystem::path              project_path = unit_.getProjectDirectory();
    std::vector<std::filesystem::path> source_files = unit_.getSourceFiles();

    std::vector<std::future<void>> futures;
    futures.reserve(source_files.size());

    std::vector<SourceFileReadResult> results;
    results.reserve(source_files.size());

    for (size_t index = 0; index < source_files.size(); index++)
    {
        auto result = std::ref(results.emplace_back());
        auto future =
            std::async(std::launch::async, readSourceFile, project_path, source_files[index], index, &unit_, result);
        futures.push_back(std::move(future));
    }

    for (auto& future : futures) { future.wait(); }

    for (auto& result : results) { source_files_.push_back(std::move(result)); }

    return source_files_.size();
}

void SourceTree::readSourceFile(std::filesystem::path const&                 project_path,
                                std::filesystem::path const&                 file_path,
                                size_t                                       index,
                                Unit*                                        unit,
                                std::reference_wrapper<SourceFileReadResult> result)
{
    Owned<SourceFile> source_file = makeOwned<SourceFile>(project_path, file_path);

    Owned<AnceSyntaxErrorHandler> syntax_error_listener = makeOwned<AnceSyntaxErrorHandler>(*source_file);

    std::fstream code;
    code.open(project_path / file_path);

    Owned<antlr4::ANTLRInputStream> input = makeOwned<antlr4::ANTLRInputStream>(code);
    Owned<anceLexer>                lexer = makeOwned<anceLexer>(input.get());
    lexer->removeErrorListeners();
    lexer->addErrorListener(syntax_error_listener->lexerErrorListener());

    Owned<antlr4::CommonTokenStream> tokens = makeOwned<antlr4::CommonTokenStream>(lexer.get());
    Owned<anceParser>                parser = makeOwned<anceParser>(tokens.get());
    parser->removeErrorListeners();
    parser->addErrorListener(syntax_error_listener->parserErrorListener());

    antlr4::tree::ParseTree* tree = unit->selectTree(*parser);

    Owned<FileContext> file_context = makeOwned<FileContext>(index, *source_file);

    result.get().file_context         = std::move(file_context);
    result.get().syntax_error_handler = std::move(syntax_error_listener);
    result.get().source_file          = std::move(source_file);
    result.get().input                = std::move(input);
    result.get().lexer                = std::move(lexer);
    result.get().tokens               = std::move(tokens);
    result.get().parser               = std::move(parser);
    result.get().tree                 = tree;
}

size_t SourceTree::emitMessages()
{
    size_t fatal_error_count = 0;

    for (auto& source_file : source_files_)
    {
        source_file.syntax_error_handler.value()->emitMessages();
        fatal_error_count += source_file.syntax_error_handler.value()->fatalSyntaxErrorCount();
    }

    return fatal_error_count;
}

void SourceTree::buildAbstractSyntaxTree()
{
    for (auto& source_file : source_files_)
    {
        unit_.addToAbstractSyntaxTree(source_file.tree, **source_file.file_context);
    }
}

std::vector<std::reference_wrapper<SourceFile>> SourceTree::getSourceFiles()
{
    std::vector<std::reference_wrapper<SourceFile>> result;

    for (auto& source_file : source_files_) { result.emplace_back(*source_file.source_file.value()); }

    return result;
}
