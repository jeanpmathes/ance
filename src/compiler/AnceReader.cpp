#include "AnceReader.h"

#include <future>

#include "compiler/Project.h"
#include "lang/ApplicationVisitor.h"

AnceReader::AnceReader(Application& application) : application_(application) {}

size_t AnceReader::readSource()
{
    std::vector<std::future<SourceFileReadResult>> futures;

    for (auto& file_path : application_.getProject().getSourceFiles())
    {
        auto result = std::async(std::launch::async, readSourceFile, file_path);
        futures.push_back(std::move(result));
    }

    for (auto& future : futures)
    {
        auto result = future.get();
        source_files_.push_back(std::move(result));
    }

    return source_files_.size();
}

AnceReader::SourceFileReadResult AnceReader::readSourceFile(std::filesystem::path file_path)
{
    std::unique_ptr<SourceFile> source_file = std::make_unique<SourceFile>(file_path);

    std::unique_ptr<AnceSyntaxErrorHandler> syntax_error_listener = std::make_unique<AnceSyntaxErrorHandler>();

    std::fstream code;
    code.open(file_path);

    std::unique_ptr<antlr4::ANTLRInputStream> input = std::make_unique<antlr4::ANTLRInputStream>(code);
    std::unique_ptr<anceLexer>                lexer = std::make_unique<anceLexer>(input.get());
    lexer->removeErrorListeners();
    lexer->addErrorListener(syntax_error_listener->lexerErrorListener());

    std::unique_ptr<antlr4::CommonTokenStream> tokens = std::make_unique<antlr4::CommonTokenStream>(lexer.get());
    std::unique_ptr<anceParser>                parser = std::make_unique<anceParser>(tokens.get());
    parser->removeErrorListeners();
    parser->addErrorListener(syntax_error_listener->parserErrorListener());

    antlr4::tree::ParseTree* tree = parser->file();

    return SourceFileReadResult {std::move(syntax_error_listener),
                                 std::move(source_file),
                                 std::move(input),
                                 std::move(lexer),
                                 std::move(tokens),
                                 std::move(parser),
                                 tree};
}

size_t AnceReader::emitMessages()
{
    size_t fatal_error_count = 0;

    for (auto& source_file : source_files_)
    {
        source_file.syntax_error_handler->emitMessages(*source_file.source_file);
        fatal_error_count += source_file.syntax_error_handler->fatalSyntaxErrorCount();
    }

    return fatal_error_count;
}

void AnceReader::visit(SourceVisitor& visitor)
{
    for (auto& source_file : source_files_) { visitor.visit(source_file.tree); }
}

std::vector<std::reference_wrapper<SourceFile>> AnceReader::getSourceFiles()
{
    std::vector<std::reference_wrapper<SourceFile>> result;

    for (auto& source_file : source_files_) { result.emplace_back(*source_file.source_file); }

    return result;
}
