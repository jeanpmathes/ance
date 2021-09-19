#include "AnceSyntaxErrorListener.h"

#include "validation/Strings.h"

size_t AnceSyntaxErrorListener::fatalSyntaxErrorCount() const
{
    return fatal_syntax_error_count_;
}

void AnceSyntaxErrorListener::syntaxError(antlr4::Recognizer* recognizer,
                                          antlr4::Token*      offending_symbol,
                                          size_t              line,
                                          size_t              char_position_in_line,
                                          const std::string&  msg,
                                          std::exception_ptr  e)
{
    log("Cannot understand code", line, char_position_in_line);
}

void AnceSyntaxErrorListener::log(const std::string& message, size_t line, size_t char_position)
{
    syntax_errors_.emplace_back(message, std::make_pair(line, char_position));
}

void AnceSyntaxErrorListener::emitMessages(const SourceFile& source_file)
{
    for (auto& [message, location] : syntax_errors_)
    {
        auto& [line, char_position] = location;
        size_t column               = char_position + 1;

        unsigned int start;

        std::cout << "ance-c: syntax: (" << line << ", " << column << ") " << message << std::endl;
        std::cout << '\t' << trim(source_file.getLine(line), start) << std::endl;

        unsigned int marker_position = column - start - 1;

        std::cout << '\t' << std::string(marker_position, ' ') << '^' << std::endl;
    }
}
